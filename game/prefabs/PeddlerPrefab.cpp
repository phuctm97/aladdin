#include "PeddlerPrefab.h"
#include "../scripts/PeddlerController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void PeddlerPrefab::doInstantiate(ala::GameObject* object) const {
	// constants
	const auto gameManager = GameManager::get();


	// components
	const auto spriteRenderer = new SpriteRenderer(object, "peddler.png");
	const auto animator = new Animator(object, "idle", "peddler.anm");

	// //For animationEditor
	//const auto animationEditor = new AnimationEditor( object, "pavilion" );
	//return;
	// //For animationEditor

	//const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_DYNAMIC, 1.5f);
	const auto collider = new Collider(object, false, Vec2(0, 0), Size(24, 15));
	collider->setTag(ENEMY_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	//const auto colliderRenderer = new ColliderRenderer(collider);
	const auto stateManager = new StateManager(object, "standstill");
	const auto controller = new PeddlerController(object);
	const auto transform = object->getTransform();

	const auto child = new GameObject(object);
	const auto spriteRenderer_Child = new SpriteRenderer(child, "peddler.png");
	const auto animator_Child = new Animator(child, "idle", "peddler.anm");
	const auto stateManager_Child = new StateManager(child, "standstill_child");
	const auto transform_Child = child->getTransform();

	transform_Child->setPosition(Vec2(50, transform_Child->getPositionY()));
	spriteRenderer_Child->setVisible(false);

	// configurations
	object->setTag(ENEMY_TAG);
	object->setLayer("Charactor");

	// states
	new State(stateManager, "standstill",
		[=] {
		animator->setAction("idle");
	}, NULL, NULL);

	new State(stateManager, "show_pavilion",
		[=] {
		animator->setAction("pavilion_1");
		controller->ShowedPavilion();
	}, [=](float dt) {
		if (!animator->isPlaying() && animator->getActionName() == "pavilion_1") {
			spriteRenderer_Child->setVisible(true);
			animator->setAction("pavilion_2");
		}
	}, NULL);

	new State(stateManager_Child, "standstill_child",
		[=] {
		animator_Child->setAction("idle");
	}, NULL, NULL);

	new State(stateManager_Child, "show_jewelry",
		[=] {
		animator_Child->setAction("jewelry");
	}, NULL, NULL);

	

	new StateTransition(stateManager_Child, "standstill_child", "show_jewelry", [=] {
		return !animator_Child->isPlaying() && controller->isShowedPavilion();
	});

	new StateTransition(stateManager_Child, "show_jewelry", "standstill_child", [=] {
		return !animator_Child->isPlaying();
	});

	new StateTransition(stateManager, "standstill", "show_pavilion", [=] {
		return !animator->isPlaying() && !controller->isShowedPavilion();
	});
	/*new StateTransition(stateManager, "show_pavilion", "standstill", [=] {
		return !animator->isPlaying();
	});*/


}

