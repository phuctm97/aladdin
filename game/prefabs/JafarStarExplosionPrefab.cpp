#include "JafarStarExplosionPrefab.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarStarExplosionPrefab, ala::PrefabV2)

void JafarStarExplosionPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // components
  const auto spriteRenderer = new SpriteRenderer( object, "jafar.png" );

  const auto animator = new Animator( object, "star_explosion", "jafar.anm" );

  const auto stateManager = new StateManager( object, "default" );

  new State( stateManager, "default", NULL,
             [=]( float dt ) {
               if ( !animator->isPlaying() ) {
                 object->release();
               }
             }, NULL );
}
