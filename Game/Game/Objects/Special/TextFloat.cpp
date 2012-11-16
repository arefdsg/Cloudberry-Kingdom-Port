﻿#include "TextFloat.h"
#include "Core/Text/EzText.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include "Game/Tools/Resources.h"
#include "Properties/Resources.Designer.h"
#include "Game/Tools/Tools.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	TextFloat::TextFloat( Localization::Words Text, Vector2 pos )
	{
		InitializeInstanceFields();
		getCore()->DrawLayer = Level::LastInLevelDrawLayer - 1;

		getCore()->Data.Position = pos;
		getCore()->Data.Velocity = Vector2(0, 8);

		MyText = std::make_shared<EzText>( Text, Resources::Font_Grobold42, 1000, true, true );
		MyText->setScale( .5f );
		MyText->MyFloatColor = ( Color( 228, 0, 69 ) ).ToVector4();
		MyText->OutlineColor = Color::White.ToVector4();

		MyText->ZoomWithCam = true;
	}

	TextFloat::TextFloat( const std::wstring &Text, Vector2 pos )
	{
		InitializeInstanceFields();
		getCore()->DrawLayer = Level::LastInLevelDrawLayer - 1;

		getCore()->Data.Position = pos;
		getCore()->Data.Velocity = Vector2(0, 8);

		MyText = std::make_shared<EzText>( Text, Resources::Font_Grobold42, 1000, true, true );
		MyText->setScale( .5f );
		MyText->MyFloatColor = ( Color( 228, 0, 69 ) ).ToVector4();
		MyText->OutlineColor = Color::White.ToVector4();

		MyText->ZoomWithCam = true;
	}

	void TextFloat::ReleaseBody()
	{
		GameObject::ReleaseBody();

		MyText->Release();
	}

	void TextFloat::MyPhsxStep()
	{
		getCore()->Data.Position += getCore()->Data.Velocity;
		Alpha += AlphaSpeed;

		if ( Alpha <= 0 )
			this->Release();
	}

	void TextFloat::Update()
	{
		MyText->setPos( getCore()->Data.Position );
		MyText->Alpha = Alpha;
	}

	void TextFloat::MyDraw()
	{
		GameObject::MyDraw();

		if ( getCore()->MarkedForDeletion || !getCore()->Active )
			return;

		if ( !getCore()->MyLevel->getMainCamera()->OnScreen(getCore()->Data.Position, 600) )
			return;

		if ( Tools::DrawGraphics )
		{
			Update();
			MyText->Draw( getCore()->MyLevel->getMainCamera() );
		}
	}

	void TextFloat::Move( Vector2 shift )
	{
		getCore()->Data.Position += shift;
	}

	void TextFloat::InitializeInstanceFields()
	{
		Alpha = 4.5f;
		AlphaSpeed = -.08f;
	}
}
