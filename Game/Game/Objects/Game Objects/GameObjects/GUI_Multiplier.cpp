#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/GUI_Multiplier.h"

#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Text/EzFont.h"
#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Tools/Resources.h"

#include "Game/Level/Level.h"
#include "Game/Games/GameType.h"

namespace CloudberryKingdom
{

	std::wstring GUI_Multiplier::ToString()
	{
		return std::wstring( L"x" ) + StringConverterHelper::toString( GetMultiplier() );
	}

	void GUI_Multiplier::OnAdd()
	{
		GUI_Panel::OnAdd();

		if ( !AddedOnce )
		{
			if ( DoSlideIn )
			{
				SlideOut( PresetPos_RIGHT, 0 );
				SlideIn();
				Show();
			}
			else
			{
				SlideIn( 0 );
				Show();
			}
		}

		AddedOnce = true;
	}

	void GUI_Multiplier::ReleaseBody()
	{
		GUI_Panel::ReleaseBody();
	}

	int GUI_Multiplier::GetMultiplier()
	{
		return Multiplier;
	}

	void GUI_Multiplier::SetMultiplier( int Multiplier )
	{
		if ( this->Multiplier != Multiplier )
		{
			this->Multiplier = Multiplier;
			UpdateMultiplierText();
		}
	}

	void GUI_Multiplier::UpdateMultiplierText()
	{
		MultiplierText->SubstituteText( ToString() );
	}

	GUI_Multiplier::GUI_Multiplier( int Style ) :
		AddedOnce( false ),
		Multiplier( 0 ),
		DoSlideIn( false )
	{
	}
	boost::shared_ptr<GUI_Multiplier> GUI_Multiplier::GUI_Multiplier_Construct( int Style )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		DoInit( Style, false );

		return boost::static_pointer_cast<GUI_Multiplier>( shared_from_this() );
	}

	GUI_Multiplier::GUI_Multiplier( int Style, bool SlideIn ) :
		AddedOnce( false ),
		Multiplier( 0 ),
		DoSlideIn( false )
	{
	}
	boost::shared_ptr<GUI_Multiplier> GUI_Multiplier::GUI_Multiplier_Construct( int Style, bool SlideIn )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		DoInit( Style, SlideIn );

		return boost::static_pointer_cast<GUI_Multiplier>( shared_from_this() );
	}

	void GUI_Multiplier::DoInit( int Style, bool SlideIn )
	{
		DoSlideIn = SlideIn;

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();

		MyPile->setPos( Vector2( 1235, 820 ) );

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

		MyPile->FancyPos->UpdateWithGame = true;

		boost::shared_ptr<EzFont> font;
		float scale;
		Color c, o;

		if ( false )
		{
			font = Resources::Font_Grobold42;
			scale = .5f;
			c = Color::White;
			o = Color::Black;
		}
		else
		{
			font = Resources::Font_Grobold42;
			scale = .5f;
			c = bColor( 228, 0, 69 );
			o = Color::White;
		}

		if ( Style == 0 )
		{
			MultiplierText = boost::make_shared<EzText>( ToString(), Resources::Font_Grobold42, 950.f, false, true );
			MultiplierText->setScale( .95f );
			MultiplierText->setPos( Vector2( 187, 130 ) );
			MultiplierText->MyFloatColor = ( bColor( 255, 255, 255 ) ).ToVector4();
		}
		else if ( Style == 1 )
		{
			MultiplierText = boost::make_shared<EzText>( ToString(), font, 950.f, false, true );
			MultiplierText->setScale( scale );
			MultiplierText->setPos( Vector2( 381.4434f, 85.55492f ) );
			MultiplierText->MyFloatColor = c.ToVector4();
			MultiplierText->OutlineColor = o.ToVector4();
		}

		MultiplierText->RightJustify = true;

		MyPile->Add( MultiplierText );
	}

	void GUI_Multiplier::MyDraw()
	{
		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints )
			return;

		GUI_Panel::MyDraw();
	}

	void GUI_Multiplier::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		//this.MultiplierText.MyFloatColor = new Color(100, 100, 200).ToVector4();

		if ( Hid || !Active )
			return;

		if ( getCore()->MyLevel->Watching || getCore()->MyLevel->Finished )
			return;

		SetMultiplier( static_cast<int>( MyGame->ScoreMultiplier + .1f ) );
	}

	void GUI_Multiplier::InitializeInstanceFields()
	{
		AddedOnce = false;
		DoSlideIn = true;
	}
}
