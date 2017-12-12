#include "ThinGuardPrefab.h"
#include "../scripts/DirectionController.h"
#include "../scripts/GuardController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void ThinGuardPrefab::doInstantiate( ala::GameObject* object ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto input = Input::get();

  const auto density = 5.0f;
  const auto runVelocity = 100.0f;

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "guards.png" );

  const auto animator = new Animator( object, "thin_guard_idle", "guards.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial( density ), ALA_BODY_TYPE_DYNAMIC, 1.0f );

  const auto collider = new Collider( object, false, Vec2( 0, 0 ), Size( 40, 50 ) );
  collider->setTag( ENEMY_TAG );
  collider->ignoreTag( ENEMY_TAG );
  collider->ignoreTag( ALADDIN_TAG );

  const auto stateManager = new StateManager( object, "idle" );

  const auto direction = new DirectionController( object, false );

  const auto controller = new GuardController( object );

  // helpers
  const auto transform = object->getTransform();

  // collider renderers
  const auto colliderRenderer = new ColliderRenderer( collider );

  // configurations
  object->setLayer( "Character" );
  object->setTag( ENEMY_TAG );

  // states
  new State( stateManager, "idle",
             [=] {
               animator->setAction( "thin_guard_idle" );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "run",
             [=] {
               animator->setAction( "thin_guard_run" );
               body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "attack",
             [=] {
               animator->setAction( "thin_guard_attack" );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "hit",
             [=] {
               animator->setAction( "thin_guard_hit" );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new StateTransition( stateManager, "idle", "run", [=] {
    return controller->isChasingAladdin();
  } );

  new StateTransition( stateManager, "attack", "run", [=] {
    return controller->isChasingAladdin();
  } );

  new StateTransition( stateManager, "idle", "attack", [=] {
    return controller->isAttacking();
  } );

  new StateTransition( stateManager, "run", "attack", [=] {
    return controller->isAttacking();
  } );

  new StateTransition( stateManager, "run", "idle", [=] {
    return controller->isIdling();
  } );

  new StateTransition( stateManager, "attack", "idle", [=] {
    return controller->isIdling();
  } );

  new StateTransition( stateManager, "hit", "idle", [=] {
    return !animator->isPlaying();
  } );
}
