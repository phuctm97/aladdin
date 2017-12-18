#include "JafarQuarterScene.h"
#include "../Define.h"
#include "../scripts/CameraController.h"
#include "../scripts/DebugCameraController.h"
#include "../scripts/NodeController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarQuarterScene, ala::Scene)

void JafarQuarterScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();

  // configurations
  new CameraController( getMainCamera() );

  // scene loader
  gameManager->loadScene( "jafar_quarter.scene" );
}
