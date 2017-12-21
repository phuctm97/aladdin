#include "FallingVasePrefab.h"
#include "../Define.h"
#include "../scripts/CollisionTracker.h"
#include "../scripts/DirectionController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(FallingVasePrefab, ala::PrefabV2)

void FallingVasePrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto dir = nextChar( argsStream );

  // constants
  const auto gameManager = GameManager::get();
  const auto enemyExplosionPrefab = gameManager->getPrefabV2( "Enemy Explosion 1" );

  const auto density = 0.5f;
  const auto fallVelocity = 21.0f;

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "civilian_enemies.png" );

  const auto animator = new Animator( object, "vase_fall", "civilian_enemies.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial( density ), ALA_BODY_TYPE_DYNAMIC, 1.5f );

  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 24, 15 ) );
  collider->setTag( VASE_TAG );
  collider->ignoreTag( ENEMY_TAG );
  collider->ignoreTag( VASE_TAG );

  const auto stateManager = new StateManager( object, "fall" );

  const auto direction = new DirectionController( object, true, 1 );
  if ( dir == 'L' ) direction->setLeft();
  else if ( dir == 'R' ) direction->setRight();

  const auto collisionTracker = new CollisionTracker( object );

  // helpers
  const auto transform = object->getTransform();

  // collider renderers
  new ColliderRenderer( collider );

  // flags
  collider->setFlags( COLLIDE_ALADDIN_FLAG );
  collider->ignoreIfNotHasAnyFlags( COLLIDE_FREE_OBJECT_FLAG );

  // configurations
  object->setTag( VASE_TAG );
  object->setLayer( "Mass Character" );

  // states
  new State( stateManager, "fall",
             [=] {
               // animation effect
               {
                 animator->setAction( "vase_fall" );
               }
             },
             [=]( float dt ) {
               // move 
               {
                 body->setVelocity( Vec2( fallVelocity, body->getVelocity().getY() ) );
               }

               // collision
               if ( collisionTracker->collidedWithObjectTag( ALADDIN_TAG ) && collisionTracker->
                 collidedWithColliderTag( SWORD_TAG ) ) {
                 enemyExplosionPrefab->instantiate( transform->getPosition() );
                 object->release();
               }
             }, NULL );

  new State( stateManager, "break",
             [=] {
               // animation effect
               {
                 animator->setAction( "vase_break" );
               }

               // move
               {
                 body->setVelocity( Vec2( 0, 0 ) );
                 body->setGravityScale( 0 );
               }

               // collision
               {
                 collider->setActive( false );
               }
             }, [=]( float dt ) {
               // release 
               {
                 if ( !animator->isPlaying() ) {
                   object->release();
                 }
               }
             }, NULL );

  new StateTransition( stateManager, "fall", "break", [=] {
    return collisionTracker->collidedWithObjectTag( GROUND_TAG );
  } );
}
