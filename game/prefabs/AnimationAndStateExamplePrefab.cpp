#include "AnimationAndStateExamplePrefab.h"
#include "../scripts/BasicController.h"

void AnimationAndStateExamplePrefab::doInstantiate( ala::GameObject* object ) const {
  // layer
  object->setLayer( "Character" );

  // sprite renderer
  new ala::SpriteRenderer( object, "aladdin.png" );

  // animator component for animation
  new ala::Animator( object, "stand", "aladdin.animation" );

  // state manager to control object state
  auto stateManager = new ala::StateManager( object, "stand-right" );

  auto transform = object->getTransform();
  transform->setScale( 3 );

  // state definitions
  new ala::State( stateManager, "stand-right",
                  [=] {
                    auto animator = object->getComponentT<ala::Animator>();
                    animator->setAction( "stand" );
                  }, NULL, NULL );
  new ala::State( stateManager, "stand-left",
                  [=] {
                    auto animator = object->getComponentT<ala::Animator>();
                    animator->setAction( "stand" );
                  }, NULL, NULL );
  new ala::State( stateManager, "go-right",
                  [=] {
                    auto animator = object->getComponentT<ala::Animator>();
                    animator->setAction( "run" );
                    transform->setScaleX( ABS(transform->getScale().getX()) );
                  },
                  [=]( float dt ) {
                    auto position = transform->getPosition();
                    position.setX( position.getX() + 200 * dt );
                    transform->setPosition( position );
                  },
                  NULL );
  new ala::State( stateManager, "go-left",
                  [=] {
                    auto animator = object->getComponentT<ala::Animator>();
                    animator->setAction( "run" );
                    transform->setScaleX( -ABS(transform->getScale().getX()) );
                  },
                  [=]( float dt ) {
                    auto position = transform->getPosition();
                    position.setX( position.getX() - 200 * dt );
                    transform->setPosition( position );
                  },
                  NULL );

  // state transitions
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
