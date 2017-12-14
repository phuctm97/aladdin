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

  const auto hub = gameManager->getPrefab( "Hub" )->instantiate( "Hub" );

  const auto ground = gameManager->getPrefab( "Agrabah Market Ground" )->instantiate( "Ground" );

  const auto stairOne = gameManager->getPrefab( "Stair 1" )->instantiate( "Start 1" );

  const auto charcoalBurnerOne = gameManager->getPrefab( "Charcoal Burner" )->instantiate(
    Vec2( 360.5f, -50 ), "Charcoal Burner 1" );

  const auto charcoalBurnerTwo = gameManager->getPrefab( "Charcoal Burner" )->instantiate(
    Vec2( 730.5f, -50 ), "Charcoal Burner 2" );

  const auto charcoalBurnerThree = gameManager->getPrefab( "Charcoal Burner" )->instantiate(
    Vec2( 906.5f, -50 ), "Charcoal Burner 3" );

  const auto charcoalBurnerFour = gameManager->getPrefab( "Charcoal Burner" )->instantiate(
    Vec2( 1915.5f, -79 ), "Charcoal Burner 4" );

  const auto charcoalBurnerFive = gameManager->getPrefab( "Charcoal Burner" )->instantiate(
    Vec2( 2987, -82 ), "Charcoal Burner 5" );

  const auto aladdin = gameManager->getPrefab( "Playable Aladdin" )->instantiate( "Aladdin" );
  aladdin->getTransform()->setPosition( Vec2( -80, -25 ) );
}
