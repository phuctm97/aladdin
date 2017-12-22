#include "CameraFollower.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(CameraFollower, ala::GameObjectComponent)

CameraFollower::CameraFollower( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ) {}

void CameraFollower::onRender() {
  const auto gameManager = GameManager::get();
  const auto camera = gameManager->getRunningScene()->getMainCamera();
  const auto cameraPosition = camera == NULL ? Vec2() : camera->getTransform()->getPosition();
  getGameObject()->getTransform()->setPosition( cameraPosition );
}
