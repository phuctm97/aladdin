/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "SpriteRenderer.h"
#include "Transform2.h"
#include "Graphics.h"
#include "../core/GameManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::SpriteRenderer, "ala::SpriteRenderer", ala::GameObjectComponent )

SpriteRenderer::SpriteRenderer( GameObject* gameObject, Sprite* sprite, const std::string& name )
  : GameObjectComponent( gameObject, name ), _sprite( sprite ) {}

SpriteRenderer::SpriteRenderer( GameObject* gameObject, const std::string& spriteResourceName, const std::string& name )
  : GameObjectComponent( gameObject, name ), _sprite( NULL ) {
  _sprite = static_cast<Sprite*>(GameManager::get()->getResource( spriteResourceName ));
}

Sprite* SpriteRenderer::getSprite() const {
  return _sprite;
}

void SpriteRenderer::setSprite( Sprite* sprite ) {
  _sprite = sprite;
}

void SpriteRenderer::onRender() {
  Transform2* transform = getGameObject()->getComponentT<Transform2>();
  if ( transform == NULL ) return;

  Graphics::get()->drawSprite( _sprite, transform->getPosition() );
}
}
