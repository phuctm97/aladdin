/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "SpriteRenderer.h"
#include "Graphics.h"
#include "Animator.h"
#include "MessageArgRect.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::SpriteRenderer, ala::GameObjectComponent )

SpriteRenderer::SpriteRenderer( GameObject* gameObject, Sprite* sprite, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _sprite( sprite ),
    _backColor( 255, 255, 255 ),
    _zOrder( 0 )
{
  auto animator = getGameObject()->getComponentT<Animator>();

  if (animator == NULL || !animator->isInitialized())
  {
    _srcRect.setTopLeft(Vec2(0.f, 0.f));
    _srcRect.setSize(_sprite->getContentSize());
  }
  else
  {
    _srcRect = animator->getCurrentFrame();
  }

  subscribeObjectMessage(getGameObject(), SOURCE_RECT_CHANGE_MESSAGE, [&](MessageArgs* message)
  {
    _srcRect = static_cast < MessageArgRect* > (message)->getRect();
  });
}

SpriteRenderer::SpriteRenderer( GameObject* gameObject, const std::string& spriteResourceName, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _sprite( NULL ),
    _backColor( 255, 255, 255 ),
    _zOrder( 0 ) {
  _sprite = static_cast<Sprite*>(GameManager::get()->getResource( spriteResourceName ));
  auto animator = getGameObject()->getComponentT<Animator>();

  if (animator == NULL || !animator->isInitialized())
  {
    _srcRect.setTopLeft(Vec2(0.f, 0.f));
    _srcRect.setSize(_sprite->getContentSize());
  }
  else
  {
    _srcRect = animator->getCurrentFrame();
  }

  subscribeObjectMessage(getGameObject(), SOURCE_RECT_CHANGE_MESSAGE, [&](MessageArgs* message)
  {
    _srcRect = static_cast < MessageArgRect* > (message)->getRect();
  });
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
  const auto transform = getGameObject()->getTransform();

  return Size(_srcRect.getSize().getWidth() * transform->getScale().getX(), 
    _srcRect.getSize().getHeight() * transform->getScale().getY());
}

void SpriteRenderer::setZOrder( const int zOrder ) {
  _zOrder = zOrder;
}

int SpriteRenderer::getZOrder() const {
  return _zOrder;
}

void SpriteRenderer::onInitialize ( )
{
}

void SpriteRenderer::onRender() {
  auto transform = getGameObject()->getTransform();

  Graphics::get()->drawSprite( _sprite, Vec2( 0.5f, 0.5f ), transform->getLocalToWorldMatrix(), _backColor, _srcRect, _zOrder );
}

void SpriteRenderer::onRelease ( )
{
  unsubcribeObjectMessage(getGameObject(), SOURCE_RECT_CHANGE_MESSAGE);
}
}
