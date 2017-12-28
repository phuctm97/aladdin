#include "JafarFirePrefab.h"
#include "../scripts/DirectionController.h"
#include "../scripts/CollisionTracker.h"
#include "../Define.h"
#include "../app/MyAppData.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarFirePrefab, ala::PrefabV2)

void JafarFirePrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const char dir = nextChar( argsStream );

  // constants
  const auto gameManager = GameManager::get();
  const auto myAppData = static_cast<MyAppData*>(gameManager->getResource("My App Data"));

  const auto moveVelocity = 80.0f;

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "jafar.png" );

  const auto animator = new Animator( object, "jafar_fire", "jafar.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial( 1, 0 ), ALA_BODY_TYPE_DYNAMIC, 1 );

  const auto groundCollider = new Collider( object, false, Vec2( 5, -12 ), Size( 30, 25 ) );
  groundCollider->setTag( FIRE_TAG );
  groundCollider->ignoreTag( ALADDIN_TAG );
  groundCollider->ignoreTag( BOSS_TAG );

  const auto aladdinCollider = new Collider( object, true, Vec2( 5, -12 ), Size( 30, 25 ) );
  aladdinCollider->setTag( FIRE_TAG );
  aladdinCollider->ignoreTag( BOSS_TAG );

  const auto stateManager = new StateManager( object, "default" );

  const auto direction = new DirectionController( object, true );
  if ( dir == 'L' ) direction->setLeft();
  else if ( dir == 'R' ) direction->setRight();

  const auto collisionTracker = new CollisionTracker( object );

  // helpers
  const auto transform = object->getTransform();

  // collider renderer
  //  new ColliderRenderer( aladdinCollider );

  // flags
  groundCollider->setFlags( EMPTY_FLAG );
  groundCollider->ignoreIfNotHasAnyFlags( STANDABLE_FLAG );

  aladdinCollider->setFlags( COLLIDE_ALADDIN_FLAG );
  aladdinCollider->ignoreIfNotHasAnyFlags( COLLIDE_FREE_OBJECT_FLAG );

  // configurations
  object->setTag( FIRE_TAG );
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
