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
  enablePhysics( Vec2( 0, -500.0f ) );

  new CameraController( getMainCamera() );

  // initial objects

  /* Backgrounds */
  gameManager->getPrefabV2( "Sprite" )->instantiateWithArgs( "jafar_quarter_background.png 0", "Background" )
             ->setTag( BACKGROUND_TAG )
             ->setLayer( "Background" )
             ->getTransform()
             ->setPosition( Vec2( 346.0f, 187.5f ) - Vec2( gameManager->getVisibleWidth() / 2,
                                                           gameManager->getVisibleHeight() / 2 ) );

  /* Ground */

  gameManager->getPrefabV2( "Jafar Quarter Ground" )->instantiateWithArgs( "" )
             ->getTransform()
             ->setPosition( Vec2( 346.0f - gameManager->getVisibleWidth() / 2 ) );

  /* Walls */

  gameManager->getPrefabV2( "Wall" )->instantiateWithArgs( "23 351" )
             ->getTransform()
             ->setPosition( Vec2( -145, 78 ) );

  gameManager->getPrefabV2( "Wall" )->instantiateWithArgs( "25 351" )
             ->getTransform()
             ->setPosition( Vec2( 517, 78 ) );


  gameManager->getPrefabV2( "Playable Aladdin" )->instantiateWithArgs( "-80 0", "Aladdin" );
}
