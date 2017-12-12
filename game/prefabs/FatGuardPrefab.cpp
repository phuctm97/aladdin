#include "FatGuardPrefab.h"
#include "../scripts/DirectionController.h"
#include "../scripts/FatGuardController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void FatGuardPrefab::doInstantiate( ala::GameObject* object ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto input = Input::get();

  const auto density = 5.0f;
  const auto runVelocity = 100.0f;

  const auto swordOffset1 = Vec2( -30, -5 );
  const auto swordSize1 = Size( 50, 15 );

  const auto swordOffset2 = Vec2( -45, 20 );
  const auto swordSize2 = Size( 50, 45 );

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "guards.png" );

  const auto animator = new Animator( object, "fat_guard_idle", "guards.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial( density ), ALA_BODY_TYPE_DYNAMIC, 1.0f );

  const auto collider = new Collider( object, false, Vec2( 0, 0 ), Size( 40, 50 ) );
  collider->setTag( ENEMY_TAG );
  collider->ignoreTag( ALADDIN_TAG );
  collider->ignoreTag( ENEMY_TAG );

  const auto swordCollider = new Collider( object, true, Vec2(), Size( 0, 0 ), 0, 0, "Sword" );
  swordCollider->setTag( SWORD_TAG );
  swordCollider->ignoreTag( ENEMY_TAG );
  swordCollider->setActive( false );

  const auto stateManager = new StateManager( object, "idle" );

  const auto direction = new DirectionController( object, false );

  const auto controller = new FatGuardController( object );

  // helpers
  const auto timer = new Timer( object );

  const auto transform = object->getTransform();

  // collider renderers
  //  const auto colliderRenderer = new ColliderRenderer( collider );
  //
  //  const auto swordColliderRenderer = new ColliderRenderer( swordCollider );

  // configurations
  object->setLayer( "Character" );
  object->setTag( ENEMY_TAG );

  // states

  new State( stateManager, "idle",
             [=] {
               animator->setAction( "fat_guard_idle" );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
               swordCollider->setActive( false );
             }, NULL, NULL );

  new State( stateManager, "provoke",
             [=] {
               animator->setAction( "fat_guard_provoke" );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "run",
             [=] {
               animator->setAction( "fat_guard_run" );
               body->setVelocity( Vec2( -runVelocity, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new State( stateManager, "attack",
             [=] {
               const auto r = rand() % 5;
               if ( r < 2 ) {
                 animator->setAction( "fat_guard_attack_1" );
                 swordCollider->setOffset( swordOffset1 );
                 swordCollider->setSize( swordSize1 );
               }
               else {
                 animator->setAction( "fat_guard_attack_2" );
                 swordCollider->setOffset( swordOffset2 );
                 swordCollider->setSize( swordSize2 );
               }
               timer->start( 0.15f );

               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             },
             [=]( float dt ) {
               if ( timer->isDone() ) {
                 if ( !swordCollider->isActive() ) {
                   swordCollider->setActive( true );
                   timer->start( 0.2f );
                 }
                 else {
                   swordCollider->setActive( false );
                   timer->start( 5 );
                 }
               }
             },
             [=] {
               swordCollider->setActive( false );
             } );

  new State( stateManager, "hit",
             [=] {
               animator->setAction( "fat_guard_hit" );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL, NULL );

  new StateTransition( stateManager, "idle", "provoke", [=] {
    return controller->isChasingAladdin() && controller->willProvokeBeforeChasing();
  } );

  new StateTransition( stateManager, "attack", "provoke", [=] {
    return controller->isChasingAladdin() && controller->willProvokeBeforeChasing();
  } );

  new StateTransition( stateManager, "idle", "run", [=] {
    return controller->isChasingAladdin();
  } );

  new StateTransition( stateManager, "attack", "run", [=] {
    return controller->isChasingAladdin();
  } );

  new StateTransition( stateManager, "provoke", "run", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "idle", "attack", [=] {
    return controller->isAttacking();
  } );

  new StateTransition( stateManager, "run", "attack", [=] {
    return controller->isAttacking();
  } );

  new StateTransition( stateManager, "attack", "attack", [=] {
    return controller->isAttacking() && !animator->isPlaying();
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
