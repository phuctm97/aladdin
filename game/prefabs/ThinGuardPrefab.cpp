#include "ThinGuardPrefab.h"
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
  collider->ignoreTag( ALADDIN_TAG );
  collider->ignoreTag( ENEMY_TAG );

  const auto colliderRenderer = new ColliderRenderer( collider );
  const auto stateManager = new StateManager( object, "initial" );
  const auto controller = new GuardController( object, "Controller" );
  const auto transform = object->getTransform();

  // configurations
  object->setLayer( "Character" );
  object->setTag( ENEMY_TAG );

  // states

  new State( stateManager, "initial",
             [=] {
               transform->setPositionX( controller->getInitialX() );
               animator->setAction( "thin_guard_idle" );
             }, NULL, NULL );

  new State( stateManager, "idle_left",
             [=] {
               transform->setScaleX( ABS(transform->getScale().getX()) );
               animator->setAction( "thin_guard_idle" );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "idle_right",
             [=] {
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               animator->setAction( "thin_guard_idle" );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "run_left",
             [=] {
               animator->setAction( "thin_guard_run" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( -runVelocity, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "run_right",
             [=] {
               animator->setAction( "thin_guard_run" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "attack_left",
             [=] {
               animator->setAction( "thin_guard_attack" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "attack_right",
             [=] {
               animator->setAction( "thin_guard_attack" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "hit_left",
             [=] {
               animator->setAction( "thin_guard_hit" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "hit_right",
             [=] {
               animator->setAction( "thin_guard_hit" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new StateTransition( stateManager, "initial", "run_left", [=] {
    return transform->getPositionX() > controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "run_right", "run_left", [=] {
    return transform->getPositionX() > controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "idle_left", "run_left", [=] {
    return transform->getPositionX() > controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "idle_right", "run_left", [=] {
    return transform->getPositionX() > controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_left", "run_left", [=] {
    return !controller->couldAttackAladdin() &&
      transform->getPositionX() > controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_right", "run_left", [=] {
    return !controller->couldAttackAladdin() &&
      transform->getPositionX() > controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_left", "idle_left", [=] {
    return !controller->couldAttackAladdin() &&
      transform->getPositionX() <= controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_right", "idle_left", [=] {
    return !controller->couldAttackAladdin() &&
      transform->getPositionX() <= controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "initial", "run_right", [=] {
    return transform->getPositionX() < controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "run_left", "run_right", [=] {
    return transform->getPositionX() < controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "idle_left", "run_right", [=] {
    return transform->getPositionX() < controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "idle_right", "run_right", [=] {
    return transform->getPositionX() < controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_left", "run_right", [=] {
    return !controller->couldAttackAladdin() &&
      transform->getPositionX() < controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_right", "run_right", [=] {
    return !controller->couldAttackAladdin() &&
      transform->getPositionX() < controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_left", "idle_right", [=] {
    return !controller->couldAttackAladdin() &&
      transform->getPositionX() >= controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_right", "idle_right", [=] {
    return !controller->couldAttackAladdin() &&
      transform->getPositionX() >= controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "run_left", "idle_left", [=] {
    return transform->getPositionX() <= controller->getMinX();
  } );

  new StateTransition( stateManager, "run_right", "idle_right", [=] {
    return transform->getPositionX() >= controller->getMaxX();
  } );

  new StateTransition( stateManager, "initial", "attack_left", [=] {
    return controller->couldAttackAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "run_right", "attack_left", [=] {
    return controller->couldAttackAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "run_left", "attack_left", [=] {
    return controller->couldAttackAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "idle_right", "attack_left", [=] {
    return controller->couldAttackAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "idle_left", "attack_left", [=] {
    return controller->couldAttackAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_right", "attack_left", [=] {
    return controller->couldAttackAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "initial", "attack_right", [=] {
    return controller->couldAttackAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "run_right", "attack_right", [=] {
    return controller->couldAttackAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "run_left", "attack_right", [=] {
    return controller->couldAttackAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "idle_right", "attack_right", [=] {
    return controller->couldAttackAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "idle_left", "attack_right", [=] {
    return controller->couldAttackAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_left", "attack_right", [=] {
    return controller->couldAttackAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "idle_left", "initial", [=] {
    return controller->isTooFarFromAladdin();
  } );

  new StateTransition( stateManager, "idle_right", "initial", [=] {
    return controller->isTooFarFromAladdin();
  } );

  new StateTransition( stateManager, "hit_left", "idle_left", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "hit_right", "idle_right", [=] {
    return !animator->isPlaying();
  } );
}
