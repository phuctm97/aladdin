#include "FloatingSalivaPrefab.h"
#include "../Define.h"
#include "../scripts/DirectionController.h"
#include "../scripts/CollisionTracker.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(FloatingSalivaPrefab, ala::PrefabV2)

void FloatingSalivaPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto dir = nextChar( argsStream );

  // constants
  const auto gameManager = GameManager::get();

  const auto floatingVelocity = 150.0f;

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "camel.png" );

  const auto animator = new Animator( object, "savila", "camel.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_DYNAMIC, 0.0f );

  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 9, 9 ) );
  collider->setTag( SAVILA_TAG );
  collider->ignoreTag( CAMEL_TAG );
  collider->ignoreTag( SAVILA_TAG );
  collider->ignoreTag( ALADDIN_TAG );

  const auto stateManager = new StateManager( object, "fly" );

  const auto direction = new DirectionController( object, true );
  if ( dir == 'L' ) direction->setLeft();
  else if ( dir == 'R' ) direction->setRight();

  const auto collisionTracker = new CollisionTracker( object );

  // helpers
  const auto transform = object->getTransform();

  // collider renderers
  new ColliderRenderer( collider );

  // configurations
  object->setTag( SAVILA_TAG );
  object->setLayer( "Foreground" );

  // states
  new State( stateManager, "fly",
             NULL, [=]( float dt ) {
               body->setVelocity( Vec2( floatingVelocity, body->getVelocity().getY() ) );

               if ( collisionTracker->collided() ) {
                 object->release();
               }
             }, NULL );
}
