﻿#include "AnimationData_Integer.h"
#include "Core/Texture/EzTexture.h"
#include "Game/Tools/Tools.h"
#include "Core/WriteReadTools.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Audio;
using namespace Microsoft::Xna::Framework::Content;
using namespace Microsoft::Xna::Framework::Graphics;
using namespace Microsoft::Xna::Framework::Input;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{

	AnimationData_Texture::AnimationData_Texture()
	{
		InitializeInstanceFields();
		Anims.clear();
	}

	AnimationData_Texture::AnimationData_Texture( const std::wstring &TextureName )
	{
		InitializeInstanceFields();
		Anims = std::vector<OneAnim_Texture>( 1 );

		AddFrame( Tools::Texture( TextureName ), 0 );

		std::shared_ptr<CloudberryKingdom::EzTexture> FirstFrameTexture = Anims[ 0 ].Data[ 0 ];
		Width = FirstFrameTexture->Width;
		Height = FirstFrameTexture->Height;
	}

	AnimationData_Texture::AnimationData_Texture( const std::wstring &TextureRoot, int StartFrame, int EndFrame )
	{
		InitializeInstanceFields();
		Anims = std::vector<OneAnim_Texture>( 1 );

		// Determine format of texture names.
		std::wstring format = _T( "" );
		int length = 1;
		if ( Tools::Texture( TextureRoot + StringConverterHelper::toString( StartFrame ) ) != Tools::TextureWad->DefaultTexture )
			format = _T( "" );
		else if ( Tools::Texture( TextureRoot + _T( "_" ) + StringConverterHelper::toString( StartFrame ) ) != Tools::TextureWad->DefaultTexture )
			format = _T( "_" );
		else if ( Tools::Texture( TextureRoot + _T( "_0" ) + StringConverterHelper::toString( StartFrame ) ) != Tools::TextureWad->DefaultTexture )
		{
			format = _T( "_" );
			length = 2;
		}
		else if ( Tools::Texture( TextureRoot + _T( "_00" ) + StringConverterHelper::toString( StartFrame ) ) != Tools::TextureWad->DefaultTexture )
		{
			format = _T( "_" );
			length = 3;
		}
		else if ( Tools::Texture( TextureRoot + _T( "_000" ) + StringConverterHelper::toString( StartFrame ) ) != Tools::TextureWad->DefaultTexture )
		{
			format = _T( "_" );
			length = 4;
		}
		else if ( Tools::Texture( TextureRoot + _T( "_0000" ) + StringConverterHelper::toString( StartFrame ) ) != Tools::TextureWad->DefaultTexture )
		{
			format = _T( "_" );
			length = 5;
		}

		const std::wstring tempVector[] = { _T( "" ), _T( "0" ), _T( "00" ), _T( "000" ), _T( "0000" ) };
		std::vector<std::wstring> pad = std::vector<std::wstring>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );

		if ( EndFrame >= StartFrame )
		{
			for ( int i = StartFrame; i <= EndFrame; i++ )
			{
				int len = i == 0 ? 1 : static_cast<int>( log10( i ) ) + 1;
				std::wstring padding = len <= length ? pad[ length - len ] : _T( "" );
				AddFrame( Tools::Texture( TextureRoot + format + padding + StringConverterHelper::toString( i ) ), 0 );
			}
		}
		else
		{
			for ( int i = EndFrame; i <= StartFrame; i-- )
				AddFrame( Tools::Texture( TextureRoot + format + StringConverterHelper::toString( i ) ), 0 );
		}

		std::shared_ptr<CloudberryKingdom::EzTexture> FirstFrameTexture = Anims[ 0 ].Data[ 0 ];
		Width = FirstFrameTexture->Width;
		Height = FirstFrameTexture->Height;
	}

	AnimationData_Texture::AnimationData_Texture( const std::shared_ptr<EzTexture> &texture )
	{
		InitializeInstanceFields();
		if ( texture == 0 )
		{
			Anims.clear();
		}
		else
		{
			Anims = std::vector<OneAnim_Texture>( 1 );
			AddFrame( texture, 0 );
		}
	}

	void AnimationData_Texture::Release()
	{
		if ( Anims.size() > 0 )
			for ( int i = 0; i < Anims.size(); i++ )
				Anims[ i ].Data.clear();
		Anims.clear();
	}

	void AnimationData_Texture::Write( const std::shared_ptr<BinaryWriter> &writer )
	{
		if ( Anims.empty() )
			writer->Write( -1 );
		else
		{
			writer->Write( Anims.size() );
			for ( int i = 0; i < Anims.size(); i++ )
				WriteReadTools::WriteOneAnim( writer, Anims[ i ] );
		}
	}

	void AnimationData_Texture::Read( const std::shared_ptr<BinaryReader> &reader )
	{
		int length = reader->ReadInt32();
		if ( length == -1 )
			Anims.clear();
		else
		{
			Anims = std::vector<OneAnim_Texture>( length );
			for ( int i = 0; i < length; i++ )
				WriteReadTools::ReadOneAnim( reader, Anims[ i ] );
		}
	}

	AnimationData_Texture::AnimationData_Texture( const std::shared_ptr<AnimationData_Texture> &data )
	{
		InitializeInstanceFields();
		Anims = std::vector<OneAnim_Texture>( data->Anims.size() );
		for ( int i = 0; i < data->Anims.size(); i++ )
			CopyAnim( data, i );
	}

	void AnimationData_Texture::CopyAnim( const std::shared_ptr<AnimationData_Texture> &data, int Anim )
	{
		if ( data->Anims[ Anim ].Data.size() > 0 )
		{
			Anims[ Anim ].Speed = data->Anims[ Anim ].Speed;
			Anims[ Anim ].Data = std::vector<EzTexture*>( data->Anims[ Anim ].Data.size() );
			data->Anims[ Anim ].Data.CopyTo( Anims[ Anim ].Data, 0 );
		}
		else
			Anims[ Anim ].Data.clear();
	}

	void AnimationData_Texture::Init()
	{
		const OneAnim_Texture tempVector2[] = { OneAnim_Texture() };
		Anims = std::vector<OneAnim_Texture>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) );
	}

	void AnimationData_Texture::InsertFrame( int anim, int frame )
	{
		if ( anim >= Anims.size() )
			return;
		if ( Anims[ anim ].Data.empty() )
			return;
		if ( frame >= Anims[ anim ].Data.size() )
			return;

		OneAnim_Texture NewAnim = OneAnim_Texture();
		NewAnim.Data = std::vector<EzTexture*>( Anims[ anim ].Data.size() + 1 );
		for ( int i = 0; i < frame; i++ )
			NewAnim.Data[ i ] = Anims[ anim ].Data[ i ];
		NewAnim.Data[ frame ] = Anims[ anim ].Data[ frame ];
		for ( int i = frame + 1; i < Anims[ anim ].Data.size() + 1; i++ )
			NewAnim.Data[ i ] = Anims[ anim ].Data[ i - 1 ];
		Anims[ anim ] = NewAnim;
	}

	void AnimationData_Texture::ClearAnim( int anim )
	{
		if ( anim >= Anims.size() )
			return;
		if ( Anims[ anim ].Data.empty() )
			return;

		OneAnim_Texture NewAnim = OneAnim_Texture();
		NewAnim.Data = std::vector<EzTexture*>( 0 );
		Anims[ anim ] = NewAnim;
	}

	void AnimationData_Texture::DeleteFrame( int anim, int frame )
	{
		if ( anim >= Anims.size() )
			return;
		if ( Anims[ anim ].Data.empty() )
			return;
		if ( frame >= Anims[ anim ].Data.size() )
			return;

		if ( Anims[ anim ].Data.size() > 1 )
		{
			OneAnim_Texture NewAnim = OneAnim_Texture();
			NewAnim.Data = std::vector<EzTexture*>( Anims[ anim ].Data.size() - 1 );
			for ( int i = 0; i < frame; i++ )
				NewAnim.Data[ i ] = Anims[ anim ].Data[ i ];
			for ( int i = frame + 1; i < Anims[ anim ].Data.size(); i++ )
				NewAnim.Data[ i - 1 ] = Anims[ anim ].Data[ i ];
			Anims[ anim ] = NewAnim;
		}
	}

	void AnimationData_Texture::AddFrame( const std::shared_ptr<EzTexture> &val, int anim )
	{
		int frame = 0;
		if ( anim >= Anims.size() )
			frame = 0;
		else if ( Anims[ anim ].Data.empty() )
			frame = 0;
		else
			frame = Anims[ anim ].Data.size();

		Set( val, anim, frame );
	}

	void AnimationData_Texture::Set( const std::shared_ptr<EzTexture> &val, int anim, int frame )
	{
		std::shared_ptr<EzTexture> Default = 0;
		if ( Anims[ 0 ].Data.size() > 0 )
		{
			Default = Anims[ 0 ].Data[ 0 ];
		}

		if ( anim >= Anims.size() )
		{
			std::vector<OneAnim_Texture> NewAnims = std::vector<OneAnim_Texture>( anim + 1 );
			Anims.CopyTo( NewAnims, 0 );
			Anims = NewAnims;
		}

		if ( Anims[ anim ].Data.empty() )
		{
			const EzTexture* tempVector3[] = { 0 };
			Anims[ anim ].Data = std::vector<EzTexture*>( tempVector3, tempVector3 + sizeof( tempVector3 ) / sizeof( tempVector3[ 0 ] ) );
		}
		else
			if ( frame > 0 )
				Default = Get( anim, frame - 1 );

		if ( frame >= Anims[ anim ].Data.size() && !(val == Default && Anims[ anim ].Data.size() <= 1) )
		{
			std::vector<EzTexture*> NewData = std::vector<EzTexture*>( frame + 1 );
			for ( int i = 0; i < frame + 1; i++ )
				NewData[ i ] = Default;

			Anims[ anim ].Data.CopyTo( NewData, 0 );
			Anims[ anim ].Data = NewData;
		}

		if ( frame < Anims[ anim ].Data.size() )
		{
			Anims[ anim ].Data[ frame ] = val;
		}
	}

	std::shared_ptr<EzTexture> AnimationData_Texture::Get( int anim, int frame )
	{
		if ( Anims[ 0 ].Data.empty() )
			return 0;

		std::shared_ptr<EzTexture> Default = Anims[ 0 ].Data[ 0 ];

		if ( anim >= Anims.size() )
			return Default;

		if ( Anims[ anim ].Data.empty() )
			return Default;
		else
		{
			int Length = Anims[ anim ].Data.size();
			if ( Length > 0 )
				Default = Anims[ anim ].Data[ 0 ];
			else
				return Default;
		}
		if ( frame >= Anims[ anim ].Data.size() || frame < 0 )
			return Default;

		return Anims[ anim ].Data[ frame ];
	}

	std::shared_ptr<EzTexture> AnimationData_Texture::NextKeyFrame()
	{
		LastSetFrame++;
		if ( LastSetFrame >= Anims[ LastSetAnim ].Data.size() )
			LastSetFrame = 0;

		return Anims[ LastSetAnim ].Data[ LastSetFrame ];
	}

	std::shared_ptr<EzTexture> AnimationData_Texture::Calc( int anim, float t, int Length, bool Loop )
	{
		int i = static_cast<int>( floor( t ) );
		LastSetFrame = i;
		LastSetAnim = anim;
		return Get( anim, i );
	}

	std::shared_ptr<EzTexture> AnimationData_Texture::Calc( int anim, float t )
	{
		return Calc( anim, t, Anims[ anim ].Data.size(), true );
	}

	void AnimationData_Texture::InitializeInstanceFields()
	{
		LastSetFrame = 0;
		LastSetAnim = 0;
	}
}
