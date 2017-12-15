/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "ExperimentalScene.h"
#include "../scripts/CameraController.h"
#include "../scripts/NodeController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ExperimentalScene::ExperimentalScene() : _logger("ExperimentalScene") {}

void ExperimentalScene::onPreInitialize() {

  // constants
  const auto gameManager = GameManager::get();
  const auto halfVisibleWidth = gameManager->getVisibleWidth() / 2;
  const auto halfVisibleHeight = gameManager->getVisibleHeight() / 2;

  // configurations
  enablePhysics( Vec2( 0, -500.0f ) );

  //  enableQuadTree( -halfVisibleWidth, -halfVisibleHeight,
  //                  4771 - halfVisibleWidth, 688 - halfVisibleHeight, 3 );

  new CameraController( getMainCamera() );


	// initial objects
	const auto background = new GameObject(this, "Background");
	background->setTag(BACKGROUND_TAG);

	const auto backgroundSpriteRenderer = new SpriteRenderer(background, "background.png");
	background->setLayer("Background");
	background->getTransform()->setPosition(
		Vec2(backgroundSpriteRenderer->getFrameSize().getWidth() / 2,
			backgroundSpriteRenderer->getFrameSize().getHeight() / 2)
		- Vec2(gameManager->getVisibleWidth() / 2,
			gameManager->getVisibleHeight() / 2));

	const auto foreground = new GameObject(this, "Foreground");
	foreground->setTag(FOREGROUND_TAG);

	const auto foregroundSpriteRenderer = new SpriteRenderer(foreground, "foreground.png");
	foreground->setLayer("Foreground");
	foreground->getTransform()->setPosition(
		Vec2(foregroundSpriteRenderer->getFrameSize().getWidth() / 2,
			foregroundSpriteRenderer->getFrameSize().getHeight() / 2)
		- Vec2(gameManager->getVisibleWidth() / 2,
			gameManager->getVisibleHeight() / 2));

	const auto hub = gameManager->getPrefab("Hub")->instantiate("Hub");

	const auto ground = gameManager->getPrefab("Ground")->instantiate("Ground");

	const auto ropeOne = gameManager->getPrefab("Rope")->instantiate("Rope 1");
	ropeOne->getTransform()->setPosition(Vec2(1931, 86));
	ropeOne->getComponentT<Collider>()->setSize(Size(5, 250));

	const auto ropeTwo = gameManager->getPrefab("Rope")->instantiate("Rope 2");
	ropeTwo->getTransform()->setPosition(Vec2(1387, 298));
	ropeTwo->getComponentT<Collider>()->setSize(Size(5, 193));

	const auto ropeThree = gameManager->getPrefab("Rope")->instantiate("Rope 3");
	ropeThree->getTransform()->setPosition(Vec2(2539, 345));
	ropeThree->getComponentT<Collider>()->setSize(Size(5, 249));

	const auto ropeFour = gameManager->getPrefab("Rope")->instantiate("Rope 4");
	ropeFour->getTransform()->setPosition(Vec2(4555, 99));
	ropeFour->getComponentT<Collider>()->setSize(Size(5, 193));

	const auto charcoalBurnerOne = gameManager->getPrefab("Charcoal Burner")->instantiate("Charcoal Burner 1");
	charcoalBurnerOne->getTransform()->setPosition(Vec2(360.5f, -50));

	const auto charcoalBurnerTwo = gameManager->getPrefab("Charcoal Burner")->instantiate("Charcoal Burner 2");
	charcoalBurnerTwo->getTransform()->setPosition(Vec2(730.5f, -50));

	const auto charcoalBurnerThree = gameManager->getPrefab("Charcoal Burner")->instantiate("Charcoal Burner 3");
	charcoalBurnerThree->getTransform()->setPosition(Vec2(906.5f, -50));

	const auto aladdin = gameManager->getPrefab("Aladdin")->instantiate("Aladdin");
	//aladdin->getTransform()->setPosition( Vec2( -80, -25 ) );
	aladdin->getTransform()->setPosition(Vec2(150, -25));
	

#pragma region Stair
#pragma region Group One
	const auto stairOne = gameManager->getPrefab("StairGroupOne")->instantiate();
	stairOne->getTransform()->setPosition(Vec2(1015.5f, -46.0f));
	stairOne->getComponentT<Collider>()->setSize(Size(45.0f, 8.0f));

	const auto stairTwo = gameManager->getPrefab("StairGroupOne")->instantiate();
	stairTwo->getTransform()->setPosition(Vec2(1055.5f, -36.0f));
	stairTwo->getComponentT<Collider>()->setSize(Size(42.0f, 7.0f));

	const auto stairThree = gameManager->getPrefab("StairGroupOne")->instantiate();
	stairThree->getTransform()->setPosition(Vec2(1096.0f, -28.5f));
	stairThree->getComponentT<Collider>()->setSize(Size(42.0f, 6.0f));

	const auto stairFour = gameManager->getPrefab("StairGroupOne")->instantiate();
	stairFour->getTransform()->setPosition(Vec2(1136.0f, -21.5f));
	stairFour->getComponentT<Collider>()->setSize(Size(45.0f, 7.0f));

	const auto stairFive = gameManager->getPrefab("StairGroupOne")->instantiate();
	stairFive->getTransform()->setPosition(Vec2(1176.0f, -12.5f));
	stairFive->getComponentT<Collider>()->setSize(Size(43.0f, 6.0f));

	const auto stairSix = gameManager->getPrefab("StairGroupOne")->instantiate();
	stairSix->getTransform()->setPosition(Vec2(1215.0f, -5.5f));
	stairSix->getComponentT<Collider>()->setSize(Size(43.0f, 7.0f));

	const auto stairSeven = gameManager->getPrefab("StairGroupOne")->instantiate();
	stairSeven->getTransform()->setPosition(Vec2(1286.0f, 2.5f));
	stairSeven->getComponentT<Collider>()->setSize(Size(106.0f, 7.0f));

	/*stairSeven->setTag(ALADDIN_TAG);
	new NodeController(stairSeven);*/
#pragma endregion
#pragma endregion


#pragma region MapBlocker
	const auto mapBlocker = gameManager->getPrefab("MapBlocker")->instantiate();
	mapBlocker->getTransform()->setPosition(Vec2(1300.5f, -41.5f));

	//mapBlocker->setTag(ALADDIN_TAG);
	//new NodeController(mapBlocker);
#pragma endregion


#pragma region Apples


	float appleGroupOneX[] = { 325.5f, 355.0f, 388.0f, 691.5f, 723.0f, 755.5f, 869.5f, 901.5f, 932.0f,1363.0f, 1396.5f, 1409.0f, 1490.5f, 1526.0f, 1559.0f, 1589.0f, 1619.5f };
	float appleGroupOneY[] = { 27.5f, 43.0f, 27.5f, 25.5f, 44.5f, 25.5f, 27.0f, 45.0f, 27.0f, 90.5f, 75.0f, 41.0f, 14.5f, 29.5f, 14.5f, 29.5f, 14.5f };
	for (int index = 0; index < 17; index++)
	{
		const auto newApple = gameManager->getPrefab("Apple")->instantiate();
		newApple->getTransform()->setPosition(Vec2(appleGroupOneX[index], appleGroupOneY[index]));
	}

	/*const auto runningApple = gameManager->getPrefab("Apple")->instantiate();
	runningApple->getTransform()->setPosition(Vec2(0 ,0));

	runningApple->setTag(ALADDIN_TAG);
	new NodeController(runningApple);*/
#pragma endregion

  


//  const auto charcoalBurnerOne = gameManager->getPrefab( "Charcoal Burner" )->instantiate();
//  charcoalBurnerOne->getTransform()->setPosition( Vec2( 360.5f, -50 ) );

  // Extra health
  /*const auto extra_health_1 = gameManager->getPrefab("extra health")->instantiate();
  extra_health_1->getTransform()->setPosition(Vec2(2228.5, -71));
  const auto extra_health_2 = gameManager->getPrefab("extra health")->instantiate();
  extra_health_2->getTransform()->setPosition(Vec2(3075.5, 185.5));
  const auto extra_health_3 = gameManager->getPrefab("extra health")->instantiate();
  extra_health_3->getTransform()->setPosition(Vec2(2884, 488));*/
  /*
  X: 2228.500000; Y: -71.000000
  X: 3075.500000; Y: 185.500000
  X: 2884.000000; Y: 488.000000
  */

  // Spend these
  /*const auto spend_these_1 = gameManager->getPrefab("spend these")->instantiate();
  spend_these_1->getTransform()->setPosition(Vec2(2499, -51.5));
  const auto spend_these_2 = gameManager->getPrefab("spend these")->instantiate();
  spend_these_2->getTransform()->setPosition(Vec2(2548, -51.5));
  const auto spend_these_3 = gameManager->getPrefab("spend these")->instantiate();
  spend_these_3->getTransform()->setPosition(Vec2(2484, 330.5));
  const auto spend_these_4 = gameManager->getPrefab("spend these")->instantiate();
  spend_these_4->getTransform()->setPosition(Vec2(2484, 297));
  const auto spend_these_5 = gameManager->getPrefab("spend these")->instantiate();
  spend_these_5->getTransform()->setPosition(Vec2(2850.5, 476));
  const auto spend_these_6 = gameManager->getPrefab("spend these")->instantiate();
  spend_these_6->getTransform()->setPosition(Vec2(2882.5, 461));
  const auto spend_these_7 = gameManager->getPrefab("spend these")->instantiate();
  spend_these_7->getTransform()->setPosition(Vec2(2918.5, 476));
  const auto spend_these_8 = gameManager->getPrefab("spend these")->instantiate();
  spend_these_8->getTransform()->setPosition(Vec2(2181, -68));*/
  /*
  X: 2499.000000; Y: -51.500000
  X: 2548.000000; Y: -51.500000
  X: 2484.000000; Y: 330.500000
  X: 2484.000000; Y: 297.000000
  X: 2850.500000; Y: 476.000000
  X: 2882.500000; Y: 461.000000
  X: 2918.500000; Y: 476.000000
  X: 2181.000000; Y: -68.000000
  */

  // Abu bonus
  /*const auto abu_bonus = gameManager->getPrefab("abu bonus")->instantiate();
  abu_bonus->getTransform()->setPosition(Vec2(3139, 413));*/
  /*X: 3139.000000; Y: 413.000000*/

  

  // Restart point
  /*const auto restart_1 = gameManager->getPrefab("restart point")->instantiate();
  restart_1->getTransform()->setPosition(Vec2(2546.5, 75.5));
  const auto restart_2 = gameManager->getPrefab("restart point")->instantiate();
  restart_2->getTransform()->setPosition(Vec2(3346.5, 107));
  const auto restart_3 = gameManager->getPrefab("restart point")->instantiate();
  restart_3->getTransform()->setPosition(Vec2(3522.5, 379.5));*/
  /*
  X: 2546.500000; Y: 75.500000
  X: 3346.500000; Y: 107.000000
  X: 3522.500000; Y: 379.500000
  */

  // Genie Bonus
  /*const auto genie_bonus_1 = gameManager->getPrefab("genie bonus")->instantiate();
  genie_bonus_1->getTransform()->setPosition(Vec2(1477, 186));
  const auto genie_bonus_2 = gameManager->getPrefab("genie bonus")->instantiate();
  genie_bonus_2->getTransform()->setPosition(Vec2(2100, -36.5));
  const auto genie_bonus_3 = gameManager->getPrefab("genie bonus")->instantiate();
  genie_bonus_3->getTransform()->setPosition(Vec2(4004.5, 204));
  const auto genie_bonus_4 = gameManager->getPrefab("genie bonus")->instantiate();
  genie_bonus_4->getTransform()->setPosition(Vec2(2392, 488.5));
  const auto genie_bonus_5 = gameManager->getPrefab("genie bonus")->instantiate();
  genie_bonus_5->getTransform()->setPosition(Vec2(2965.5, 362));*/
  /*
  X: 1477.000000; Y: 186.000000
  X: 2100.000000; Y: -36.500000
  X: 4004.500000; Y: 204.000000
  X: 2392.000000; Y: 488.500000
  X: 2965.500000; Y: 362.000000
  */

  // Genie lamp
  /*const auto genie_lamp_1 = gameManager->getPrefab("genie lamp")->instantiate();
  genie_lamp_1->getTransform()->setPosition(Vec2(1843, 146.5));
  const auto genie_lamp_2 = gameManager->getPrefab("genie lamp")->instantiate();
  genie_lamp_2->getTransform()->setPosition(Vec2(2304, 50.5));
  const auto genie_lamp_3 = gameManager->getPrefab("genie lamp")->instantiate();
  genie_lamp_3->getTransform()->setPosition(Vec2(2898, 162));*/
  /*
  X: 1843.000000; Y: 146.500000
  X: 2304.000000; Y: 50.500000
  X: 2898.000000; Y: 162.000000
  */

  // Camel
  const auto camel = gameManager->getPrefab("camel")->instantiate();
  camel->getTransform()->setPosition(Vec2(1400, -55));

  // Peddler
  const auto peddler = gameManager->getPrefab("peddler")->instantiate();
  peddler->getTransform()->setPosition(Vec2(3783.5, 388));
  /* X: 3783.500000; Y: 388.000000*/

  // Spring
  /*const auto spring = gameManager->getPrefab("spring")->instantiate();
  spring->getTransform()->setPosition(Vec2(100, -25));*/
  /*X: 
  3322.000000; Y: 323.500000
  3335.000000; Y: 416.500000
  */

  /*spend_these->setTag(ALADDIN_TAG);
  new NodeController(spend_these);
  return;*/

  // Hand enemy
  const auto handEnemy_1 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_1->getTransform()->setPosition(Vec2(1632.5, 91.5));
  const auto handEnemy_2 = gameManager->getPrefab("Hand Enemy")->instantiate();
  handEnemy_2->getTransform()->setPosition(Vec2(1680.5, 60));
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
