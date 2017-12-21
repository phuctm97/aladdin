#include "GuardFivePrefab.h"
#include "../Define.h"
#include "../scripts/GuardController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(GuardFivePrefab, ala::PrefabV2)

void GuardFivePrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto initialX = nextFloat( argsStream );
  const auto leftBoundX = nextFloat( argsStream );
  const auto rightBoundX = nextFloat( argsStream );

  // constants
  const auto density = 5.0f;
  const auto runVelocity = 20.0f;
  const auto minIdleDelay = 300;
  const auto maxIdleDelay = 2000;
  const auto swordOffset = Vec2( 20, 5 );
  const auto swordSize = Size( 40, 20 );

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "civilian_enemies.png" );

  const auto animator = new Animator( object, "hide_guard_idle_0", "civilian_enemies.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial( density ), ALA_BODY_TYPE_DYNAMIC, 1.0f );

  const auto collider = new Collider( object, false, Vec2( 0, 0 ), Size( 40, 50 ) );
  collider->setTag( ENEMY_TAG );
  collider->ignoreTag( ENEMY_TAG );
  collider->ignoreTag( ALADDIN_TAG );

  const auto swordCollider = new Collider( object, true, swordOffset, swordSize, 0, 0, "Sword" );
  swordCollider->setTag( SWORD_TAG );
  swordCollider->ignoreTag( ENEMY_TAG );
  swordCollider->setActive( false );

  const auto stateManager = new StateManager( object, "idle" );

  const auto direction = new DirectionController( object, true );

  const auto controller = new GuardController( object );
  controller->setInitialX( initialX );
  controller->setLeftBoundX( leftBoundX );
  controller->setRightBoundX( rightBoundX );
  controller->setMinDistanceCouldAttack( 5 );
  controller->setMaxDistanceCouldAttack( 50 );

  // helpers
  const auto timer = new Timer( object );

  const auto transform = object->getTransform();

  // collider renderers
  new ColliderRenderer( collider );
  new ColliderRenderer( swordCollider );

  // flags
  collider->setFlags( COLLIDE_FREE_OBJECT_FLAG );
  collider->ignoreIfNotHasAnyFlags( COLLIDE_ENEMY_FLAG );
  swordCollider->setFlags( COLLIDE_ALADDIN_FLAG | COLLIDE_FREE_OBJECT_FLAG );

  // configurations
  object->setLayer( "Supporting Character" );
  object->setTag( ENEMY_TAG );

  // states
  new State( stateManager, "idle",
             [=] {
               // animation effect
               {
                 animator->setAction( "hide_guard_idle_0" );
                 timer->start( (rand() % (maxIdleDelay - minIdleDelay) + minIdleDelay) / 1000.0f );
               }

               // move
               {
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
               }

               // sword
               {
                 swordCollider->setActive( false );
               }
             },
             [=]( float dt ) {
               // animation effect
               {
                 if ( !animator->isPlaying() && timer->isDone() ) {
                   if ( animator->getActionName() == "hide_guard_idle_0" ) {
                     animator->setAction( "hide_guard_idle_0_1" );
                   }
                   else if ( animator->getActionName() == "hide_guard_idle_0_1" ) {
                     animator->setAction( "hide_guard_idle_1" );
                     timer->start( (rand() % (maxIdleDelay - minIdleDelay) + minIdleDelay) / 1000.0f );
                   }
                   else if ( animator->getActionName() == "hide_guard_idle_1" ) {
                     animator->setAction( "hide_guard_idle_1_0" );
                   }
                   else if ( animator->getActionName() == "hide_guard_idle_1_0" ) {
                     animator->setAction( "hide_guard_idle_0" );
                     timer->start( (rand() % (maxIdleDelay - minIdleDelay) + minIdleDelay) / 1000.0f );
                   }
                 }
               }

               // reset
               {
                 if ( controller->isTooFarFromAladdin() ) {
                   transform->setPositionX( controller->getInitialX() );
                 }
               }

               // direction
               {
                 int directionToFace = controller->getDirectionToFaceToAladdin();
                 if ( directionToFace == 'L' && direction->isRight() ) direction->setLeft();
                 else if ( directionToFace == 'R' && direction->isLeft() ) direction->setRight();
               }
             }, NULL );

  new State( stateManager, "attack",
             [=] {
               // animation effect
               {
                 animator->setAction( "hide_guard_attack" );
               }

               // sword
               {
                 timer->start( 0.36f );
               }
             },
             [=]( float dt ) {
               // direction
               {
                 int directionToFace = controller->getDirectionToFaceToAladdin();
                 if ( directionToFace == 'L' && direction->isRight() ) direction->setLeft();
                 else if ( directionToFace == 'R' && direction->isLeft() ) direction->setRight();
               }

               // sword 
               {
                 if ( timer->isDone() ) {
                   if ( !swordCollider->isActive() ) {
                     swordCollider->setActive( true );
                     timer->start( 0.14f );
                   }
                   else {
                     swordCollider->setActive( false );
                     timer->start( 5 );
                   }
                 }
               }
             },
             [=] {
               // sword
               {
                 swordCollider->setActive( false );
               }
             } );

  new State( stateManager, "run",
             [=] {
               // animation effect 
               {
                 animator->setAction( "hide_guard_run" );
               }
             },
             [=]( float dt ) {
               // move
               {
                 body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );
               }

               // direction
               {
                 char directionToGo = controller->getDirectionToGoToAttackAladdin();
                 if ( directionToGo == 'L' && direction->isRight() ) direction->setLeft();
                 else if ( directionToGo == 'R' && direction->isLeft() ) direction->setRight();
               }

               // bound 
               {
                 controller->keepInBound();
               }
             }, NULL );

  new StateTransition( stateManager, "idle", "run", [=] {
    return controller->isAbleToSeeAladdin() && !controller->isAbleToAttackAladdin() &&
    ((direction->isRight() && controller->isAbleToGoRight()) ||
      (direction->isLeft() && controller->isAbleToGoLeft()));
  } );

  new StateTransition( stateManager, "run", "idle", [=] {
    return controller->isAbleToAttackAladdin() ||
      (direction->isLeft() && !controller->isAbleToGoLeft()) ||
      (direction->isRight() && !controller->isAbleToGoRight());
  } );

  new StateTransition( stateManager, "idle", "attack", [=] {
    return controller->isAbleToAttackAladdin();
  } );

  new StateTransition( stateManager, "attack", "idle", [=] {
    return !animator->isPlaying();
  } );
}
