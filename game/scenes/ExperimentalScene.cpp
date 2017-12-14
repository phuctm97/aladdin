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

  


}

void ExperimentalScene::onPreRelease() {}
