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

  /*const auto extra_health = gameManager->getPrefab("extra health")->instantiate();
  extra_health->getTransform()->setPosition(Vec2(100, -25));*/

  /*const auto spend_these = gameManager->getPrefab("spend these")->instantiate();
  spend_these->getTransform()->setPosition(Vec2(120, -25));*/

  /*const auto abu_bonus = gameManager->getPrefab("abu bonus")->instantiate();
  abu_bonus->getTransform()->setPosition(Vec2(150, -25));*/

  /*const auto charcoalBurnerOne = gameManager->getPrefab( "Charcoal Burner" )->instantiate();
  charcoalBurnerOne->getTransform()->setPosition( Vec2( 360.5f, -50 ) );*/

  /*const auto restart = gameManager->getPrefab("restart point")->instantiate();
  restart->getTransform()->setPosition(Vec2(30, -35));*/

  const auto genie_bonus = gameManager->getPrefab("genie bonus")->instantiate();
  genie_bonus->getTransform()->setPosition(Vec2(190, -15));

  const auto genie_lamp = gameManager->getPrefab("genie lamp")->instantiate();
  genie_lamp->getTransform()->setPosition(Vec2(50, -45));

  /*const auto camel = gameManager->getPrefab("camel")->instantiate();
  camel->getTransform()->setPosition(Vec2(1400, -55));*/

  /*const auto spring = gameManager->getPrefab("spring")->instantiate();
  spring->getTransform()->setPosition(Vec2(100, -25));*/

  /*const auto peddler = gameManager->getPrefab("peddler")->instantiate();
  peddler->getTransform()->setPosition(Vec2(-80, -25));*/

  /*spring->setTag(ALADDIN_TAG);
  new NodeController(spring);
  return;*/

  /*X: 3322.000000; Y: 323.500000
  3335.000000; Y: 416.500000
  */

  
  /*const auto handEnemy_1 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_1->getTransform()->setPosition(Vec2(1632.5, 91.5));
  const auto handEnemy_2 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_2->getTransform()->setPosition(Vec2(1680.5, 60));*/
  /*const auto handEnemy_3 = gameManager->getPrefab("Hand Enemy")->instantiate();
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
  
}

void ExperimentalScene::onPreRelease() {}
