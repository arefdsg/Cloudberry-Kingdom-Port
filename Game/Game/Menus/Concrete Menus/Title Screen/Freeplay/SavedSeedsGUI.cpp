#include <small_header.h>
#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/SavedSeedsGUI.h"

#include "Core/FancyVector2.h"
#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
#include "Core/Input/ButtonCheck.h"
#include "Core/Text/EzFont.h"
#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Menus/CkBaseMenu.h"
#include "Game/Games/NormalGame.h"
#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
#include "Game/Level/Make/LockableBool.h"
#include "Game/Level/Make/LevelSeedData.h"
#include "Game/Menus/Menu.h"
#include "Game/Menus/LongMenu.h"
#include "Game/Tools/EzStorage.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/VerifyDeleteSeeds.h"
#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomLevel_GUI.h"
#include "Game/Menus/Concrete Menus/Title Screen/TitleGameBase.h"
#include "Game/Menus/Menu Components/ScrollBar.h"
#include "Game/Player/PlayerData.h"
#include "Game/Tools/Tools.h"

#include "Core/Tools/Random.h"
#include "Game/Player/SavedSeeds.h"
#include "Game/Player/PlayerManager.h"

#include <Utility\ConsoleInformation.h>
#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	int SavedSeedsGUI::LastSeedSave_TimeStamp = 0;

	SavedSeedsGUI::PostMakeStandardLoadHelper::PostMakeStandardLoadHelper( const boost::shared_ptr<LevelSeedData> &seed )
	{
		this->seed = seed;
	}

	void SavedSeedsGUI::PostMakeStandardLoadHelper::Apply( const boost::shared_ptr<Level> &level )
	{
		seed->PostMake_StandardLoad( level );
	}

	SavedSeedsGUI::LoadFromFreeplayMenuHelper::LoadFromFreeplayMenuHelper( const boost::shared_ptr<LevelSeedData> &seed, const std::wstring &seedstr, const boost::shared_ptr<CustomLevel_GUI> &simple )
	{
		this->seed = seed;
		this->seedstr = seedstr;
		this->simple = simple;
	}

	void SavedSeedsGUI::LoadFromFreeplayMenuHelper::Apply()
	{
		simple->StartLevel( seed );

		// Randomize the seed for the next level, if the player chooses to continue using this LevelSeedData.
		seed = boost::make_shared<LevelSeedData>();
		seed->ReadString( seedstr );
		seed->PostMake->Add( boost::make_shared<PostMakeStandardLoadHelper>( seed ) );
		seed->setSeed( Tools::GlobalRnd->Rnd->Next() );
	}

	SavedSeedsGUI::SaveSeedsDeleteLambda::SaveSeedsDeleteLambda( const boost::shared_ptr<SavedSeedsGUI> &gui )
	{
		this->gui = gui;
	}

	bool SavedSeedsGUI::SaveSeedsDeleteLambda::Apply( const boost::shared_ptr<Menu> &menu )
	{
		return gui->Delete( menu );
	}

	SavedSeedsGUI::ReturnToCallerProxy::ReturnToCallerProxy( const boost::shared_ptr<SavedSeedsGUI> &ssGui )
	{
		this->ssGui = ssGui;
	}

	void SavedSeedsGUI::ReturnToCallerProxy::Apply()
	{
		ssGui->ReturnToCaller();
	}

	SavedSeedsGUI::DoDeletionProxy::DoDeletionProxy( const boost::shared_ptr<SavedSeedsGUI> &ssGui )
	{
		this->ssGui = ssGui;
	}

	void SavedSeedsGUI::DoDeletionProxy::Apply( const bool &choice )
	{
		ssGui->DoDeletion( choice );
	}

	SavedSeedsGUI::SortProxy::SortProxy( const boost::shared_ptr<SavedSeedsGUI> &ssGui )
	{
		this->ssGui = ssGui;
	}

	void SavedSeedsGUI::SortProxy::Apply()
	{
		ssGui->Sort();
	}

	SavedSeedsGUI::SaveSeedsBackLambda::SaveSeedsBackLambda( const boost::shared_ptr<SavedSeedsGUI> &gui )
	{
		this->gui = gui;
	}

	bool SavedSeedsGUI::SaveSeedsBackLambda::Apply( const boost::shared_ptr<Menu> &menu )
	{
		return gui->Back( menu );
	}

	SavedSeedsGUI::SeedItem::SeedItem( const std::wstring &name, const std::wstring &seed, const boost::shared_ptr<EzFont> &font ) : MenuItem( boost::shared_ptr<EzText>( 0 ) )
	{
		InitializeInstanceFields();
	}
	boost::shared_ptr<SavedSeedsGUI::SeedItem> SavedSeedsGUI::SeedItem::SeedItem_Construct( const std::wstring &name, const std::wstring &seed, const boost::shared_ptr<EzFont> &font )
	{
		MenuItem::MenuItem_Construct( boost::make_shared<EzText>( name, font ) );

		this->Name = name;
		this->Seed = seed;

		return boost::static_pointer_cast<SavedSeedsGUI::SeedItem>( shared_from_this() );
	}

	void SavedSeedsGUI::SeedItem::ToggleDeletion()
	{
		MarkedForDeletion = !MarkedForDeletion;

		// Make items marked for deletion semi-transparent.
		if ( MarkedForDeletion )
			MyText->Alpha = MySelectedText->Alpha = .3f;
		else
			MyText->Alpha = MySelectedText->Alpha = 1;
	}

	void SavedSeedsGUI::SeedItem::InitializeInstanceFields()
	{
		MarkedForDeletion = false;
	}

	SavedSeedsGUI::StartLevelProxy1::StartLevelProxy1( const boost::shared_ptr<SavedSeedsGUI> &ssGui, const std::wstring &_seed )
	{
		this->ssGui = ssGui;
		this->_seed = _seed;
	}

	void VerifyDelete( boost::shared_ptr<SavedSeedsGUI> ssGui )
	{
		if ( !ssGui->Active )
			return;

		ssGui->SlideOutTo = ssGui->SlideInFrom = ssGui->PresetPos_RIGHT;

		int num = ssGui->NumSeedsToDelete();
		if ( num > 0 )
		{
			boost::shared_ptr<VerifyDeleteSeeds> verify = MakeMagic( VerifyDeleteSeeds, ( ssGui->getControl(), num, ssGui->UseBounce ) );
			verify->OnSelect->Add( boost::make_shared<SavedSeedsGUI::DoDeletionProxy>( boost::static_pointer_cast<SavedSeedsGUI>( ssGui->shared_from_this() ) ) );

			ssGui->SlideOutTo = GUI_Panel::PresetPos_LEFT;
			ssGui->SlideInFrom = GUI_Panel::PresetPos_LEFT;
			ssGui->Call( verify, 0 );

			if (ssGui->UseBounce)
			{
				ssGui->Hid = true;
				ssGui->RegularSlideOut( GUI_Panel::PresetPos_RIGHT, 0 );
			}
			else
			{
				ssGui->Hide( GUI_Panel::PresetPos_LEFT );
			}
		}
		else
			ssGui->ReturnToCaller();
	}

	void SavedSeedsGUI::StartLevelProxy1::Apply( const boost::shared_ptr<MenuItem> &_menu )
	{
		int n = ssGui->NumSeedsToDelete();

		if (n > 0)
		{
			//ssGui->Back( ssGui->MyMenu );
			VerifyDelete( ssGui );
		}
		else
			ssGui->StartLevel(_seed);
	}

	


	SavedSeedsGUI::OnAddHelper::OnAddHelper( const boost::shared_ptr<ScrollBar> &bar )
	{
		this->bar = bar;
	}

	bool SavedSeedsGUI::OnAddHelper::Apply()
	{
#if defined(WINDOWS) && !defined(NOT_PC)
		return bar->MyMenu->HitTest();
#else
		return false;
#endif
	}

	SavedSeedsGUI::SavedSeedsGUI()
	{
		MyInit_TimeStamp = 0;
	}
	boost::shared_ptr<SavedSeedsGUI> SavedSeedsGUI::SavedSeedsGUI_Construct()
	{
		CkBaseMenu::CkBaseMenu_Construct();
		
		//EnableBounce();

		return boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() );
	}

	void SavedSeedsGUI::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->Shadow = false;
	}

	void SavedSeedsGUI::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;
	}

	void SavedSeedsGUI::StartLevel( const std::wstring &seedstr )
	{
		LoadSeed( seedstr, boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}

	boost::shared_ptr<CustomLevel_GUI> SavedSeedsGUI::FreeplayMenu = 0;

	void SavedSeedsGUI::LoadSeed( const std::wstring &seedstr, const boost::shared_ptr<GUI_Panel> &panel )
	{
		// If the current panel or parent panel is the Freeplay menu,
		// then directly start the level.
		FreeplayMenu = boost::dynamic_pointer_cast<CustomLevel_GUI>( panel->Caller );
		if ( FreeplayMenu == 0 )
			FreeplayMenu = boost::dynamic_pointer_cast<CustomLevel_GUI>( panel );
		if ( 0 != FreeplayMenu )
		{
			LoadFromFreeplayMenu( seedstr, FreeplayMenu );
		}
		else
		{
			// Otherwise, if the parent game is Freeplay, then queue Freeplay to load the level.
			if ( boost::dynamic_pointer_cast<TitleGameData>( Tools::CurGameData->ParentGame ) != 0 )
			{
				Tools::CurrentAftermath = boost::make_shared<AftermathData>();
				Tools::CurrentAftermath->Success = false;
				Tools::CurrentAftermath->EarlyExit = true;

				CustomLevel_GUI::SeedStringToLoad = seedstr;
				Tools::CurGameData->EndGame->Apply( false );
			}
			else
				CustomLevel_GUI::SeedStringToLoad = seedstr;

	//#if defined(DEBUG)
	//                // otherwise, hard load the game, and forget about how it connects to anything else.
	//                // This will cause crashes if you try to exit the game afterwards, but is fine for testing purposes.
	//                else
	//                {
	//                    GameData.LockLevelStart = false;
	//                    LevelSeedData.ForcedReturnEarly = 0;

	//                    LevelSeedData data = new LevelSeedData();
	//                    data.ReadString(seedstr);
	//                    GameData.StartLevel(data);
	//                }
	//#endif
		}
	}

	void SavedSeedsGUI::LoadFromFreeplayMenu( const std::wstring &seedstr, const boost::shared_ptr<CustomLevel_GUI> &simple )
	{
		boost::shared_ptr<LevelSeedData> seed = boost::make_shared<LevelSeedData>();
		seed->ReadString( seedstr );
		seed->PostMake->Add( boost::make_shared<PostMakeStandardLoadHelper>( seed ) );

		simple->MyGame->PlayGame( boost::make_shared<LoadFromFreeplayMenuHelper>( seed, seedstr, simple ) );

	}

	int SavedSeedsGUI::NumSeedsToDelete()
	{
		int count = 0;
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			boost::shared_ptr<SeedItem> seeditem = boost::dynamic_pointer_cast<SeedItem>( *item );
			if ( 0 != seeditem && seeditem->MarkedForDeletion )
				count++;
		}

		return count;
	}

	bool SavedSeedsGUI::Delete( const boost::shared_ptr<Menu> &_menu )
	{
		if ( !Active )
			return true;

		boost::shared_ptr<SeedItem> seeditem = boost::dynamic_pointer_cast<SeedItem>( MyMenu->getCurItem() );
		if ( 0 != seeditem )
			seeditem->ToggleDeletion();

		return true;
	}

	void SavedSeedsGUI::DoDeletion( bool choice )
	{
		Active = false;

		// If "No", do not delete any seeds.
		if ( !choice )
		{
			//MyGame->WaitThenDo( 10, boost::make_shared<ReturnToCallerProxy>( boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() ) ) );
			return;
		}

		// Delete all saved seeds.
		player->MySavedSeeds->SeedStrings.clear();

		// Save seeds not marked for deletion.
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			boost::shared_ptr<SeedItem> seeditem = boost::dynamic_pointer_cast<SeedItem>( *item );
			if ( 0 == seeditem )
				continue;
			if ( seeditem->MarkedForDeletion )
				continue;

			player->MySavedSeeds->SeedStrings.push_back( seeditem->Seed );
		}

		SaveGroup::SaveAll();

		LastSeedSave_TimeStamp = Tools::DrawCount;
		ReInit();

		SlideOut( PresetPos_LEFT, 0 );
		SlideInFrom = SlideOutTo = PresetPos_LEFT;
	}

	void SavedSeedsGUI::ReInit()
	{
		MyInit_TimeStamp = Tools::DrawCount;

		boost::shared_ptr<FancyVector2> HoldPos = Pos;
		Init();
		Pos = HoldPos;

		if ( bar != 0 )
		{
			bar->Release();

			bar = MakeMagic( ScrollBar, ( boost::static_pointer_cast<LongMenu>( MyMenu ), boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );
			bar->setBarPos( Vector2( -1860, 102.7778f ) );
			MyGame->AddGameObject( bar );

#if defined(PC_VERSION)
			MyMenu->AdditionalCheckForOutsideClick = boost::make_shared<OnAddHelper>( bar );
#endif
		}
	}

	void SavedSeedsGUI::Sort()
	{
		if ( !Active )
			return;
	}

	void SavedSeedsGUI::Init()
	{
		if ( boost::dynamic_pointer_cast<NormalGameData>( Tools::CurGameData ) != 0 )
		{
            EnableBounce();
		}

		MyInit_TimeStamp = Tools::DrawCount;

		CkBaseMenu::Init();

		setControl( -1 );
		MyPile = boost::make_shared<DrawPile>();

		// Get the activating player
		//player = MenuItem::GetActivatingPlayerData();
		player = PlayerManager::Players[ 0 ];
		if ( player == 0 )
		{
			player = MenuItem::GetActivatingPlayerData();
		}

		// Set slide in and out parameters
		ReturnToCallerDelay = 6;
		SlideInFrom = PresetPos_RIGHT;
		SlideOutTo = PresetPos_RIGHT;
		SlideInLength = 25;
		SlideOutLength = 20;

		// Make the menu
		//MyMenu = new Menu(false);
		MyMenu = boost::make_shared<LongMenu>();
		MyMenu->FixedToCamera = false;
		MyMenu->WrapSelect = false;
		( boost::static_pointer_cast<LongMenu>( MyMenu ) )->OffsetStep = 30;
		EnsureFancy();
		MyMenu->OnA.reset();
		MyMenu->OnB = boost::make_shared<SaveSeedsBackLambda>( boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() ) );
		MyMenu->OnX = boost::make_shared<SaveSeedsDeleteLambda>( boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() ) );
		MyMenu->OnY = boost::make_shared<SortProxy>( boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() ) );
		MyMenu->SelectDelay = 11;

		ItemPos = Vector2( 80.5547f, 756.1112f );
		PosAdd = Vector2( 0, -120 );

		FontScale = .666f;

		// Backdrop
		boost::shared_ptr<QuadClass> backdrop;
		if (UseSimpleBackdrop)
			backdrop = boost::make_shared<QuadClass>( std::wstring( L"Arcade_BoxLeft" ), 1500.f, true );
		else
			backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1500x900" ), 1500.f, true );

		backdrop->Name = L"Backdrop";
		MyPile->Add( backdrop );

		if ( !UseSimpleBackdrop )
		{
			EpilepsySafe(.9f);
		}

		// Header
		boost::shared_ptr<MenuItem> item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_SavedSeeds, ItemFont ) ) );
		item->Name = std::wstring( L"Header" );
		item->Selectable = false;
		SetHeaderProperties( item->MySelectedText );
		AddItem( item );

		Vector2 SavePos = ItemPos;
		MakeOptions();
		ItemPos = SavePos;
		
		MakeList();

	#if !defined(PC_VERSION)
		OptionalBackButton();
	#endif

		SetPos();
if ( ButtonCheck::ControllerInUse )
{
		MyMenu->SelectItem( 4 );
}
else
{
		MyMenu->SelectItem( 3 );
}
	}

	void SavedSeedsGUI::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( CoreData->Released || !Active ) return;

		if ( MyInit_TimeStamp + 10 < LastSeedSave_TimeStamp )
		{
			ReInit();
		}

		// Update "Confirm"
		//if ( ButtonCheck::State( ControllerButtons_A, -2 )->Pressed )
		{
			int n = NumSeedsToDelete();
			//MyPile->FindQuad( L"Confirm" )->Show = n > 0;
			//MyPile->FindEzText( L"Confirm" )->Show = n > 0;

			std::wstring GoString;
			if ( n == 0 )      GoString = Localization::WordString( Localization::Words_LoadSeed );
			else if ( n == 1 ) GoString = Format( Localization::WordString( Localization::Words_DeleteSeeds ).c_str(), ToString( n ).c_str() );
			else		       GoString = Format( Localization::WordString( Localization::Words_DeleteSeedsPlural ).c_str(), ToString( n ).c_str() );

			boost::shared_ptr<MenuItem> _item = MyMenu->FindItemByName( L"Load" );
			if ( _item != 0 )
			{
				_item->MyText->SubstituteText( GoString );
				_item->MySelectedText->SubstituteText( GoString );
			}
		}

	#if defined(WINDOWS)
		if ( ButtonCheck::State( Keys_Delete ).Pressed )
			Delete( MyMenu );
	#endif
	}

	bool SavedSeedsGUI::Back( const boost::shared_ptr<Menu> &menu )
	{
		if ( !Active )
			return true;

		SlideOutTo = SlideInFrom = PresetPos_RIGHT;

		//int num = NumSeedsToDelete();
		//if ( num > 0 )
		//{
		//	boost::shared_ptr<VerifyDeleteSeeds> verify = MakeMagic( VerifyDeleteSeeds, ( getControl(), num, UseBounce ) );
		//	verify->OnSelect->Add( boost::make_shared<DoDeletionProxy>( boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() ) ) );

		//	SlideOutTo = PresetPos_LEFT;
		//	SlideInFrom = PresetPos_LEFT;
		//	Call( verify, 0 );

		//	if (UseBounce)
		//	{
		//		Hid = true;
		//		RegularSlideOut(PresetPos_RIGHT, 0);
		//	}
		//	else
		//	{
		//		Hide(PresetPos_LEFT);
		//	}
		//}
		//else
			ReturnToCaller();

		return true;
	}

	void SavedSeedsGUI::OnReturnTo()
	{
		// Clear the pre-deleted items
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			boost::shared_ptr<SeedItem> sitem = boost::dynamic_pointer_cast<SeedItem>( *item );
			if ( 0 != sitem && sitem->MarkedForDeletion )
				sitem->ToggleDeletion();
		}

		//Hid = false;
		//CallToLeft = false;
		//UseBounce = false;
		//SlideOutLength = 0;
		//ReturnToCallerDelay = 0;

		CkBaseMenu::OnReturnTo();
	}

	void SavedSeedsGUI::OptionalBackButton()
	{
		// Make a back button if there is no saved seeds.
		if ( player->MySavedSeeds->SeedStrings.empty() )
			MakeBackButton();
	}

	void SavedSeedsGUI::SetPos()
	{
			boost::shared_ptr<MenuItem> _item;
			boost::shared_ptr<QuadClass> _q;

if ( ButtonCheck::ControllerInUse )
{
			_item = MyMenu->FindItemByName( L"Header" ); if (_item != 0 ) { _item->setSetPos( Vector2( 69.44482f, 955.5558f ) ); _item->MyText->setScale( 0.666f ); _item->MySelectedText->setScale( 0.666f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Load" ); if (_item != 0 ) { _item->setSetPos( Vector2( 736.1101f, 983.3332f ) ); _item->MyText->setScale( 0.4186335f ); _item->MySelectedText->setScale( 0.4186335f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Delete" ); if (_item != 0 ) { _item->setSetPos( Vector2( 741.6659f, 860.5553f ) ); _item->MyText->setScale( 0.3892168f ); _item->MySelectedText->setScale( 0.3892168f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 741.6665f, 756.6665f ) ); _item->MyText->setScale( 0.4212168f ); _item->MySelectedText->setScale( 0.4212168f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-1016.667f, 0.f ) );

			_q = MyPile->FindQuad( L"Button_A" ); if (_q != 0 ) { _q->setPos( Vector2( 658.3345f, 911.1108f ) ); _q->setSize( Vector2( 56.16665f, 56.16665f ) ); }
			_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2( 661.1113f, 794.4444f ) ); _q->setSize( Vector2( 57.66665f, 57.66665f ) ); }
			_q = MyPile->FindQuad( L"Button_B" ); if (_q != 0 ) { _q->setPos( Vector2( 663.8892f, 677.7778f ) ); _q->setSize( Vector2( 56.41664f, 56.41664f ) ); }
			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 2.77771f, 22.22221f ) ); _q->setSize( Vector2( 1572.44f, 1572.44f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else
{	
			_item = MyMenu->FindItemByName( L"Header" ); if (_item != 0 ) { _item->setSetPos( Vector2( 88.88916f, 941.6669f ) ); _item->MyText->setScale( 0.666f ); _item->MySelectedText->setScale( 0.666f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Load" ); if (_item != 0 ) { _item->setSetPos( Vector2( 591.6653f, 988.889f ) ); _item->MyText->setScale( 0.3920501f ); _item->MySelectedText->setScale( 0.3920501f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 591.6661f, 893.8889f ) ); _item->MyText->setScale( 0.3935499f ); _item->MySelectedText->setScale( 0.3935499f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-1016.667f, 0.f ) );

			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 2.77771f, 22.22221f ) ); _q->setSize( Vector2( 1572.44f, 1572.44f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}

			// Extra squeeze
			Vector2 squeeze = Vector2(-15, -18 ) * CloudberryKingdomGame::GuiSqueeze;

			_item = MyMenu->FindItemByName( L"Load" ); if (_item != 0 ) { _item->setSetPos( _item->Pos + squeeze ); }
			_item = MyMenu->FindItemByName( L"Delete" ); if (_item != 0 ) { _item->setSetPos( _item->Pos + squeeze ); }
			_item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( _item->Pos + squeeze ); }

			_q = MyPile->FindQuad( L"Button_A" ); if (_q != 0 ) { _q->setPos( _q->getPos() + squeeze ); }
			_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( _q->getPos() + squeeze ); }
			_q = MyPile->FindQuad( L"Button_B" ); if (_q != 0 ) { _q->setPos( _q->getPos() + squeeze ); }

		if ( IsAspect4by3() )
		{
			MyPile->setPos( MyPile->getPos() + Vector2(0, -20) );
		}

	}

	void SavedSeedsGUI::MakeList()
	{
		for ( std::vector<std::wstring>::const_iterator seed = player->MySavedSeeds->SeedStrings.begin(); seed != player->MySavedSeeds->SeedStrings.end(); ++seed )
		{
			std::wstring _seed = *seed;
			std::wstring name = LevelSeedData::GetNameFromSeedStr( *seed );

			// Get name of seed
			boost::shared_ptr<MenuItem> seeditem = MakeMagic( SeedItem, ( name, *seed, ItemFont ) );
			seeditem->setGo( boost::make_shared<StartLevelProxy1>( boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() ), _seed ) );
			AddItem( seeditem );
			
			seeditem->ScaleText( .635f );
			float w = seeditem->MyText->GetWorldWidth();
			if (w > 1900) seeditem->ScaleText( 1900.0f / w );
		}
	}

	void SavedSeedsGUI::OnAdd()
	{
		CkBaseMenu::OnAdd();

		// Scroll bar
	#if defined(WINDOWS)
	//#ifdef PC_VERSION
		//if (false)
		{
			bar = MakeMagic( ScrollBar, ( boost::static_pointer_cast<LongMenu>( MyMenu ), boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );
			bar->setBarPos( Vector2( -1860, 102.7778f ) );
			MyGame->AddGameObject( bar );
	#if defined(PC_VERSION)
			MyMenu->AdditionalCheckForOutsideClick = boost::make_shared<OnAddHelper>( bar );
	#endif
		}
	#endif

		if ( boost::dynamic_pointer_cast<CustomLevel_GUI>( Caller ) != 0 )
		{
			RegularSlideOut( PresetPos_RIGHT, 0 );
			SlideIn( 30 );
		}
	}

	void SavedSeedsGUI::MakeOptions()
	{
		FontScale *= .8f;

		//MakeBackButton( Localization::Words_Back, false )->UnaffectedByScroll = true;

        boost::shared_ptr<MenuItem> item;

if ( ButtonCheck::ControllerInUse )
{
		// Load
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_LoadSeed, ItemFont ) ) );
		item->Name = L"Load";
		AddItem( item );
		item->SelectSound = 0;
		item->UnaffectedByScroll = true;
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getGo(), 90.0f, std::wstring( L"Button_A" ) ) );
		item->Selectable = false;
#if XBOX
		item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedBackColor;
		item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
#endif
}

if ( ButtonCheck::ControllerInUse )
{
		// Delete
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Delete, ItemFont ) ) );
		item->Name = L"Delete";
		AddItem( item );
		item->SelectSound = 0;
		item->UnaffectedByScroll = true;

		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getX(), 90.0f, std::wstring( L"Button_X" ) ) );
		item->Selectable = false;
#if XBOX
		item->MyText->MyFloatColor = Color( 204, 220, 255 )->ToVector4();
		item->MySelectedText->MyFloatColor = Color( 204, 220, 255 )->ToVector4();
#endif
}

		// Back
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Back, ItemFont ) ) );
		item->Name = L"Back";
		AddItem( item );
		item->SelectSound = 0;
		item->setGo( boost::make_shared<ItemReturnToCallerProxy>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );
		item->UnaffectedByScroll = true;
if ( ButtonCheck::ControllerInUse )
{
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getBack(), 90.0f, std::wstring( L"Button_B" ) ) );
		item->Selectable = false;
}
#if XBOX
		item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedBackColor;
		item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
#endif
	}
}
