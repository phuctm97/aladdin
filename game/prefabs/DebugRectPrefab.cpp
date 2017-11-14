#include "DebugRectPrefab.h"

USING_NAMESPACE_ALA;

void DebugRectPrefab::doInstantiate( ala::GameObject* object ) const {
  const auto spriteRenderer = new SpriteRenderer( object, "debug_red.png" );

  object->setLayer( "Foreground" );

  const auto transform = object->getTransform();
  transform->setScale( 20 );
}
