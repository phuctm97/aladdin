#include"SmallFireworkPrefab.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(SmallFireworkPrefab, ala::PrefabV2)

void SmallFireworkPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // components
  const auto spriteRenderer = new SpriteRenderer( object, "items.png" );

  const auto animator = new Animator( object, "small_firework", "items.anm" );

  const auto stateManager = new StateManager( object, "static" );

  // configurations
  object->setLayer( "UI" );

  // states
  new State( stateManager, "static",
             NULL,
             [=]( float dt ) {
               if ( !animator->isPlaying() )
                 object->release();
             }, NULL );
}
