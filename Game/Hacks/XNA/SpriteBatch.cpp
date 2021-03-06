#include "SpriteBatch.h"

#include <Core.h>
#include <Graphics\TextDrawer.h>
#include <Hacks\String.h>

#include <Hacks\XNA\SpriteFont.h>

struct SpriteBatchInternal
{
};

SpriteBatch::SpriteBatch()
{
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::DrawString( const boost::shared_ptr<SpriteFont> &font, const std::wstring &str, const Vector2 &loc, const Color &c, float rotation, const Vector2 &origin, const Vector2 &scale, SpriteEffects se, float depth )
{
	TEXT_DRAWER->Draw( font->font_, font->fontTexture_, WstringToUtf8( str ), loc, c.ToVector4(), scale * ( 1000.f / 360.f ) );
}

void SpriteBatch::Draw( const boost::shared_ptr<struct Texture2D> &texture, const Vector2 &position, Rectangle *rect, const Color &c, float rotation, const Vector2 &origin, const Vector2 &scale, SpriteEffects se, float depth )
{
}

void SpriteBatch::Begin( SpriteSortMode ssm, GfxBlendState bs, GfxSamplerState ss, GfxDepthStencilState dss, GfxRasterizerState rs, const boost::shared_ptr<Effect> &effect, const Matrix &transform )
{
}

void SpriteBatch::End()
{
}