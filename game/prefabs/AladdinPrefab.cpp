#include "AladdinPrefab.h"
#include "../scripts/AladdinController.h"

USING_NAMESPACE_ALA;

void AladdinPrefab::doInstantiate( ala::GameObject* object ) const {
  const auto gameManager = GameManager::get();

  const auto spriteRenderer = new SpriteRenderer( object, "aladdin.png" );
  const auto animator = new Animator( object, "idle_1", "aladdin.anm" );

  //    // For animationEditor
  //    const auto animationEditor = new AnimationEditor( object, "stop" );
  //    object->setLayer( "Character" );
  //    object->getTransform()->setPosition( -80, -40 );
  //    return;
  //    // For animationEditor

  const auto timer = new Timer( object );
  const auto stateManager = new StateManager( object, "idle_right" );
  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 40, 50 ) );
  const auto controller = new AladdinController( object );
  const auto debugRect = gameManager->getPrefab( "Debug Rect" )->instantiate( object )
                                    ->setLayer( "Character" )
                                    ->getTransform()
                                    ->setScale( 50 )
                                    ->getGameObject();
  const auto transform = object->getTransform();
  const auto input = Input::get();

  // initial configurations
  object->setLayer( "Character" );
  transform->setPosition( -80, -40 );

  // states

  new State( stateManager, "idle_left",
             [=] {
               if ( stateManager->getPreviousStateName() == "face_up_left" ) {
                 animator->setAction( "face_up_to_idle_1" );
               }
               else if ( stateManager->getPreviousStateName() == "sit_left" ) {
                 animator->setAction( "stand_up" );
               }
               else {
                 animator->setAction( "idle_1" );
                 timer->start( 0.5f );
               }
               transform->setScaleX( -ABS(transform->getScale().getX()) );
             },
             [=]( float dt ) {
               if ( !animator->isPlaying() && timer->isDone() ) {
                 if ( animator->getActionName() == "idle_4_to_1" ||
                   animator->getActionName() == "face_up_to_idle_1" ||
                   animator->getActionName() == "stand_up" ) {
                   animator->setAction( "idle_1" );
                   timer->start( 0.5f );
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
                     timer->start( 1.0f * (200 + rand() % 900) / 1000 );
                   }
                 }
                 else if ( animator->getActionName() == "idle_2" ) {
                   animator->setAction( "idle_2_to_3" );
                 }
                 else if ( animator->getActionName() == "idle_2_to_3" ) {
                   animator->setAction( "idle_3" );
                   timer->start( 1.0f * (200 + rand() % 900) / 1000 );
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
               if ( stateManager->getPreviousStateName() == "face_up_right" ) {
                 animator->setAction( "face_up_to_idle_1" );
               }
               else if ( stateManager->getPreviousStateName() == "sit_right" ) {
                 animator->setAction( "stand_up" );
               }
               else {
                 animator->setAction( "idle_1" );
                 timer->start( 0.5f );
               }
               transform->setScaleX( ABS(transform->getScale().getX()) );
             },
             [=]( float dt ) {
               if ( !animator->isPlaying() && timer->isDone() ) {
                 if ( animator->getActionName() == "idle_4_to_1" ||
                   animator->getActionName() == "face_up_to_idle_1" ||
                   animator->getActionName() == "stand_up" ) {
                   animator->setAction( "idle_1" );
                   timer->start( 0.5f );
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
                     timer->start( 1.0f * (200 + rand() % 900) / 1000 );
                   }
                 }
                 else if ( animator->getActionName() == "idle_2" ) {
                   animator->setAction( "idle_2_to_3" );
                 }
                 else if ( animator->getActionName() == "idle_2_to_3" ) {
                   animator->setAction( "idle_3" );
                   timer->start( 1.0f * (200 + rand() % 900) / 1000 );
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
             }, NULL, NULL );

  new State( stateManager, "attack_1_right",
             [=] {
               animator->setAction( "attack_1" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
             }, NULL, NULL );

  new State( stateManager, "attack_2_left",
             [=] {
               animator->setAction( "attack_2" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
             }, NULL, NULL );

  new State( stateManager, "attack_2_right",
             [=] {
               animator->setAction( "attack_2" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
             }, NULL, NULL );

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
             }, NULL, NULL );

  new State( stateManager, "attack_3_right",
             [=] {
               animator->setAction( "attack_3" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
             }, NULL, NULL );

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
             }, NULL, NULL );

  new State( stateManager, "sit_attack_1_right",
             [=] {
               animator->setAction( "sit_attack_1" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
             }, NULL, NULL );

  new State( stateManager, "sit_attack_2_left",
             [=] {
               animator->setAction( "sit_attack_2" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
             }, NULL, NULL );

  new State( stateManager, "sit_attack_2_right",
             [=] {
               animator->setAction( "sit_attack_2" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
             }, NULL, NULL );

  new State( stateManager, "run_left",
             [=] {
               animator->setAction( "start_run" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
               timer->start( 1 );
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
               timer->start( 1 );
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
             }, NULL, NULL );

  new State( stateManager, "stop_right",
             [=] {
               animator->setAction( "stop" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
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
    return input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "idle_right", "attack_3_right", [=] {
    return input->getKeyDown( ALA_KEY_A );
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
    return input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "face_up_right", "attack_3_right", [=] {
    return input->getKeyDown( ALA_KEY_A );
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
    return input->getKeyDown( ALA_KEY_A );
  } );

  new StateTransition( stateManager, "sit_right", "sit_attack_2_right", [=] {
    return input->getKeyDown( ALA_KEY_A );
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
    return !input->getKey( ALA_KEY_LEFT_ARROW ) && !timer->isDone();
  } );

  new StateTransition( stateManager, "run_right", "idle_right", [=] {
    return !input->getKey( ALA_KEY_RIGHT_ARROW ) && !timer->isDone();
  } );

  new StateTransition( stateManager, "run_left", "stop_left", [=] {
    return !input->getKey( ALA_KEY_LEFT_ARROW ) && timer->isDone();
  } );

  new StateTransition( stateManager, "run_right", "stop_right", [=] {
    return !input->getKey( ALA_KEY_RIGHT_ARROW ) && timer->isDone();
  } );

  new StateTransition( stateManager, "stop_left", "idle_left", [=] {
    return !animator->isPlaying();
  } );

  new StateTransition( stateManager, "stop_right", "idle_right", [=] {
    return !animator->isPlaying();
  } );

}
