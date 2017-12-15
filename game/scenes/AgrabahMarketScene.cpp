#include "AgrabahMarketScene.h"
#include "../Define.h"
#include "../scripts/CameraController.h"
#include "../scripts/DebugCameraController.h"
#include "../scripts/NodeController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AgrabahMarketScene, ala::Scene)

void AgrabahMarketScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();

  // configurations
  enablePhysics( Vec2( 0, -500.0f ) );

  new CameraController( getMainCamera() );

  // initial objects
  gameManager->getPrefabV2( "Sprite" )->instantiateWithArgs( "background.png 0", "Background" )
             ->setTag( BACKGROUND_TAG )
             ->setLayer( "Background" )
             ->getTransform()
             ->setPosition( Vec2( 2385.5f, 344 ) - Vec2( gameManager->getVisibleWidth() / 2,
                                                         gameManager->getVisibleHeight() / 2 ) );

  gameManager->getPrefabV2( "Sprite" )->instantiateWithArgs( "foreground.png 0", "Foreground" )
             ->setTag( FOREGROUND_TAG )
             ->setLayer( "Second Foreground" )
             ->getTransform()
             ->setPosition( Vec2( 2385.5f, 344 ) - Vec2( gameManager->getVisibleWidth() / 2,
                                                         gameManager->getVisibleHeight() / 2 ) );

  gameManager->getPrefabV2( "Hub" )->instantiateWithArgs( "", "Hub" );

  gameManager->getPrefabV2( "Agrabah Market Ground" )->instantiateWithArgs( "", "Ground" );

  gameManager->getPrefabV2( "Agrabah Market Stair 1" )->instantiateWithArgs( "", "Start 1" );

  /* Walls */

  gameManager->getPrefabV2( "Wall" )->instantiateWithArgs( "29 68" )
             ->getTransform()->setPosition( Vec2( 1299, -47 ) );


  /* Charcoal Burners
   
  gameManager->getPrefabV2( "Charcoal Burner" )->instantiateWithArgs( "90", "Charcoal Burner 1" )
             ->getTransform()
             ->setPosition( Vec2( 360.5f, -50 ) );

  gameManager->getPrefabV2( "Charcoal Burner" )->instantiateWithArgs( "90", "Charcoal Burner 2" )
             ->getTransform()
             ->setPosition( Vec2( 730.5f, -50 ) );

  gameManager->getPrefabV2( "Charcoal Burner" )->instantiateWithArgs( "90", "Charcoal Burner 3" )
             ->getTransform()
             ->setPosition( Vec2( 906.5f, -50 ) );

  gameManager->getPrefabV2( "Charcoal Burner" )->instantiateWithArgs( "90", "Charcoal Burner 4" )
             ->getTransform()
             ->setPosition( Vec2( 1915.5f, -79 ) );

  gameManager->getPrefabV2( "Charcoal Burner" )->instantiateWithArgs( "110", "Charcoal Burner 4" )
             ->getTransform()
             ->setPosition( Vec2( 2987, -82 ) );

             */

  /* Camels
   
  gameManager->getPrefabV2( "Camel" )->instantiateWithArgs( "R" )
             ->getTransform()
             ->setPosition( Vec2( 1404.5, -57.5 ) );
  
  */

  /* Hand Enemies
   
  gameManager->getPrefabV2( "Hand Enemy" )->instantiateWithArgs( "R 45 80 0 -80", "Hand Enemy 1" )
             ->getTransform()
             ->setPosition( Vec2( 1680.0f, 57.5f ) );

  gameManager->getPrefabV2( "Hand Enemy" )->instantiateWithArgs( "R 45 100 0 -102" )
             ->getTransform()
             ->setPosition( Vec2( 1632.5f, 89.5f ) );

  */

  /* Eatable Apples

  gameManager->getPrefabV2( "Eatable Apple" )->instantiateWithArgs( "", "Apple 1" )
             ->getTransform()
             ->setPosition( Vec2( 0, 10 ) );

             */

  /* Guards
   
  gameManager->getPrefabV2( "Guard 1" )->instantiateWithArgs( "550 430 670", "Guard 1" )
             ->getTransform()->setPositionY( -25 );

  gameManager->getPrefabV2( "Guard 2" )->instantiateWithArgs( "818 595 1010", "Guard 2" )
             ->getTransform()->setPositionY( -25 );

             */


  const auto aladdin = gameManager->getPrefab( "Playable Aladdin" )->instantiate( "Aladdin" );
  aladdin->getTransform()->setPosition( Vec2( 1500, -25 ) );
}
