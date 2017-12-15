#include "SalivaPrefab.h"
#include "../scripts/SalivaController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void SalivaPrefab::doInstantiate(ala::GameObject* object) const {
	// constants
	const auto gameManager = GameManager::get();

	const auto density = 0.5f;
	const auto runVelocity = 150.0f;

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "saliva.png");
	const auto animator = new Animator(object, "fly_straight", "saliva.anm");

	const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_DYNAMIC, 0.0f);
	const auto collider = new Collider(object, true, Vec2(0, 0), Size(24, 15));
	collider->setTag(ENEMY_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	//const auto colliderRenderer = new ColliderRenderer(collider);
	const auto stateManager = new StateManager(object, "fly");
	const auto controller = new SalivaController(object);
	const auto transform = object->getTransform();

	// configurations
	object->setTag(ENEMY_TAG);
	object->setLayer("Background");

	// states
	new State(stateManager, "fly",
		[=] {
		animator->setAction("fly_straight");
	}, [=](float dt) {
		body->setVelocity(Vec2(runVelocity, body->getVelocity().getY()));
	}, NULL);


}

