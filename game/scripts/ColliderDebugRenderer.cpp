#include "ColliderDebugRenderer.h"

USING_NAMESPACE_ALA;

ColliderDebugRenderer::ColliderDebugRenderer( ala::GameObject* gameObject, const std::string& debugSpriteResourceName,
                                              const float opacity,
                                              const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _backColor( 255, 255, 255, (static_cast<unsigned char>(opacity * 255)) ),
    _zOrder( 0 ) {
  _sprite = static_cast<Sprite*>(GameManager::get()->getResource( debugSpriteResourceName ));
}

int ColliderDebugRenderer::getZOrder() const { return _zOrder; }

void ColliderDebugRenderer::setZOrder( const int order ) { _zOrder = order; }

void ColliderDebugRenderer::setOpacity( const float opacity ) {
  _backColor.setA( static_cast<unsigned char>(opacity * 255) );
}

float ColliderDebugRenderer::getOpacity() const {
  return _backColor.getA() / 255.0f;
}

void ColliderDebugRenderer::onRender() {
  const auto transform = getGameObject()->getTransform();
  const auto collider = getGameObject()->getComponentT<Collider>();
  if ( collider == NULL ) return;
  const auto worldZOrder = calculateWorldZOrder();

  const auto offset = collider->getOffset();
  const auto oldPosition = transform->getPosition();
  const auto oldScale = transform->getScale();
  transform->setPositionX( transform->getPositionX() + offset.getX() * transform->getScale().getX() );
  transform->setPositionY( transform->getPositionY() + offset.getY() * transform->getScale().getY() );
  transform->setScale( Vec2( collider->getSize().getWidth(), collider->getSize().getHeight() ) );
  Graphics::get()->drawSprite( _sprite,
                               Vec2( 0.5f, 0.5f ), transform->getLocalToWorldMatrix(), _backColor,
                               Rect( Vec2( 0, 0 ), _sprite->getContentSize() ), worldZOrder );
  transform->setPosition( oldPosition );
  transform->setScale( oldScale );
}

int ColliderDebugRenderer::calculateWorldZOrder() const {
  const auto layerIndex = GameManager::get()->getLayerIndex( getGameObject()->getLayer() );
  const auto worldZOrder = layerIndex * 1000 + _zOrder;
  return worldZOrder;
}
