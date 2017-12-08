/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "ExperimentalScene.h"
#include "../scripts/CameraController.h"
#include "../scripts/NodeController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ExperimentalScene::ExperimentalScene() : _logger( "ExperimentalScene" ) {}

void ExperimentalScene::onPreInitialize() {
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

  const auto ground = gameManager->getPrefab( "Ground" )->instantiate( "Ground" );

  const auto ropeOne = gameManager->getPrefab( "Rope" )->instantiate( "Rope 1" );
  ropeOne->getTransform()->setPosition( Vec2( 1931, 86 ) );
  ropeOne->getComponentT<Collider>()->setSize( Size( 5, 250 ) );

  const auto ropeTwo = gameManager->getPrefab( "Rope" )->instantiate( "Rope 2" );
  ropeTwo->getTransform()->setPosition( Vec2( 1387, 298 ) );
  ropeTwo->getComponentT<Collider>()->setSize( Size( 5, 193 ) );

  const auto ropeThree = gameManager->getPrefab( "Rope" )->instantiate( "Rope 3" );
  ropeThree->getTransform()->setPosition( Vec2( 2539, 345 ) );
  ropeThree->getComponentT<Collider>()->setSize( Size( 5, 249 ) );

  const auto ropeFour = gameManager->getPrefab( "Rope" )->instantiate( "Rope 4" );
  ropeFour->getTransform()->setPosition( Vec2( 4555, 99 ) );
  ropeFour->getComponentT<Collider>()->setSize( Size( 5, 193 ) );

  const auto aladdin = gameManager->getPrefab( "Aladdin" )->instantiate( "Aladdin" );
  aladdin->getTransform()->setPosition( Vec2( -80, -25 ) );

  const auto charcoalBurnerOne = gameManager->getPrefab( "Charcoal Burner" )->instantiate();
  charcoalBurnerOne->getTransform()->setPosition( Vec2( 360.5f, -50 ) );

  const auto handEnemy_1 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_1->getTransform()->setPosition(Vec2(1632.5, 91.5));
  const auto handEnemy_2 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_2->getTransform()->setPosition(Vec2(1680.5, 60));/*
  const auto handEnemy_3 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_3->getTransform()->setPosition(Vec2(1792.5, 235));
  const auto handEnemy_4 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_4->getTransform()->setPosition(Vec2(1680.5, 235.5));
  const auto handEnemy_5 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_5->getTransform()->setPosition(Vec2(1584.5, 411));
  const auto handEnemy_6 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_6->getTransform()->setPosition(Vec2(1792.5, 411));
  const auto handEnemy_7 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_7->getTransform()->setPosition(Vec2(1952.5, 411));
  const auto handEnemy_8 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_8->getTransform()->setPosition(Vec2(2352.5, 219));
  const auto handEnemy_9 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_9->getTransform()->setPosition(Vec2(3616.5, 27.5));
  const auto handEnemy_10 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_10->getTransform()->setPosition(Vec2(3792.5, 27.5));
  const auto handEnemy_11 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_11->getTransform()->setPosition(Vec2(3856.5, 59.5));
  const auto handEnemy_12 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_12->getTransform()->setPosition(Vec2(3152.5, 203));
  */
  /*handEnemy_12->setTag(ALADDIN_TAG);
  new NodeController(handEnemy);*/
}

void ExperimentalScene::onPreRelease() {}
