#include "GroundPrefab.h"
#include "../Define.h"

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
	const auto firstGroundSize = Size(1475 -5, 63);
	const auto firstGroundOffset = Vec2(firstGroundSize.getWidth() / 2 - 5, firstGroundSize.getHeight() / 2);
	const auto firstGroundCollider = new Collider(object, false, firstGroundOffset, firstGroundSize, 1, 0, "FirstGround");


	// Second ground
	const auto secondGroundSize = Size(768, 33);
	const auto secondGroundOffset = Vec2(firstGroundSize.getWidth() + secondGroundSize.getWidth() / 2,
		secondGroundSize.getHeight() / 2);
	const auto secondGroundCollider = new Collider(object, false, secondGroundOffset, secondGroundSize, 1, 0, "SecondGround");


	// Third ground
	const auto thirdGroundSize = Size(578, 22);
	const auto thirdGroundOffset = Vec2(secondGroundOffset.getX() + secondGroundSize.getWidth() / 2 + thirdGroundSize.getWidth() / 2,
		thirdGroundSize.getHeight() / 2);
	const auto thirdGroundCollider = new Collider(object, false, thirdGroundOffset, thirdGroundSize, 1, 0, "ThirdGround");


	// Fourth ground
	const auto fourthGroundSize = Size(1952, 30);
	const auto fourthGroundOffset = Vec2(thirdGroundOffset.getX() + thirdGroundSize.getWidth() / 2 + fourthGroundSize.getWidth() / 2,
		fourthGroundSize.getHeight() / 2);
	const auto fourthGroundCollider = new Collider(object, false, fourthGroundOffset, fourthGroundSize, 1, 0, "FourthGround");

#pragma endregion

#pragma region Map blocker - wall

	const auto mapBlockerSize = Size(20, 688);

	const auto mapStartBlocker = new Collider(object, false,
		Vec2(firstGroundOffset.getX()-firstGroundSize.getWidth() / 2 - mapBlockerSize.getWidth() / 2, firstGroundOffset.getY()-firstGroundSize.getHeight() / 2 + mapBlockerSize.getHeight() / 2),
		mapBlockerSize, 1, 0, "MapStartBlocker");

	const auto mapEndBlocker = new Collider(object, false,
		Vec2(fourthGroundOffset.getX() + fourthGroundSize.getWidth() / 2 + mapBlockerSize.getWidth() / 2, fourthGroundOffset.getY()-fourthGroundSize.getHeight() / 2 + mapBlockerSize.getHeight() / 2),
		mapBlockerSize, 1, 0, "MapEndBlocker");

	const auto mapWallAtStairGroupOne = new Collider(object, false,
		Vec2(1470, 75), Size(11, 81), 1, 0, "MapWallAtStairGroupOne");



#pragma endregion

	// configurations
  object->setTag( GROUND_TAG );
  object->setLayer( "Foregound" );

	transform->setPosition(Vec2(-halfVisibleSize.getWidth(),
		-halfVisibleSize.getHeight()));

	// Collider Renderer
	const auto firstGroundColliderRenderer = new ColliderRenderer(firstGroundCollider);
	const auto secondGroundColliderRenderer = new ColliderRenderer(secondGroundCollider);
	const auto thirdGroundColliderRenderer = new ColliderRenderer(thirdGroundCollider);
	const auto fourthGroundColliderRenderer = new ColliderRenderer(fourthGroundCollider);

	const auto mapWallAtStairGroupOneColliderRenderer = new ColliderRenderer(mapWallAtStairGroupOne);
}
