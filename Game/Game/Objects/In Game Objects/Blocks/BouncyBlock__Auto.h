#ifndef BOUNCYBLOCK__AUTO
#define BOUNCYBLOCK__AUTO

#include <small_header.h>

//#include "Game/Objects/ObjectBase.h"
//#include "Game/Level/Make/DifficultyHelper.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Level/Make/Parameters/Param.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Blocks/BouncyBlock.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tools/Recycler.h"


namespace CloudberryKingdom
{

	struct BouncyBlock_Parameters : public AutoGen_Parameters
	{

		virtual ~BouncyBlock_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "BouncyBlock_Parameters" );
#endif
		}


		struct _Special
		{
			/// <summary>
			/// A special fill type. Creates a ceiling and ground of bouncy blocks.
			/// </summary>
		
			bool Hallway;
		};
	
		Param Speed, Size, SideDampening, KeepUnused, EdgeSafety;

		_Special Special;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	};

	struct BouncyBlock_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<BouncyBlock_AutoGen> instance;
	
		const static boost::shared_ptr<BouncyBlock_AutoGen> &getInstance();

	
		BouncyBlock_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

	
		void SetHallwaysBlockProperties( const boost::shared_ptr<BouncyBlock> &block, const boost::shared_ptr<Level> &level );
		void Hallway( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	
		void PreFill_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos );
	};
}


#endif	//#ifndef BOUNCYBLOCK__AUTO
