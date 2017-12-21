#include "JafarPrefab.h"
#include "../Define.h"
#include "../scripts/DirectionController.h"
#include "../scripts/JafarController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarPrefab, ala::PrefabV2)

void JafarPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto firePrefab = gameManager->getPrefabV2( "Jafar Fire" );
  const auto starPrefab = gameManager->getPrefabV2( "Jafar Star" );
  const auto explosionPrefab = gameManager->getPrefabV2( "Big Explosion" );

  const auto minIdle1Delay = 300;
  const auto maxIdle1Delay = 1000;
  const auto minIdle2Delay = 700;
  const auto maxIdle2Delay = 1300;
  const auto minAttackDelay = 1000;
  const auto maxAttackDelay = 2300;
  const auto releaseStarDelay = 0.3f;
  const auto bodyOffset1 = Vec2( 0, 0 );
  const auto bodySize1 = Size( 35, 70 );
  const auto bodyOffset2 = Vec2( 15, 0 );
  const auto bodySize2 = Size( 60, 70 );
  std::vector<float> firePositions = { -8, -8 + 18 * 1, -8 + 18 * 2 };

  // components

  const auto spriteRenderer = new SpriteRenderer( object, "jafar.png" );
  spriteRenderer->setZOrder( 1 );

  const auto animator = new Animator( object, "jafar_1_attack", "jafar.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 60, 70 ), 1, 0 );
  collider->setTag( BOSS_TAG );
  collider->ignoreTag( FIRE_TAG );

  const auto stateManager = new StateManager( object, "idle_1" );

  const auto direction = new DirectionController( object );

  const auto controller = new JafarController( object );

  std::vector<SpriteRenderer*> fireSprites;
  for ( const auto firePos : firePositions ) {
    const auto fire = new GameObject( object );
    const auto fireSpriteRenderer = new SpriteRenderer( fire, "jafar.png" );
    const auto fireAnimator = new Animator( fire, "fire_loop", "jafar.anm" );
    fire->getTransform()->setPosition( firePos, -14 );
    fire->setLayer( "Supporting Character" );
    fireSpriteRenderer->setZOrder( 2 );

    fireSprites.push_back( fireSpriteRenderer );
  }

  // helpers
  const auto timer1 = new Timer( object );
  const auto timer2 = new Timer( object );

  const auto transform = object->getTransform();

  // collider renderers
  //  const auto colliderRenderer = new ColliderRenderer( collider );
  //  colliderRenderer->setZOrder( 3 );

  // configurations
  object->setTag( BOSS_TAG );
  object->setLayer( "Supporting Character" );

  // states
  new State( stateManager, "idle_1",
             [=] {
               // animation effect
               {
                 if ( stateManager->getPreviousStateName() == "attack_1" ) {
                   animator->setAction( "jafar_1_attack_to_idle" );
                 }
                 else {
                   animator->setAction( "jafar_1_idle" );
                 }

                 if ( stateManager->getPreviousStateName() == "idle_2" ||
                   stateManager->getPreviousStateName() == "attack_2" ) {
                   transform->setPositionY( transform->getPositionY() + 10 );
                   explosionPrefab->instantiateWithArgs( "" )
                                  ->getTransform()->setPosition( transform->getPosition() );
                 }
               }

               // transition
               {
                 timer1->start( (rand() % (maxIdle1Delay - minIdle1Delay) + minIdle1Delay) / 1000.0f );
               }

               // body
               {
                 collider->setOffset( bodyOffset1 );
                 collider->setSize( bodySize1 );
               }

               // fires
               {
                 for ( const auto fireSprite : fireSprites ) fireSprite->setVisible( false );
               }
             },
             [=]( float dt ) {
               // direction  
               {
                 if ( controller->getDirectionToFaceAladdin() == 'L' && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( controller->getDirectionToFaceAladdin() == 'R' && direction->isLeft() ) {
                   direction->setRight();
                 }
               }
             }, NULL );

  new State( stateManager, "attack_1",
             [=] {
               // animation effect
               {
                 animator->setAction( "jafar_1_attack" );
               }

               // transition
               {
                 timer1->start( (rand() % (maxAttackDelay - minAttackDelay) + minAttackDelay) / 1000.0f );
               }

               // attack
               {
                 timer2->start( 0.56f );
               }
             },
             [=]( float dt ) {
               // direction  
               {
                 if ( controller->getDirectionToFaceAladdin() == 'L' && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( controller->getDirectionToFaceAladdin() == 'R' && direction->isLeft() ) {
                   direction->setRight();
                 }
               }

               // attack
               {
                 if ( timer2->isDone() ) {
                   if ( direction->isLeft() ) {
                     starPrefab->instantiateWithArgs( "" )
                               ->getTransform()->setPosition( transform->getPosition() + Vec2( -44, 22 ) );
                   }
                   else {
                     starPrefab->instantiateWithArgs( "" )
                               ->getTransform()->setPosition( transform->getPosition() + Vec2( 44, 22 ) );
                   }

                   timer2->start( releaseStarDelay );
                 }
               }
             }, NULL );

  // states
  new State( stateManager, "idle_2",
             [=] {
               // animation effect
               {
                 animator->setAction( "jafar_2_idle" );

                 if ( stateManager->getPreviousStateName() == "idle_1" ||
                   stateManager->getPreviousStateName() == "attack_1" ) {
                   transform->setPositionY( transform->getPositionY() - 10 );
                   explosionPrefab->instantiateWithArgs( "" )
                                  ->getTransform()->setPosition( transform->getPosition() );
                 }
               }

               // transition
               {
                 timer1->start( (rand() % (maxIdle2Delay - minIdle2Delay) + minIdle2Delay) / 1000.0f );
               }

               // body
               {
                 collider->setOffset( bodyOffset2 );
                 collider->setSize( bodySize2 );
               }

               // fires
               {
                 for ( const auto fireSprite : fireSprites ) fireSprite->setVisible( true );
               }
             },
             [=]( float dt ) {
               // direction  
               {
                 if ( controller->getDirectionToFaceAladdin() == 'L' && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( controller->getDirectionToFaceAladdin() == 'R' && direction->isLeft() ) {
                   direction->setRight();
                 }
               }
             }, NULL );

  new State( stateManager, "attack_2",
             [=] {
               // animation effect
               {
                 animator->setAction( "jafar_2_attack" );
               }

               // throw
               {
                 timer1->start( 0.24f );
               }
             },
             [=]( float dt ) {
               // direction  
               {
                 if ( controller->getDirectionToFaceAladdin() == 'L' && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( controller->getDirectionToFaceAladdin() == 'R' && direction->isLeft() ) {
                   direction->setRight();
                 }
               }

               // throw
               {
                 if ( timer1->isDone() ) {
                   if ( direction->isLeft() ) {
                     firePrefab->instantiateWithArgs( "L" )
                               ->getTransform()->setPosition( transform->getPosition() + Vec2( -15, -15 ) );
                   }
                   else {
                     firePrefab->instantiateWithArgs( "R" )
                               ->getTransform()->setPosition( transform->getPosition() + Vec2( 15, -15 ) );
                   }
                   timer1->start( 1000 );
                 }
               }
             }, NULL );

  new StateTransition( stateManager, "idle_1", "attack_1", [=] {
    return timer1->isDone() && !animator->isPlaying();
  } );

  new StateTransition( stateManager, "attack_1", "idle_1", [=] {
    return timer1->isDone() && !animator->isPlaying();
  } );

  new StateTransition( stateManager, "idle_2", "attack_2", [=] {
    return timer1->isDone();
  } );

  new StateTransition( stateManager, "attack_2", "idle_2", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "idle_1", "idle_2", [=] {
    return controller->getMode() == 2;
  } );

  new StateTransition( stateManager, "attack_1", "idle_2", [=] {
    return controller->getMode() == 2;
  } );
}
