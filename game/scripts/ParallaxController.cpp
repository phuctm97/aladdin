#include "ParallaxController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(ParallaxController, ala::GameObjectComponent)

ParallaxController::ParallaxController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ) {}

void ParallaxController::setOffset( const ala::Vec2& offset ) {
  _offset = offset;
}

void ParallaxController::onRender() {
  const auto gameManager = GameManager::get();
  const auto camera = gameManager->getRunningScene()->getMainCamera();
  const auto cameraPosition = camera == NULL ? Vec2() : camera->getTransform()->getPosition();
  getGameObject()->getTransform()->setPosition( cameraPosition + _offset );
}
