#include "PeddlerPrefab.h"
//#include "../scripts/SpringController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void PeddlerPrefab::doInstantiate(ala::GameObject* object) const {
	// constants
	const auto gameManager = GameManager::get();


	// components
	const auto spriteRenderer = new SpriteRenderer(object, "peddler.png");
	const auto animator = new Animator(object, "idle", "peddler.anm");

	// //For animationEditor
	//const auto animationEditor = new AnimationEditor( object, "spring" );
	//return;
	// //For animationEditor

	const auto collider = new Collider(object, false, Vec2(0, 0), Size(24, 15));
	collider->setTag(ANIMAL_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	//const auto colliderRenderer = new ColliderRenderer(collider);
	const auto stateManager = new StateManager(object, "standstill");
	//const auto controller = new SpringController(object);
	const auto transform = object->getTransform();

	// configurations
	object->setTag(ANIMAL_TAG);
	object->setLayer("Background");

	// states
	new State(stateManager, "standstill",
		[=] {
		animator->setAction("idle");
	}, NULL, NULL);

	new State(stateManager, "elastic",
		[=] {
		animator->setAction("spring");
	}, NULL, NULL);

	new StateTransition(stateManager, "standstill", "elastic", [=] {
		return false;
	});
	new StateTransition(stateManager, "elastic", "standstill", [=] {
		return !animator->isPlaying();
	});


}

