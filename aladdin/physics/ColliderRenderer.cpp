#include "ColliderRenderer.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::ColliderRenderer, ala::GameObjectComponent)

ColliderRenderer::ColliderRenderer( ala::Collider* collider,
                                    const int type, const float opacity,
                                    const std::string& name )
  : GameObjectComponent( collider->getGameObject(), name ),
    _collider( collider ),
    _backColor( 255, 255, 255, (static_cast<unsigned char>(opacity * 255)) ),
    _zOrder( 0 ) {

  switch ( type ) {
  case ALA_COLLIDER_RENDERER_RED:
    _sprite = static_cast<Sprite*>(GameManager::get()->getResource( ALA_EMPTY_RED_SPRITE ));
    break;
  case ALA_COLLIDER_RENDERER_GREEN:
    _sprite = static_cast<Sprite*>(GameManager::get()->getResource( ALA_EMPTY_GREEN_SPRITE ));
    break;
  case ALA_COLLIDER_RENDERER_BLUE:
    _sprite = static_cast<Sprite*>(GameManager::get()->getResource( ALA_EMPTY_BLUE_SPRITE ));
    break;
  default:
    _sprite = static_cast<Sprite*>(GameManager::get()->getResource( ALA_EMPTY_RED_SPRITE ));
    break;
  }
}

int ColliderRenderer::getZOrder() const { return _zOrder; }

void ColliderRenderer::setZOrder( const int order ) { _zOrder = order; }

void ColliderRenderer::setOpacity( const float opacity ) {
  _backColor.setA( static_cast<unsigned char>(opacity * 255) );
}

float ColliderRenderer::getOpacity() const {
  return _backColor.getA() / 255.0f;
}

void ColliderRenderer::onRender() {
  const auto transform = getGameObject()->getTransform();
  if ( _collider == NULL ) return;
  const auto worldZOrder = calculateWorldZOrder();

  const auto offset = _collider->getOffset();
  const auto oldPosition = transform->getPosition();
  const auto oldScale = transform->getScale();
  transform->setPositionX( transform->getPositionX() + offset.getX() * transform->getScale().getX() );
  transform->setPositionY( transform->getPositionY() + offset.getY() * transform->getScale().getY() );
  transform->setScale( Vec2( _collider->getSize().getWidth(), _collider->getSize().getHeight() ) );
  Graphics::get()->drawSprite( _sprite,
                               Vec2( 0.5f, 0.5f ), transform->getLocalToWorldMatrix(), _backColor,
                               Rect( Vec2( 0, 0 ), _sprite->getContentSize() ), worldZOrder );
  transform->setPosition( oldPosition );
  transform->setScale( oldScale );
}

int ColliderRenderer::calculateWorldZOrder() const {
  const auto layerIndex = GameManager::get()->getLayerIndex( getGameObject()->getLayer() );
  const auto worldZOrder = layerIndex * 1000 + _zOrder;
  return worldZOrder;
}
}
