#include "ThrowVasePrefab.h"
#include "../scripts/ThrowVaseController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void ThrowVasePrefab::doInstantiate(ala::GameObject* object) const {
	// constants
	const auto gameManager = GameManager::get();

	const auto density = 0.5f;
	const auto runVelocity = 21.0f;

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "civilian-enemies.png");
	const auto animator = new Animator(object, "vase_fall", "civilian-enemies.anm");

	const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_DYNAMIC, 1.5f);
	const auto collider = new Collider(object, false, Vec2(0, 0), Size(24, 15));
	collider->setTag(ENEMY_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	//const auto colliderRenderer = new ColliderRenderer(collider);
	const auto stateManager = new StateManager(object, "fall");
	const auto controller = new ThrowVaseController(object);
	const auto transform = object->getTransform();

	// configurations
	object->setTag(ENEMY_TAG);
	object->setLayer("Background");

	// states
	new State(stateManager, "fall",
		[=] {
		animator->setAction("vase_fall");
	}, [=](float dt) {
		body->setVelocity(Vec2(runVelocity, body->getVelocity().getY()));
	}, NULL);

	new State(stateManager, "break",
		[=] {
		animator->setAction("vase_break");
		body->setVelocity(Vec2(0, 0));
	}, [=](float dt) {
		if (!animator->isPlaying()) {
			object->release();
		}
	}, NULL);

	new StateTransition(stateManager, "fall", "break", [=] {
		return controller->isCollidedWithGround();
	});

}

