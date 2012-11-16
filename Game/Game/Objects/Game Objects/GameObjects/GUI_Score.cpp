#include "GUI_Score.h"
#include "Game/Player/PlayerData.h"
#include "Game/Tools/Tools.h"
#include "Game/Localization.h"
#include "Core/Text/EzText.h"
#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Text/EzFont.h"
#include "Game/Tools/Resources.h"
#include "Properties/Resources.Designer.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	int GUI_CampaignScore::RunningCampaignScoreLambda::Apply( const std::shared_ptr<PlayerData> &p )
	{
		return p->RunningCampaignScore();
	}

	GUI_CampaignScore::GUI_CampaignScore() : GUI_Score(false)
	{
		PreventRelease = false;
		UpdateAfterLevelFinish = true;
	}

	int GUI_CampaignScore::GetScore()
	{
		int Score = PlayerManager::PlayerSum( std::make_shared<RunningCampaignScoreLambda>() );
		return Score;
	}

	std::wstring GUI_Score::ToString()
	{
		Tools::Warning();
		return Localization::WordString( Localization::Words_SCORE ) + _T( " " ) + StringConverterHelper::toString( GetScore() );
	}

	void GUI_Score::OnAdd()
	{
		GUI_Panel::OnAdd();

		if ( !AddedOnce )
		{
			if ( DoSlideIn )
			{
				SlideOut( PresetPos_TOP, 0 );
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

	void GUI_Score::ReleaseBody()
	{
		GUI_Panel::ReleaseBody();
	}

	int GUI_Score::GetScore()
	{
		return Score;
	}

	void GUI_Score::SetScore( int Score )
	{
		if ( this->Score != Score )
		{
			this->Score = Score;
			UpdateScoreText();
		}
	}

	void GUI_Score::UpdateScoreText()
	{
		ScoreText->SubstituteText( ToString() );
	}

	GUI_Score::GUI_Score()
	{
		InitializeInstanceFields();
		DoInit( false );
	}

	GUI_Score::GUI_Score( bool SlideIn )
	{
		InitializeInstanceFields();
		DoInit( SlideIn );
	}

	void GUI_Score::DoInit( bool SlideIn )
	{
		DoSlideIn = SlideIn;

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		MyPile->setPos( Vector2( 1235, 820 ) );

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

		MyPile->FancyPos->UpdateWithGame = true;

		std::shared_ptr<EzFont> font;
		float scale;
		Color c, o;

			font = Resources::Font_Grobold42;
			scale = .5f;
			c = Color( 228, 0, 69 );
			o = Color::White;

			ScoreText = std::make_shared<EzText>( ToString(), font, 950, false, true );
			ScoreText->setScale( scale );
			ScoreText->setPos( Vector2( 381.4434f, 85.55492f ) );
			ScoreText->MyFloatColor = c.ToVector4();
			ScoreText->OutlineColor = o.ToVector4();

		ScoreText->RightJustify = true;

		MyPile->Add( ScoreText );
	}

	void GUI_Score::MyDraw()
	{
		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints )
			return;

		GUI_Panel::MyDraw();
	}

	void GUI_Score::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( Hid || !Active )
			return;

		if ( getCore()->MyLevel->Watching || (getCore()->MyLevel->Finished && !UpdateAfterLevelFinish) )
			return;

		if ( MyGame->AlwaysGiveCoinScore )
			SetScore( PlayerManager::GetGameScore() );
		else
			SetScore( PlayerManager::GetGameScore_WithTemporary() );
	}

	void GUI_Score::InitializeInstanceFields()
	{
		AddedOnce = false;
		DoSlideIn = true;
		UpdateAfterLevelFinish = false;
	}
}
