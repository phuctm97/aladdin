#include "AnimationExamplePrefab.h"
#include "../scripts/BallController.h"

void AnimationExamplePrefab::doInstantiate( ala::GameObject* object ) {
  new ala::SpriteRenderer( object, "aladdin.png" );
  new ala::Animator( object, "idle1", "aladdin.animation" );
  new ala::AudioSource( object, "wow.wav" );
  auto stateManager = new ala::StateManager( object, "stand-right" );

  new ala::State( stateManager, "stand-right",
                  [=] {
                  auto animator = object->getComponentT<ala::Animator>();
                  animator->setAction( "idle1" );
                }, NULL, NULL );
  new ala::State( stateManager, "stand-left",
                  [=] {
                  auto animator = object->getComponentT<ala::Animator>();
                  animator->setAction( "idle1" );
                }, NULL, NULL );
  new ala::State( stateManager, "go-right",
                  [=] {
                  auto animator = object->getComponentT<ala::Animator>();
                  animator->setAction( "run" );
                  object->getTransform()->setScaleX( 1 );
                },
                  [=]( float dt ) {
                  auto position = object->getTransform()->getPosition();
                  position.setX( position.getX() + 100 * dt );
                  object->getTransform()->setPosition( position );
                },
                  NULL );
  new ala::State( stateManager, "go-left",
                  [=] {
                  auto animator = object->getComponentT<ala::Animator>();
                  animator->setAction( "run" );
                  object->getTransform()->setScaleX( -1 );
                },
                  [=]( float dt ) {
                  auto position = object->getTransform()->getPosition();
                  position.setX( position.getX() - 100 * dt );
                  object->getTransform()->setPosition( position );
                },
                  NULL );
  new ala::StateTransition( stateManager, "go-left", "go-right", [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_RIGHT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "go-left", "stand-left", [] {
                            return ala::Input::get()->getKeyUp( ALA_KEY_LEFT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "go-right", "go-left", [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "go-right", "stand-right", [] {
                            return ala::Input::get()->getKeyUp( ALA_KEY_RIGHT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "stand-left", "go-left", [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "stand-left", "go-right", [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_RIGHT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "stand-right", "go-left", [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "stand-right", "go-right", [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_RIGHT_ARROW );
                          } );
}
