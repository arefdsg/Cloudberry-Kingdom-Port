#include <Content/FilesystemWiiU.h>

#include <Content/File.h>
#include <Utility/Log.h>

#include <cafe.h>
#include <cafe/fs.h>
#include <sstream>

/**
 * File implementation for Pc.
 */
class FileWiiU : public File
{

	const char *buffer_;
	size_t length_;
	size_t get_;

private:

	/// No copying.
	FileWiiU( const FileWiiU & ) { }

	/// No assignment.
	FileWiiU &operator = ( const FileWiiU & ) {	return *this; }

public:

	FileWiiU( const char *buffer, size_t length ) :
		buffer_( buffer ),
		length_( length ),
		get_( 0 )
	{
	}

	~FileWiiU()
	{
		MEMFreeToDefaultHeap( const_cast< char * >( buffer_ ) );
	}

	/**
	 * @see File::Read()
	 */
	size_t Read( char *buffer, size_t length )
	{
		// Current position plus requested length goes beyond the buffer.
		if( get_ + length >= length_ )
		{
			memcpy( buffer, buffer_ + get_, length_ - get_ );
			get_ = length_;
			return length_ - get_;
		}

		memcpy( buffer, buffer_ + get_, length );
		get_ += length;
		return length;
	}

	/**
	 * @see File::Write()
	 */
	size_t Write( const char *buffer, size_t length )
	{
		assert( !"File writing not yet implemented." );
	}

	/**
	 * @see File::ReadLine()
	 */
	std::string ReadLine()
	{
		const char *start = buffer_ + get_;
		while( get_ < length_ && buffer_[ get_ ] != '\n' )
			++get_;

		++get_;
		return std::string( start, buffer_ + get_ - 1 );
	}
	
	/**
	 * @see File::Peek()
	 */
	int Peek()
	{
		return buffer_[ get_ ];
	}

	/**
	 * @see File::IsOpen()
	 */
	bool IsOpen()
	{
		return true;
	}

	/**
	 * @see File::EOF()
	 */
	bool IsEOF()
	{
		return get_ >= length_;
	}

};

struct FilesystemWiiUInternal
{
	FSClient *Client;
	FSCmdBlock *Cmd;
};

FilesystemWiiU::FilesystemWiiU() :
	internal_( new FilesystemWiiUInternal )
{
	FSInit();
	LOG.Write( "Filesystem initialized\n" );

	internal_->Client = reinterpret_cast< FSClient * >( MEMAllocFromDefaultHeap( sizeof( FSClient ) ) );
	if( !internal_->Client )
		OSHalt( "Error: cannot allocate filesystem client.\n" );
	internal_->Cmd = reinterpret_cast< FSCmdBlock * >( MEMAllocFromDefaultHeap( sizeof( FSCmdBlock ) ) );
	if( !internal_->Cmd )
		OSHalt( "Error: cannot allocate command queue.\n" );

	FSAddClient( internal_->Client, FS_RET_NO_ERROR );
	LOG.Write( "Client added\n" );

	FSInitCmdBlock( internal_->Cmd );
	LOG.Write( "Command block ready\n" );
}

FilesystemWiiU::~FilesystemWiiU()
{
	MEMFreeToDefaultHeap( internal_->Client );
	MEMFreeToDefaultHeap( internal_->Cmd );

	FSShutdown();
	delete internal_;
}

boost::shared_ptr<File> FilesystemWiiU::Open( const std::string &path, bool write )
{
	FSFileHandle fh;
	FSStat stat;

	std::string localPath = ( path[ 0 ] == '/' ? "/vol/content" : "/vol/content/" ) + path;
	LOG.Write( "Opening %s\n", localPath.c_str() );

	FSOpenFile( internal_->Client, internal_->Cmd, localPath.c_str(), "r", &fh, FS_RET_NO_ERROR );

	memset( &stat, 0, sizeof( FSStat ) );
	FSGetStatFile( internal_->Client, internal_->Cmd, fh, &stat, FS_RET_NO_ERROR );

	char *buffer = reinterpret_cast< char * >( MEMAllocFromDefaultHeapEx( stat.size, FS_IO_BUFFER_ALIGN ) );
	FSReadFile( internal_->Client, internal_->Cmd, buffer, stat.size, 1, fh, 0, FS_RET_NO_ERROR );
	FSCloseFile( internal_->Client, internal_->Cmd, fh, FS_RET_NO_ERROR );

	return boost::static_pointer_cast<File>( boost::make_shared<FileWiiU>( buffer, stat.size ) );
}
