#include "SceneInfoQuerier.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(SceneInfoQuerier, ala::GameObjectComponent)

SceneInfoQuerier::SceneInfoQuerier( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _cameraTransform( NULL ) {}

std::vector<ala::GameObject*> SceneInfoQuerier::getAllEnemiesInCamera() const {
  const auto gameManager = GameManager::get();
  const auto visibleWidth = gameManager->getVisibleWidth();
  const auto visibleHeight = gameManager->getVisibleHeight();
  const auto halfVisibleWidth = visibleWidth / 2;
  const auto halfVisibleHeight = visibleHeight / 2;

  const auto& enemies = gameManager->getAllObjectsByTag( ENEMY_TAG );

  std::vector<ala::GameObject*> enemiesInCamera;
  for ( const auto& enemy : enemies ) {
    const auto& enemyPosition = enemy->getTransform()->getPosition();
    if ( ABS(enemyPosition.getX() - _cameraTransform->getPositionX()) <= halfVisibleWidth
      && ABS(enemyPosition.getY() - _cameraTransform->getPositionY()) <= halfVisibleHeight ) {
      enemiesInCamera.push_back( enemy );
    }
  }

  return enemiesInCamera;
}

void SceneInfoQuerier::onInitialize() {
  const auto gameManager = GameManager::get();

  const auto camera = gameManager->getRunningScene()->getMainCamera();

  _cameraTransform = camera->getTransform();
}
