#include "DebugScene.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(DebugScene, ala::Scene)

void DebugScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();

  // configurations
  enablePhysics( Vec2( 0, -500.0f ) );

  //  enableQuadTree( -160, -115, 4771, 688, 3 );

  // objects
  gameManager->getPrefabV2( "Sprite" )->instantiateWithArgs( "jafar_quarter_background.png 0", "Background" )
             ->setTag( BACKGROUND_TAG )
             ->setLayer( "Background" )
             ->getTransform()
             ->setPosition( 186, 72.5 );

  gameManager->getPrefabV2( "Jafar Quarter Ground" )->instantiateWithArgs( "" )
             ->getTransform()
             ->setPosition( 186, 0 );

  gameManager->getPrefabV2( "Wall" )->instantiateWithArgs( "23 351" )
             ->getTransform()
             ->setPosition( -145, 78 );

  gameManager->getPrefabV2( "Wall" )->instantiateWithArgs( "23 351" )
             ->getTransform()
             ->setPosition( 517, 78 );

  gameManager->getPrefabV2( "Jafar" )->instantiateWithArgs( "" );
}
