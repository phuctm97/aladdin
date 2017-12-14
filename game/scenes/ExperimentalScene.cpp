/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "ExperimentalScene.h"
#include "../scripts/CameraController.h"
#include "../scripts/GuardController.h"
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

	const auto guardOne = gameManager->getPrefab("Thin Guard")->instantiate("Guard 1");
	guardOne->getTransform()->setPositionY(-25);
	guardOne->getComponentT<GuardController>()->set( 550, 430, 670 );
	
	const auto guardTwo = gameManager->getPrefab( "Fat Guard" )->instantiate( "Guard 2" );
    guardTwo->getTransform()->setPositionY( -25 );
    guardTwo->getComponentT<GuardController>()->set( 818, 620, 992 );

	const auto aladdin = gameManager->getPrefab("Aladdin")->instantiate("Aladdin");
	//aladdin->getTransform()->setPosition( Vec2( -80, -25 ) );
	aladdin->getTransform()->setPosition(Vec2(1335, 500));
	

#pragma region Stair
#pragma region Group One

	const auto stair_GOne_NoOne = gameManager->getPrefab("StairGroupOne")->instantiate();
	stair_GOne_NoOne->getTransform()->setPosition(Vec2(1015.5f, -46.0f));
	stair_GOne_NoOne->getComponentT<Collider>()->setSize(Size(45.0f, 8.0f));

	const auto stair_GOne_NoTwo = gameManager->getPrefab("StairGroupOne")->instantiate();
	stair_GOne_NoTwo->getTransform()->setPosition(Vec2(1055.5f, -36.0f));
	stair_GOne_NoTwo->getComponentT<Collider>()->setSize(Size(42.0f, 7.0f));

	const auto stair_GOne_NoThree = gameManager->getPrefab("StairGroupOne")->instantiate();
	stair_GOne_NoThree->getTransform()->setPosition(Vec2(1096.0f, -28.5f));
	stair_GOne_NoThree->getComponentT<Collider>()->setSize(Size(42.0f, 6.0f));

	const auto stair_GOne_NoFour = gameManager->getPrefab("StairGroupOne")->instantiate();
	stair_GOne_NoFour->getTransform()->setPosition(Vec2(1136.0f, -21.5f));
	stair_GOne_NoFour->getComponentT<Collider>()->setSize(Size(45.0f, 7.0f));

	const auto stair_GOne_NoFive = gameManager->getPrefab("StairGroupOne")->instantiate();
	stair_GOne_NoFive->getTransform()->setPosition(Vec2(1176.0f, -12.5f));
	stair_GOne_NoFive->getComponentT<Collider>()->setSize(Size(43.0f, 6.0f));

	const auto stair_GOne_NoSix = gameManager->getPrefab("StairGroupOne")->instantiate();
	stair_GOne_NoSix->getTransform()->setPosition(Vec2(1215.0f, -5.5f));
	stair_GOne_NoSix->getComponentT<Collider>()->setSize(Size(43.0f, 7.0f));

	const auto stair_GOne_NoSeven = gameManager->getPrefab("StairGroupOne")->instantiate();
	stair_GOne_NoSeven->getTransform()->setPosition(Vec2(1286.0f, 2.5f));
	stair_GOne_NoSeven->getComponentT<Collider>()->setSize(Size(106.0f, 7.0f));

	/*stairSeven->setTag(ALADDIN_TAG);
	new NodeController(stairSeven);*/
#pragma endregion

#pragma region Group Two

	/*const auto stair_GTwo_NoOne = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoOne->getTransform()->setPosition(Vec2(2449.0f, -91.0f));
	stair_GTwo_NoOne->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoTwo = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoTwo->getTransform()->setPosition(Vec2(2441.0f, -85.0f));
	stair_GTwo_NoTwo->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoThree = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoThree->getTransform()->setPosition(Vec2(2415.5f, -81.0f));
	stair_GTwo_NoThree->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoFour = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoFour->getTransform()->setPosition(Vec2(2413.0f, -77.0f));
	stair_GTwo_NoFour->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoFive = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoFive->getTransform()->setPosition(Vec2(2392.0f, -73.0f));
	stair_GTwo_NoFive->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoSix = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoSix->getTransform()->setPosition(Vec2(2388.0f, -69.0f));
	stair_GTwo_NoSix->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoSeven = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoSeven->getTransform()->setPosition(Vec2(2359.0f, -66.0f));
	stair_GTwo_NoSeven->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoEight = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoEight->getTransform()->setPosition(Vec2(2353.5f, -61.0f));
	stair_GTwo_NoEight->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoNine = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoNine->getTransform()->setPosition(Vec2(2327.5f, -58.0f));
	stair_GTwo_NoNine->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoTen = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoTen->getTransform()->setPosition(Vec2(2324.5f, -53.0f));
	stair_GTwo_NoTen->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoEleven = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoEleven->getTransform()->setPosition(Vec2(2296.0f, -50.5f));
	stair_GTwo_NoEleven->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoTwelve = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoTwelve->getTransform()->setPosition(Vec2(2290.5f, -45.5f));
	stair_GTwo_NoTwelve->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoThirteen = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoThirteen->getTransform()->setPosition(Vec2(2263.5f, -42.0f));
	stair_GTwo_NoThirteen->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoFourteen = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoFourteen->getTransform()->setPosition(Vec2(2259.0f, -38.0f));
	stair_GTwo_NoFourteen->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoFifteen = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoFifteen->getTransform()->setPosition(Vec2(2215.0f, -34.0f));
	stair_GTwo_NoFifteen->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoSixteen = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoSixteen->getTransform()->setPosition(Vec2(2210.5f, -29.0f));
	stair_GTwo_NoSixteen->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoSeventeen = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoSeventeen->getTransform()->setPosition(Vec2(2183.5f, -26.0f));
	stair_GTwo_NoSeventeen->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoEighteen = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoEighteen->getTransform()->setPosition(Vec2(2179.5f, -21.5f));
	stair_GTwo_NoEighteen->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoNineteen = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoNineteen->getTransform()->setPosition(Vec2(2152.0f, -18.5f));
	stair_GTwo_NoNineteen->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoTwenty = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoTwenty->getTransform()->setPosition(Vec2(2147.5f, -13.0f));
	stair_GTwo_NoTwenty->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoTwentyOne = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoTwentyOne->getTransform()->setPosition(Vec2(2119.0f, -10.0f));
	stair_GTwo_NoTwentyOne->getComponentT<Collider>()->setSize(Size(26.0f, 3.0f));

	const auto stair_GTwo_NoTwentyTwo = gameManager->getPrefab("StairGroupTwo")->instantiate();
	stair_GTwo_NoTwentyTwo->getTransform()->setPosition(Vec2(2108.5f, -5.0f));
	stair_GTwo_NoTwentyTwo->getComponentT<Collider>()->setSize(Size(45.0f, 3.0f));*/

	/*stair_GTwo_NoOne->setTag(ALADDIN_TAG);
	new NodeController(stair_GTwo_NoOne);*/
#pragma endregion

#pragma endregion

#pragma region MapBlocker
	const auto mapBlocker = gameManager->getPrefab("MapBlocker")->instantiate();
	mapBlocker->getTransform()->setPosition(Vec2(1300.5f, -51.5f));
	mapBlocker->getComponentT<Collider>()->setSize(Size(31, 101));

	//mapBlocker->setTag(ALADDIN_TAG);
	//new NodeController(mapBlocker);
#pragma endregion

#pragma region Apples


	/*float appleGroupOneX[] = { 325.5f, 355.0f, 388.0f, 691.5f, 723.0f, 755.5f, 869.5f, 901.5f, 932.0f,1363.0f, 1396.5f, 1409.0f, 1490.5f, 1526.0f, 1559.0f, 1589.0f, 1619.5f };
	float appleGroupOneY[] = { 27.5f, 43.0f, 27.5f, 25.5f, 44.5f, 25.5f, 27.0f, 45.0f, 27.0f, 90.5f, 75.0f, 41.0f, 14.5f, 29.5f, 14.5f, 29.5f, 14.5f };
	for (int index = 0; index < 17; index++)
	{
		const auto newApple = gameManager->getPrefab("Apple")->instantiate();
		newApple->getTransform()->setPosition(Vec2(appleGroupOneX[index], appleGroupOneY[index]));
	}
*/
	/*const auto runningApple = gameManager->getPrefab("Apple")->instantiate();
	runningApple->getTransform()->setPosition(Vec2(0 ,0));

	runningApple->setTag(ALADDIN_TAG);
	new NodeController(runningApple);*/
#pragma endregion

#pragma region Horizontal bar

	const auto horizontalBar= gameManager->getPrefab("HorizontalBar")->instantiate();
	horizontalBar->getTransform()->setPosition(Vec2(4403.0f, 262.5f));
	horizontalBar->getComponentT<Collider>()->setSize(Size(380.0f, 8.0f));

	/*const auto runningBlock = gameManager->getPrefab("HorizontalBar")->instantiate();
	runningBlock->getTransform()->setPosition(Vec2(3000 ,0));

	runningBlock->setTag(ALADDIN_TAG);
	new NodeController(runningBlock);*/
#pragma endregion

#pragma region Platform

	const auto platform1 = gameManager->getPrefab("Platform")->instantiate();
	platform1->getTransform()->setPosition(Vec2(1735.0f, 128.0f));
	static_cast<Collider*>(platform1->getComponent("Upon"))->setSize(Size(295.0f, 4.5f));
	static_cast<Collider*>(platform1->getComponent("Below"))->setSize(Size(295.0f, 4.5f));
	static_cast<Collider*>(platform1->getComponent("Upon"))->setOffset(Vec2(0, 2.25f));
	static_cast<Collider*>(platform1->getComponent("Below"))->setOffset(Vec2(0, -3.f));

	const auto platform2 = gameManager->getPrefab("Platform")->instantiate(); 
	platform2->getTransform()->setPosition(Vec2(1367.5f, 127.0f));
	static_cast<Collider*>(platform2->getComponent("Upon"))->setSize(Size(105.0f, 4.5f));
	static_cast<Collider*>(platform2->getComponent("Below"))->setSize(Size(105.0f, 4.5f));
	static_cast<Collider*>(platform2->getComponent("Upon"))->setOffset(Vec2(0, 2.25f));
	static_cast<Collider*>(platform2->getComponent("Below"))->setOffset(Vec2(0, -3.0f));
	
	const auto platform3 = gameManager->getPrefab("Platform")->instantiate(); 
	platform3->getTransform()->setPosition(Vec2(1335.5f, 175.5f));
	static_cast<Collider*>(platform3->getComponent("Upon"))->setSize(Size(39.0f, 4.5f));
	static_cast<Collider*>(platform3->getComponent("Below"))->setSize(Size(39.0f, 4.5f));
	static_cast<Collider*>(platform3->getComponent("Upon"))->setOffset(Vec2(0, 2.25f));
	static_cast<Collider*>(platform3->getComponent("Below"))->setOffset(Vec2(0, -2.75f));

	
	/*const auto runningBlock = gameManager->getPrefab("HorizontalBar")->instantiate();
	runningBlock->getTransform()->setPosition(Vec2(300 ,0));
	runningBlock->getComponentT<Collider>()->setSize(Size(5, 5));
	runningBlock->getComponentT<Collider>()->setTrigger(false);

	runningBlock->setTag(ALADDIN_TAG);
	new NodeController(runningBlock);*/

#pragma endregion




}

void ExperimentalScene::onPreRelease() {}
