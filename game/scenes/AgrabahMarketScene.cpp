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

	/* Springs*/
	/*gameManager->getPrefabV2( "Jumpable Spring" )->instantiateWithArgs( "" )
		->getTransform()->setPosition(Vec2(3302.5f, 323.0f));

	gameManager->getPrefabV2( "Jumpable Spring" )->instantiateWithArgs( "" )
		->getTransform()->setPosition(Vec2(3319.5f, 403.0f));
	
	gameManager->getPrefabV2("Jumpable Spring")->instantiateWithArgs("")
		->getTransform()->setPosition(Vec2(4084.0f, 452.0f));
*/
	
	/* Checkpoints */
	/*gameManager->getPrefabV2( "Checkpoint" )->instantiateWithArgs( "" )
			->getTransform()
			->setPosition( Vec2( 2545, 73 ) );

	gameManager->getPrefabV2("Checkpoint")->instantiateWithArgs("")
		->getTransform()
		->setPosition(Vec2(3519.5f, 379.0f));

	gameManager->getPrefabV2("Checkpoint")->instantiateWithArgs("")
		->getTransform()
		->setPosition(Vec2(3346.0f, 108.5f));*/
	
	/* Charcoal Burners */
	/*gameManager->getPrefabV2( "Charcoal Burner" )->instantiateWithArgs( "90", "Charcoal Burner 1" )
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
			->setPosition( Vec2( 2987, -82 ) );*/

	/* Camels */
	/*gameManager->getPrefabV2( "Camel" )->instantiateWithArgs( "R" )
			->getTransform()
			->setPosition( Vec2( 1404.5, -57.5 ) );*/

	/* Hand Enemies ? ? :D ? ?*/
	/*gameManager->getPrefabV2( "Hand Enemy" )->instantiateWithArgs( "R 45 80 0 -80", "Hand Enemy 1" )
			->getTransform()
			->setPosition( Vec2( 1680.0f, 57.5f ) );

	gameManager->getPrefabV2( "Hand Enemy" )->instantiateWithArgs( "R 45 100 0 -102" )
			->getTransform()
			->setPosition( Vec2( 1632.5f, 89.5f ) );
	*/

	/* Eatable Apples */
	//float appleX[] = { //325.5f, 355.0f, 388.0f, 691.5f, 723.0f, 755.5f, 869.5f, 901.5f, 932.0f,1363.0f, 1396.5f, 1409.0f, 1490.5f, 1526.0f, 1559.0f, 1589.0f, 1619.5f, 1839, 1845, 1869, 1978, 2006, 2011,
	//	//1607, 1402, 1338, 1338, 1346, 1361, 1616, 1654, 1690, 1824, 1858, 1900, 2132, 2164, 2190, 2190, 2190, 2190, 2190
	//	//2100, 2115, 2131, 2257, 2373, 2272,2727, 2727, 2727, 2947, 2983, 3018, 3181, 3244, 3211, 3348, 3414, 3381, 3682, 3744, 3713, 3936, 3999, 3968, 4489, 4396, 4347, 4290,
	//	4050, 3944, 3782, 3746, 3700, 3370, 3334, 3298, 3254, 3212, 3170, 2776, 2738, 2700, 2488, 2704, 2720, 2740, 3146, 3162, 3194, 3458, 4136, 4164, 4164, 4192 };
	//float appleY[] = { //27.5f, 43.0f, 27.5f, 25.5f, 44.5f, 25.5f, 27.0f, 45.0f, 27.0f, 90.5f, 75.0f, 41.0f, 14.5f, 29.5f, 14.5f, 29.5f, 14.5f, 24, 60, 95, 95, 56, 24,
	//	//206, 181, 255, 296, 333, 362,380, 392, 380, 378, 402, 378, 378, 376, 340, 284, 232, 184, 142
	//	//51, 70, 51, -4, -26, 85,82, 35, -15, -9, 9, -10, -10, -10, 8, -9, -9, 9, -9, -8, 10, -5, -5, 9, 165, 221, 240, 221
	//	155, 137, 201, 191, 157, 167, 185, 167, 167, 193, 167, 229, 247, 231, 365, 337, 359, 337, 459, 491, 505, 395, 543, 563, 525, 541 };
	
	////for (size_t i = 0; i<sizeof(appleX); i++)
	//for (int i = 0; i<28; i++)
	//{
	//	gameManager->getPrefabV2( "Eatable Apple" )->instantiateWithArgs( "", "Apple 1" )
	//		->getTransform()->setPosition( Vec2( appleX[i], appleY[i] ) );
	//}
	
	/* Eatable Hearts */
	/*gameManager->getPrefabV2( "Eatable Heart" )->instantiateWithArgs( "", "Heart 1" )
			->getTransform()
			->setPosition( Vec2(2232.0f, -68.5f) );
	
	gameManager->getPrefabV2("Eatable Heart")->instantiateWithArgs("", "Heart 1")
		->getTransform()
		->setPosition(Vec2(3077.0f, 186.5f));
	
	gameManager->getPrefabV2("Eatable Heart")->instantiateWithArgs("", "Heart 1")
		->getTransform()
		->setPosition(Vec2(2875.5f, 504.0f));*/

	/* Genie Lamps */
	/*gameManager->getPrefabV2("Genie Lamp")->instantiateWithArgs("", "Genie Lamp 1")
			->getTransform()
			->setPosition(Vec2(1849.5f, 142.0f));

	gameManager->getPrefabV2("Genie Lamp")->instantiateWithArgs("", "Genie Lamp 1")
		->getTransform()
		->setPosition(Vec2(2309.5f, 47.0f));
	
	gameManager->getPrefabV2("Genie Lamp")->instantiateWithArgs("", "Genie Lamp 1")
		->getTransform()
		->setPosition(Vec2(2899.5f, 159.5f));*/
	
	/* Genie Bonuses */
	/*gameManager->getPrefabV2( "Genie Bonus" )->instantiateWithArgs( "", "Genie Bonus 1" )
			->getTransform()
			->setPosition( Vec2(1474.5f, 172.0f));
	
	gameManager->getPrefabV2("Genie Bonus")->instantiateWithArgs("", "Genie Bonus 1")
		->getTransform()
		->setPosition(Vec2(2094.5f, -41.0f));
	
	gameManager->getPrefabV2("Genie Bonus")->instantiateWithArgs("", "Genie Bonus 1")
		->getTransform()
		->setPosition(Vec2(3992.0f, 184.0f));

	gameManager->getPrefabV2("Genie Bonus")->instantiateWithArgs("", "Genie Bonus 1")
		->getTransform()
		->setPosition(Vec2(2375.5f, 494.0f));
	
	gameManager->getPrefabV2("Genie Bonus")->instantiateWithArgs("", "Genie Bonus 1")
		->getTransform()
		->setPosition(Vec2(2961.5f, 359.0f));*/

	/* Spend Theses */
	/*gameManager->getPrefabV2( "Spend These" )->instantiateWithArgs( "", "Spend These 1" )
		->getTransform()
		->setPosition(Vec2(2182.0f, -71.0f));

	gameManager->getPrefabV2("Spend These")->instantiateWithArgs("", "Spend These 1")
		->getTransform()
		->setPosition(Vec2(2497.0f, -53.5f));

	gameManager->getPrefabV2("Spend These")->instantiateWithArgs("", "Spend These 1")
		->getTransform()
		->setPosition(Vec2(2552.0f, -53.5f));

	gameManager->getPrefabV2("Spend These")->instantiateWithArgs("", "Spend These 1")
		->getTransform()
		->setPosition(Vec2(2488.5f, 329.0f));

	gameManager->getPrefabV2("Spend These")->instantiateWithArgs("", "Spend These 1")
		->getTransform()
		->setPosition(Vec2(2488.5f, 300.0f));
	
	gameManager->getPrefabV2("Spend These")->instantiateWithArgs("", "Spend These 1")
		->getTransform()
		->setPosition(Vec2(2849.5f, 480.0f));

	gameManager->getPrefabV2("Spend These")->instantiateWithArgs("", "Spend These 1")
		->getTransform()
		->setPosition(Vec2(2879.5f, 461.0f));

	gameManager->getPrefabV2("Spend These")->instantiateWithArgs("", "Spend These 1")
		->getTransform()
		->setPosition(Vec2(2908.5f, 480.0f));*/
		
	/* Abu Bonus */
	/*gameManager->getPrefabV2( "Abu Bonus" )->instantiateWithArgs( "", "Abu Bonus 1" )
		 ->getTransform()
		 ->setPosition(Vec2(3143.0f, 404.0f));*/

	/* Peddlers */
	/*gameManager->getPrefabV2( "Peddler" )->instantiateWithArgs( "", "Peddler 1" )
		->getTransform()
		->setPosition(Vec2(3790.5f, 386.5f));*/

	/* Guards */
	/*gameManager->getPrefabV2( "Guard 1" )->instantiateWithArgs( "550 430 670", "Guard 1" )
	   ->getTransform()->setPositionY( -25 );

	gameManager->getPrefabV2( "Guard 2" )->instantiateWithArgs( "818 595 1010", "Guard 2" )
	   ->getTransform()->setPositionY( -25 ); 

	gameManager->getPrefabV2( "Guard 3" )->instantiateWithArgs( "1559 1380 1699", "Guard 3" )
	   ->getTransform()->setPositionY( -25 ); 

	gameManager->getPrefabV2( "Guard 4" )->instantiateWithArgs( "1169", "Guard 4" )
	   ->getTransform()->setPositionY( 10 );

	gameManager->getPrefabV2("Guard 3")->instantiateWithArgs("1660 1597 1875", "Guard 3")
		->getTransform()->setPositionY(163);

	gameManager->getPrefabV2("Guard 2")->instantiateWithArgs("1567 1437 2102", "Guard 2")
		->getTransform()->setPositionY(336);

	gameManager->getPrefabV2("Guard 3")->instantiateWithArgs("2050 1437 2102", "Guard 3")
		->getTransform()->setPositionY(336);

	gameManager->getPrefabV2("Guard 4")->instantiateWithArgs("2370", "Guard 4")
		->getTransform()->setPositionY(81);

	gameManager->getPrefabV2("Guard 3")->instantiateWithArgs("2657 2577 2680", "Guard 3")
		->getTransform()->setPositionY(43);

	gameManager->getPrefabV2("Guard 2")->instantiateWithArgs("3080 2662 4170", "Guard 2")
		->getTransform()->setPositionY(-40);

	gameManager->getPrefabV2("Guard 3")->instantiateWithArgs("3305 2662 4170", "Guard 3")
		->getTransform()->setPositionY(-40);

	gameManager->getPrefabV2("Guard 2")->instantiateWithArgs("3507 2662 4170", "Guard 2")
		->getTransform()->setPositionY(-40);

	gameManager->getPrefabV2("Guard 2")->instantiateWithArgs("4137 2662 4170", "Guard 2")
		->getTransform()->setPositionY(-40);

	gameManager->getPrefabV2("Guard 3")->instantiateWithArgs("4498 4315 4607", "Guard 3")
		->getTransform()->setPositionY(-6);

	gameManager->getPrefabV2("Guard 4")->instantiateWithArgs("4190", "Guard 4")
		->getTransform()->setPositionY(150);

	gameManager->getPrefabV2("Guard 3")->instantiateWithArgs("3740 3685 3800", "Guard 3")
		->getTransform()->setPositionY(160);

	gameManager->getPrefabV2("Guard 2")->instantiateWithArgs("3630 2902 3660", "Guard 2")
		->getTransform()->setPositionY(123);

	gameManager->getPrefabV2("Guard 3")->instantiateWithArgs("2992 3685 3800", "Guard 3")
		->getTransform()->setPositionY(160);

	gameManager->getPrefabV2("Guard 3")->instantiateWithArgs("2832 2660 2922", "Guard 3")
		->getTransform()->setPositionY(191);

	gameManager->getPrefabV2("Guard 5")->instantiateWithArgs("2697 2660 2922", "Guard 5")
		->getTransform()->setPositionY(191);

	gameManager->getPrefabV2("Guard 4")->instantiateWithArgs("2378", "Guard 4")
		->getTransform()->setPositionY(443);

	gameManager->getPrefabV2("Guard 4")->instantiateWithArgs("2952", "Guard 4")
		->getTransform()->setPositionY(443);

	gameManager->getPrefabV2("Guard 2")->instantiateWithArgs("2915 2662 3030", "Guard 2")
		->getTransform()->setPositionY(319);

	gameManager->getPrefabV2("Guard 3")->instantiateWithArgs("3135 3037 3385", "Guard 3")
		->getTransform()->setPositionY(286);

	gameManager->getPrefabV2("Guard 2")->instantiateWithArgs("4357 4192 4535", "Guard 2")
		->getTransform()->setPositionY(400);*/

	///////// ALADDIN //////////////
	new CameraController(getMainCamera());
	gameManager->getPrefabV2("Playable Aladdin")->instantiateWithArgs("-80 -25", "Aladdin");
	
	/* Dev support*/
	/*gameManager->getPrefabV2("Playable Aladdin")->instantiateWithArgs("3872 200", "Aladdin");

	const auto devNode = gameManager->getPrefab("Node")->instantiate();
	devNode->setLayer("Debug");
	devNode->getTransform()->setPosition(Vec2(600, 0));

	new DebugCameraController(getMainCamera(), devNode);*/

}
