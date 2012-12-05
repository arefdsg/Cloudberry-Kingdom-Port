#include <global_header.h>

namespace CloudberryKingdom
{

	StartMenu::StartMenuLambda_Campaign::StartMenuLambda_Campaign( const std::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::StartMenuLambda_Campaign::Apply( const std::shared_ptr<MenuItem> &item )
	{
		sm->MenuGo_Campaign( item );
	}

	StartMenu::StartMenuLambda_Arcade::StartMenuLambda_Arcade( const std::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::StartMenuLambda_Arcade::Apply( const std::shared_ptr<MenuItem> &item )
	{
		sm->MenuGo_Arcade( item );
	}

	StartMenu::StartMenuLambda_Freeplay::StartMenuLambda_Freeplay( const std::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::StartMenuLambda_Freeplay::Apply( const std::shared_ptr<MenuItem> &item )
	{
		sm->MenuGo_Freeplay( item );
	}

	StartMenu::CharacterSelectProxy::CharacterSelectProxy( const std::shared_ptr<StartMenu> &startMenu )
	{
		this->startMenu = startMenu;
	}

	void StartMenu::CharacterSelectProxy::Apply()
	{
		startMenu->CharacterSelect();
	}

	StartMenu::MenuGo_ScreenSaverHelper::MenuGo_ScreenSaverHelper( const std::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::MenuGo_ScreenSaverHelper::Apply()
	{
		sm->MyGame->Release();
	}

	StartMenu::StartMenuLambda_Controls::StartMenuLambda_Controls( const std::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::StartMenuLambda_Controls::Apply( const std::shared_ptr<MenuItem> &item )
	{
		sm->MenuGo_Controls( item );
	}

	StartMenu::StartMenuLambda_Options::StartMenuLambda_Options( const std::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::StartMenuLambda_Options::Apply( const std::shared_ptr<MenuItem> &item )
	{
		sm->MenuGo_Options( item );
	}

	StartMenu::StartMenuLambda_Exit::StartMenuLambda_Exit( const std::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::StartMenuLambda_Exit::Apply( const std::shared_ptr<MenuItem> &item )
	{
		sm->MenuGo_Exit( item );
	}

	StartMenu::StartMenuExitLambda::StartMenuExitLambda( const std::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	bool StartMenu::StartMenuExitLambda::Apply( const std::shared_ptr<Menu> &menu )
	{
		sm->Exit();
		return false;
	}

	StartMenu::DoneWithCharSelectProxy::DoneWithCharSelectProxy( const std::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::DoneWithCharSelectProxy::Apply()
	{
		sm->DoneWithCharSelect();
	}

	StartMenu::BringNextMenuLambda::BringNextMenuLambda( const std::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::BringNextMenuLambda::Apply()
	{
		sm->BringNextMenu();
	}

	void StartMenu::Hide( const std::shared_ptr<PresetPos> &pos, int frames )
	{
		CkBaseMenu::Hide( pos, frames );
		ButtonCheck::PreLogIn = false;
	}

	void StartMenu::MenuGo_Campaign( const std::shared_ptr<MenuItem> &item )
	{
		MyNextMenu = Next_CAMPAIGN;
		BringCharacterSelect();
	}

	void StartMenu::MenuGo_Arcade( const std::shared_ptr<MenuItem> &item )
	{
		MyNextMenu = Next_ARCADE;
		BringCharacterSelect();
		//DoneWithCharSelect();StartMenu_MW_HeroSelect
	}

	void StartMenu::MenuGo_Freeplay( const std::shared_ptr<MenuItem> &item )
	{
		MyNextMenu = Next_FREEPLAY;
		BringCharacterSelect();
		//DoneWithCharSelect();
	}

	void StartMenu::BringCharacterSelect()
	{
		NoBack = true;
		MyGame->SlideOut_FadeIn( 20, std::make_shared<CharacterSelectProxy>( shared_from_this() ) );
	}

	void StartMenu::Show()
	{
		NoBack = false;
		CkBaseMenu::Show();
	}

	void StartMenu::ReturnToCaller()
	{
		CkBaseMenu::ReturnToCaller();
	}

	void StartMenu::CharacterSelect()
	{
		Hide();
		CharacterSelectManager::Start( shared_from_this() );
		CharacterSelectManager::OnDone = std::make_shared<DoneWithCharSelectProxy>( shared_from_this() );
		CharacterSelectManager::OnBack.reset();
	}

	void StartMenu::MenuGo_ScreenSaver( const std::shared_ptr<MenuItem> &item )
	{
		std::shared_ptr<ScreenSaver> Intro = std::make_shared<ScreenSaver>();
		Intro->Init();
		Tools::TheGame->LogoScreenPropUp = false;
		Tools::AddToDo( std::make_shared<MenuGo_ScreenSaverHelper>( shared_from_this() ) );
	}

	void StartMenu::MenuGo_Controls( const std::shared_ptr<MenuItem> &item )
	{
		Call( std::make_shared<ControlScreen>( getControl() ), 0 );
	}

	void StartMenu::MenuGo_Stats( const std::shared_ptr<MenuItem> &item )
	{
		Call( std::make_shared<StatsMenu>( StatGroup_LIFETIME ), 0 );
	}

	void StartMenu::MenuGo_Options( const std::shared_ptr<MenuItem> &item )
	{
		Call( std::make_shared<SoundMenu>( getControl() ), 0 );
	}

	void StartMenu::MenuGo_Exit( const std::shared_ptr<MenuItem> &item )
	{
		Exit();
	}

	void StartMenu::Exit()
	{
		SelectSound.reset();
		Call( std::make_shared<VerifyQuitGameMenu2>( getControl() ), 0 );
	}

	StartMenu::StartMenu()
	{
		InitializeInstanceFields();
		if ( Tools::TheGame->LoadingScreen_Renamed != 0 )
			Tools::TheGame->LoadingScreen_Renamed->IsDone = true;
	}

	void StartMenu::SlideIn( int Frames )
	{
		CkBaseMenu::SlideIn( Frames );
		//base.SlideIn(0);
		//return;

		//if (SlideOnReturn)
		//    base.SlideIn(Frames);
		//else
		//{
		//    base.SlideIn(0);

		//    MyPile.BubbleUp(true, 8, 1);
		//    MyMenu.FancyPos.LerpTo(MenuPos_Down, MenuPos, 40);
		//}

		//SlideOnReturn = false;
	}

	void StartMenu::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );
		SetItemProperties_Red( item );
	}

	void StartMenu::SetText_Green( const std::shared_ptr<EzText> &text, bool outline )
	{
		if ( text == 0 )
			return;

		text->OutlineColor = ( Color( 0, 0, 0, outline ? 255 : 0 ) ).ToVector4();
		text->MyFloatColor = ( Color( 34, 214, 47 ) ).ToVector4();
	}

	void StartMenu::SetSelectedText_Green( const std::shared_ptr<EzText> &text, bool outline )
	{
		if ( text == 0 )
			return;

		text->OutlineColor = ( Color( 0, 0, 0, outline ? 255 : 0 ) ).ToVector4();
		text->MyFloatColor = ( Color( 65, 255, 100 ) ).ToVector4();
	}

	void StartMenu::SetItemProperties_Green( const std::shared_ptr<MenuItem> &item, bool outline )
	{
		SetText_Green( item->MyText, outline );
		SetText_Green( item->MySelectedText, outline );
	}

	void StartMenu::SetItemProperties_Red( const std::shared_ptr<MenuItem> &item )
	{
		if ( item->MyText == 0 )
			return;
		item->MyText->OutlineColor = ( Color( 191, 191, 191 ) ).ToVector4();
		item->MyText->MyFloatColor = ( Color( 175, 8, 64 ) ).ToVector4();
		item->MySelectedText->OutlineColor = ( Color( 205, 205, 205 ) ).ToVector4();
		item->MySelectedText->MyFloatColor = ( Color( 242, 12, 85 ) ).ToVector4();
	}

	void StartMenu::OnAdd()
	{
		CkBaseMenu::OnAdd();
	}

	void StartMenu::Init()
	{
		 CkBaseMenu::Init();

		SlideInFrom = PresetPos_LEFT;
		SlideOutTo = PresetPos_LEFT;

		ReturnToCallerDelay = 4;
		CallDelay = 33;
		setSlideLength( 36 );
		DestinationScale *= 1.015f;

		MyPile = std::make_shared<DrawPile>();

		MyMenu = std::make_shared<Menu>( false );

		MyMenu->setControl( -2 );

		MyMenu->CheckForOutsideClick = false;
		MyMenu->OnB = std::make_shared<StartMenuExitLambda>( shared_from_this() );

		FontScale *= .88f;
		PosAdd = Vector2( 0, -117 );

		// Make the start menu
		MakeMenu();
	}

	void StartMenu::GrayItem( const std::shared_ptr<MenuItem> &item )
	{
		item->MyText->MyFloatColor = ColorHelper::Gray( .535f );
		item->MySelectedText->MyFloatColor = ColorHelper::Gray( .55f );
	}

	void StartMenu::MakeMenu()
	{
		std::shared_ptr<MenuItem> item;

		// Arcade
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_THE_ARCADE, ItemFont ) );
		item->Name = _T( "Arcade" );
		item->setGo( std::make_shared<StartMenuLambda_Arcade>( shared_from_this() ) );
		AddItem( item );

		// Campaign
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_STORY_MODE, ItemFont ) );
		item->Name = _T( "Campaign" );
		AddItem( item );
		item->setGo( std::make_shared<StartMenuLambda_Campaign>( shared_from_this() ) );

		//// Extra
		//item = new MenuItem(new EzText("Extras", ItemFont));
		//item.Name = "Freeplay";
		//item.Go = null;
		//AddItem(item);

		// Free Play
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_FREE_PLAY, ItemFont ) );
		item->Name = _T( "Freeplay" );
		item->setGo( std::make_shared<StartMenuLambda_Freeplay>( shared_from_this() ) );
		AddItem( item );

		//// Jukebox
		//item = new MenuItem(new EzText("Jukebox", ItemFont));
		//item.Name = "Jukebox";
		//item.Go = MenuGo_ScreenSaver;
		//AddItem(item);

		// Options
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_OPTIONS, ItemFont ) );
		item->Name = _T( "Options" );
		item->setGo( std::make_shared<StartMenuLambda_Options>( shared_from_this() ) );
		AddItem( item );

		// Stats
		//item = new MenuItem(new EzText("Stats", ItemFont));
		//item.Go = new StartMenuLambda_Stats(this);
		//AddItem(item);

		// Exit
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_EXIT, ItemFont ) );
		item->Name = _T( "Exit" );
		item->setGo( std::make_shared<StartMenuLambda_Exit>( shared_from_this() ) );
		AddItem( item );

		EnsureFancy();

		this->CallToLeft = true;
	}

	void StartMenu::BlackBox()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Campaign" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2206.164f, 346.4168f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Arcade" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2118.89f, 148.8611f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Freeplay" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2156.22f, -34.80548f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Jukebox" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 2.666809f, -843.4722f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Options" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2090.221f, -213.25f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Exit" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1950.778f, -413.5834f ) );
		}

		MyMenu->setPos( Vector2( 1737.697f, -212.8573f ) );

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "TitleScreen" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1799.546f, 1012.247f ) );
		}
		_q = MyPile->FindQuad( _T( "BackBox" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -94.44531f, -355.5555f ) );
			_q->setSize( Vector2( 458.5224f, 560.4163f ) );
		}
		_q = MyPile->FindQuad( _T( "Title" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -25, 88.88889f ) );
			_q->setSize( Vector2( 1690.654f, 950.9934f ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	}

	void StartMenu::Centered()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Campaign" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2206.164f, 346.4168f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Arcade" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2116.112f, 148.8611f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Freeplay" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2156.22f, -34.80548f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Jukebox" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 2.666809f, -843.4722f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Options" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2087.443f, -213.25f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Exit" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1950.778f, -410.8056f ) );
		}

		MyMenu->setPos( Vector2( 1715.474f, -154.5238f ) );

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "TitleScreen" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1799.547f, 1012.247f ) );
		}
		_q = MyPile->FindQuad( _T( "Title" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -25, 88.88889f ) );
			_q->setSize( Vector2( 1690.655f, 950.9938f ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	}

	void StartMenu::Forest()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Campaign" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -45.05542f, 907.5278f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Arcade" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 89.4444f, 690.5278f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Freeplay" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -17.33331f, 509.6389f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Jukebox" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 49.88898f, 312.0833f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Options" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 112.5558f, 114.5278f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Exit" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 357.5555f, -83.02777f ) );
		}

		MyMenu->setPos( Vector2( 746.03f, -312.8573f ) );

		MyPile->setPos( Vector2( 0, 0 ) );
	}

	void StartMenu::Title3()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Campaign" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -45.05542f, 907.5278f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Arcade" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 89.4444f, 690.5278f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Freeplay" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -17.33331f, 509.6389f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Jukebox" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 49.88898f, 312.0833f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Options" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 112.5558f, 114.5278f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Exit" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 357.5555f, -83.02777f ) );
		}

		MyMenu->setPos( Vector2( -228.97f, -551.7461f ) );

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "TitleScreen" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1799.551f, 1012.248f ) );
		}
		_q = MyPile->FindQuad( _T( "Title" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -25, 88.88889f ) );
			_q->setSize( Vector2( 1690.66f, 950.9964f ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	}

	void StartMenu::SetChildControl( const std::shared_ptr<GUI_Panel> &child )
	{
	}

	void StartMenu::MyPhsxStep()
	{
		MyMenu->Active = !NoBack;

		CkBaseMenu::MyPhsxStep();

		if ( Active )
			ButtonCheck::PreLogIn = true;
	}

	void StartMenu::DoneWithCharSelect()
	{
		MyGame->WaitThenDo( 0, std::make_shared<BringNextMenuLambda>( shared_from_this() ) );
	}

	void StartMenu::BringNextMenu()
	{
		switch ( MyNextMenu )
		{
			case Next_CAMPAIGN:
				BringCampaign();
				break;
			case Next_ARCADE:
				BringArcade();
				break;
			case Next_FREEPLAY:
				BringFreeplay();
				break;
		}
	}

	void StartMenu::BringCampaign()
	{
	}

	void StartMenu::BringArcade()
	{
	}

	void StartMenu::BringFreeplay()
	{
		//Call(new CustomLevel_GUI());
	}

	void StartMenu::OnReturnTo()
	{
		CkBaseMenu::OnReturnTo();
		NoBack = false;
	}

	void StartMenu::InitializeInstanceFields()
	{
		NoBack = false;
	}
}
