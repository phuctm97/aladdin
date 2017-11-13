#include "AladdinPrefab.h"
#include "../scripts/LimitedGravityAffectedVelocityBasedMovement.h"

void AladdinPrefab::doInstantiate( ala::GameObject* object ) {
  new ala::SpriteRenderer( object, "aladdin.png" );
  auto animator = new ala::Animator( object, "idle_1", "aladdin.animation" );
  auto stateManager = new ala::StateManager( object, "stand_right" );
  auto movement = new LimitedGravityAffectedVelocityBasedMovement( object );

  object->setLayer( "Character" );

  auto transform = object->getTransform();
  auto input = ala::Input::get();

  // Start position
  transform->setPosition( ala::GameManager::get()->getVisibleWidth() / 2,
                          ala::GameManager::get()->getVisibleHeight() / 2 );

  new ala::State( stateManager, "stand_right",
                  [=] {
                    animator->setAction( "idle_1" );
                    transform->setScaleX( 1 );
                    movement->setVelocityX( 0 );
                  }, NULL, NULL );


  new ala::State( stateManager, "jump_right",
                  [=] {
                    transform->setScale( 1 );
                    movement->addVelocityY( 300 );
                  }, [=]( float dt ) {
                    if ( transform->getPositionY() <= 200 && input->getKey( ALA_KEY_SPACE ) ) {
                      movement->addVelocityY( 300 * dt );
                    }
                  }, NULL );

  new ala::State( stateManager, "fall_right", [=] { }, NULL, NULL );

  new ala::StateTransition( stateManager, "stand_right", "jump_right", [] {
    return ala::Input::get()->getKeyDown( ALA_KEY_SPACE );
  } );

  new ala::StateTransition( stateManager, "jump_right", "stand_right", [=] {
    return movement->getVelocity().getY() == 0;
  } );


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
