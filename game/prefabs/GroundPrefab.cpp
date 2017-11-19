#include "GroundPrefab.h"

USING_NAMESPACE_ALA;

void GroundPrefab::doInstantiate(ala::GameObject* object) const {
	// constants
	const auto gameManager = GameManager::get();
	const auto halfVisibleSize = Size(gameManager->getVisibleWidth() / 2, gameManager->getVisibleHeight() / 2);
	const auto body = new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);
	const auto transform = object->getTransform();

	// components


	// First ground
	const auto firstGroundSize = Size(1475, 63);
	const auto firstGroundCollider = new Collider(object, false, Vec2(0, 0), firstGroundSize, 0, "firstGround");


	// Second ground
	const auto secondGroundSize = Size(768, 33);
	const auto secondGroundOffset = Vec2(firstGroundSize.getWidth() / 2 + secondGroundSize.getWidth() / 2,
		-secondGroundSize.getHeight() / 2);
	const auto secondGroundCollider = new Collider(object, false, secondGroundOffset, secondGroundSize, 0, "secondGround");


	// Third ground
	const auto thirdGroundSize = Size(578, 22);
	const auto thirdGroundOffset = Vec2(secondGroundOffset.getX() + secondGroundSize.getWidth() / 2 + thirdGroundSize.getWidth() / 2,
		-firstGroundSize.getHeight() / 2 + thirdGroundSize.getHeight() / 2);
	const auto thirdGroundCollider = new Collider(object, false, thirdGroundOffset, thirdGroundSize, 0, "thirdGround");


	// Fourth ground
	const auto fourthGroundSize = Size(1952, 30);
	const auto fourthGroundOffset = Vec2(thirdGroundOffset.getX() + thirdGroundSize.getWidth() / 2 + fourthGroundSize.getWidth() / 2,
		-firstGroundSize.getHeight() / 2 + fourthGroundSize.getHeight() / 2);
	const auto fourthGroundCollider = new Collider(object, false, fourthGroundOffset, fourthGroundSize, 0, "fourthGround");

	// configurations
	transform->setPosition(Vec2(-halfVisibleSize.getWidth() + firstGroundSize.getWidth() / 2,
		-halfVisibleSize.getHeight() + firstGroundSize.getHeight() / 2));


	// Map blocker - wall
	const auto mapBlockerSize = Size(20, 688);

	const auto mapStartBlocker = new Collider(object, false,
		Vec2(-firstGroundSize.getWidth() / 2 - mapBlockerSize.getWidth() / 2, -firstGroundSize.getHeight() / 2 + mapBlockerSize.getHeight() / 2),
		mapBlockerSize, 0, "mapStartBlocker");

	const auto mapEndBlocker = new Collider(object, false,
		Vec2(fourthGroundOffset.getX() + fourthGroundSize.getWidth() / 2 + mapBlockerSize.getWidth() / 2, -firstGroundSize.getHeight() / 2 + mapBlockerSize.getHeight() / 2),
		mapBlockerSize, 0, "mapEndBlocker");

	// Collider Renderer
	const auto firstGroundColliderRenderer = new ColliderRenderer(firstGroundCollider);
	const auto secondGroundColliderRenderer = new ColliderRenderer(secondGroundCollider);
	const auto thirdGroundColliderRenderer = new ColliderRenderer(thirdGroundCollider);
	const auto fourthGroundColliderRenderer = new ColliderRenderer(fourthGroundCollider);

}
