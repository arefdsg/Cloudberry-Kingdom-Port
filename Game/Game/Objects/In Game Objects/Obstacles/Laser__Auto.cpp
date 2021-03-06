#include <small_header.h>
#include "Game/Objects/In Game Objects/Obstacles/Laser__Auto.h"

#include "Game/Level/Make/DifficultyHelper.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Objects/In Game Objects/Obstacles/Laser.h"
#include "Game/Tools/Recycler.h"
#include "Game/Tools/Tools.h"
#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Core/Tools/Random.h"
#include "Game/Tools/Camera.h"

namespace CloudberryKingdom
{

	void Laser_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		boost::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		// General difficulty
		BobWidthLevel = Param( PieceSeed, u->Get( Upgrade_LASER ) );

		LaserStep = Param( PieceSeed, u->Get( Upgrade_LASER ) == 0 ? LaserStepCutoff + 1 : DifficultyHelper::Interp159( 1450, 400, 60, u->Get( Upgrade_LASER ) ) );

		LaserPeriod = Param( PieceSeed, __max( 70, 200 - 11 * u->Get( Upgrade_SPEED ) ) );
	}

	void Laser_Parameters::InitializeInstanceFields()
	{
		LaserStepCutoff = 1499;
	}

boost::shared_ptr<Laser_AutoGen> Laser_AutoGen::instance = boost::make_shared<Laser_AutoGen>();

	const boost::shared_ptr<Laser_AutoGen> &Laser_AutoGen::getInstance()
	{
		return instance;
	}

	Laser_AutoGen::Laser_AutoGen()
	{
		Do_PreFill_2 = true;
		//Generators.AddGenerator(this);
	}

	boost::shared_ptr<AutoGen_Parameters> Laser_AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<Laser_Parameters> Params = boost::make_shared<Laser_Parameters>();
		Params->SetParameters( data, level );

		return boost::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void Laser_AutoGen::PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );

		BL += Vector2( -400, 0 );
		TR += Vector2( 350, 0 );

		// Get Laser parameters
		boost::shared_ptr<Laser_Parameters> Params = boost::static_pointer_cast<Laser_Parameters>( level->getStyle()->FindParams( Laser_AutoGen::getInstance() ) );

		float step = 5;

		Vector2 loc;
		if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
			loc = Vector2( BL.X + 600, ( TR.Y + BL.Y ) / 2 );
		else
			loc = Vector2( ( TR.X + BL.X ) / 2, BL.Y + 600 );

		while ( loc.X < TR.X && level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT || loc.Y < TR.Y && (level->getPieceSeed()->GeometryType == LevelGeometry_UP || level->getPieceSeed()->GeometryType == LevelGeometry_DOWN) )
		{
			step = level->getRnd()->RndFloat(Params->LaserStep.GetVal(loc), Params->LaserStep.GetVal(loc));

			Vector2 CamSize = level->getMainCamera()->GetSize();

			if ( step < Params->LaserStepCutoff )
			{
				boost::shared_ptr<Laser> laser = boost::static_pointer_cast<Laser>( level->getRecycle()->GetObject(ObjectType_LASER, true) );
				laser->Init( Vector2(), level );

				laser->getCore()->Data.Position = loc;
				float shift = level->getRnd()->RndFloat(-800, 800);

				Vector2 p1, p2;
				if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
				{
					p1 = loc + Vector2( shift, CamSize.Y / 2 + 300 );
					p2 = loc - Vector2( shift, CamSize.Y / 2 + 300 );
				}
				else
				{
					p1 = loc + Vector2( CamSize.X / 2 + 300, shift );
					p2 = loc - Vector2( CamSize.X / 2 + 300, shift );
				}

				laser->SetLine( p1, p2 );
				laser->Period = static_cast<int>( Params->LaserPeriod.GetVal( loc ) );
				laser->Offset = level->getRnd()->Rnd->Next(laser->Period);
				laser->WarnDuration = static_cast<int>( laser->Period *.35f );
				laser->Duration = static_cast<int>( laser->Period *.2f );

				laser->getCore()->GenData.LimitGeneralDensity = false;

				// Make sure we stay in bounds
				Tools::EnsureBounds_X( laser, TR, BL );

				level->AddObject( laser );
			}

			if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
				loc.X += step;
			else
				loc.Y += step;
		}
	}

	void Laser_AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}
}
