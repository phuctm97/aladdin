#include "ThrowableKnifePrefab.h"
#include "../scripts/ThrowableKnifeController.h"

USING_NAMESPACE_ALA;

void ThrowableKnifePrefab::doInstantiate(ala::GameObject* object) const
{
	// constants
	const auto gameManager = GameManager::get();
	const auto input = Input::get();

	const auto density = 3.0f;
	const auto throwVelocity = 150.0f;

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "guards.png");
	const auto animator = new Animator(object, "throwable_knife", "guards.anm");

	const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_DYNAMIC, 1.0f);
	const auto collider = new Collider(object, true, Vec2(0, 0), Size(4, 5));
	const auto stateManager = new StateManager(object, "throwable_knife_left");

	const auto controller = new ThrowableKnifeController(object, "controller");
	const auto transform = object->getTransform();

	// configurations
	object->setLayer("Apple");

	// states
	new State(stateManager, "knife_destroy",
		[=] {
		body->setVelocity(Vec2(0, 0));
		body->setGravityScale(0);
	}, [=](float dt) {
			object->release();
	}
	, NULL);

	new State(stateManager, "throwable_knife_left",
		[=] {
		animator->setAction("throwable_knife");
		transform->setScaleX(-ABS(transform->getScale().getX()));
	}, NULL, NULL);

	new State(stateManager, "throwable_knife_right",
		[=] {
		animator->setAction("throwable_knife");
		transform->setScaleX(ABS(transform->getScale().getX()));
	}, NULL, NULL);


	new StateTransition(stateManager, "throwable_knife_left", "knife_destroy", [=] {
		return controller->isCollidedWithGround();
	});

	new StateTransition(stateManager, "throwable_knife_right", "knife_destroy", [=] {
		return controller->isCollidedWithGround();
	});
}

