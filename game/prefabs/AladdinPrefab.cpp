#include "AladdinPrefab.h"
#include "../scripts/AladdinController.h"
#include "../scripts/Timer.h"

USING_NAMESPACE_ALA;

void AladdinPrefab::doInstantiate( ala::GameObject* object ) {
  // ReSharper disable CppNonReclaimedResourceAcquisition
  const auto spriteRenderer = new SpriteRenderer( object, "aladdin.png" );
  const auto animator = new Animator( object, "idle_1", "aladdin.anm" );
  const auto stateManager = new StateManager( object, "idle_left" );
  const auto timer = new Timer( object );
  const auto controller = new AladdinController( object );
  const auto transform = object->getTransform();
  const auto input = Input::get();

  // initial configurations
  object->setLayer( "Character" );
  spriteRenderer->setAnchorPoint( Vec2( 0.5f, 0 ) );
  transform->setPosition( -80, -70 );

  // states

  new State( stateManager, "idle_left",
             [=] {
               animator->setAction( "idle_1" );
               timer->start( 0.5 );
             },
             [=]( float dt ) {
               if ( !animator->isPlaying() && timer->isDone() ) {
                 if ( animator->getAction() == "idle_4_to_1" ) {
                   animator->setAction( "idle_1" );
                   timer->start( 0.2f );
                 }
                 if ( animator->getAction() == "idle_1" || animator->getAction() == "idle_4_to_1" ) {
                   animator->setAction( "idle_1_to_2" );
                 }
                 else if ( animator->getAction() == "idle_1_to_2" || animator->getAction() == "idle_3_to_2" ) {
                   const auto way = rand() % 5;
                   if ( way == 0 ) {
                     animator->setAction( "idle_2_to_4" );
                   }
                   else {
                     animator->setAction( "idle_2" );
                     timer->start( 1.0f * (200 + rand() % 900) / 1000 );
                   }
                 }
                 else if ( animator->getAction() == "idle_2" ) {
                   animator->setAction( "idle_2_to_3" );
                 }
                 else if ( animator->getAction() == "idle_2_to_3" ) {
                   animator->setAction( "idle_3" );
                   timer->start( 1.0f * (200 + rand() % 900) / 1000 );
                 }
                 else if ( animator->getAction() == "idle_3" ) {
                   animator->setAction( "idle_3_to_2" );
                 }
                 else if ( animator->getAction() == "idle_2_to_4" ||
                   animator->getAction() == "idle_4_to_4_way_1" ||
                   animator->getAction() == "idle_4_to_4_way_2" ) {
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

  //  new State( stateManager, "idle_2_left",
  //             [=] {
  //               if ( stateManager->getPreviousStateName() != "idle_3_left" ) {
  //                 animator->setAction( "idle_2" );
  //                 effect->resetEffectTwoTimer();
  //               }
  //             }, NULL, NULL );

  //  new State( stateManager, "idle_3_left",
  //             [=] {
  //               animator->setAction( "idle_3" );
  //               effect->resetEffectTwoTimer();
  //             }, NULL, NULL );
  //
  //  new State( stateManager, "idle_4_left",
  //             [=] {
  //               animator->setAction( "idle_4" );
  //             }, NULL, NULL );
  //

  //
  //  new StateTransition( stateManager, "idle_1_left", "idle_2_left", [=] {
  //    return effect->isEffectTwoTimerUp();
  //  } );
  //
  //  new StateTransition( stateManager, "idle_2_left", "idle_3_left", [=] {
  //    return effect->isEffectTwoTimerUp();
  //  } );
  //
  //  new StateTransition( stateManager, "idle_3_left", "idle_2_left", [=] {
  //    return effect->isEffectTwoTimerUp();
  //  } );
  //
  //  new StateTransition( stateManager, "idle_2_left", "idle_4_left", [=] {
  //    return effect->isEffectThreeUp();
  //  } );
  //
  //  new StateTransition( stateManager, "idle_4_left", "idle_4_left", [=] {
  //    return !animator->isPlaying() && effect->isEffectFourUp();
  //  } );
  //
  //  new StateTransition( stateManager, "idle_4_left", "idle_4_left", [=] {
  //    return !animator->isPlaying() && effect->isEffectFourUp();
  //  } );

  /*
   
  // State Stand
  new ala::State( stateManager, "stand_left",
                  [=] {
                    animator->setAction( "idle_1" );
                    transform->setScaleX( -1 );
                    movement->setVelocityX( 0 );
                  }, NULL, NULL );


  // State Go
  float goSpeed = 90;

  new ala::State( stateManager, "go_right",
                  [=] {
                    animator->setAction( "run_1" );
                    transform->setScaleX( 1 );
                    movement->setVelocityX( goSpeed );
                  },
                  [=]( float dt ) {
                    if ( animator->getAction() == "run_1" && !animator->isPlaying() )
                      animator->setAction( "run_2" );
                  }, NULL );
  new ala::State( stateManager, "go_left",
                  [=] {
                    animator->setAction( "run_1" );
                    transform->setScaleX( -1 );
                    movement->setVelocityX( -goSpeed );
                  },
                  [=]( float dt ) {
                    if ( animator->getAction() == "run_1" && !animator->isPlaying() )
                      animator->setAction( "run_2" );
                  }, NULL );

  // State Sit
  new ala::State( stateManager, "sit_left",
                  [=] {
                    animator->setAction( "sit" );
                    transform->setScaleX( -1 );
                    movement->setVelocityX( 0 );
                  }, NULL, NULL );
  new ala::State( stateManager, "sit_right",
                  [=] {
                    animator->setAction( "sit" );
                    transform->setScaleX( 1 );
                    movement->setVelocityX( 0 );
                  }, NULL, NULL );

  // State Throw
  new ala::State( stateManager, "throw_right",
                  [=] {
                    animator->setAction( "throw" );
                    transform->setScaleX( 1 );
                    movement->setVelocityX( 0 );
                  }, NULL, NULL );
  new ala::State( stateManager, "throw_left",
                  [=] {
                    animator->setAction( "throw" );
                    transform->setScaleX( -1 );
                    movement->setVelocityX( 0 );
                  }, NULL, NULL );

  new ala::StateTransition( stateManager, "stand_right", "go_right",
                            [] {
                              return ala::Input::get()->getKeyDown( ALA_KEY_RIGHT_ARROW );
                            } );
  new ala::StateTransition( stateManager, "stand_right", "go_left",
                            [] {
                              return ala::Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW );
                            } );
  new ala::StateTransition( stateManager, "go_right", "go_left",
                            [] {
                              return ala::Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW );
                            } );
  new ala::StateTransition( stateManager, "go_right", "stand_right",
                            [] {
                              return ala::Input::get()->getKeyUp( ALA_KEY_RIGHT_ARROW );
                            } );
  new ala::StateTransition( stateManager, "stand_left", "go_left",
                            [] {
                              return ala::Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW );
                            } );
  new ala::StateTransition( stateManager, "stand_left", "go_right",
                            [] {
                              return ala::Input::get()->getKeyDown( ALA_KEY_RIGHT_ARROW );
                            } );
  new ala::StateTransition( stateManager, "go_left", "stand_left",
                            [] {
                              return ala::Input::get()->getKeyUp( ALA_KEY_LEFT_ARROW );
                            } );
  new ala::StateTransition( stateManager, "stand_left", "sit_left",
                            [] {
                              return ala::Input::get()->getKeyDown( ALA_KEY_DOWN_ARROW );
                            } );
  new ala::StateTransition( stateManager, "stand_right", "sit_right",
                            [] {
                              return ala::Input::get()->getKeyDown( ALA_KEY_DOWN_ARROW );
                            } );
  new ala::StateTransition( stateManager, "sit_left", "stand_left",
                            [] {
                              return ala::Input::get()->getKeyUp( ALA_KEY_DOWN_ARROW );
                            } );
  new ala::StateTransition( stateManager, "sit_right", "stand_right",
                            [] {
                              return ala::Input::get()->getKeyUp( ALA_KEY_DOWN_ARROW );
                            } );
  new ala::StateTransition( stateManager, "throw_right", "stand_right",
                            [=] {
                              return animator->getAction() == "throw" && !animator->isPlaying();
                            } );
  new ala::StateTransition( stateManager, "stand_right", "throw_right",
                            [] {
                              return ala::Input::get()->getKeyDown( ALA_KEY_A );
                            } );
  new ala::StateTransition( stateManager, "throw_left", "stand_left",
                            [=] {
                              return animator->getAction() == "throw" && !animator->isPlaying();
                            } );
  new ala::StateTransition( stateManager, "stand_left", "throw_left",
                            [] {
                              return ala::Input::get()->getKeyDown( ALA_KEY_A );
                            } );
  */
}
