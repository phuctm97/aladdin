#include "AgrabahMarketScene.h"
#include "../Define.h"
#include "../app/MyAppData.h"
#include "../scripts/CameraController.h"
#include "../scripts/DebugCameraController.h"
#include "../scripts/NodeController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AgrabahMarketScene, ala::Scene)

void AgrabahMarketScene::onPreInitialize() {
	// constants
	const auto gameManager = GameManager::get();
	const auto startPosition = Vec2(-80, -25);

	// configurations
	enablePhysics(Vec2(0, -500.0f));

	

	//new CameraController(getMainCamera());

	// initial objects
	gameManager->getPrefabV2("Sprite")->instantiateWithArgs("background.png 0", "Background")
		->setTag(BACKGROUND_TAG)
		->setLayer("Background")
		->getTransform()
		->setPosition(Vec2(2385.5f, 344) - Vec2(gameManager->getVisibleWidth() / 2,
			gameManager->getVisibleHeight() / 2));

	gameManager->getPrefabV2("Sprite")->instantiateWithArgs("foreground.png 0", "Foreground")
		->setTag(FOREGROUND_TAG)
		->setLayer("Second Foreground")
		->getTransform()
		->setPosition(Vec2(2385.5f, 344) - Vec2(gameManager->getVisibleWidth() / 2,
			gameManager->getVisibleHeight() / 2));

	gameManager->getPrefabV2("Hub")->instantiateWithArgs("", "Hub");

	gameManager->getPrefabV2("Agrabah Market Ground")->instantiateWithArgs("", "Ground");


	/* Stairs */
	/*gameManager->getPrefabV2("Agrabah Market Stairs 1")->instantiateWithArgs("", "Stairs 1")
		->getTransform()->setPosition(1015.5f, -46.0f);

	gameManager->getPrefabV2("Agrabah Market Stairs 4")->instantiateWithArgs("0", "Stairs 4")
		->getTransform()->setPosition(2445.0f, -87.5f);

	gameManager->getPrefabV2("Agrabah Market Stairs 5")->instantiateWithArgs("0", "Stairs 5")
		->getTransform()->setPosition(3811.0f, 124.5f);

	gameManager->getPrefabV2("Agrabah Market Stairs 6")->instantiateWithArgs("0", "Stairs 5")
		->getTransform()->setPosition(4214.5f, -76.5f);*/


	/* Platforms */
	/*gameManager->getPrefabV2("Platform")->instantiateWithArgs("295")
		->getTransform()->setPosition(Vec2(1735.0f, 130.0f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("105")
		->getTransform()->setPosition(Vec2(1367.5f, 130.0f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("39")
		->getTransform()->setPosition(Vec2(1335.5f, 178.5f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("682")
		->getTransform()->setPosition(Vec2(1768.50f, 292.00f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("129")
		->getTransform()->setPosition(Vec2(2427.50f, 403.00f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("275")
		->getTransform()->setPosition(Vec2(2786.00f, 144.50f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("762")
		->getTransform()->setPosition(Vec2(3276.00f, 84.50f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("106")
		->getTransform()->setPosition(Vec2(2631.00f, 4.50f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("192")
		->getTransform()->setPosition(Vec2(2554.50f, 164.00f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("409")
		->getTransform()->setPosition(Vec2(2837.00f, 276.50f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("86")
		->getTransform()->setPosition(Vec2(2625.00f, 403.00f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("193")
		->getTransform()->setPosition(Vec2(2906.50f, 402.50f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("90")
		->getTransform()->setPosition(Vec2(4190.50f, 100.00f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("440")
		->getTransform()->setPosition(Vec2(3253.0f, 248.00f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("110")
		->getTransform()->setPosition(Vec2(3397.00f, 450.50f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("717")
		->getTransform()->setPosition(Vec2(3775.5f, 356.50f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("405")
		->getTransform()->setPosition(Vec2(4400.50f, 357.00f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("90")
		->getTransform()->setPosition(Vec2(4190.50f, 100.50f));

	gameManager->getPrefabV2("Platform")->instantiateWithArgs("88")
		->getTransform()->setPosition(Vec2(3872.0f, 131.5f)); */

	/* Walls */
	/*gameManager->getPrefabV2("Wall")->instantiateWithArgs("29 68")
		->getTransform()->setPosition(Vec2(1299, -47));

	gameManager->getPrefabV2("Wall")->instantiateWithArgs("20 387")
		->getTransform()->setPosition(Vec2(1305.5f, 317.0f));

	gameManager->getPrefabV2("Wall")->instantiateWithArgs("40 349")
		->getTransform()->setPosition(Vec2(2064.0f, 95.0f));

	gameManager->getPrefabV2("Wall")->instantiateWithArgs("26 190")
		->getTransform()->setPosition(Vec2(2351.0f, 462.5f));

	gameManager->getPrefabV2("Wall")->instantiateWithArgs("41 222")
		->getTransform()->setPosition(Vec2(2463.5f, 277.0f));

	gameManager->getPrefabV2("Wall")->instantiateWithArgs("39 120")
		->getTransform()->setPosition(Vec2(2639.5f, 327.5f));

	gameManager->getPrefabV2("Wall")->instantiateWithArgs("39 57")
		->getTransform()->setPosition(Vec2(2879.5f, 107.5f));

	gameManager->getPrefabV2("Wall")->instantiateWithArgs("27 169")
		->getTransform()->setPosition(Vec2(3016.5f, 474.5f));

	gameManager->getPrefabV2("Wall")->instantiateWithArgs("44 206")
		->getTransform()->setPosition(Vec2(3422.0f, 334.0f));

	gameManager->getPrefabV2("Wall")->instantiateWithArgs("61 175")
		->getTransform()->setPosition(Vec2(4165.5f, 428.0f));*/

	/* Ropes */

	/*gameManager->getPrefabV2( "Climbable Rope" )->instantiateWithArgs( "280" )
			   ->getTransform()->setPosition( Vec2( 1931, 252 ) );

	gameManager->getPrefabV2("Climbable Rope")->instantiateWithArgs("205")
		->getTransform()->setPosition(Vec2(1387.0f, 428.0f));

	gameManager->getPrefabV2("Climbable Rope")->instantiateWithArgs("255")
		->getTransform()->setPosition(Vec2(2538.5f, 493.0f));

	gameManager->getPrefabV2("Climbable Rope")->instantiateWithArgs("200")
		->getTransform()->setPosition(Vec2(4555.0f, 220.5f));*/
	
	
	/* Bars */
	/*gameManager->getPrefabV2( "Holdable Bar" )->instantiateWithArgs( "412" )
		->getTransform()
		->setPosition(4598.5f, 262.5f);
	
	gameManager->getPrefabV2("Holdable Bar")->instantiateWithArgs("192")
		->getTransform()
		->setPosition(4391.0f, 487.0f);*/

	/* Springs

	gameManager->getPrefabV2( "Jumpable Spring" )->instantiateWithArgs( "" )
			   ->getTransform()
			   ->setPosition( 0, 42 );

	*/

	/* Checkpoints
	gameManager->getPrefabV2( "Checkpoint" )->instantiateWithArgs( "" )
			->getTransform()
			->setPosition( Vec2( 2545, 73 ) );

	*/

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



	/* Eatable Apples

	gameManager->getPrefabV2( "Eatable Apple" )->instantiateWithArgs( "", "Apple 1" )
			->getTransform()
			->setPosition( Vec2( 0, 10 ) );

	*/

	/* Eatable Hearts

	gameManager->getPrefabV2( "Eatable Heart" )->instantiateWithArgs( "", "Heart 1" )
			->getTransform()
			->setPosition( Vec2( 0, 10 ) );

	*/

	/* Genie Lamps

	gameManager->getPrefabV2("Genie Lamp")->instantiateWithArgs("", "Genie Lamp 1")
			->getTransform()
			->setPosition(Vec2(600, 10));

	*/

	/* Genie Bonuses

	gameManager->getPrefabV2( "Genie Bonus" )->instantiateWithArgs( "", "Genie Bonus 1" )
			->getTransform()
			->setPosition( Vec2( 0, 10 ) );

	*/

	/* Spend Theses

	gameManager->getPrefabV2( "Spend These" )->instantiateWithArgs( "", "Spend These 1" )
		->getTransform()
		->setPosition( Vec2( 0, 10 ) );

	*/

	/* Abu Bonus

	gameManager->getPrefabV2( "Abu Bonus" )->instantiateWithArgs( "", "Abu Bonus 1" )
		 ->getTransform()
		 ->setPosition( Vec2( 0, 10 ) );

	*/

	/* Peddlers

	gameManager->getPrefabV2( "Peddler" )->instantiateWithArgs( "", "Peddler 1" )
		->getTransform()
		->setPosition( Vec2( 0, 10 ) );

	*/

	/* Guards

	gameManager->getPrefabV2( "Guard 1" )->instantiateWithArgs( "550 430 670", "Guard 1" )
	   ->getTransform()->setPositionY( -25 );

	gameManager->getPrefabV2( "Guard 2" )->instantiateWithArgs( "818 595 1010", "Guard 2" )
	   ->getTransform()->setPositionY( -25 );

	gameManager->getPrefabV2( "Guard 3" )->instantiateWithArgs( "1559 1380 1699", "Guard 3" )
	   ->getTransform()->setPositionY( -25 );

	gameManager->getPrefabV2( "Guard 4" )->instantiateWithArgs( "1169", "Guard 4" )
	   ->getTransform()->setPositionY( 10 );

	gameManager->getPrefabV2( "Guard 5" )->instantiateWithArgs( "550 430 670", "Guard 5" )
	   ->getTransform()->setPositionY( -25 );

	*/

	//gameManager->getPrefabV2("Playable Aladdin")->instantiateWithArgs("-80 -25", "Aladdin");
	gameManager->getPrefabV2("Playable Aladdin")->instantiateWithArgs("3872 200", "Aladdin");

	const auto devNode = gameManager->getPrefab("Node")->instantiate();
	devNode->setLayer("Debug");
	devNode->getTransform()->setPosition(Vec2(4555.0f, 220.5f));

	new DebugCameraController(getMainCamera(), devNode);

}
