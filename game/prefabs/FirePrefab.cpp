#include "FirePrefab.h"

USING_NAMESPACE_ALA;

void FirePrefab::doInstantiate( ala::GameObject* object ) const {
  const auto spriteRenderer = new SpriteRenderer( object, "jafar.png" );
  const auto animator = new Animator( object, "fire", "jafar.anm" );
}
