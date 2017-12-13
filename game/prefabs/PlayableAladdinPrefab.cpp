#include "PlayableAladdinPrefab.h"
#include "../Define.h"
#include "../scripts/DirectionController.h"
#include "../scripts/PlayableAladdinController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PlayableAladdinPrefab, ala::Prefab)

void PlayableAladdinPrefab::doInstantiate( ala::GameObject* object ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto input = Input::get();
  const auto density = 5.0f;

  const auto throwImpulse = Vec2( 20000.0f, 1000.0f );
  const auto swordOffset1 = Vec2( 45, 10 );
  const auto swordSize1 = Size( 40, 45 );
  const auto swordOffset2 = Vec2( 55, -2.5f );
  const auto swordSize2 = Size( 40, 20 );
  const auto swordOffset5 = Vec2( -35, 20 );
  const auto swordSize5 = Size( 25, 40 );
  const auto swordOffset6 = Vec2( 35, 25 );
  const auto swordSize6 = Size( 35, 45 );

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "aladdin.png" );

  const auto animator = new Animator( object, "idle_1", "aladdin.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial( density ), ALA_BODY_TYPE_DYNAMIC, 1.0f );

  const auto collider = new Collider( object, false, Vec2( 0, 0 ), Size( 40, 50 ), 1, 0, "Body" );
  collider->setTag( ALADDIN_TAG );
  collider->ignoreTag( ALADDIN_TAG );
  collider->ignoreTag( ENEMY_TAG );

  const auto swordCollider = new Collider( object, true, Vec2(), Size( 0, 0 ), 0, 0, "Sword" );
  swordCollider->setTag( SWORD_TAG );
  swordCollider->ignoreTag( ALADDIN_TAG );
  swordCollider->setActive( false );

  const auto stateManager = new StateManager( object, "idle" );

  const auto direction = new DirectionController( object, true, 1 );

  const auto controller = new PlayableAladdinController( object );

  // helpers
  const auto transform = object->getTransform();

  const auto timer1 = new Timer( object );

  const auto timer2 = new Timer( object );

  const auto timer3 = new Timer( object );

  const auto timer4 = new Timer( object );

  // collider renderers
  new ColliderRenderer( collider );

  new ColliderRenderer( swordCollider );

  // configurations
  object->setTag( ALADDIN_TAG );
  object->setLayer( "Character" );
  controller->setLives( 3 );
  controller->setApples( 10 );

  // states
  new State( stateManager, "idle",
             [=] {
               // animation effect
               {
                 if ( stateManager->getPreviousStateName() == "jump" ) {
                   animator->setAction( "fall_to_idle_1" );
                 }
                 else if ( stateManager->getPreviousStateName() == "jump_attack" ||
                   stateManager->getPreviousStateName() == "run_and_jump" ||
                   stateManager->getPreviousStateName() == "run_and_throw" ||
                   stateManager->getPreviousStateName() == "jump_throw_apple" ) {
                   animator->setAction( "touched_ground" );
                 }
                 else if ( stateManager->getPreviousStateName() == "face_up" ) {
                   animator->setAction( "face_up_to_idle_1" );
                 }
                 else if ( stateManager->getPreviousStateName() == "sit" ) {
                   animator->setAction( "stand_up" );
                 }
                 else {
                   animator->setAction( "idle_1" );
                   timer1->start( 0.5f );
                 }
               }

               // direction
               {
                 if ( input->getKey( ALA_KEY_LEFT_ARROW ) && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( input->getKey( ALA_KEY_RIGHT_ARROW ) && direction->isLeft() ) {
                   direction->setRight();
                 }
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
                 if ( !animator->isPlaying() && timer1->isDone() ) {
                   if ( animator->getActionName() == "idle_4_to_1" ||
                     animator->getActionName() == "fall_to_idle_1" ||
                     animator->getActionName() == "touched_ground" ||
                     animator->getActionName() == "face_up_to_idle_1" ||
                     animator->getActionName() == "stand_up" ) {
                     animator->setAction( "idle_1" );
                     timer1->start( 0.5f );
                   }
                   if ( animator->getActionName() == "idle_1" || animator->getActionName() == "idle_4_to_1" ) {
                     animator->setAction( "idle_1_to_2" );
                   }
                   else if ( animator->getActionName() == "idle_1_to_2" || animator->getActionName() == "idle_3_to_2"
                   ) {
                     const auto way = rand() % 5;
                     if ( way == 0 ) {
                       animator->setAction( "idle_2_to_4" );
                     }
                     else {
                       animator->setAction( "idle_2" );
                       timer1->start( 1.0f * (200 + rand() % 900) / 1000 );
                     }
                   }
                   else if ( animator->getActionName() == "idle_2" ) {
                     animator->setAction( "idle_2_to_3" );
                   }
                   else if ( animator->getActionName() == "idle_2_to_3" ) {
                     animator->setAction( "idle_3" );
                     timer1->start( 1.0f * (200 + rand() % 900) / 1000 );
                   }
                   else if ( animator->getActionName() == "idle_3" ) {
                     animator->setAction( "idle_3_to_2" );
                   }
                   else if ( animator->getActionName() == "idle_2_to_4" ||
                     animator->getActionName() == "idle_4_to_4_way_1" ||
                     animator->getActionName() == "idle_4_to_4_way_2" ) {
                     const auto way = rand() % 9;
                     if ( way < 4 ) {
                       animator->setAction( "idle_4_to_4_way_1" );
                     }
                     else if ( way < 8 ) {
                       animator->setAction( "idle_4_to_4_way_2" );
                     }
                     else {
                       animator->setAction( "idle_4_to_1" );
                     }
                   }
                 }
               }

               // change direction
               {
                 if ( input->getKeyDown( ALA_KEY_LEFT_ARROW ) && direction->isRight() ) {
                   direction->setLeft();
                   animator->setAction( "idle_1" );
                   timer1->start( 0.5f );
                 }
                 else if ( input->getKeyDown( ALA_KEY_RIGHT_ARROW ) && direction->isLeft() ) {
                   direction->setRight();
                   animator->setAction( "idle_1" );
                   timer1->start( 0.5f );
                 }
               }
             }, NULL );

  new State( stateManager, "attack",
             [=] {
               // animation effect
               {
                 animator->setAction( "attack_1" );
               }

               // sword
               {
                 swordCollider->setOffset( swordOffset1 );
                 swordCollider->setSize( swordSize1 );
                 swordCollider->setActive( false );
                 timer4->start( 0.2f );
               }
             },
             [=]( float dt ) {
               // sword
               {
                 if ( timer4->isDone() ) {
                   if ( !swordCollider->isActive() ) {
                     swordCollider->setActive( true );
                     timer4->start( 0.2f );
                   }
                   else {
                     swordCollider->setActive( false );
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

  new State( stateManager, "throw",
             [=] {
               // animation effect
               {
                 animator->setAction( "attack_3" );
               }

               // throw
               {
                 timer1->start( 0.1f );
               }
             },
             [=]( float ) {
               // direction
               {
                 if ( input->getKeyDown( ALA_KEY_LEFT_ARROW ) && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( input->getKeyDown( ALA_KEY_RIGHT_ARROW ) && direction->isLeft() ) {
                   direction->setRight();
                 }
               }

               // throw 
               {
                 if ( timer1->isDone() ) {
                   if ( direction->isRight() ) {
                     controller->throwApple( 'R', 0.0f, 0.0f, throwImpulse.getX(), throwImpulse.getY() );
                   }
                   else {
                     controller->throwApple( 'L', 0.0f, 0.0f, throwImpulse.getX(), throwImpulse.getY() );
                   }

                   timer1->start( 5.0f );
                 }
               }
             }, NULL );

  new State( stateManager, "face_up",
             [=] {
               // animation effect 
               {
                 if ( stateManager->getPreviousStateName() == "face_up_attack" ||
                   stateManager->getPreviousStateName() == "face_up_throw" ) {
                   animator->setAction( "face_is_up" );
                 }
                 else {
                   animator->setAction( "face_up" );
                 }
               }

               // direction
               {
                 if ( input->getKey( ALA_KEY_LEFT_ARROW ) && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( input->getKey( ALA_KEY_RIGHT_ARROW ) && direction->isLeft() ) {
                   direction->setRight();
                 }
               }
             },
             [=]( float dt ) {
               // direction
               {
                 if ( input->getKeyDown( ALA_KEY_LEFT_ARROW ) && direction->isRight() ) {
                   direction->setLeft();
                   if ( !animator->isPlaying() ) {
                     animator->setAction( "face_is_up" );
                   }
                 }
                 else if ( input->getKeyDown( ALA_KEY_RIGHT_ARROW ) && direction->isLeft() ) {
                   direction->setRight();
                   if ( !animator->isPlaying() ) {
                     animator->setAction( "face_is_up" );
                   }
                 }
               }
             }, NULL );

  new State( stateManager, "face_up_attack",
             [=] {
               // animation effect
               {
                 animator->setAction( "attack_2" );
               }

               // direction
               {
                 if ( input->getKey( ALA_KEY_LEFT_ARROW ) && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( input->getKey( ALA_KEY_RIGHT_ARROW ) && direction->isLeft() ) {
                   direction->setRight();
                 }
               }

               // sword
               {
                 swordCollider->setOffset( swordOffset5 );
                 swordCollider->setSize( swordSize5 );
                 swordCollider->setActive( false );
                 timer4->start( 0.2f );
               }
             },
             [=]( float dt ) {
               // sword
               {
                 if ( timer4->isDone() ) {
                   if ( !swordCollider->isActive() ) {
                     swordCollider->setActive( true );
                     timer4->start( 0.25f );
                   }
                   else {
                     swordCollider->setActive( false );
                     if ( swordCollider->getOffset() == swordOffset5 ) {
                       swordCollider->setOffset( swordOffset6 );
                       swordCollider->setSize( swordSize6 );
                       timer4->start( 0.15f );
                     }
                     else {
                       timer4->start( 5 );
                     }
                   }
                 }
               }

               // direction
               {
                 if ( input->getKeyDown( ALA_KEY_LEFT_ARROW ) && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( input->getKeyDown( ALA_KEY_RIGHT_ARROW ) && direction->isLeft() ) {
                   direction->setRight();
                 }
               }
             },
             [=] {
               // sword
               {
                 swordCollider->setActive( false );
               }
             } );

  new State( stateManager, "face_up_throw",
             [=] {
               // animation effect
               {
                 animator->setAction( "attack_3" );
               }

               // throw
               {
                 timer1->start( 0.1f );
               }
             },
             [=]( float ) {
               // direction
               {
                 if ( input->getKeyDown( ALA_KEY_LEFT_ARROW ) && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( input->getKeyDown( ALA_KEY_RIGHT_ARROW ) && direction->isLeft() ) {
                   direction->setRight();
                 }
               }

               // throw
               {
                 if ( timer1->isDone() ) {
                   if ( direction->isRight() ) {
                     controller->throwApple( 'R', 0.0f, 0.0f, throwImpulse.getX(), throwImpulse.getY() );
                   }
                   else {
                     controller->throwApple( 'L', 0.0f, 0.0f, throwImpulse.getX(), throwImpulse.getY() );
                   }

                   timer1->start( 5.0f );
                 }
               }
             }, NULL );

  new State( stateManager, "sit",
             [=] {
               // animation effect 
               {
                 if ( stateManager->getPreviousStateName() == "sit_attack" ) {
                   animator->setAction( "sit_attack_1_to_sit" );
                 }
                 else if ( stateManager->getPreviousStateName() == "sit_throw" ) {
                   animator->setAction( "sit_attack_2_to_sit" );
                 }
                 else {
                   animator->setAction( "sit_down" );
                 }
               }

               // direction
               {
                 if ( input->getKey( ALA_KEY_LEFT_ARROW ) && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( input->getKey( ALA_KEY_RIGHT_ARROW ) && direction->isLeft() ) {
                   direction->setRight();
                 }
               }
             },
             [=]( float dt ) {
               // direction
               {
                 if ( input->getKeyDown( ALA_KEY_LEFT_ARROW ) && direction->isRight() ) {
                   direction->setLeft();
                   if ( !animator->isPlaying() ) {
                     animator->setAction( "sit" );
                   }
                 }
                 else if ( input->getKeyDown( ALA_KEY_RIGHT_ARROW ) && direction->isLeft() ) {
                   direction->setRight();
                   if ( !animator->isPlaying() ) {
                     animator->setAction( "sit" );
                   }
                 }
               }
             }, NULL );

  new State( stateManager, "sit_attack",
             [=] {
               // animation effect
               {
                 animator->setAction( "sit_attack_1" );
               }

               // direction
               {
                 if ( input->getKey( ALA_KEY_LEFT_ARROW ) && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( input->getKey( ALA_KEY_RIGHT_ARROW ) && direction->isLeft() ) {
                   direction->setRight();
                 }
               }

               // sword
               {
                 swordCollider->setOffset( swordOffset2 );
                 swordCollider->setSize( swordSize2 );
                 swordCollider->setActive( false );
                 timer4->start( 0.2f );
               }
             },
             [=]( float dt ) {
               // sword
               {
                 if ( timer4->isDone() ) {
                   if ( !swordCollider->isActive() ) {
                     swordCollider->setActive( true );
                     timer4->start( 0.2f );
                   }
                   else {
                     swordCollider->setActive( false );
                   }
                 }
               }

               // direction
               {
                 if ( input->getKeyDown( ALA_KEY_LEFT_ARROW ) && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( input->getKeyDown( ALA_KEY_RIGHT_ARROW ) && direction->isLeft() ) {
                   direction->setRight();
                 }
               }
             },
             [=] {
               // sword
               {
                 swordCollider->setActive( false );
               }
             } );

  new State( stateManager, "sit_throw",
             [=] {
               // animation effect
               {
                 animator->setAction( "sit_attack_2" );
               }

               // throw
               {
                 timer1->start( 0.1f );
               }
             },
             [=]( float ) {
               // direction
               {
                 if ( input->getKeyDown( ALA_KEY_LEFT_ARROW ) && direction->isRight() ) {
                   direction->setLeft();
                 }
                 else if ( input->getKeyDown( ALA_KEY_RIGHT_ARROW ) && direction->isLeft() ) {
                   direction->setRight();
                 }
               }

               // throw
               if ( timer1->isDone() ) {
                 if ( direction->isRight() ) {
                   controller->throwApple( 'R', 0, -collider->getSize().getHeight() / 4,
                                           throwImpulse.getX(), throwImpulse.getY() );
                 }
                 else {
                   controller->throwApple( 'L', 0, -collider->getSize().getHeight() / 4,
                                           throwImpulse.getX(), throwImpulse.getY() );
                 }

                 timer1->start( 5.0f );
               }
             }, NULL );

  new StateTransition( stateManager, "idle", "attack", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "attack", "idle", [=] {
    return (!animator->isPlaying())
      || (direction->isRight() && input->getKey( ALA_KEY_LEFT_ARROW ))
      || (direction->isLeft() && input->getKey( ALA_KEY_RIGHT_ARROW ));;
  } );

  new StateTransition( stateManager, "idle", "throw", [=] {
    return input->getKeyDown( ALA_KEY_A ) && controller->getApples() > 0;
  } );

  new StateTransition( stateManager, "throw", "idle", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "idle", "sit", [=] {
    return input->getKey( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "attack", "sit", [=] {
    return input->getKey( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "sit", "idle", [=] {
    return !input->getKey( ALA_KEY_DOWN_ARROW ) && !animator->isPlaying();
  } );

  new StateTransition( stateManager, "sit", "sit_attack", [=] {
    return input->getKeyDown( ALA_KEY_S ) && !animator->isPlaying();
  } );

  new StateTransition( stateManager, "sit_attack", "sit", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "sit", "sit_throw", [=] {
    return input->getKeyDown( ALA_KEY_A ) && !animator->isPlaying() && controller->getApples() > 0;
  } );

  new StateTransition( stateManager, "sit_throw", "sit", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "idle", "face_up", [=] {
    return input->getKey( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( stateManager, "attack", "face_up", [=] {
    return input->getKey( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( stateManager, "face_up", "idle", [=] {
    return !input->getKey( ALA_KEY_UP_ARROW ) && !animator->isPlaying();
  } );

  new StateTransition( stateManager, "face_up", "face_up_attack", [=] {
    return input->getKeyDown( ALA_KEY_S ) && !animator->isPlaying();
  } );

  new StateTransition( stateManager, "face_up_attack", "face_up", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "face_up", "face_up_throw", [=] {
    return input->getKeyDown( ALA_KEY_A ) && !animator->isPlaying() && controller->getApples() > 0;
  } );

  new StateTransition( stateManager, "face_up_throw", "face_up", [=] {
    return input->getKey( ALA_KEY_UP_ARROW ) && !animator->isPlaying();
  } );
}
