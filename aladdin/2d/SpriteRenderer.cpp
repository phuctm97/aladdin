/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "SpriteRenderer.h"
#include "Graphics.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::SpriteRenderer, ala::GameObjectComponent )

SpriteRenderer::SpriteRenderer( GameObject* gameObject, Sprite* sprite, const std::string& name )
  : GameObjectComponent( gameObject, name ), _sprite( sprite ) {}

SpriteRenderer::SpriteRenderer( GameObject* gameObject, const std::string& spriteResourceName, const std::string& name )
  : GameObjectComponent( gameObject, name ), _sprite( NULL ) {
  _sprite = static_cast<Sprite*>(GameManager::get()->getResource( spriteResourceName ));
}

SpriteRenderer::~SpriteRenderer() {}

Sprite* SpriteRenderer::getSprite() const {
  return _sprite;
}

void SpriteRenderer::setSprite( Sprite* sprite ) {
  _sprite = sprite;
}

void SpriteRenderer::onRender() {
  Transform* transform = getGameObject()->getComponentT<Transform>();
  if ( transform == NULL ) return;

  Graphics::get()->drawSprite( _sprite, transform->getPosition() );
}
}
