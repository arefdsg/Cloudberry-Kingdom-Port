﻿#include "StringWorld_Timed.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer_Base.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Score.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Level.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Level/Make/CloudberryKingdom.LevelSeedData.h"
#include "Game/Objects/Game Objects/GameObjects/PerfectScoreObject.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer.h"
#include "Game/Objects/Game Objects/GameObjects/TimerWarning.h"
#include "Game/Objects/Game Objects/GameObjects/CoinScoreMultiplierObject.h"
#include "Game/Games/GameType.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;

namespace CloudberryKingdom
{

	StringWorldTimed::StringWorldOnTimerExpiredLambda::StringWorldOnTimerExpiredLambda( const std::shared_ptr<GUI_Score> &MyGUI_Score, const std::shared_ptr<GUI_Level> &MyGUI_Level )
	{
		this->MyGUI_Score = MyGUI_Score;
		this->MyGUI_Level = MyGUI_Level;
	}

	void StringWorldTimed::StringWorldOnTimerExpiredLambda::Apply( const std::shared_ptr<GUI_Timer_Base> &timer )
	{
		MyGUI_Score->SlideOut( GUI_Panel::PresetPos_TOP );
		MyGUI_Level->SlideOut( GUI_Panel::PresetPos_TOP );
	}

	StringWorldTimed::OnSwapLambda::OnSwapLambda( const std::shared_ptr<StringWorldTimed> &ch )
	{
		this->ch = ch;
	}

	void StringWorldTimed::OnSwapLambda::Apply( const std::shared_ptr<LevelSeedData> &data )
	{
		data->MyGame->AddGameObject( ch->MyGUI_Timer, ch->Warning, ch->MyGUI_Score, ch->MyGUI_Level, ch->MyCoinScoreMultiplier, std::make_shared<PerfectScoreObject>( false, true ) );
	}

	StringWorldTimed::StringWorldTimed( Func<int, LevelSeedData*> GetSeed, const std::shared_ptr<GUI_Timer> &Timer ) : StringWorldGameData( std::make_shared<Func>( this, &StringWorldTimed::GetSeed ) )
	{
		MyGUI_Timer = Timer;

		Warning = std::make_shared<TimerWarning>();
		Warning->MyTimer = Timer;

		MyGUI_Score = std::make_shared<GUI_Score>();
		MyGUI_Level = std::make_shared<GUI_Level>();

		Timer->OnTimeExpired->Add( std::make_shared<StringWorldOnTimerExpiredLambda>( MyGUI_Score, MyGUI_Level ) );

		// Coin score multiplier
		MyCoinScoreMultiplier = std::make_shared<CoinScoreMultiplierObject>();

		// Add 'Perfect' watcher
		OnSwapToFirstLevel->Add( std::make_shared<OnSwapLambda>( this ) );
	}

	void StringWorldTimed::Release()
	{
		StringWorldGameData::Release();

		MyGUI_Timer->ForceRelease();
	}

	void StringWorldTimed::AdditionalSwapToLevelProcessing( const std::shared_ptr<GameData> &game )
	{
		StringWorldGameData::AdditionalSwapToLevelProcessing( game );

		MyGUI_Level->SetLevel( CurLevelIndex + 1 );

		game->TakeOnce = true;
	}
}
