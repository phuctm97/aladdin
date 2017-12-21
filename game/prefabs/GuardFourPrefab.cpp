#include "GuardFourPrefab.h"
#include "../Define.h"
#include "../scripts/DirectionController.h"
#include "../scripts/GuardController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(GuardFourPrefab, ala::PrefabV2)

void GuardFourPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto initialX = nextFloat( argsStream );

  // constants
  const auto gameManager = GameManager::get();
  const auto throwableKnifePrefab = gameManager->getPrefabV2( "Throwable Knife" );

  const auto density = 5.0f;
  const auto throwImpulse1 = Vec2( 6000.0f, 14000.0f );
  const auto throwImpulse2 = Vec2( 20000.0f, 1000.0f );

  const auto swordOffset = Vec2( -50, 5 );
  const auto swordSize = Size( 50, 32 );

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "civilian_enemies.png" );

  const auto animator = new Animator( object, "nake_guard_stand", "civilian_enemies.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial( density ), ALA_BODY_TYPE_DYNAMIC, 1.0f );

  const auto collider = new Collider( object, false, Vec2( 0, 0 ), Size( 40, 50 ) );
  collider->setTag( ENEMY_TAG );
  collider->ignoreTag( ENEMY_TAG );
  collider->ignoreTag( ALADDIN_TAG );

  const auto stateManager = new StateManager( object, "idle" );

  const auto direction = new DirectionController( object, true, -1 );

  const auto controller = new GuardController( object );
  controller->setInitialX( initialX );
  controller->setLeftBoundX( initialX );
  controller->setRightBoundX( initialX );
  controller->setMinDistanceXCouldAttack( 5 );
  controller->setMaxDistanceXCouldAttack( 160 );
  controller->setMinDistanceYCouldAttack( 0 );
  controller->setMaxDistanceYCouldAttack( 130 );

  // helpers
  const auto timer1 = new Timer( object );
  const auto timer2 = new Timer( object );

  const auto transform = object->getTransform();

  // collider renderers
  new ColliderRenderer( collider );

  // flags
  collider->setFlags( COLLIDE_FREE_OBJECT_FLAG );
  collider->ignoreIfNotHasAnyFlags( COLLIDE_ENEMY_FLAG );

  // configurations
  object->setLayer( "Supporting Character" );
  object->setTag( ENEMY_TAG );

  new State( stateManager, "null", NULL, NULL, NULL );

  // states
  new State( stateManager, "idle",
             [=] {
               // animation effect
               {
                 animator->setAction( "nake_guard_stand" );
               }

               // move
               {
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
               }

               // throw 
               {
                 timer2->start( 0.75f );
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
                 animator->setAction( "nake_guard_throw" );
               }

               // throw
               {
                 timer1->start( 0.15f );
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
                 if ( timer1->isDone() ) {
                   std::stringstream throwArgsStream;

                   if ( direction->isRight() ) {
                     throwArgsStream << 'R';
                   }
                   else {
                     throwArgsStream << 'L';
                   }

                   const auto r = rand() % 2;
                   if ( r == 0 ) {
                     throwArgsStream << ' ' << throwImpulse1.getX() << ' ' << throwImpulse1.getY();
                   }
                   else {
                     throwArgsStream << ' ' << throwImpulse2.getX() << ' ' << throwImpulse2.getY();
                   }

                   throwableKnifePrefab->instantiateWithArgs( throwArgsStream.str() )
                                       ->getTransform()
                                       ->setPosition( transform->getPosition() +
                                         Vec2( collider->getSize().getWidth() / 2,
                                               collider->getSize().getHeight() / 2 - collider->getSize().getHeight() *
                                               0.25f ) );

                   timer1->start( 5 );
                 }
               }
             }, NULL );

  new StateTransition( stateManager, "idle", "throw", [=] {
    return controller->isAbleToAttackAladdin() && timer2->isDone();
  } );

  new StateTransition( stateManager, "throw", "idle", [=] {
    return !animator->isPlaying();
  } );
}
