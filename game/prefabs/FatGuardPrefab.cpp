#include "FatGuardPrefab.h"
#include "../scripts/GuardController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void FatGuardPrefab::doInstantiate( ala::GameObject* object ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto input = Input::get();

  const auto density = 5.0f;
  const auto runVelocity = 100.0f;

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "guards.png" );
  const auto animator = new Animator( object, "fat_guard_idle", "guards.anm" );

  // For animationEditor
  //const auto animationEditor = new AnimationEditor( object, "fat_guard_attack2" );
  //object->getTransform()->setPosition( 80, -40 );
  //return;
  // For animationEditor

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
               animator->setAction( "fat_guard_idle" );
             }, NULL, NULL );

  new State( stateManager, "idle_left",
             [=] {
               transform->setScaleX( ABS(transform->getScale().getX()) );
               animator->setAction( "fat_guard_idle" );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "idle_right",
             [=] {
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               animator->setAction( "fat_guard_idle" );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "provoke_left",
             [=] {
               transform->setScaleX( ABS(transform->getScale().getX()) );
               animator->setAction( "fat_guard_provoke" );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "provoke_right",
             [=] {
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               animator->setAction( "fat_guard_provoke" );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "run_left",
             [=] {
               animator->setAction( "fat_guard_run" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( -runVelocity, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "run_right",
             [=] {
               animator->setAction( "fat_guard_run" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "attack_left",
             [=] {
               const auto r = rand() % 5;
               if ( r < 2 ) {
                 animator->setAction( "fat_guard_attack_1" );
               }
               else {
                 animator->setAction( "fat_guard_attack_2" );
               }
               transform->setScaleX( ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "attack_right",
             [=] {
               const auto r = rand() % 5;
               if ( r < 2 ) {
                 animator->setAction( "fat_guard_attack_1" );
               }
               else {
                 animator->setAction( "fat_guard_attack_2" );
               }
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new StateTransition( stateManager, "initial", "provoke_left", [=] {
    const auto r = rand() % 5;
    return r < 2 && transform->getPositionX() > controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "run_right", "provoke_left", [=] {
    const auto r = rand() % 5;
    return r < 2 && transform->getPositionX() > controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "idle_left", "provoke_left", [=] {
    const auto r = rand() % 5;
    return r < 2 && transform->getPositionX() > controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "idle_right", "provoke_left", [=] {
    const auto r = rand() % 5;
    return r < 2 && transform->getPositionX() > controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_left", "provoke_left", [=] {
    const auto r = rand() % 5;
    return r < 2 && !controller->couldAttackAladdin() &&
      transform->getPositionX() > controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_right", "provoke_left", [=] {
    const auto r = rand() % 5;
    return r < 2 && !controller->couldAttackAladdin() &&
      transform->getPositionX() > controller->getMinX() &&
      controller->couldSeeAladdin() && controller->isOnRightOfAladdin();
  } );

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

  new StateTransition( stateManager, "provoke_left", "run_left", [=] {
    return !animator->isPlaying() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "provoke_right", "run_left", [=] {
    return !animator->isPlaying() && controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "initial", "provoke_right", [=] {
    const auto r = rand() % 5;
    return r < 2 && transform->getPositionX() < controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "run_left", "provoke_right", [=] {
    const auto r = rand() % 5;
    return r < 2 && transform->getPositionX() < controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "idle_left", "provoke_right", [=] {
    const auto r = rand() % 5;
    return r < 2 && transform->getPositionX() < controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "idle_right", "provoke_right", [=] {
    const auto r = rand() % 5;
    return r < 2 && transform->getPositionX() < controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_left", "provoke_right", [=] {
    const auto r = rand() % 5;
    return r < 2 && !controller->couldAttackAladdin() &&
      transform->getPositionX() < controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "attack_right", "provoke_right", [=] {
    const auto r = rand() % 5;
    return r < 2 && !controller->couldAttackAladdin() &&
      transform->getPositionX() < controller->getMaxX() &&
      controller->couldSeeAladdin() && !controller->isOnRightOfAladdin();
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

  new StateTransition( stateManager, "provoke_left", "run_right", [=] {
    return !animator->isPlaying() && !controller->isOnRightOfAladdin();
  } );

  new StateTransition( stateManager, "provoke_right", "run_right", [=] {
    return !animator->isPlaying() && !controller->isOnRightOfAladdin();
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

  /*
  new State( stateManager, "fat_guard_provocative_left",
             [=] {
               animator->setAction( "fat_guard_provocative" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( 0, 0 ) );
             }, NULL, NULL );

  new State( stateManager, "fat_guard_provocative_right",
             [=] {
               animator->setAction( "fat_guard_provocative" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( 0, 0 ) );
             }, NULL, NULL );

  new State( stateManager, "fat_guard_run_left",
             [=] {
               animator->setAction( "fat_guard_run" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( -runVelocity, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "fat_guard_run_right",
             [=] {
               animator->setAction( "fat_guard_run" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "fat_guard_attack_left",
             [=] {
               animator->setAction( "fat_guard_attack2" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( 0, 0 ) );
               timer1->start( 0.8 );
             }, [=]( float dt ) {
               if ( timer1->isDone() && animator->isPlaying() ) {
                 auto var = rand() % 7;
                 if ( var <= 2 ) {
                   animator->setAction( "fat_guard_attack1" );
                   timer1->start( 0.8 );
                 }
                 else {
                   animator->setAction( "fat_guard_attack2" );
                   timer1->start( 0.8 );
                 }
               }
             }, NULL );

  new State( stateManager, "fat_guard_attack_right",
             [=] {
               animator->setAction( "fat_guard_attack2" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( 0, 0 ) );
               timer1->start( 0.8 );
             }, [=]( float dt ) {
               if ( timer1->isDone() && animator->isPlaying() ) {
                 auto var = rand() % 7;
                 if ( var <= 2 ) {
                   animator->setAction( "fat_guard_attack1" );
                   timer1->start( 0.8 );
                 }
                 else {
                   animator->setAction( "fat_guard_attack2" );
                   timer1->start( 0.8 );
                 }
               }
             }, NULL );

  new StateTransition( stateManager, "fat_guard_provocative_left", "fat_guard_provocative_right", [=] {
    return !controller->isOnRightOfAladdin();
  } );
  new StateTransition( stateManager, "fat_guard_provocative_right", "fat_guard_provocative_left", [=] {
    return controller->isOnRightOfAladdin();
  } );
  new StateTransition( stateManager, "fat_guard_provocative_left", "fat_guard_run_left", [=] {
    return controller->coundSeeAladdin();
  } );
  new StateTransition( stateManager, "fat_guard_provocative_right", "fat_guard_run_right", [=] {
    return controller->coundSeeAladdin();
  } );
  new StateTransition( stateManager, "fat_guard_run_left", "fat_guard_attack_left", [=] {
    return controller->couldAttackAladdin();
  } );
  new StateTransition( stateManager, "fat_guard_run_right", "fat_guard_attack_right", [=] {
    return controller->couldAttackAladdin();
  } );
  new StateTransition( stateManager, "fat_guard_attack_right", "fat_guard_run_right", [=] {
    if ( controller->couldAttackAladdin() == false && controller->isOnRightOfAladdin() == false )
      return true;
    else return false;
  } );
  new StateTransition( stateManager, "fat_guard_attack_right", "fat_guard_run_left", [=] {
    if ( controller->couldAttackAladdin() == false && controller->isOnRightOfAladdin() == true )
      return true;
    else return false;
  } );
  new StateTransition( stateManager, "fat_guard_attack_left", "fat_guard_run_left", [=] {
    if ( controller->couldAttackAladdin() == false && controller->isOnRightOfAladdin() == true )
      return true;
    else return false;
  } );
  new StateTransition( stateManager, "fat_guard_attack_left", "fat_guard_run_right", [=] {
    if ( controller->couldAttackAladdin() == false && controller->isOnRightOfAladdin() == false )
      return true;
    else return false;
  } );
  */
}
