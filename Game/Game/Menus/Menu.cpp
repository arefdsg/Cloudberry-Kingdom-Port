#include <small_header.h>
#include "Game/Menus/Menu.h"

#include "Core/FancyVector2.h"
#include "Core/Graphics/Draw/Quads/PieceQuad.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
#include "Core/Input/ButtonCheck.h"
#include "Core/Sound/EzSound.h"
#include "Core/Texture/EzTexture.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Tools/Tools.h"

#include "Core/Text/EzText.h"
#include "Game/Tools/Camera.h"
#include "Game/Games/GameType.h"
#include "Game/Level/Level.h"

#include "Hacks/List.h"
#include "Hacks/Compare.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	// Statics
            Vector4 Menu::DefaultMenuInfo::SelectedNextColor;
			Vector4 Menu::DefaultMenuInfo::UnselectedNextColor;

			Vector4 Menu::DefaultMenuInfo::SelectedBackColor;
            Vector4 Menu::DefaultMenuInfo::UnselectedBackColor;
			
			Vector4 Menu::DefaultMenuInfo::SelectedXColor;
			Vector4 Menu::DefaultMenuInfo::UnselectedXColor;
			
			Vector4 Menu::DefaultMenuInfo::SelectedYColor;
			Vector4 Menu::DefaultMenuInfo::UnselectedYColor;

			void Menu::DefaultMenuInfo::SetNext( boost::shared_ptr<MenuItem> item)
			{
				item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedNextColor;
				item->MyText->OutlineColor = Color::Black.ToVector4();
				item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedNextColor;
				item->MySelectedText->OutlineColor = Color::Black.ToVector4();
			}

			void Menu::DefaultMenuInfo::SetBack( boost::shared_ptr<MenuItem> item)
			{
				item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedBackColor;
				item->MyText->OutlineColor = Color::Black.ToVector4();
				item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
				item->MySelectedText->OutlineColor = Color::Black.ToVector4();
			}

			void Menu::DefaultMenuInfo::SetX( boost::shared_ptr<MenuItem> item)
			{
				item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedXColor;
				item->MyText->OutlineColor = Color::Black.ToVector4();
				item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedXColor;
				item->MySelectedText->OutlineColor = Color::Black.ToVector4();
			}

			void Menu::DefaultMenuInfo::SetY( boost::shared_ptr<MenuItem> item)
			{
				item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedYColor;
				item->MyText->OutlineColor = Color::Black.ToVector4();
				item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedYColor;
				item->MySelectedText->OutlineColor = Color::Black.ToVector4();
			}

	boost::shared_ptr<EzSound> Menu::DefaultMenuInfo::Menu_UpDown_Sound;
	boost::shared_ptr<EzSound> Menu::DefaultMenuInfo::Menu_Select_Sound;
	boost::shared_ptr<EzSound> Menu::DefaultMenuInfo::Menu_Slide_Sound;
	boost::shared_ptr<EzSound> Menu::DefaultMenuInfo::Menu_ListScroll_Sound;
	boost::shared_ptr<EzSound> Menu::DefaultMenuInfo::Menu_Back_Sound;
	int Menu::DefaultMenuInfo::Menu_Slide_SoundDelay;
	boost::shared_ptr<EzTexture> Menu::DefaultMenuInfo::MenuRightArrow_Texture;
	boost::shared_ptr<EzTexture> Menu::DefaultMenuInfo::MenuLeftArrow_Texture;
	Vector2 Menu::DefaultMenuInfo::MenuRightArrow_Offset;
	Vector2 Menu::DefaultMenuInfo::MenuLeftArrow_Offset;
	Vector2 Menu::DefaultMenuInfo::MenuArrow_Size;
	Vector4 Menu::DefaultMenuInfo::MenuArrow_Color;
	boost::shared_ptr<EzTexture> Menu::DefaultMenuInfo::MenuRightArrow_Selected_Texture;
	boost::shared_ptr<EzTexture> Menu::DefaultMenuInfo::MenuLeftArrow_Selected_Texture;
	Vector2 Menu::DefaultMenuInfo::MenuRightArrow_Selected_Offset;
	Vector2 Menu::DefaultMenuInfo::MenuLeftArrow_Selected_Offset;
	Vector2 Menu::DefaultMenuInfo::MenuArrow_Selected_Size;
	Vector4 Menu::DefaultMenuInfo::MenuArrow_Selected_Color;
	boost::shared_ptr<EzTexture> Menu::DefaultMenuInfo::SliderBack_Texture;
	Vector2 Menu::DefaultMenuInfo::SliderBack_Size;
	boost::shared_ptr<EzTexture> Menu::DefaultMenuInfo::Slider_Texture;
	Vector2 Menu::DefaultMenuInfo::Slider_StartPos;
	Vector2 Menu::DefaultMenuInfo::Slider_EndPos;
	Vector2 Menu::DefaultMenuInfo::Slider_Size;

	Cast::ToMenuHelper1::ToMenuHelper1( const boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > &a )
	{
		this->a = a;
	}

	bool Cast::ToMenuHelper1::Apply( const boost::shared_ptr<Menu> &dummy )
	{
		a->Apply( 0 );
		return true;
	}

	Cast::LambdaWrapper::LambdaWrapper( const boost::shared_ptr<Lambda> &a )
	{
		this->a = a;
	}

	void Cast::LambdaWrapper::Apply( const boost::shared_ptr<MenuItem> &dummy )
	{
		a->Apply();
	}

	Cast::Lambda_1Wrapper::Lambda_1Wrapper( const boost::shared_ptr<Lambda_1<boost::shared_ptr<Menu> > > &a )
	{
		this->a = a;
	}

	void Cast::Lambda_1Wrapper::Apply()
	{
		a->Apply( 0 );
	}

	Cast::Lambda_1Wrapper_MenuItem::Lambda_1Wrapper_MenuItem( const boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > &a )
	{
		this->a = a;
	}

	void Cast::Lambda_1Wrapper_MenuItem::Apply()
	{
		a->Apply( 0 );
	}

	Cast::ToMenuHelper::ToMenuHelper( const boost::shared_ptr<Lambda> &a )
	{
		this->a = a;
	}

	bool Cast::ToMenuHelper::Apply( const boost::shared_ptr<Menu> &dummy )
	{
		a->Apply();
		return true;
	}

	boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Menu> , bool> > Cast::ToMenu( const boost::shared_ptr<Lambda> &a )
	{
		return boost::make_shared<ToMenuHelper>( a );
	}

	boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Menu> , bool> > Cast::ToMenu( const boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > &a )
	{
		return boost::make_shared<ToMenuHelper1>( a );
	}

	boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > Cast::ToItem( const boost::shared_ptr<Lambda> &a )
	{
		return boost::make_shared<LambdaWrapper>( a );
	}

	boost::shared_ptr<Lambda> Cast::ToAction( const boost::shared_ptr<Lambda_1<boost::shared_ptr<Menu> > > &a )
	{
		return boost::make_shared<Lambda_1Wrapper>( a );
	}

	boost::shared_ptr<Lambda> Cast::ToAction( const boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > &a )
	{
		return boost::make_shared<Lambda_1Wrapper_MenuItem>( a );
	}

	Menu::FindItemByNameLambda::FindItemByNameLambda( const std::wstring &name )
	{
		this->name = name;
	}

	bool Menu::FindItemByNameLambda::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		return item->Name == name;
	}

	bool Menu::DefaultOnBProxy::Apply( const boost::shared_ptr<Menu> &menu )
	{
		return Menu::DefaultOnB( menu );
	}

	boost::shared_ptr<MenuItem> Menu::FindItemByName( const std::wstring &name )
	{
		return Tools::Find<boost::shared_ptr<MenuItem> >( Items, boost::make_shared<FindItemByNameLambda>( name ) );
	}

	const Vector2 &Menu::getPos() const
	{
		return FancyPos->RelVal;
	}

	void Menu::setPos( const Vector2 &value )
	{
		FancyPos->RelVal = value;
	}

	const int &Menu::getControl() const
	{
		return _Control;
	}

	void Menu::setControl( const int &value )
	{
		_Control = value;
	}

	const boost::shared_ptr<MenuItem> Menu::getCurItem() const
	{
		if ( Items.empty() )
			return 0;

		return Items[ CurIndex ];
	}

	void Menu::Release()
	{
		Release( true );
	}

	void Menu::Release( bool ReleaseParents )
	{
		if ( Released )
			return;
		Released = true;

		if ( SelectIcon != 0 ) SelectIcon->Release(); SelectIcon.reset();
		if ( FancyPos != 0 ) FancyPos->Release(); FancyPos.reset();

		if ( ReleaseParents && ParentMenu != 0 ) ParentMenu->Release( true ); ParentMenu.reset();

		if ( Items.size() > 0 )
			for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = Items.begin(); item != Items.end(); ++item )
				( *item )->Release();
		Items.clear();

		OnStart.reset(); OnX.reset(); OnA.reset(); OnB.reset();
		OnSelect.reset(); OnY.reset();

		UpDownSound.reset(); SelectSound.reset(); BackSound.reset(); SlideSound.reset(); ListScrollSound.reset();
		MyPieceQuad.reset(); MyPieceQuadTemplate.reset();
		MyPieceQuad2.reset(); MyPieceQuadTemplate2.reset();

		AdditionalCheckForOutsideClick.reset();
	}

	void Menu::ClearList()
	{
		if ( Items.size() > 0 )
			for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = Items.begin(); item != Items.end(); ++item )
				( *item )->Release();
		Items.clear();
	}

	Menu::Menu()
	{
		InitializeInstanceFields();
		Init();
	}

	Menu::Menu( bool FixedToCamera )
	{
		InitializeInstanceFields();
		Init();
		this->FixedToCamera = FixedToCamera;
	}

	void Menu::Init()
	{
		UpDownSound = DefaultMenuInfo::Menu_UpDown_Sound;
		SelectSound = DefaultMenuInfo::Menu_Select_Sound;
		BackSound = DefaultMenuInfo::Menu_Back_Sound;
		SlideSound = DefaultMenuInfo::Menu_Slide_Sound;
		ListScrollSound = DefaultMenuInfo::Menu_ListScroll_Sound;

		SkipPhsx = true;

		setControl( -1 );

		Items = std::vector<boost::shared_ptr<MenuItem> >();
		CurIndex = 0;

		OnB = boost::make_shared<DefaultOnBProxy>();

		MyPieceQuadTemplate.reset();
		MyPieceQuadTemplate2.reset();
	}

	bool Menu::DefaultOnB( const boost::shared_ptr<Menu> &menu )
	{
		menu->Release( false );

		return true;
	}

	void Menu::SelectItem( const boost::shared_ptr<MenuItem> &item )
	{
		HasSelectedThisStep = true;

		int Index = IndexOf( Items, item );
		if ( CurIndex != Index )
		{
			SelectItem( Index );
		}
	}

	void Menu::SelectItem( int Index )
	{
		HasSelectedThisStep = true;

		// If no items are selectable, return
		bool All = true;
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = Items.begin(); item != Items.end(); ++item )
			if ( ( *item )->Selectable )
				All = false;
		if ( All )
			return;

		// Play a selection sound
		if ( UpDownSound != 0 && ReadyToPlaySound )
			UpDownSound->Play();

//C# TO C++ CONVERTER NOTE: The variable Sign was renamed since it is named the same as a user-defined type:
		int Sign_Renamed = ::Sign( Index - CurIndex );
		if ( Sign_Renamed == 0 )
			Sign_Renamed = 1;

		// Ensure a valid index
		if ( WrapSelect )
		{
			if ( Index < 0 )
			{
				CurIndex = Index = Items.size() - 1;
			}
			if ( Index >= static_cast<int>( Items.size() ) )
			{
				CurIndex = Index = 0;
			}
		}
		else
			Index = __max( 0, __min( static_cast<int>( Items.size() ) - 1, Index ) );


		if ( Items[ Index ]->Selectable && Items[ Index ]->Show )
			CurIndex = Index;
		else
		{
			// Find the next selectable index
			while ( !Items[ Index ]->Selectable || !Items[ Index ]->Show )
			{
				//if (Index > CurIndex) Index++;
				//else if (Index < CurIndex) Index--;
				//else Index++;

				Index += Sign_Renamed;

				if ( WrapSelect )
				{
					if ( Index < 0 )
						Index = Items.size() - 1;
					if ( Index >= static_cast<int>( Items.size() ) )
						Index = 0;
				}
				else
				{
					if ( Index < 0 ) // Index = 0; CurIndex = 0; }
					{
						Index = CurIndex;
						break;
					}
					if ( Index >= static_cast<int>( Items.size() ) ) // Index = Items.Count; CurIndex = Items.Count + 1; }
					{
						Index = CurIndex;
						break;
					}
				}
			}

			CurIndex = Index;
		}

		if ( OnSelect != 0 )
			OnSelect->Apply();

		SkipPhsx = true;
	}

	bool Menu::CheckForBackFromOutsideClick()
	{
	#if defined(PC_VERSION)
		bool Hit = HitTest();

		if ( !Hit && AdditionalCheckForOutsideClick != 0 )
			Hit |= AdditionalCheckForOutsideClick->Apply();

		// Update the mouse icon to reflect whether clicking will go back or not
		Tools::TheGame->setDrawMouseBackIcon( !Hit );

		return !Hit;
	#else
		return false;
	#endif
	}

#if defined(PC_VERSION)
	bool Menu::HitTest()
	{
		return HitTest( Vector2( 100, 100 ) );
	}
#endif

#if defined(PC_VERSION)
	bool Menu::HitTest( Vector2 HitPadding )
	{
		Vector2 MousePos = Tools::MouseGUIPos( getMyCameraZoom() );

		bool Hit = false;
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = Items.begin(); item != Items.end(); ++item )
			Hit |= ( *item )->HitTest( MousePos, HitPadding );

		return Hit;
	}
#endif

	void Menu::PhsxStep()
	{
		if ( !Active || !Show )
			return;

		if ( CloudberryKingdomGame::getSuperPause() ) return;

		if ( SkipPhsx )
		{
			SkipPhsx = false;
			return;
		}

		if ( Tools::TheGame->DrawCount - ActiveTimeStamp > 5 )
		{
			SkipPhsx = true;
			ActiveTimeStamp = Tools::TheGame->DrawCount;
			return;
		}
		ActiveTimeStamp = Tools::TheGame->DrawCount;

	#if defined(PC_VERSION)
		// Show the mouse 
		Tools::TheGame->ShowMouse = true;

		// If mouse is in use check to see if anything should be selected
		if ( ButtonCheck::MouseInUse )
		{
			/*
			if (Tools::MouseDown())
			    NoneSelected = false;
			else*/
		{
				// MUST BE POSITIVE
				Vector2 HitPadding = Vector2( 100, 0 );

				// If we are checking whether to start showing selections again,
				// only do so if we actually hit a MenuItem
				if ( NoneSelected )
					HitPadding = Vector2();

				if ( !HitTest( HitPadding ) )
					NoneSelected = true;
				else
					NoneSelected = false;
			}
		}
		else
		{
			// If the mouse isn't in use and the menu is capable of using the keyboard,
			// then start behaving as if the keyboard is the main input device and no mouse exists
			if ( !MouseOnly )
				NoneSelected = false;
		}
	#endif 

		// Start button action
		if ( OnStart != 0 && ButtonCheck::State( ControllerButtons_START, getControl() ).Pressed )
		{
			ButtonCheck::PreventInput();
			OnStart->Apply( shared_from_this() );
		}

		// X button action
		if ( OnX != 0 )
		{
            ButtonData data = ButtonCheck::State( ControllerButtons_X, getControl() );
            if ( data.Pressed )
            {
                MenuItem::ActivatingPlayer = data.PressingPlayer;

				ButtonCheck::PreventInput();
				OnX->Apply( shared_from_this() );
			}
		}

		// Y button action
		if ( OnY != 0 )
		{
            ButtonData data = ButtonCheck::State( ControllerButtons_Y, getControl() );
            if (data.Pressed)
            {
				MenuItem::ActivatingPlayer = data.PressingPlayer;

				ButtonCheck::PreventInput();
				OnY->Apply();
			}
		}

		// Allow for a new item to be selected if the user has stopped holding down A (or LeftMouseButton)
		if ( !ButtonCheck::State( ControllerButtons_A, getControl() ).Pressed )
			HasSelectedThisStep = false;

		if ( OnA_AutoTimerLength > 0 && OnA_AutoTimerCount > 0 )
		{
			OnA_AutoTimerCount--;
			if ( OnA_AutoTimerCount == 0 )
				if ( OnA != 0 )
					if ( OnA->Apply( shared_from_this() ) )
						return;
		}

		bool ActivateOnA = false;
		ButtonData _data = ButtonCheck::State( ControllerButtons_A, getControl() );
		if ( _data.Pressed )
		{
			MenuItem::ActivatingPlayer = _data.PressingPlayer;
			ActivateOnA = true;
		}

		// Don't activate the item if it isn't being drawn as selected
		//if (NoneSelected)
		//    ActivateOnA = false;

	#if defined(WINDOWS)
		if ( !Tools::MouseNotDown() )
			ActivateOnA = false;
	#endif
		// A button
		if ( ActivateOnA )
		{
			bool CheckForOverride = true;
	#if defined(PC_VERSION)
			if ( ButtonCheck::State( ButtonCheck::Go_Secondary ).Pressed )
				CheckForOverride = false;
	#endif
			if ( OnA != 0 && !( CheckForOverride && Items[ CurIndex ]->getOverrideA() ) )
			{
				//ButtonCheck.PreventInput();
				if ( OnA->Apply( shared_from_this() ) )
					return;
			}
		}

		if ( SkipPhsx )
		{
			return;
		}

		// Click outside the menu to go back
		bool ClickBack = false;

	#if defined(PC_VERSION)
		if ( CheckForOutsideClick && NoneSelected && ButtonCheck::MouseInUse && Tools::MouseReleased() )
			if ( outside )
				ClickBack = true;
		if ( !Tools::CurMouseDown() )
		{
			if ( CheckForOutsideClick && OnB != 0 )
				outside = CheckForBackFromOutsideClick();
			else
			{
				outside = false;
				if ( AffectsOutsideMouse )
					Tools::TheGame->setDrawMouseBackIcon( false );
			}
		}

		if ( Tools::RightMouseReleased() )
			ClickBack = true;
	#endif
		// B button
		if ( ButtonCheck::State( ControllerButtons_B, getControl() ).Pressed || ClickBack )
		{
			if ( OnB != 0 )
			{
				if ( BackSound != 0 )
					BackSound->Play();

				if ( OnB->Apply( shared_from_this() ) )
					return;

				ButtonCheck::PreventInput();
			}
		}

		if ( SkipPhsx )
		{
			return;
		}

		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = Items.begin(); item != Items.end(); ++item )
		{
			( *item )->PhsxStep( *item == Items[ CurIndex ] && ( !NoneSelected || AlwaysSelected ) );
			if ( Released )
				return;
		}

	#if defined(PC_VERSION)
		// If the mouse is in use and nothing is selected, then hitting a key on the keyboard
		// should only hide the mouse, it shouldn't immediately change what is selected
		if ( ButtonCheck::MouseInUse )
		{
			if ( NoneSelected )
				DelayCount = SelectDelay;
			else
				DelayCount = 0;
		}
	#endif

		// If the menu can use the keyboard then check for index changes by the arrow keys
	#if defined(PC_VERSION)
		if ( !MouseOnly && !ButtonCheck::PrevMouseInUse )
	#else
		if ( !MouseOnly )
	#endif
		{
			if ( DelayCount > 0 )
				DelayCount--;

			Vector2 Dir = Vector2();
			if ( getControl() < 0 )
			{
				Dir = ButtonCheck::GetMaxDir( getControl() == -1 );
			}
			else
				Dir = ButtonCheck::GetDir( getControl() );

			if ( Dir.Length() < .2f )
				DelayCount = 0;

			if ( fabs( Dir.Y ) > ButtonCheck::ThresholdSensitivity )
			{
				MotionCount++;
				if ( DelayCount <= 0 )
				{
					if ( Dir.Y > 0 )
						SelectItem( CurIndex - 1 );
					else
						SelectItem( CurIndex + 1 );

					DelayCount = SelectDelay;
					if ( MotionCount > SelectDelay * 2 )
						DelayCount /= 2;
				}
			}
			else
				MotionCount = 0;
		}

		ReadyToPlaySound = true;
	}

	void Menu::ArrangeItems( float Spacing, Vector2 Center )
	{
		Vector2 Pos = Center;
		for ( int i = 0; i < static_cast<int>( Items.size() ); i++ )
		{
			Pos.Y -= Spacing + Items[ i ]->Height() / 2;

			Items[ i ]->Pos = Pos;

			Pos.Y -= Spacing + Items[ i ]->Height() / 2;
		}

		float Height = Center.Y - Pos.Y;
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = Items.begin(); item != Items.end(); ++item )
			( *item )->Pos.Y += Height / 2;
	}

	void Menu::SetBoundary()
	{
		SetBoundary( Vector2( 110, 84 ), Vector2( 110, 84 ) );
	}

	void Menu::SetBoundary( Vector2 Padding )
	{
		SetBoundary( Padding, Padding );
	}

	void Menu::SetBoundary( Vector2 TR_Padding, Vector2 BL_Padding )
	{
		CalcBounds();

		TR += TR_Padding;
		BL -= BL_Padding;

		ResetPieces();
	}

	void Menu::CalcBounds()
	{
		TR = Vector2( -100000, -100000 );
		BL = Vector2( 100000, 100000 );

		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = Items.begin(); item != Items.end(); ++item )
		{
			Vector2 Size = ( *item )->Size();
			TR = Vector2::Max( TR, ( *item )->Pos + Size / 2 );
			BL = Vector2::Min( BL, ( *item )->Pos - Size / 2 );
		}
	}

	int Menu::SortByHeightMethod( const boost::shared_ptr<MenuItem> &item1, const boost::shared_ptr<MenuItem> &item2 )
	{
		return Compare( item2->Pos.Y, item1->Pos.Y );
	}

	void Menu::SortByHeight()
	{
		Sort( Items, SortByHeightMethod );
	}

	void Menu::ResetPieces()
	{
		MyPieceQuad = boost::make_shared<PieceQuad>();
		MyPieceQuad->Clone( MyPieceQuadTemplate );
		MyPieceQuad->CalcQuads( ( TR - BL ) / 2 );
		BackdropShift = ( TR + BL ) / 2;

		if ( MyPieceQuadTemplate2 != 0 )
		{
			MyPieceQuad2 = boost::make_shared<PieceQuad>();
			MyPieceQuad2->Clone( MyPieceQuadTemplate2 );
			MyPieceQuad2->CalcQuads( ( TR - BL ) / 2 );
		}
	}

	void Menu::DrawNonText( int Layer )
	{
        if ( Items.size() == 0 ) return;

		setMyCameraZoom( Tools::getCurCamera()->getZoom() );
		if ( !Show )
			return;

		if ( FancyPos != 0 )
			PosOffset = FancyPos->Update();

		if ( MyPieceQuad != 0 && Layer == 0 )
		{
			if ( FixedToCamera )
				MyPieceQuad->Base.Origin = Tools::CurGameData->MyLevel->getMainCamera()->Data.Position + BackdropShift + PosOffset;
			else
				MyPieceQuad->Base.Origin = BackdropShift + PosOffset;
			MyPieceQuad->Draw();
		}

		CurDrawLayer = Layer;

		int SelectedIndex = getApparentCurIndex();

		// Draw item text backdrops
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = Items.begin(); item != Items.end(); ++item )
		{
			( *item )->PosOffset = PosOffset;
			if ( SelectedIndex < 0 || ( *item ).get() != Items[ SelectedIndex ].get() )
				( *item )->DrawBackdrop( false );
		}
		if ( SelectedIndex >= 0 && Items.size() > 0 )
			Items[ SelectedIndex ]->DrawBackdrop( true );

		// Draw item non-text
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = Items.begin(); item != Items.end(); ++item )
		{
			( *item )->PosOffset = PosOffset;
			( *item )->Draw( false, Tools::CurLevel->getMainCamera(), DrawItemAsSelected(*item) );
		}

		if ( MyPieceQuadTemplate2 != 0 )
		{
			MyPieceQuad2->Base.Origin = Tools::CurLevel->getMainCamera()->Data.Position + BackdropShift + PosOffset;
			MyPieceQuad2->Draw();
		}
	}

	void Menu::DrawNonText2()
	{
		if ( Items.size() == 0 ) return;

		setMyCameraZoom( Tools::getCurCamera()->getZoom() );
		if ( !Show )
			return;

		CurDrawLayer = 1;
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = Items.begin(); item != Items.end(); ++item )
		{
			( *item )->Draw( false, Tools::CurLevel->getMainCamera(), DrawItemAsSelected(*item) );
		}

		// Draw select icon
		if ( SelectIcon != 0 && getApparentCurIndex() >= 0 )
		{
			SelectIcon->setPos( Items[ getApparentCurIndex() ]->Pos + Items[ getApparentCurIndex() ]->PosOffset + Items[ getApparentCurIndex() ]->SelectIconOffset );
			if ( FixedToCamera )
				SelectIcon->setPos( SelectIcon->getPos() + Tools::CurLevel->getMainCamera()->Data.Position );
			SelectIcon->Draw();
		}
	}

	void Menu::DrawText( int Layer )
	{
		setMyCameraZoom( Tools::getCurCamera()->getZoom() );
		if ( !Show )
			return;

		CurDrawLayer = Layer;

		// Draw item text
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = Items.begin(); item != Items.end(); ++item )
		{
			( *item )->PosOffset = PosOffset;
			if ( ( *item )->UnaffectedByScroll )
				( *item )->PosOffset -= FancyPos->RelVal;

			( *item )->Draw( true, Tools::CurLevel->getMainCamera(), DrawItemAsSelected(*item) );
		}
	}

	bool Menu::DrawItemAsSelected( const boost::shared_ptr<MenuItem> &item )
	{
	#if defined(PC_VERSION)
	#else
		// Never draw anything as selected if the menu is mouse only and there is no mouse
		if ( MouseOnly )
			return false;
	#endif

		if ( !NoneSelected || AlwaysSelected )
			return item == Items[ CurIndex ];
		else if ( ShowLastActivated && LastActivatedItem >= 0 )
			return item == Items[ LastActivatedItem ];
		else
			return false;
	}

	const int Menu::getApparentCurIndex() const
	{
		if ( !NoneSelected )
			return CurIndex;
		else if ( ShowLastActivated && LastActivatedItem >= 0 )
			return LastActivatedItem;
		else
			return -1;
	}

	const Vector2 &Menu::getMyCameraZoom() const
	{
		return _MyCameraZoom;
	}

	void Menu::setMyCameraZoom( const Vector2 &value )
	{
		_MyCameraZoom = value;
	}

	void Menu::Draw()
	{
		setMyCameraZoom( Tools::getCurCamera()->getZoom() );

		if ( !Show || Items.size() == 0 )
			return;

		DrawNonText( 0 );
		DrawText( 0 );
		Tools::Render->EndSpriteBatch();
		DrawNonText2();
		DrawText( 1 );
	}

	void Menu::Add( const boost::shared_ptr<MenuItem> &item )
	{
		Add( item, Items.size() );
	}

	void Menu::Add( const boost::shared_ptr<MenuItem> &item, int index )
	{
		item->SelectSound = SelectSound;
		item->SlideSound = SlideSound;
		item->ListScrollSound = ListScrollSound;

		item->MyMenu = shared_from_this();
		item->setFixedToCamera( FixedToCamera );
		item->Control = getControl();
		Insert( Items, index, item );
	}

	void Menu::InitializeInstanceFields()
	{
		Layer = 0;
		FixedToCamera = true;
		ReadyToPlaySound = false;
		SkipPhsx = false;
		_Control = 0;
		CurIndex = 0;
		SelectDelay = 11;
		DelayCount = 0;
		MotionCount = 0;
		CurDrawLayer = 0;
		OnA_AutoTimerLength = -1;
		OnA_AutoTimerCount = 0;
		Released = false;
		HasSelectedThisStep = false;
		WrapSelect = true;
		MouseOnly = false;
		SlipSelect = false;
		NoneSelected = false;
		AlwaysSelected = false;
		ShowLastActivated = false;
		LastActivatedItem = -1;
		ActiveTimeStamp = 0;
		Active = true;
		CheckForOutsideClick = false;
		AffectsOutsideMouse = true;
		outside = false;
		_MyCameraZoom = Vector2(1);
		Show = true;
	}
}
