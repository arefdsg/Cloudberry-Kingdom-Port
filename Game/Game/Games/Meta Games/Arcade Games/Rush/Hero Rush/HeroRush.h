﻿#ifndef HERORUSH
#define HERORUSH

#include "../Game/Games/Meta Games/Arcade Games/Rush/Rush.h"
#include "../Core/Lambdas/Lambda_1.h"
#include "../Game/Games/Meta Games/Arcade Games/Rush/Time Crisis/TimeCrisis.h"
#include "../Game/Games/Meta Games/Arcade Games/Rush/Hero Rush 2/HeroRush2.h"
#include "../Game/Games/Meta Games/Arcade Games/Escalate/Escalation.h"
#include "../Game/Games/ScreenSaver.h"
#include "../Game/Games/Meta Games/StringWorlds/StringWorld_Timed.h"
#include "../Game/Games/Meta Games/StringWorlds/StringWorld_Endurance.h"
#include "../Core/Lambdas/Lambda_2.h"
#include <string>
#include <vector>
#include <cmath>

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class GameData;
}

namespace CloudberryKingdom
{
	class PieceSeedData;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class BobPhsx;
}

namespace CloudberryKingdom
{
	class TileSet;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Challenge_HeroRush : public Rush
	{
	private:
		class OnSwapLambda : public Lambda_1<LevelSeedData*>
		{
		private:
			std::shared_ptr<Challenge_HeroRush> ch;
		public:
			OnSwapLambda( const std::shared_ptr<Challenge_HeroRush> &ch );

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};

	private:
		class ScoreMultiplierHelper : public Lambda_1<GameData*>
		{
		private:
			float multiplier;

		public:
			ScoreMultiplierHelper( float multiplier );

			void Apply( const std::shared_ptr<GameData> &game );
		};

	private:
		class AdditionalPreStartOnSwapToLevelHelper : public Lambda_1<int>
		{
		private:
			std::shared_ptr<Challenge_HeroRush> chr;

		public:
			AdditionalPreStartOnSwapToLevelHelper( const std::shared_ptr<Challenge_HeroRush> &chr );

			void Apply( int levelindex );
		};

	private:
		class MakeMyModParamsHelper : public Lambda_2<Level*, PieceSeedData*>
		{
		public:
			void Apply( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &p );
		};

	private:
		static const std::shared_ptr<Challenge_HeroRush> instance;
	public:
		const static std::shared_ptr<Challenge_HeroRush> &getInstance() const;

	protected:
		Challenge_HeroRush();

		// The progression of max time and start time for increasing difficulty
	private:
		static std::vector<int> MaxTime_ByDifficulty;
		static std::vector<int> StartTime_ByDifficulty;

		void SetTimerProperties( int Difficulty );

	protected:
		virtual void PreStart_Tutorial( bool TemporarySkip );

		virtual void MakeExitDoorIcon( int levelindex );

	private:
		int LevelsPerDifficulty;
	protected:
		virtual void AdditionalPreStart();

	private:
		void OnSwapTo_GUI( int levelindex );

	public:
		virtual std::shared_ptr<LevelSeedData> GetSeed( int Index );

	private:
		static std::vector<BobPhsx*> HeroTypes;

	protected:
		virtual std::shared_ptr<BobPhsx> GetHero( int i );

	private:
		int LevelsPerTileset;
		static std::vector<std::wstring> tilesets;
		//static string[] tilesets = { "hills", "forest", "cloud", "cave", "castle", "sea" };

	protected:
		virtual std::shared_ptr<TileSet> GetTileSet( int i );

	private:
		int LevelLength_Short;
		int LevelLength_Long;
	protected:
		virtual std::shared_ptr<LevelSeedData> Make( int Index, float Difficulty );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HERORUSH
