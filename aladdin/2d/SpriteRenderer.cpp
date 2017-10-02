/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "SpriteRenderer.h"
#include "Graphics.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::SpriteRenderer, ala::GameObjectComponent )

SpriteRenderer::SpriteRenderer( GameObject* gameObject, Sprite* sprite, const std::string& name )
  : GameObjectComponent( gameObject, name ), _sprite( sprite ),
    _backColor( 255, 255, 255 ) {}

SpriteRenderer::SpriteRenderer( GameObject* gameObject, const std::string& spriteResourceName, const std::string& name )
  : GameObjectComponent( gameObject, name ), _sprite( NULL ),
    _backColor( 255, 255, 255 ) {
  _sprite = static_cast<Sprite*>(GameManager::get()->getResource( spriteResourceName ));
}

SpriteRenderer::~SpriteRenderer() {}

Sprite* SpriteRenderer::getSprite() const {
  return _sprite;
}

void SpriteRenderer::setSprite( Sprite* sprite ) {
  _sprite = sprite;
}

const Color& SpriteRenderer::getBackColor() const {
  return _backColor;
}

void SpriteRenderer::setBackColor( const Color& color ) {
  _backColor = color;
}

Size SpriteRenderer::getFrameSize() const {
  auto frameSize = _sprite->getContentSize();
  const auto transform = getGameObject()->getTransform();
  frameSize.setWidth( frameSize.getWidth() * transform->getScale().getX() );
  frameSize.setHeight( frameSize.getHeight() * transform->getScale().getY() );

  return frameSize;
}

void SpriteRenderer::onRender() {
  auto transform = getGameObject()->getTransform();
  auto frameSize = getFrameSize();

  Rect srcRect;
  srcRect.setTopLeft( Vec2( 0.f, 0.f ) );
  srcRect.setSize( _sprite->getContentSize() );

  // TODO: currently use default origin?
  // Unity's sprite renderer uses (0.5, 0.5) origin
  // Only images with RectTransform which are used mainly for creating UI (score, HP bar, etc...) uses anchor point
  // source rect might needs a little fix after implementing animation
  Graphics::get()->drawSprite( _sprite, Vec2( 0.5f, 0.5f ), transform->getLocalToWorldMatrix(), _backColor, srcRect );
}
}
