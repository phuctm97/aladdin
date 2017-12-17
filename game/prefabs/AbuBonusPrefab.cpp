#include"AbuBonusPrefab.h"
#include"../Define.h"
#include "../scripts/CollisionTracker.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AbuBonusPrefab, ala::PrefabV2)

void AbuBonusPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto smallFireworkPrefab = gameManager->getPrefabV2( "Small Firework" );

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "items.png" );

  const auto animator = new Animator( object, "abu_bonus", "items.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 10, 10 ), 1, 0 );
  collider->setTag( ABU_BONUS_TAG );
  collider->ignoreTag( APPLE_TAG );
  collider->ignoreTag( ENEMY_TAG );

  const auto stateManager = new StateManager( object, "static" );

  const auto collision = new CollisionTracker( object );

  // helpers
  const auto transform = object->getTransform();

  // collider renderers
  new ColliderRenderer( collider );

  // configurations
  object->setTag( ABU_BONUS_TAG );
  object->setLayer( "Foreground" );

  // states
  new State( stateManager, "static", NULL,
             [=]( float dt ) {
               if ( collision->collidedWithObjectTag( ALADDIN_TAG ) ) {
                 smallFireworkPrefab->instantiate( transform->getPosition() );
                 object->release();
               }
             }, NULL );

}
