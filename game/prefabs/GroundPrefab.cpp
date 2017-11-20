#include "GroundPrefab.h"

USING_NAMESPACE_ALA;

void GroundPrefab::doInstantiate(ala::GameObject* object) const {
	// constants
	const auto gameManager = GameManager::get();
	const auto halfVisibleSize = Size(gameManager->getVisibleWidth() / 2, gameManager->getVisibleHeight() / 2);
	const auto body = new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);
	const auto transform = object->getTransform();

	// components

#pragma region Ground

	// First ground
	const auto firstGroundSize = Size(1475, 63);
	const auto firstGroundOffset = Vec2(firstGroundSize.getWidth() / 2, firstGroundSize.getHeight() / 2);
	const auto firstGroundCollider = new Collider(object, false, firstGroundOffset, firstGroundSize, 0, "FirstGround");


	// Second ground
	const auto secondGroundSize = Size(768, 33);
	const auto secondGroundOffset = Vec2(firstGroundSize.getWidth() + secondGroundSize.getWidth() / 2,
		secondGroundSize.getHeight() / 2);
	const auto secondGroundCollider = new Collider(object, false, secondGroundOffset, secondGroundSize, 0, "SecondGround");


	// Third ground
	const auto thirdGroundSize = Size(578, 22);
	const auto thirdGroundOffset = Vec2(secondGroundOffset.getX() + secondGroundSize.getWidth() / 2 + thirdGroundSize.getWidth() / 2,
		thirdGroundSize.getHeight() / 2);
	const auto thirdGroundCollider = new Collider(object, false, thirdGroundOffset, thirdGroundSize, 0, "ThirdGround");


	// Fourth ground
	const auto fourthGroundSize = Size(1952, 30);
	const auto fourthGroundOffset = Vec2(thirdGroundOffset.getX() + thirdGroundSize.getWidth() / 2 + fourthGroundSize.getWidth() / 2,
		fourthGroundSize.getHeight() / 2);
	const auto fourthGroundCollider = new Collider(object, false, fourthGroundOffset, fourthGroundSize, 0, "FourthGround");

#pragma endregion

#pragma region Map blocker - wall

	const auto mapBlockerSize = Size(20, 688);

	const auto mapStartBlocker = new Collider(object, false,
		Vec2(-firstGroundSize.getWidth() / 2 - mapBlockerSize.getWidth() / 2, -firstGroundSize.getHeight() / 2 + mapBlockerSize.getHeight() / 2),
		mapBlockerSize, 0, "MapStartBlocker");

	const auto mapEndBlocker = new Collider(object, false,
		Vec2(fourthGroundOffset.getX() + fourthGroundSize.getWidth() / 2 + mapBlockerSize.getWidth() / 2, -firstGroundSize.getHeight() / 2 + mapBlockerSize.getHeight() / 2),
		mapBlockerSize, 0, "MapEndBlocker");

	const auto mapWallAtStairGroupOne = new Collider(object, false,
		Vec2(1470, 75), Size(11, 91), 0, "MapWallAtStairGroupOne");



#pragma endregion

#pragma region Stair

#pragma region Stair group 1

	/// Stair 1
	const auto stairG1No1Size = Size(41, 75);
	const auto stairG1No1Offset = Vec2(1160 + stairG1No1Size.getWidth() / 2, 0 + stairG1No1Size.getHeight() / 2);
	const auto stairG1No1Collider = new Collider(object, false, stairG1No1Offset, stairG1No1Size, 0, "StairG1No1");

	/// Stair 2
	const auto stairG1No2Size = Size(41, 84);
	const auto stairG1No2Offset = Vec2(stairG1No1Offset.getX() + stairG1No1Size.getWidth() / 2 + stairG1No2Size.getWidth() / 2, 0 + stairG1No2Size.getHeight() / 2);
	const auto stairG1No2Collider = new Collider(object, false, stairG1No2Offset, stairG1No2Size, 0, "StairG1No2");

	/// Stair 3
	const auto stairG1No3Size = Size(39, 90);
	const auto stairG1No3Offset = Vec2(stairG1No2Offset.getX() + stairG1No2Size.getWidth() / 2 + stairG1No3Size.getWidth() / 2, 0 + stairG1No3Size.getHeight() / 2);
	const auto stairG1No3Collider = new Collider(object, false, stairG1No3Offset, stairG1No3Size, 0, "StairG1No3");

	// Stair 4
	const auto stairG1No4Size = Size(40, 99);
	const auto stairG1No4Offset = Vec2(stairG1No3Offset.getX() + stairG1No3Size.getWidth() / 2 + stairG1No4Size.getWidth() / 2, 0 + stairG1No4Size.getHeight() / 2);
	const auto stairG1No4Collider = new Collider(object, false, stairG1No4Offset, stairG1No4Size, 0, "StairG1No4");
	
	// Stair 5
	const auto stairG1No5Size = Size(40, 106);
	const auto stairG1No5Offset = Vec2(stairG1No4Offset.getX() + stairG1No4Size.getWidth() / 2 + stairG1No5Size.getWidth() / 2, 0 + stairG1No5Size.getHeight() / 2);
	const auto stairG1No5Collider = new Collider(object, false, stairG1No5Offset, stairG1No5Size, 0, "stairG1No5");

	// Stair 6
	const auto stairG1No6Size = Size(40, 115);
	const auto stairG1No6Offset = Vec2(stairG1No5Offset.getX() + stairG1No5Size.getWidth() / 2 + stairG1No6Size.getWidth() / 2, 0 + stairG1No6Size.getHeight() / 2);
	const auto stairG1No6Collider = new Collider(object, false, stairG1No6Offset, stairG1No6Size, 0, "stairG1No6");

	// Stair 7
	const auto stairG1No7Size = Size(99, 9);
	const auto stairG1No7Offset = Vec2(1401 + stairG1No7Size.getWidth()/2, 114 + stairG1No7Size.getHeight()/2);
	const auto stairG1No7Collider = new Collider(object, false, stairG1No7Offset, stairG1No7Size, 0, "StairG1No7");


#pragma endregion

#pragma endregion

#pragma region Rope

	//// 1st rope
	//const auto firstRopeSize = Size(5, 250);
	//const auto firstRopeOffset = Vec2(2091, 90 + firstRopeSize.getHeight()/2);
	//const auto firstRopeCollider = new Collider(object, true, firstRopeOffset, firstRopeSize, 0, "FirstRope");

	//// 2nd rope
	//const auto firstRopeSize = Size(5, 250);
	//const auto firstRopeOffset = Vec2(2091, 90 + firstRopeSize.getHeight() / 2);
	//const auto firstRopeCollider = new Collider(object, true, firstRopeOffset, firstRopeSize, 0, "FirstRope");

#pragma endregion

	// Triggers


	// configurations
	transform->setPosition(Vec2(-halfVisibleSize.getWidth(),
		-halfVisibleSize.getHeight()));

	// Collider Renderer
	const auto firstGroundColliderRenderer = new ColliderRenderer(firstGroundCollider);
	const auto secondGroundColliderRenderer = new ColliderRenderer(secondGroundCollider);
	const auto thirdGroundColliderRenderer = new ColliderRenderer(thirdGroundCollider);
	const auto fourthGroundColliderRenderer = new ColliderRenderer(fourthGroundCollider);

	const auto stairG1No1ColliderRenderer = new ColliderRenderer(stairG1No1Collider);
	const auto stairG1No2ColliderRenderer = new ColliderRenderer(stairG1No2Collider);
	const auto stairG1No3ColliderRenderer = new ColliderRenderer(stairG1No3Collider);
	const auto stairG1No4ColliderRenderer = new ColliderRenderer(stairG1No4Collider);
	const auto stairG1No5ColliderRenderer = new ColliderRenderer(stairG1No5Collider);
	const auto stairG1No6CollciderRenderer = new ColliderRenderer(stairG1No6Collider);
	const auto stairG1No7CollciderRenderer = new ColliderRenderer(stairG1No7Collider);

	const auto mapWallAtStairGroupOneColliderRenderer = new ColliderRenderer(mapWallAtStairGroupOne);


	// const auto firstRopeColliderRenderer = new ColliderRenderer(firstRopeCollider);


}
