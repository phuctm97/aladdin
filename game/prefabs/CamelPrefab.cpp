#include "CamelPrefab.h"
#include "../scripts/CamelController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void CamelPrefab::doInstantiate(ala::GameObject* object) const {
	// constants
	const auto gameManager = GameManager::get();

	const auto density = 0.5f;

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "camel.png");
	const auto animator = new Animator(object, "idle", "camel.anm");

	// //For animationEditor
	//const auto animationEditor = new AnimationEditor( object, "idle" );
	//return;
	// //For animationEditor

	const auto timer = new Timer(object);
	//const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_DYNAMIC, 1.5f);
	const auto collider = new Collider(object, false, Vec2(0, 0), Size(24, 15));
	collider->setTag(ANIMAL_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	//const auto colliderRenderer = new ColliderRenderer(collider);
	const auto stateManager = new StateManager(object, "camel_idle");
	const auto controller = new CamelController(object);
	const auto transform = object->getTransform();

	// configurations
	object->setTag(ANIMAL_TAG);
	object->setLayer("Background");

	// states
	new State(stateManager, "camel_idle",
		[=] {
		animator->setAction("idle");
	}, NULL, NULL);

	new State(stateManager, "camel_puff",
		[=] {
		animator->setAction("puff");
		timer->start(0.3);
	}, [=](float dt) {
		if (timer->isDone()) {
			controller->puffSaliva(90.0f, -10.0f, 195.0f, 1000.0f);
			timer->start(10.f);
		}
	}, NULL);

	new StateTransition(stateManager, "camel_idle", "camel_puff", [=] {
		return controller->isAladdinOnBack();
	});
	new StateTransition(stateManager, "camel_puff", "camel_idle", [=] {
		return !animator->isPlaying();
	});


}

