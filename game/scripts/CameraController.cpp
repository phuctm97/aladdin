#include "CameraController.h"

CameraController::CameraController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ) {
  _speed = 10;
}

void CameraController::onUpdate( const float delta ) {
  auto transform = getGameObject()->getTransform();

  const auto spriteRenderer =
    ala::GameManager::get()->getObjectByName( "Background" )->getComponentT<ala::SpriteRenderer>();

  auto backgroundFrameSize = spriteRenderer->getFrameSize();

  if ( ala::Input::get()->getKey( ALA_KEY_LEFT_ARROW ) ) {
    if ( transform->getPositionX() - ala::GameManager::get()->getScreenWidth() / 2 > 0 )
      transform->setPositionX( transform->getPositionX() - _speed );
  }
  else if ( ala::Input::get()->getKey( ALA_KEY_RIGHT_ARROW ) ) {
    if ( transform->getPositionX() + ala::GameManager::get()->getScreenWidth() / 2 < backgroundFrameSize.getWidth() )
      transform->setPositionX( transform->getPositionX() + _speed );
  }
  else if ( ala::Input::get()->getKey( ALA_KEY_UP_ARROW ) ) {
    if ( transform->getPositionY() + ala::GameManager::get()->getScreenHeight() / 2 < backgroundFrameSize.getHeight() )
      transform->setPositionY( transform->getPositionY() + _speed );
  }
  else if ( ala::Input::get()->getKey( ALA_KEY_DOWN_ARROW ) ) {
    if ( transform->getPositionY() - ala::GameManager::get()->getScreenHeight() / 2 > 0 )
      transform->setPositionY( transform->getPositionY() - _speed );
  };
}

void CameraController::onRelease() {}
