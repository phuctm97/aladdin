#include "CameraController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

CameraController::CameraController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _targetPosition( 0, 0 ), _movingSpeed( 7.0f ) {}

void CameraController::onUpdate( const float delta ) {
  auto transform = getGameObject()->getTransform();

  const auto halfVisibleWidth = GameManager::get()->getVisibleWidth() / 2;
  const auto halfVisibleHeight = GameManager::get()->getVisibleHeight() / 2;

  const auto background = GameManager::get()->getObjectByName( "Background" );
  if ( background == NULL ) return;

  const auto& backgroundPosition = background->getTransform()->getPosition();
  const auto& backgroundFrameSize = background->getComponentT<SpriteRenderer>()
                                              ->getFrameSize();

  const auto backgroundLeft = backgroundPosition.getX() - backgroundFrameSize.getWidth() / 2;
  const auto backgroundRight = backgroundPosition.getX() + backgroundFrameSize.getWidth() / 2;
  const auto backgroundTop = backgroundPosition.getY() + backgroundFrameSize.getHeight() / 2;
  const auto backgroundBottom = backgroundPosition.getY() - backgroundFrameSize.getHeight() / 2;

  const auto aladdin = GameManager::get()->getObjectByTag( ALADDIN_TAG );
  if ( aladdin == NULL ) return;

  const auto& aladdinPosition = aladdin->getTransform()->getPosition();
  const auto& aladdinScale = aladdin->getTransform()->getScale();

  // aladdin horizontal direction
  if ( aladdinScale.getX() >= 0 ) {
    _targetPosition.setX( aladdinPosition.getX() + halfVisibleWidth * 0.25f );
  }
  else {
    _targetPosition.setX( aladdinPosition.getX() - halfVisibleWidth * 0.25f );
  }

  // aladdin vertical direction
  const auto aladdinStateManager = aladdin->getComponentT<StateManager>();
  if ( aladdinStateManager != NULL &&
    (aladdinStateManager->getCurrentStateName() == "face_up_left" ||
      aladdinStateManager->getCurrentStateName() == "face_up_right" ||
      aladdinStateManager->getCurrentStateName() == "attack_2_left" ||
      aladdinStateManager->getCurrentStateName() == "attack_2_right" ||
      (aladdinStateManager->getCurrentStateName() == "idle_left" &&
        aladdinStateManager->getPreviousStateName() == "attack_2_left") ||
      (aladdinStateManager->getCurrentStateName() == "idle_right" &&
        aladdinStateManager->getPreviousStateName() == "attack_2_right")) ) {
    _targetPosition.setY( aladdinPosition.getY() + halfVisibleHeight * 0.7f );
  }
  else {
    _targetPosition.setY( aladdinPosition.getY() - halfVisibleHeight * 0.1f );
  }

  // guard camera in background bounding zone
  if ( _targetPosition.getX() - backgroundLeft < halfVisibleWidth ) {
    _targetPosition.setX( backgroundLeft + halfVisibleWidth );
  }
  else if ( backgroundRight - _targetPosition.getX() < halfVisibleWidth ) {
    _targetPosition.setX( backgroundRight - halfVisibleWidth );
  }
  if ( _targetPosition.getY() - backgroundBottom < halfVisibleHeight ) {
    _targetPosition.setY( backgroundBottom + halfVisibleHeight );
  }
  else if ( backgroundTop - _targetPosition.getY() < halfVisibleHeight ) {
    _targetPosition.setY( backgroundTop - halfVisibleHeight );
  }

  // move camera toward target
  const auto diff = _targetPosition - transform->getPosition();
  const auto diffLength = diff.getLength();
  if ( diffLength <= _movingSpeed ) {
    transform->setPosition( _targetPosition );
  }
  else {
    const auto normalizedDiff = diff / diffLength;
    transform->setPosition( transform->getPosition() + normalizedDiff * _movingSpeed );
  }
}

void CameraController::onRelease() {}
