#include "DebugCameraController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(DebugCameraController, ala::GameObjectComponent)

DebugCameraController::DebugCameraController( ala::GameObject* gameObject, ala::GameObject* target,
                                              const std::string& name )
  : GameObjectComponent( gameObject, name ), _speed( 2.0f ), _logger( "DebugCameraController" ), _target( target ), _backupTarget( target ) {}

void DebugCameraController::onUpdate( const float delta ) {
  const auto input = Input::get();
  const auto transform = getGameObject()->getTransform();
  
  if (input->getKey(ALA_KEY_F7)) {
  	if(_target == NULL) _target = _backupTarget;
  	else _target = NULL;
  }

  if ( _target != NULL ) {
    transform->setPosition( _target->getTransform()->getPosition() );
  }
  else {
    Vec2 move;

    if ( input->getKey( ALA_KEY_F1 ) ) {
      _speed -= 0.5f;
      _logger.info( "Camera moving speed %f", _speed );
    }
    else if ( input->getKey( ALA_KEY_F2 ) ) {
      _speed += 0.5f;
      _logger.info( "Camera moving speed %f", _speed );
    }

    if ( input->getKey( ALA_KEY_LEFT_ARROW ) ) {
      move.setX( -_speed );
    }
    else if ( input->getKey( ALA_KEY_RIGHT_ARROW ) ) {
      move.setX( _speed );
    }

    if ( input->getKey( ALA_KEY_UP_ARROW ) ) {
      move.setY( _speed );
    }
    else if ( input->getKey( ALA_KEY_DOWN_ARROW ) ) {
      move.setY( -_speed );
    }

    transform->setPosition( transform->getPosition() + move );
  }
}
