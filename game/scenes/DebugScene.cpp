#include "DebugScene.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(DebugScene, ala::Scene)

void DebugScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();

  // configurations
  enablePhysics( Vec2( 0, -500.0f ) );

  enableQuadTree( -160, -115, 4771, 688, 3 );

  // objects
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
}
