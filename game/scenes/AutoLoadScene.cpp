#include "AutoLoadScene.h"
#include "../scripts/CameraController.h"
#include "../scripts/DebugCameraController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AutoLoadScene, ala::Scene)

void AutoLoadScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();

  // configurations
  if ( _useCameraController ) {
    new CameraController( getMainCamera() );
  }

  // scene loader
  gameManager->loadScene( _sceneName );
}
