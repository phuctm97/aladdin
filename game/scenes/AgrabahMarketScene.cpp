#include "AgrabahMarketScene.h"
#include "../Define.h"
#include "../scripts/CameraController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AgrabahMarketScene, ala::Scene)

void AgrabahMarketScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();
  const auto halfVisibleWidth = gameManager->getVisibleWidth() / 2;
  const auto halfVisibleHeight = gameManager->getVisibleHeight() / 2;

  // configurations
  enablePhysics( Vec2( 0, -500.0f ) );

  new CameraController( getMainCamera() );

  // initial objects
  const auto background = new GameObject( this, "Background" );
  background->setTag( BACKGROUND_TAG );
  const auto backgroundSpriteRenderer = new SpriteRenderer( background, "background.png" );
  background->setLayer( "Background" );
  background->getTransform()->setPosition(
    Vec2( backgroundSpriteRenderer->getFrameSize().getWidth() / 2,
          backgroundSpriteRenderer->getFrameSize().getHeight() / 2 )
    - Vec2( gameManager->getVisibleWidth() / 2,
            gameManager->getVisibleHeight() / 2 ) );

  const auto foreground = new GameObject( this, "Foreground" );
  foreground->setTag( FOREGROUND_TAG );
  const auto foregroundSpriteRenderer = new SpriteRenderer( foreground, "foreground.png" );
  foreground->setLayer( "Foreground" );
  foreground->getTransform()->setPosition(
    Vec2( foregroundSpriteRenderer->getFrameSize().getWidth() / 2,
          foregroundSpriteRenderer->getFrameSize().getHeight() / 2 )
    - Vec2( gameManager->getVisibleWidth() / 2,
            gameManager->getVisibleHeight() / 2 ) );

  const auto ground = gameManager->getPrefab( "Agrabah Market Ground" )->instantiate( "Ground" );

  const auto stairOne = gameManager->getPrefab( "Stair" )->instantiate( "Start 1" );
  stairOne->getTransform()->setPosition( Vec2( 1015.5f, -46.0f ) );
  stairOne->getComponentT<Collider>()->setSize( Size( 45.0f, 8.0f ) );

  const auto stairTwo = gameManager->getPrefab( "Stair" )->instantiate( "Start 2" );
  stairTwo->getTransform()->setPosition( Vec2( 1055.5f, -36.0f ) );
  stairTwo->getComponentT<Collider>()->setSize( Size( 42.0f, 7.0f ) );

  const auto stairThree = gameManager->getPrefab( "Stair" )->instantiate( "Start 3" );
  stairThree->getTransform()->setPosition( Vec2( 1096.0f, -28.5f ) );
  stairThree->getComponentT<Collider>()->setSize( Size( 42.0f, 6.0f ) );

  const auto stairFour = gameManager->getPrefab( "Stair" )->instantiate( "Start 4" );
  stairFour->getTransform()->setPosition( Vec2( 1136.0f, -21.5f ) );
  stairFour->getComponentT<Collider>()->setSize( Size( 45.0f, 7.0f ) );

  const auto stairFive = gameManager->getPrefab( "Stair" )->instantiate( "Start 5" );
  stairFive->getTransform()->setPosition( Vec2( 1176.0f, -12.5f ) );
  stairFive->getComponentT<Collider>()->setSize( Size( 43.0f, 6.0f ) );

  const auto stairSix = gameManager->getPrefab( "Stair" )->instantiate( "Start 6" );
  stairSix->getTransform()->setPosition( Vec2( 1215.0f, -5.5f ) );
  stairSix->getComponentT<Collider>()->setSize( Size( 43.0f, 7.0f ) );

  const auto stairSeven = gameManager->getPrefab( "Stair" )->instantiate( "Start 7" );
  stairSeven->getTransform()->setPosition( Vec2( 1286.0f, 2.5f ) );
  stairSeven->getComponentT<Collider>()->setSize( Size( 106.0f, 7.0f ) );

  const auto aladdin = gameManager->getPrefab( "Playable Aladdin" )->instantiate( "Aladdin" );
  aladdin->getTransform()->setPosition( Vec2( -80, -25 ) );
}
