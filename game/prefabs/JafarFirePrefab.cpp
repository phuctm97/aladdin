#include "JafarFirePrefab.h"
#include "../scripts/DirectionController.h"
#include "../scripts/CollisionTracker.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarFirePrefab, ala::PrefabV2)

void JafarFirePrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const char dir = nextChar( argsStream );

  // constants
  const auto gameManager = GameManager::get();

  const auto moveVelocity = 80.0f;

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "jafar.png" );

  const auto animator = new Animator( object, "jafar_fire", "jafar.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial( 1, 0 ), ALA_BODY_TYPE_DYNAMIC, 1 );

  const auto collider = new Collider( object, false, Vec2( 0, -7 ), Size( 40, 35 ) );
  collider->setTag( FIRE_TAG );
  collider->ignoreTag( ALADDIN_TAG );
  collider->ignoreTag( BOSS_TAG );

  const auto stateManager = new StateManager( object, "default" );

  const auto direction = new DirectionController( object, true );
  if ( dir == 'L' ) direction->setLeft();
  else if ( dir == 'R' ) direction->setRight();

  const auto collisionTracker = new CollisionTracker( object );

  // helpers
  const auto transform = object->getTransform();

  // collider renderer
  new ColliderRenderer( collider );

  // configurations
  object->setLayer( "Foreground" );

  // states
  new State( stateManager, "default", NULL,
             [=]( float dt ) {
               // move
               {
                 body->setVelocity( Vec2( moveVelocity, body->getVelocity().getY() ) );
               }

               // destroy 
               {
                 if ( collisionTracker->collidedWithObjectTag( WALL_TAG ) ) {
                   object->release();
                 }
               }
             }, NULL );
}
