#include "EatableHeartPrefab.h"
#include "../Define.h"
#include "../scripts/CollisionTracker.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(EatableHeartPrefab, ala::PrefabV2)

void EatableHeartPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto smallFireworkPrefab = gameManager->getPrefabV2( "Small Firework" );

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "items.png" );

  const auto animator = new Animator( object, "extra_health", "items.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, false, Vec2( 0, 2 ), Size( 15, 15 ) );
  collider->setTag( HEART_TAG );

  const auto stateManager = new StateManager( object, "static" );

  const auto collision = new CollisionTracker( object );

  // helpers
  const auto transform = object->getTransform();

  // collider renderers
  //  new ColliderRenderer( collider );

  // flags
  collider->setFlags( COLLIDE_ALADDIN_FLAG | STATIC_FLAG );
  collider->ignoreIfHasAnyFlags( STATIC_FLAG );

  // configurations
  object->setTag( HEART_TAG );
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
