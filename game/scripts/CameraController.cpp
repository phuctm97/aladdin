#include "CameraController.h"

USING_NAMESPACE_ALA;

CameraController::CameraController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ) {}

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

  const auto aladdin = GameManager::get()->getObjectByName( "Node" );
  if ( aladdin == NULL ) return;

  const auto& aladdinPosition = aladdin->getTransform()->getPosition();

  transform->setPosition( aladdinPosition );

  if ( transform->getPositionX() - backgroundLeft < halfVisibleWidth ) {
    transform->setPositionX( halfVisibleWidth + backgroundLeft );
  }
  if ( backgroundRight - transform->getPositionX() < halfVisibleWidth ) {
    transform->setPositionX( backgroundRight - halfVisibleWidth );
  }
  if ( transform->getPositionY() - backgroundBottom < halfVisibleHeight ) {
    transform->setPositionY( halfVisibleHeight + backgroundBottom );
  }
  if ( backgroundTop - transform->getPositionY() < halfVisibleHeight ) {
    transform->setPositionY( backgroundTop - halfVisibleHeight );
  }
}

void CameraController::onRelease() {}
