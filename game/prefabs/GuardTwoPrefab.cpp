#include "GuardTwoPrefab.h"
#include "../Define.h"
#include "../scripts/DirectionController.h"
#include "../scripts/CharcoalBurnerCollisionTracker.h"
#include "../scripts/GuardController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(GuardTwoPrefab, ala::PrefabV2)

void GuardTwoPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto initialX = nextFloat( argsStream );
  const auto leftBoundX = nextFloat( argsStream );
  const auto rightBoundX = nextFloat( argsStream );

  // constants
  const auto density = 5.0f;
  const auto runVelocity = 140.0f;
  const auto runOneLegVelocity = 60.0f;

  const auto swordOffset1 = Vec2( -30, -5 );
  const auto swordSize1 = Size( 50, 15 );

  const auto swordOffset2 = Vec2( -45, 20 );
  const auto swordSize2 = Size( 50, 45 );

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "guards.png" );

  const auto animator = new Animator( object, "fat_guard_idle", "guards.anm" );

  const auto highSwordAudio = new AudioSource( object, "High Sword.wav" );

  const auto commonAudio = new AudioSource( object, "Guard Beckon.wav" );

  const auto hitAudio = new AudioSource( object, "Guard Hit 1.wav" );

  const auto body = new Rigidbody( object, PhysicsMaterial( density ), ALA_BODY_TYPE_DYNAMIC, 1.0f );

  const auto collider = new Collider( object, false, Vec2( 0, 0 ), Size( 40, 50 ) );
  collider->setTag( ENEMY_TAG );
  collider->ignoreTag( ENEMY_TAG );
  collider->ignoreTag( ALADDIN_TAG );

  const auto swordCollider = new Collider( object, true, Vec2(), Size( 0, 0 ), 0, 0, "Sword" );
  swordCollider->setTag( SWORD_TAG );
  swordCollider->ignoreTag( ENEMY_TAG );
  swordCollider->setActive( false );

  const auto stateManager = new StateManager( object, "idle" );

  const auto direction = new DirectionController( object, false );

  const auto charcoalBurnerCollison = new CharcoalBurnerCollisionTracker( object );

  const auto controller = new GuardController( object );
  controller->setInitialX( initialX );
  controller->setLeftBoundX( leftBoundX );
  controller->setRightBoundX( rightBoundX );
  controller->setMinDistanceYCouldAttack( 0 );
  controller->setMaxDistanceYCouldAttack( 50 );

  // helpers
  const auto timer = new Timer( object );

  const auto transform = object->getTransform();

  // collider renderers
  //  new ColliderRenderer( collider );
  //  new ColliderRenderer( swordCollider );

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
                 animator->setAction( "fat_guard_idle" );
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

  new State( stateManager, "provoke",
             [=] {
               // animation effect
               {
                 animator->setAction( "fat_guard_provoke" );
               }

               //audio
               {
                 commonAudio->play();
               }
             }, NULL, NULL );

  new State( stateManager, "attack",
             [=] {
               const auto r = rand() % 5;

               // animation effect
               {
                 if ( r < 2 ) {
                   animator->setAction( "fat_guard_attack_1" );
                 }
                 else {
                   animator->setAction( "fat_guard_attack_2" );
                 }
               }

               //audio
               {
                 if ( r >= 2 ) {
                   highSwordAudio->play();
                 }
               }

               // sword
               {
                 timer->start( 0.15f );
                 if ( r < 2 ) {
                   swordCollider->setOffset( swordOffset1 );
                   swordCollider->setSize( swordSize1 );
                 }
                 else {
                   swordCollider->setOffset( swordOffset2 );
                   swordCollider->setSize( swordSize2 );
                 }
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
                     timer->start( 0.2f );
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
                 animator->setAction( "fat_guard_run" );
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

  new State( stateManager, "run_one_leg",
             [=] {
               // animation effect 
               {
                 animator->setAction( "fat_guard_run_one_leg" );
               }
             },
             [=]( float dt ) {
               // move
               {
                 body->setVelocity( Vec2( runOneLegVelocity, body->getVelocity().getY() ) );
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
                 animator->setAction( "fat_guard_hit" );
               }

               // audio
               {
                 hitAudio->play();
               }

               // move
               {
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
               }
             }, NULL, NULL );


  new StateTransition( stateManager, "idle", "provoke", [=] {
    const auto r = rand() % 5;
    return r < 2 && controller->isAbleToSeeAladdin() && !controller->isInBestPositionToAttackAladdin() &&
    ((direction->isRight() && controller->isAbleToGoRight()) ||
      (direction->isLeft() && controller->isAbleToGoLeft()));
  } );

  new StateTransition( stateManager, "idle", "run", [=] {
    return controller->isAbleToSeeAladdin() && !controller->isInBestPositionToAttackAladdin() &&
    ((direction->isRight() && controller->isAbleToGoRight()) ||
      (direction->isLeft() && controller->isAbleToGoLeft()));
  } );

  new StateTransition( stateManager, "provoke", "run", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "run", "idle", [=] {
    return controller->isInBestPositionToAttackAladdin() ||
      (direction->isLeft() && !controller->isAbleToGoLeft()) ||
      (direction->isRight() && !controller->isAbleToGoRight());
  } );

  new StateTransition( stateManager, "run", "run_one_leg", [=] {
    return charcoalBurnerCollison->isBeingCollided();
  } );

  new StateTransition( stateManager, "run_one_leg", "run", [=] {
    return !charcoalBurnerCollison->isBeingCollided();
  } );

  new StateTransition( stateManager, "idle", "attack", [=] {
    return controller->isAbleToAttackAladdin();
  } );

  new StateTransition( stateManager, "attack", "idle", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "hit", "run_one_leg", [=] {
    return stateManager->getPreviousStateName() == "run_one_leg" && !animator->isPlaying();
  } );

  new StateTransition( stateManager, "hit", "idle", [=] {
    return !animator->isPlaying();
  } );

}
