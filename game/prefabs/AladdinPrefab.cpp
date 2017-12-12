#include "AladdinPrefab.h"
#include "../scripts/AladdinController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void AladdinPrefab::doInstantiate( ala::GameObject* object ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto input = Input::get();

  const auto density = 5.0f;
  const auto runVelocity = 140.0f;
  const auto stopAcceleration = 4.0f;
  const auto swordOffset1 = Vec2( 45, 10 );
  const auto swordSize1 = Size( 40, 45 );
  const auto swordOffset2 = Vec2( 55, -2.5f );
  const auto swordSize2 = Size( 40, 20 );
  const auto swordOffset3 = Vec2( 25, 10 );
  const auto swordSize3 = Size( 25, 40 );
  const auto swordOffset4 = Vec2( 20, 0 );
  const auto swordSize4 = Size( 40, 55 );
  const auto swordOffset5 = Vec2( -35, 20 );
  const auto swordSize5 = Size( 25, 40 );
  const auto swordOffset6 = Vec2( 35, 25 );
  const auto swordSize6 = Size( 35, 45 );

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "aladdin.png" );

  const auto animator = new Animator( object, "idle_1", "aladdin.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial( density ), ALA_BODY_TYPE_DYNAMIC, 1.0f );

  const auto collider = new Collider( object, false, Vec2( 0, 0 ), Size( 40, 50 ) );
  collider->setTag( ALADDIN_TAG );
  collider->ignoreTag( ALADDIN_TAG );
  collider->ignoreTag( ENEMY_TAG );

  const auto swordCollider = new Collider( object, true, Vec2(), Size( 0, 0 ), 0 );
  swordCollider->setTag( SWORD_TAG );
  swordCollider->ignoreTag( ALADDIN_TAG );
  swordCollider->setActive( false );

  const auto stateManager = new StateManager( object, "idle_right" );

  const auto actionManager = new ActionManager( object );
  
  const auto controller = new AladdinController( object, "Controller" );

  // helpers
  const auto transform = object->getTransform();
  
  const auto timer1 = new Timer( object );
  
  const auto timer2 = new Timer( object );
  
  const auto timer3 = new Timer( object );
  
  const auto timer4 = new Timer( object );

  // collider renderers
  const auto colliderRenderer = new ColliderRenderer( collider );

  const auto swordColliderRenderer = new ColliderRenderer( swordCollider );

  // configurations
  object->setTag( ALADDIN_TAG );
  object->setLayer( "Character" );
  controller->setLives( 3 );
  controller->setApples( 5 );
  controller->setHealth( 10 );

  // states
  new State( stateManager, "idle_left",
             [=] {
               if ( stateManager->getPreviousStateName() == "jump_left" ) {
                 animator->setAction( "fall_to_idle_1" );
               }
               else if ( stateManager->getPreviousStateName() == "jump_left_attack" ||
                 stateManager->getPreviousStateName() == "run_left_to_jump" ||
                 stateManager->getPreviousStateName() == "jump_throw_apple_left" ||
                 stateManager->getPreviousStateName() == "run_left_to_throw" ) {
                 animator->setAction( "touched_ground" );
               }
               else if ( stateManager->getPreviousStateName() == "face_up_left" ) {
                 animator->setAction( "face_up_to_idle_1" );
               }
               else if ( stateManager->getPreviousStateName() == "sit_left" ) {
                 animator->setAction( "stand_up" );
               }
               else {
                 animator->setAction( "idle_1" );
                 timer1->start( 0.5f );
               }
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             },
             [=]( float dt ) {
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
                 else if ( animator->getActionName() == "idle_1_to_2" || animator->getActionName() == "idle_3_to_2" ) {
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
             }, NULL );

  new State( stateManager, "idle_right",
             [=] {
               if ( stateManager->getPreviousStateName() == "jump_right" ) {
                 animator->setAction( "fall_to_idle_1" );
               }
               else if ( stateManager->getPreviousStateName() == "jump_right_attack" ||
                 stateManager->getPreviousStateName() == "run_right_to_jump" ||
                 stateManager->getPreviousStateName() == "jump_throw_apple_right" ||
                 stateManager->getPreviousStateName() == "run_right_to_throw" ) {
                 animator->setAction( "touched_ground" );
               }
               else if ( stateManager->getPreviousStateName() == "face_up_right" ) {
                 animator->setAction( "face_up_to_idle_1" );
               }
               else if ( stateManager->getPreviousStateName() == "sit_right" ) {
                 animator->setAction( "stand_up" );
               }
               else {
                 animator->setAction( "idle_1" );
                 timer1->start( 0.5f );
               }
               transform->setScaleX( ABS(transform->getScale().getX()) );
               body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             },
             [=]( float dt ) {
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
                 else if ( animator->getActionName() == "idle_1_to_2" || animator->getActionName() == "idle_3_to_2" ) {
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
             }, NULL );

  new State( stateManager, "attack_1_left",
             [=] {
               animator->setAction( "attack_1" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );

               swordCollider->setOffset( swordOffset1 );
               swordCollider->setSize( swordSize1 );
               swordCollider->setActive( false );
               timer4->start( 0.2f );
             },
             [=]( float dt ) {
               if ( timer4->isDone() ) {
                 if ( !swordCollider->isActive() ) {
                   swordCollider->setActive( true );
                   timer4->start( 0.2f );
                 }
                 else {
                   swordCollider->setActive( false );
                 }
               }
             },
             [=] {
               swordCollider->setActive( false );
             } );

  new State( stateManager, "attack_1_right",
             [=] {
               animator->setAction( "attack_1" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
               swordCollider->setOffset( swordOffset1 );
               swordCollider->setSize( swordSize1 );
               swordCollider->setActive( false );
               timer4->start( 0.2f );
             },
             [=]( float dt ) {
               if ( timer4->isDone() ) {
                 if ( !swordCollider->isActive() ) {
                   swordCollider->setActive( true );
                   timer4->start( 0.2f );
                 }
                 else {
                   swordCollider->setActive( false );
                 }
               }
             },
             [=] {
               swordCollider->setActive( false );
             } );

  new State( stateManager, "attack_2_left",
             [=] {
               animator->setAction( "attack_2" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );

               swordCollider->setOffset( swordOffset5 );
               swordCollider->setSize( swordSize5 );
               swordCollider->setActive( false );
               timer4->start( 0.2f );
             },
             [=]( float dt ) {
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
             },
             [=] {
               swordCollider->setActive( false );
             } );

  new State( stateManager, "attack_2_right",
             [=] {
               animator->setAction( "attack_2" );
               transform->setScaleX( ABS(transform->getScale().getX()) );

               swordCollider->setOffset( swordOffset5 );
               swordCollider->setSize( swordSize5 );
               swordCollider->setActive( false );
               timer4->start( 0.2f );
             },
             [=]( float dt ) {
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
             },
             [=] {
               swordCollider->setActive( false );
             } );

  new State( stateManager, "face_up_left",
             [=] {
               if ( stateManager->getPreviousStateName() == "face_up_right" ) {
                 animator->setAction( "face_is_up" );
               }
               else {
                 animator->setAction( "face_up" );
               }
               transform->setScaleX( -ABS(transform->getScale().getX()) );
             }, NULL, NULL );

  new State( stateManager, "face_up_right",
             [=] {
               if ( stateManager->getPreviousStateName() == "face_up_left" ) {
                 animator->setAction( "face_is_up" );
               }
               else {
                 animator->setAction( "face_up" );
               }
               transform->setScaleX( ABS(transform->getScale().getX()) );
             }, NULL, NULL );

  new State( stateManager, "attack_3_left",
             [=] {
               animator->setAction( "attack_3" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               timer1->start( 0.1f );
             },
             [=]( float ) {
               if ( timer1->isDone() ) {
                 controller->throwApple( 'L', 0.0f, 0.0f, -20000.0f, 1000.0f );
                 timer1->start( 5.0f );
               }
             }, NULL );

  new State( stateManager, "attack_3_right",
             [=] {
               animator->setAction( "attack_3" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
               timer1->start( 0.1f );
             },
             [=]( float ) {
               if ( timer1->isDone() ) {
                 controller->throwApple( 'R', 0.0f, 0.0f, 20000.0f, 1000.0f );
                 timer1->start( 5.0f );
               }
             }, NULL );

  new State( stateManager, "sit_left",
             [=] {
               if ( stateManager->getPreviousStateName() == "idle_left" ) {
                 animator->setAction( "sit_down" );
               }
               else if ( stateManager->getPreviousStateName() == "sit_attack_1_left" ) {
                 animator->setAction( "sit_attack_1_to_sit" );
               }
               else if ( stateManager->getPreviousStateName() == "sit_attack_2_left" ) {
                 animator->setAction( "sit_attack_2_to_sit" );
               }
               else if ( stateManager->getPreviousStateName() == "sit_right" ) {
                 animator->setAction( "sit" );
               }
               transform->setScaleX( -ABS(transform->getScale().getX()) );
             }, NULL, NULL );

  new State( stateManager, "sit_right",
             [=] {
               if ( stateManager->getPreviousStateName() == "idle_right" ) {
                 animator->setAction( "sit_down" );
               }
               else if ( stateManager->getPreviousStateName() == "sit_attack_1_right" ) {
                 animator->setAction( "sit_attack_1_to_sit" );
               }
               else if ( stateManager->getPreviousStateName() == "sit_attack_2_right" ) {
                 animator->setAction( "sit_attack_2_to_sit" );
               }
               else if ( stateManager->getPreviousStateName() == "sit_left" ) {
                 animator->setAction( "sit" );
               }
               transform->setScaleX( ABS(transform->getScale().getX()) );
             }, NULL, NULL );

  new State( stateManager, "sit_attack_1_left",
             [=] {
               animator->setAction( "sit_attack_1" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );

               swordCollider->setOffset( swordOffset2 );
               swordCollider->setSize( swordSize2 );
               swordCollider->setActive( false );
               timer4->start( 0.2f );
             },
             [=]( float dt ) {
               if ( timer4->isDone() ) {
                 if ( !swordCollider->isActive() ) {
                   swordCollider->setActive( true );
                   timer4->start( 0.2f );
                 }
                 else {
                   swordCollider->setActive( false );
                 }
               }
             },
             [=] {
               swordCollider->setActive( false );
             } );

  new State( stateManager, "sit_attack_1_right",
             [=] {
               animator->setAction( "sit_attack_1" );
               transform->setScaleX( ABS(transform->getScale().getX()) );

               swordCollider->setOffset( swordOffset2 );
               swordCollider->setSize( swordSize2 );
               swordCollider->setActive( false );
               timer4->start( 0.2f );
             },
             [=]( float dt ) {
               if ( timer4->isDone() ) {
                 if ( !swordCollider->isActive() ) {
                   swordCollider->setActive( true );
                   timer4->start( 0.2f );
                 }
                 else {
                   swordCollider->setActive( false );
                 }
               }
             },
             [=] {
               swordCollider->setActive( false );
             } );

  new State( stateManager, "sit_attack_2_left",
             [=] {
               animator->setAction( "sit_attack_2" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               timer1->start( 0.1f );
             },
             [=]( float ) {
               if ( timer1->isDone() ) {
                 controller->throwApple( 'L',
                                         -(collider->getSize().getHeight()),
                                         -(collider->getSize().getHeight() / 4), -20000.0f, 1000.0f );
                 timer1->start( 5.0f );
               }
             }, NULL );

  new State( stateManager, "sit_attack_2_right",
             [=] {
               animator->setAction( "sit_attack_2" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
               timer1->start( 0.1f );
             },
             [=]( float ) {
               if ( timer1->isDone() ) {
                 controller->throwApple( 'R', 0, -(collider->getSize().getHeight() / 4), 20000.0f, 1000.0f );
                 timer1->start( 5.0f );
               }
             }, NULL );

  new State( stateManager, "run_left",
             [=] {
               animator->setAction( "start_run" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               timer1->start( 1 );
               body->setVelocity( Vec2( -runVelocity, body->getVelocity().getY() ) );
             },
             [=]( float dt ) {
               if ( !animator->isPlaying() && animator->getActionName() == "start_run" ) {
                 animator->setAction( "run" );
               }
             }
             , NULL );

  new State( stateManager, "run_right",
             [=] {
               animator->setAction( "start_run" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
               timer1->start( 1 );
               body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );
             },
             [=]( float dt ) {
               if ( !animator->isPlaying() && animator->getActionName() == "start_run" ) {
                 animator->setAction( "run" );
               }
             }
             , NULL );

  new State( stateManager, "stop_left",
             [=] {
               animator->setAction( "stop" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
             },
             [=]( float dt ) {
               float newVelocity = 0;
               if ( body->getVelocity() < 0 ) {
                 newVelocity = body->getVelocity().getX() + stopAcceleration;
                 if ( newVelocity > 0 ) newVelocity = 0;
               }
               else if ( body->getVelocity() > 0 ) {
                 newVelocity = body->getVelocity().getX() - stopAcceleration;
                 if ( newVelocity < 0 ) newVelocity = 0;
               }

               body->setVelocity( Vec2( newVelocity, body->getVelocity().getY() ) );
             }, NULL );

  new State( stateManager, "stop_right",
             [=] {
               animator->setAction( "stop" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
             },
             [=]( float dt ) {
               float newVelocity = 0;
               if ( body->getVelocity() < 0 ) {
                 newVelocity = body->getVelocity().getX() + stopAcceleration;
                 if ( newVelocity > 0 ) newVelocity = 0;
               }
               else if ( body->getVelocity() > 0 ) {
                 newVelocity = body->getVelocity().getX() - stopAcceleration;
                 if ( newVelocity < 0 ) newVelocity = 0;
               }

               body->setVelocity( Vec2( newVelocity, body->getVelocity().getY() ) );
             }, NULL );

  new State( stateManager, "jump_left",
             [=] {
               if ( stateManager->getPreviousStateName() != "jump_right" ) {
                 animator->setAction( "jump" );
                 transform->setScaleX( -ABS(transform->getScale().getX()) );
                 controller->resetCollidedWithGround();
                 body->addImpulse( Vec2( 0, 3000000.0f ) );
               }
               else {
                 transform->setScaleX( -ABS(transform->getScale().getX()) );
               }
             },
             [=]( float dt ) {
               if ( body->getVelocity().getY() < -10 && animator->getActionName() == "jump" )
                 animator->setAction( "fall" );

               if ( input->getKey( ALA_KEY_LEFT_ARROW ) )
                 body->setVelocity( Vec2( -runVelocity, body->getVelocity().getY() ) );

               if ( input->getKeyUp( ALA_KEY_LEFT_ARROW ) )
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL );

  new State( stateManager, "jump_right",
             [=] {
               if ( stateManager->getPreviousStateName() != "jump_left" ) {
                 animator->setAction( "jump" );
                 transform->setScaleX( ABS(transform->getScale().getX()) );
                 controller->resetCollidedWithGround();
                 body->addImpulse( Vec2( 0, 3000000.0f ) );
               }
               else {
                 transform->setScaleX( ABS(transform->getScale().getX()) );
               }
             },
             [=]( float dt ) {
               if ( body->getVelocity().getY() < -10 && animator->getActionName() == "jump" )
                 animator->setAction( "fall" );

               if ( input->getKey( ALA_KEY_RIGHT_ARROW ) )
                 body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );

               if ( input->getKeyUp( ALA_KEY_RIGHT_ARROW ) )
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL );

  new State( stateManager, "run_left_to_jump",
             [=] {
               if ( stateManager->getPreviousStateName() != "run_right_to_jump" ) {
                 animator->setAction( "run_to_jump" );
                 transform->setScaleX( -ABS(transform->getScale().getX()) );
                 controller->resetCollidedWithGround();
                 body->addImpulse( Vec2( 0, 2650000.0f ) );
               }
               else {
                 transform->setScaleX( -ABS(transform->getScale().getX()) );
               }
             },
             [=]( float dt ) {
               if ( body->getVelocity().getY() < 0 && animator->getActionName() == "run_to_jump" )
                 animator->setAction( "run_to_jump_fall" );

               if ( input->getKey( ALA_KEY_LEFT_ARROW ) )
                 body->setVelocity( Vec2( -runVelocity, body->getVelocity().getY() ) );

               if ( input->getKeyUp( ALA_KEY_LEFT_ARROW ) )
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL );

  new State( stateManager, "run_right_to_jump",
             [=] {
               if ( stateManager->getPreviousStateName() != "run_left_to_jump" ) {
                 animator->setAction( "run_to_jump" );
                 transform->setScaleX( ABS(transform->getScale().getX()) );
                 controller->resetCollidedWithGround();
                 body->addImpulse( Vec2( 0, 2650000.0f ) );
               }
               else {
                 transform->setScaleX( ABS(transform->getScale().getX()) );
               }
             },
             [=]( float dt ) {
               if ( body->getVelocity().getY() < 0 && animator->getActionName() == "run_to_jump" )
                 animator->setAction( "run_to_jump_fall" );

               if ( input->getKey( ALA_KEY_RIGHT_ARROW ) )
                 body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );

               if ( input->getKeyUp( ALA_KEY_RIGHT_ARROW ) )
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
             }, NULL );

  new State( stateManager, "jump_left_attack",
             [=] {
               if ( stateManager->getPreviousStateName() != "jump_right_attack" )
                 animator->setAction( "jump_attack" );
               else
                 transform->setScaleX( -ABS(transform->getScale().getX()) );

               swordCollider->setOffset( swordOffset4 );
               swordCollider->setSize( swordSize4 );
               swordCollider->setActive( false );
               timer4->start( 0.2f );
             },
             [=]( float dt ) {
               if ( body->getVelocity().getY() < -3 && animator->getActionName() == "jump_attack" )
                 animator->setAction( "jump_attack_fall" );

               if ( input->getKey( ALA_KEY_LEFT_ARROW ) )
                 body->setVelocity( Vec2( -runVelocity, body->getVelocity().getY() ) );

               if ( input->getKeyUp( ALA_KEY_LEFT_ARROW ) )
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );

               if ( timer4->isDone() ) {
                 if ( !swordCollider->isActive() ) {
                   swordCollider->setActive( true );
                   timer4->start( 0.2f );
                 }
                 else {
                   swordCollider->setActive( false );
                   timer4->start( 5 );
                 }
               }
             },
             [=] {
               swordCollider->setActive( false );
             } );

  new State( stateManager, "jump_right_attack",
             [=] {
               if ( stateManager->getPreviousStateName() != "jump_left_attack" )
                 animator->setAction( "jump_attack" );
               else
                 transform->setScaleX( ABS(transform->getScale().getX()) );

               swordCollider->setOffset( swordOffset4 );
               swordCollider->setSize( swordSize4 );
               swordCollider->setActive( false );
               timer4->start( 0.2f );
             },
             [=]( float dt ) {
               if ( body->getVelocity().getY() < -3 && animator->getActionName() == "jump_attack" )
                 animator->setAction( "jump_attack_fall" );

               if ( input->getKey( ALA_KEY_RIGHT_ARROW ) )
                 body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );

               if ( input->getKeyUp( ALA_KEY_RIGHT_ARROW ) )
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );

               if ( timer4->isDone() ) {
                 if ( !swordCollider->isActive() ) {
                   swordCollider->setActive( true );
                   timer4->start( 0.2f );
                 }
                 else {
                   swordCollider->setActive( false );
                   timer4->start( 5 );
                 }
               }
             },
             [=] {
               swordCollider->setActive( false );
             } );

  new State( stateManager, "run_left_to_throw",
             [=] {
               if ( stateManager->getPreviousStateName() != "run_right_to_throw" ) {
                 animator->setAction( "jump_throw_apple" );
                 timer2->start( 0.1f );
                 timer3->start( 0.3f );
               }
             },
             [=]( float dt ) {
               if ( timer2->isDone() ) {
                 controller->throwApple( 'L', 0.0f, -10.0f, -20000.0f, 1000.0f );
                 animator->setAction( "jump_throw_apple_fall" );
                 timer2->start( 2.0f );
               }

               if ( input->getKey( ALA_KEY_RIGHT_ARROW ) ) {
                 transform->setScaleX( ABS(transform->getScale().getX()) );
                 body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );
               }
               if ( input->getKey( ALA_KEY_LEFT_ARROW ) ) {
                 body->setVelocity( Vec2( -runVelocity, body->getVelocity().getY() ) );
                 transform->setScaleX( -ABS(transform->getScale().getX()) );
               }
               if ( input->getKeyUp( ALA_KEY_RIGHT_ARROW ) || input->getKeyUp( ALA_KEY_LEFT_ARROW ) )
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
               if ( controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A ) && timer3->isDone() ) {
                 timer2->start( 0.1f );
                 timer3->start( 0.3f );
                 animator->setAction( "jump_throw_apple" );
               }
             }
             , NULL );

  new State( stateManager, "run_right_to_throw",
             [=] {
               if ( stateManager->getPreviousStateName() != "run_left_to_throw" ) {
                 animator->setAction( "jump_throw_apple" );
                 timer2->start( 0.1f );
                 timer3->start( 0.3f );
               }
             },
             [=]( float dt ) {
               if ( timer2->isDone() ) {
                 controller->throwApple( 'R', 0.0f, -10.0f, 20000.0f, 1000.0f );
                 animator->setAction( "jump_throw_apple_fall" );
                 timer2->start( 2.0f );
               }

               if ( input->getKey( ALA_KEY_RIGHT_ARROW ) ) {
                 transform->setScaleX( ABS(transform->getScale().getX()) );
                 body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );
               }
               if ( input->getKey( ALA_KEY_LEFT_ARROW ) ) {
                 body->setVelocity( Vec2( -runVelocity, body->getVelocity().getY() ) );
                 transform->setScaleX( -ABS(transform->getScale().getX()) );
               }
               if ( input->getKeyUp( ALA_KEY_RIGHT_ARROW ) || input->getKeyUp( ALA_KEY_LEFT_ARROW ) )
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
               if ( controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A ) && timer3->isDone() ) {
                 timer2->start( 0.1f );
                 timer3->start( 0.3f );
                 animator->setAction( "jump_throw_apple" );
               }
             }
             , NULL );

  new State( stateManager, "jump_throw_apple_left",
             [=] {
               if ( stateManager->getPreviousStateName() != "jump_throw_apple_right" ) {
                 animator->setAction( "jump_throw_apple" );
                 timer2->start( 0.1f );
                 timer3->start( 0.3f );
               }
             },
             [=]( float dt ) {
               if ( timer2->isDone() ) {
                 controller->throwApple( 'L',
                                         -(collider->getSize().getHeight() - 5.0f),
                                         -(collider->getSize().getHeight() / 4), -20000.0f, 1000.0f );
                 animator->setAction( "jump_throw_apple_fall" );
                 timer2->start( 2.0f );
               }

               if ( input->getKey( ALA_KEY_RIGHT_ARROW ) ) {
                 transform->setScaleX( ABS(transform->getScale().getX()) );
                 body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );
               }
               if ( input->getKey( ALA_KEY_LEFT_ARROW ) ) {
                 body->setVelocity( Vec2( -runVelocity, body->getVelocity().getY() ) );
                 transform->setScaleX( -ABS(transform->getScale().getX()) );
               }
               if ( input->getKeyUp( ALA_KEY_RIGHT_ARROW ) || input->getKeyUp( ALA_KEY_LEFT_ARROW ) )
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
               if ( controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A ) && timer3->isDone() ) {
                 timer2->start( 0.1f );
                 timer3->start( 0.3f );
                 animator->setAction( "jump_throw_apple" );
               }
             }
             , NULL );

  new State( stateManager, "jump_throw_apple_right",
             [=] {
               if ( stateManager->getPreviousStateName() != "jump_throw_apple_left" ) {
                 animator->setAction( "jump_throw_apple" );
                 timer2->start( 0.1f );
                 timer3->start( 0.3f );
               }
             },
             [=]( float dt ) {
               if ( timer2->isDone() ) {
                 controller->throwApple( 'R', 0.0f, -10.0f, 20000.0f, 1000.0f );
                 animator->setAction( "jump_throw_apple_fall" );
                 timer2->start( 2.0f );
               }

               if ( input->getKey( ALA_KEY_RIGHT_ARROW ) ) {
                 transform->setScaleX( ABS(transform->getScale().getX()) );
                 body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );
               }
               if ( input->getKey( ALA_KEY_LEFT_ARROW ) ) {
                 body->setVelocity( Vec2( -runVelocity, body->getVelocity().getY() ) );
                 transform->setScaleX( -ABS(transform->getScale().getX()) );
               }
               if ( input->getKeyUp( ALA_KEY_RIGHT_ARROW ) || input->getKeyUp( ALA_KEY_LEFT_ARROW ) )
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );
               if ( controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A ) && timer3->isDone() ) {
                 timer2->start( 0.1f );
                 timer3->start( 0.3f );
                 animator->setAction( "jump_throw_apple" );
               }
             }
             , NULL );

  new State( stateManager, "run_left_to_jump_attack",
             [=] {
               if ( stateManager->getPreviousStateName() != "run_right_to_jump_attack" )
                 animator->setAction( "jump_attack" );
               else
                 transform->setScaleX( -ABS(transform->getScale().getX()) );

               swordCollider->setOffset( swordOffset4 );
               swordCollider->setSize( swordSize4 );
               swordCollider->setActive( false );
               timer4->start( 0.2f );
             },
             [=]( float dt ) {
               if ( body->getVelocity().getY() < -3 && animator->getActionName() == "jump_attack" )
                 animator->setAction( "jump_attack_fall" );

               if ( input->getKey( ALA_KEY_LEFT_ARROW ) )
                 body->setVelocity( Vec2( -runVelocity, body->getVelocity().getY() ) );

               if ( input->getKeyUp( ALA_KEY_LEFT_ARROW ) )
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );

               if ( timer4->isDone() ) {
                 if ( !swordCollider->isActive() ) {
                   swordCollider->setActive( true );
                   timer4->start( 0.2f );
                 }
                 else {
                   swordCollider->setActive( false );
                   timer4->start( 5 );
                 }
               }
             },
             [=] {
               swordCollider->setActive( false );
             } );

  new State( stateManager, "run_right_to_jump_attack",
             [=] {
               if ( stateManager->getPreviousStateName() != "run_left_to_jump_attack" )
                 animator->setAction( "jump_attack" );
               else
                 transform->setScaleX( ABS(transform->getScale().getX()) );

               swordCollider->setOffset( swordOffset4 );
               swordCollider->setSize( swordSize4 );
               swordCollider->setActive( false );
               timer4->start( 0.2f );
             },
             [=]( float dt ) {
               if ( body->getVelocity().getY() < -3 && animator->getActionName() == "jump_attack" )
                 animator->setAction( "jump_attack_fall" );

               if ( input->getKey( ALA_KEY_RIGHT_ARROW ) )
                 body->setVelocity( Vec2( runVelocity, body->getVelocity().getY() ) );

               if ( input->getKeyUp( ALA_KEY_RIGHT_ARROW ) )
                 body->setVelocity( Vec2( 0, body->getVelocity().getY() ) );

               if ( timer4->isDone() ) {
                 if ( !swordCollider->isActive() ) {
                   swordCollider->setActive( true );
                   timer4->start( 0.2f );
                 }
                 else {
                   swordCollider->setActive( false );
                   timer4->start( 5 );
                 }
               }
             },
             [=] {
               swordCollider->setActive( false );
             } );

  new State( stateManager, "run_left_attack",
             [=] {
               animator->setAction( "run_attack" );

               swordCollider->setOffset( swordOffset3 );
               swordCollider->setSize( swordSize3 );
               swordCollider->setActive( false );
               timer4->start( 0.2f );
             },
             [=]( float dt ) {
               if ( timer4->isDone() ) {
                 if ( !swordCollider->isActive() ) {
                   swordCollider->setActive( true );
                   timer4->start( 0.2f );
                 }
                 else {
                   swordCollider->setActive( false );
                 }
               }
             },
             [=] {
               swordCollider->setActive( false );
             } );

  new State( stateManager, "run_right_attack",
             [=] {
               animator->setAction( "run_attack" );

               swordCollider->setOffset( swordOffset3 );
               swordCollider->setSize( swordSize3 );
               swordCollider->setActive( false );
               timer4->start( 0.2f );
             },
             [=]( float dt ) {
               if ( timer4->isDone() ) {
                 if ( !swordCollider->isActive() ) {
                   swordCollider->setActive( true );
                   timer4->start( 0.2f );
                 }
                 else {
                   swordCollider->setActive( false );
                 }
               }
             },
             [=] {
               swordCollider->setActive( false );
             } );

  new State( stateManager, "hit_left", [=] {
    animator->setAction( "hit" );
    transform->setScaleX( -ABS(transform->getScale().getX()) );
    body->setVelocity( Vec2( 0, 0 ) );
  }, NULL, NULL );

  new State( stateManager, "hit_right", [=] {
    animator->setAction( "hit" );
    transform->setScaleX( ABS(transform->getScale().getX()) );
    body->setVelocity( Vec2( 0, 0 ) );
  }, NULL, NULL );

  new StateTransition( stateManager, "idle_left", "idle_right", [=] {
    return input->getKeyDown( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "idle_right", "idle_left", [=] {
    return input->getKeyDown( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "idle_left", "attack_1_left", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "idle_right", "attack_1_right", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "attack_1_left", "idle_left", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "attack_1_right", "idle_right", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "idle_left", "attack_3_left", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "idle_right", "attack_3_right", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "attack_3_left", "idle_left", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "attack_3_right", "idle_right", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "idle_left", "face_up_left", [=] {
    return input->getKey( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( stateManager, "face_up_left", "idle_left", [=] {
    return !input->getKey( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( stateManager, "idle_right", "face_up_right", [=] {
    return input->getKey( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( stateManager, "face_up_right", "idle_right", [=] {
    return !input->getKey( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( stateManager, "face_up_left", "attack_2_left", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "face_up_right", "attack_2_right", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "face_up_left", "attack_3_left", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "face_up_right", "attack_3_right", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "face_up_left", "face_up_right", [=] {
    return input->getKey( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "face_up_right", "face_up_left", [=] {
    return input->getKey( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "attack_2_left", "idle_left", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "attack_2_right", "idle_right", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "idle_left", "sit_left", [=] {
    return input->getKey( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "sit_left", "idle_left", [=] {
    return !input->getKey( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "idle_right", "sit_right", [=] {
    return input->getKey( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "sit_right", "idle_right", [=] {
    return !input->getKey( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "sit_left", "sit_right", [=] {
    return input->getKey( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "sit_right", "sit_left", [=] {
    return input->getKey( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "sit_left", "sit_attack_1_left", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "sit_right", "sit_attack_1_right", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "sit_attack_1_left", "sit_left", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "sit_attack_1_right", "sit_right", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "sit_left", "sit_attack_2_left", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "sit_right", "sit_attack_2_right", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "sit_attack_2_left", "sit_left", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "sit_attack_2_right", "sit_right", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "idle_left", "run_left", [=] {
    return input->getKey( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "idle_left", "run_right", [=] {
    return input->getKey( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "idle_right", "run_left", [=] {
    return input->getKey( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "idle_right", "run_right", [=] {
    return input->getKey( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "run_left", "idle_left", [=] {
    return !input->getKey( ALA_KEY_LEFT_ARROW ) && !timer1->isDone();
  } );

  new StateTransition( stateManager, "run_right", "idle_right", [=] {
    return !input->getKey( ALA_KEY_RIGHT_ARROW ) && !timer1->isDone();
  } );

  new StateTransition( stateManager, "run_left", "stop_left", [=] {
    return !input->getKey( ALA_KEY_LEFT_ARROW ) && timer1->isDone();
  } );

  new StateTransition( stateManager, "run_right", "stop_right", [=] {
    return !input->getKey( ALA_KEY_RIGHT_ARROW ) && timer1->isDone();
  } );

  new StateTransition( stateManager, "stop_left", "idle_left", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "stop_right", "idle_right", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "idle_left", "jump_left", [=] {
    return input->getKeyDown( ALA_KEY_D );
  } );

  new StateTransition( stateManager, "idle_right", "jump_right", [=] {
    return input->getKeyDown( ALA_KEY_D );
  } );

  new StateTransition( stateManager, "jump_left", "idle_left", [=] {
    return controller->isCollidedWithGround();
  } );

  new StateTransition( stateManager, "jump_left", "jump_right", [=] {
    return input->getKeyDown( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "jump_right", "jump_left", [=] {
    return input->getKeyDown( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "jump_right", "idle_right", [=] {
    return controller->isCollidedWithGround();
  } );

  new StateTransition( stateManager, "run_left", "run_left_to_jump", [=] {
    return input->getKeyDown( ALA_KEY_D );
  } );

  new StateTransition( stateManager, "run_right", "run_right_to_jump", [=] {
    return input->getKeyDown( ALA_KEY_D );
  } );

  new StateTransition( stateManager, "run_left_to_jump", "run_left", [=] {
    return controller->isCollidedWithGround() && input->getKey( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "run_right_to_jump", "run_right", [=] {
    return controller->isCollidedWithGround() && input->getKey( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "run_right_to_jump", "run_left_to_jump", [=] {
    return input->getKeyDown( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "run_left_to_jump", "run_right_to_jump", [=] {
    return input->getKeyDown( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "run_left_to_jump", "idle_left", [=] {
    return controller->isCollidedWithGround();
  } );

  new StateTransition( stateManager, "run_right_to_jump", "idle_right", [=] {
    return controller->isCollidedWithGround();
  } );

  new StateTransition( stateManager, "jump_left", "jump_left_attack", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "jump_right", "jump_right_attack", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "jump_left_attack", "jump_right_attack", [=] {
    return input->getKeyDown( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "jump_right_attack", "jump_left_attack", [=] {
    return input->getKeyDown( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "jump_left_attack", "idle_left", [=] {
    return controller->isCollidedWithGround();
  } );

  new StateTransition( stateManager, "jump_right_attack", "idle_right", [=] {
    return controller->isCollidedWithGround();
  } );

  new StateTransition( stateManager, "run_left_to_jump_attack", "idle_left", [=] {
    return controller->isCollidedWithGround();
  } );

  new StateTransition( stateManager, "run_right_to_jump_attack", "idle_right", [=] {
    return controller->isCollidedWithGround();
  } );

  new StateTransition( stateManager, "run_left_to_jump", "run_left_to_jump_attack", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "run_left_to_jump", "run_left_to_throw", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "run_right_to_jump", "run_right_to_throw", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "run_left_to_throw", "idle_left", [=] {
    return controller->isCollidedWithGround();
  } );

  new StateTransition( stateManager, "run_right_to_throw", "idle_right", [=] {
    return controller->isCollidedWithGround();
  } );

  new StateTransition( stateManager, "run_right_to_jump", "run_right_to_jump_attack", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "jump_left", "jump_throw_apple_left", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "jump_throw_apple_left", "idle_left", [=] {
    return controller->isCollidedWithGround();
  } );

  new StateTransition( stateManager, "jump_throw_apple_left", "jump_throw_apple_right", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "jump_throw_apple_right", "jump_throw_apple_left", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "jump_throw_apple_right", "idle_right", [=] {
    return controller->isCollidedWithGround();
  } );

  new StateTransition( stateManager, "jump_right", "jump_throw_apple_right", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "run_left_to_jump_attack", "run_right_to_jump_attack", [=] {
    return input->getKeyDown( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "run_right_to_jump_attack", "run_left_to_jump_attack", [=] {
    return input->getKeyDown( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "run_left", "run_left_attack", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "run_right", "run_right_attack", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "run_right_attack", "run_left", [=] {
    return input->getKey( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "run_left_attack", "run_right", [=] {
    return input->getKey( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "run_left_attack", "run_left", [=] {
    return input->getKey( ALA_KEY_LEFT_ARROW ) && !animator->isPlaying();
  } );

  new StateTransition( stateManager, "run_right_attack", "run_right", [=] {
    return input->getKey( ALA_KEY_RIGHT_ARROW ) && !animator->isPlaying();
  } );

  new StateTransition( stateManager, "run_left_attack", "idle_left", [=] {
    return !input->getKey( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "run_right_attack", "idle_right", [=] {
    return !input->getKey( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "run_left_to_throw", "run_right_to_throw", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_RIGHT_ARROW );
  } );

  new StateTransition( stateManager, "run_right_to_throw", "run_left_to_throw", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "jump_throw_apple_left", "jump_left_attack", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "jump_throw_apple_right", "jump_right_attack", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "jump_left_attack", "jump_throw_apple_left", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "jump_right_attack", "jump_throw_apple_right", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "run_left_to_jump_attack", "jump_throw_apple_left", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "run_right_to_jump_attack", "jump_throw_apple_right", [=] {
    return controller->getApples() > 0 && input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "run_left_to_throw", "run_left_to_jump_attack", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "run_right_to_throw", "run_right_to_jump_attack", [=] {
    return input->getKeyDown( ALA_KEY_S );
  } );

  new StateTransition( stateManager, "hit_left", "idle_left", [=] {
    return !animator->isPlaying() || input->getKeyDown( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "hit_right", "idle_right", [=] {
    return !animator->isPlaying() || input->getKeyDown( ALA_KEY_RIGHT_ARROW );;
  } );
}
