#include "JumpableSpringPrefab.h"
#include "../Define.h"
#include "../scripts/CollisionTracker.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JumpableSpringPrefab, ala::PrefabV2)

void JumpableSpringPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // components
  const auto spriteRenderer = new SpriteRenderer( object, "items.png" );

  const auto animator = new Animator( object, "spring", "items.anm" );

  const auto stateManager = new StateManager( object, "static" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 30, 15 ), 1, 0 );
  collider->setTag( SPRING_TAG );
  collider->ignoreTag( SPRING_TAG );
  collider->ignoreTag( ENEMY_TAG );
  collider->ignoreTag( APPLE_TAG );
  collider->ignoreTag( SWORD_TAG );

  const auto collisionTracker = new CollisionTracker( object );

  // helpers
  const auto transform = object->getTransform();

  // collider renderers
  new ColliderRenderer( collider );

  // configurations
  object->setTag( SPRING_TAG );
  object->setLayer( "Debug" );

  // states
  new State( stateManager, "static", NULL,
             [=]( float dt ) {
               if ( collisionTracker->collidedWithObjectTag( ALADDIN_TAG ) ) {
                 collisionTracker->reset();
                 animator->playFromStart();
               }
             }, NULL );
}
