#include "GuardThreePrefab.h"
#include "../Define.h"
#include "../scripts/DirectionController.h"
#include "../scripts/GuardController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(GuardThreePrefab, ala::PrefabV2)

void GuardThreePrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto initialX = nextFloat( argsStream );
  const auto leftBoundX = nextFloat( argsStream );
  const auto rightBoundX = nextFloat( argsStream );

  // constants
  const auto gameManager = GameManager::get();
  const auto throwableKnifePrefab = gameManager->getPrefabV2( "Throwable Knife" );

  const auto density = 5.0f;
  const auto runVelocity = 100.0f;
  const auto throwImpulse = Vec2( 20000.0f, 1000.0f );

  const auto swordOffset = Vec2( -50, 5 );
  const auto swordSize = Size( 50, 32 );

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "guards.png" );

  const auto animator = new Animator( object, "adorable_guard_idle", "guards.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial( density ), ALA_BODY_TYPE_DYNAMIC, 1.0f );

  const auto collider = new Collider( object, false, Vec2( 0, 0 ), Size( 40, 50 ) );
  collider->setTag( ENEMY_TAG );
  collider->ignoreTag( ENEMY_TAG );
  collider->ignoreTag( ALADDIN_TAG );

  const auto stateManager = new StateManager( object, "idle" );

  const auto direction = new DirectionController( object, false );

  const auto controller = new GuardController( object );
  controller->setInitialX( initialX );
  controller->setLeftBoundX( leftBoundX );
  controller->setRightBoundX( rightBoundX );
  controller->setMinDistanceCouldAttack( 40 );
  controller->setMaxDistanceCouldAttack( 150 );

  // helpers
  const auto timer = new Timer( object );

  const auto transform = object->getTransform();

  // collider renderers
  new ColliderRenderer( collider );

  // configurations
  object->setLayer( "Supporting Character" );
  object->setTag( ENEMY_TAG );

  new State( stateManager, "null", NULL, NULL, NULL );

  // states
  new State( stateManager, "idle",
             [=] {
               // animation effect
               {
                 animator->setAction( "adorable_guard_idle" );
               }

               // move
               {
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
               }
             },
             [=]( float dt ) {
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

  new State( stateManager, "throw",
             [=] {
               // animation effect
               {
                 animator->setAction( "adorable_guard_throw" );
               }

               // throw
               {
                 timer->start( 0.15f );
               }
             },
             [=]( float dt ) {
               // direction
               {
                 int directionToFace = controller->getDirectionToFaceToAladdin();
                 if ( directionToFace == 'L' && direction->isRight() ) direction->setLeft();
                 else if ( directionToFace == 'R' && direction->isLeft() ) direction->setRight();
               }

               // throw 
               {
                 if ( timer->isDone() ) {
                   std::stringstream throwArgsStream;

                   if ( direction->isRight() ) {
                     throwArgsStream << 'R';
                   }
                   else {
                     throwArgsStream << 'L';
                   }

                   throwArgsStream << ' ' << throwImpulse.getX() << ' ' << throwImpulse.getY();

                   throwableKnifePrefab->instantiateWithArgs( throwArgsStream.str() )
                                       ->getTransform()
                                       ->setPosition( transform->getPosition() +
                                         Vec2( collider->getSize().getWidth() / 2,
                                               collider->getSize().getHeight() / 2 - collider->getSize().getHeight() *
                                               0.25f ) );

                   timer->start( 5 );
                 }
               }
             }, NULL );

  new State( stateManager, "run",
             [=] {
               // animation effect 
               {
                 animator->setAction( "adorable_guard_run" );
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

  new State( stateManager, "hit",
             [=] {
               // animation effect
               {
                 animator->setAction( "adorable_guard_hit" );
               }

               // move
               {
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
               }
             }, NULL, NULL );

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

  new StateTransition( stateManager, "idle", "throw", [=] {
    return controller->isAbleToAttackAladdin();
  } );

  new StateTransition( stateManager, "throw", "idle", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "hit", "idle", [=] {
    return !animator->isPlaying();
  } );
}
