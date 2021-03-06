#include <small_header.h>
#include "Game/Tilesets/SpriteInfo.h"

#include "Core/Texture/TextureOrAnim.h"
#include "Core/Texture/EzTexture.h"

namespace CloudberryKingdom
{

	LineSpriteInfo::LineSpriteInfo( const boost::shared_ptr<TextureOrAnim> &End1, const boost::shared_ptr<TextureOrAnim> &Body, const boost::shared_ptr<TextureOrAnim> &End2, float Width )
	{
		InitializeInstanceFields();
		DrawEndPoints = true;
		this->End1 = End1;
		this->End2 = End2;
		this->Sprite = Body;

		this->Width = Width;
		this->RepeatWidth = Width * static_cast<float>( Body->MyTexture->Height ) / static_cast<float>( Body->MyTexture->Width );

		this->Dir = 0;
		this->Tint = Vector4( 1 );
		this->BlendAddRatio = 0;
	}

	LineSpriteInfo::LineSpriteInfo( const boost::shared_ptr<TextureOrAnim> &Sprite, float Width, float RepeatWidth )
	{
		InitializeInstanceFields();
		this->Sprite = Sprite;
		this->Width = Width;
		this->RepeatWidth = RepeatWidth;
		this->Dir = 0;
		this->Tint = Vector4( 1 );
		this->BlendAddRatio = 0;
	}

	LineSpriteInfo::LineSpriteInfo( const boost::shared_ptr<TextureOrAnim> &Sprite, float Width, float RepeatWidth, int Dir, Vector4 Tint )
	{
		InitializeInstanceFields();
		this->Sprite = Sprite;
		this->Width = Width;
		this->RepeatWidth = RepeatWidth;
		this->Dir = Dir;
		this->Tint = Tint;
		this->BlendAddRatio = 0;
	}

	LineSpriteInfo::LineSpriteInfo( const boost::shared_ptr<TextureOrAnim> &Sprite, float Width, float RepeatWidth, int Dir, Vector4 Tint, float BlendAddRatio )
	{
		InitializeInstanceFields();
		this->Sprite = Sprite;
		this->Width = Width;
		this->RepeatWidth = RepeatWidth;
		this->Dir = Dir;
		this->Tint = Tint;
		this->BlendAddRatio = BlendAddRatio;
	}

	void LineSpriteInfo::InitializeInstanceFields()
	{
		Wrap = false;
		DrawEndPoints = false;
	}

	SpriteInfo::SpriteInfo( const boost::shared_ptr<TextureOrAnim> &Sprite )
	{
		InitializeInstanceFields();
		this->Sprite = Sprite;
		this->Size = Vector2(1);
		this->Offset = Vector2();
		this->Tint = Color::White;
		this->RelativeOffset = false;
	}

	SpriteInfo::SpriteInfo( const boost::shared_ptr<TextureOrAnim> &Sprite, Vector2 Size )
	{
		InitializeInstanceFields();
		this->Sprite = Sprite;
		this->Size = Size;
		this->Offset = Vector2();
		this->Tint = Color::White;
		this->RelativeOffset = false;
	}

	SpriteInfo::SpriteInfo( const boost::shared_ptr<TextureOrAnim> &Sprite, Vector2 Size, Vector2 Offset, Color Tint )
	{
		InitializeInstanceFields();
		this->Sprite = Sprite;
		this->Size = Size;
		this->Offset = Offset;
		this->Tint = Tint;
		this->RelativeOffset = false;
	}

	SpriteInfo::SpriteInfo( const boost::shared_ptr<TextureOrAnim> &Sprite, Vector2 Size, Vector2 Offset, Color Tint, bool RelativeOffset )
	{
		InitializeInstanceFields();
		this->Sprite = Sprite;
		this->Size = Size;
		this->Offset = Offset;
		this->Tint = Tint;
		this->RelativeOffset = RelativeOffset;
	}

	void SpriteInfo::InitializeInstanceFields()
	{
		Degrees = 0;
		ColorMatrix = Matrix::Identity();
	}
}
