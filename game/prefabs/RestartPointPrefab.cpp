#include"RestartPointPrefab.h"
#include"../scripts/RestartPointController.h"
#include"../Define.h"


USING_NAMESPACE_ALA;

void RestartPointPrefab::doInstantiate(ala::GameObject* object) const {
	const auto gameManager = GameManager::get();

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "items.png");
	const auto animator = new Animator(object, "idle_0", "items.anm");

	// //For animationEditor
	//const auto animationEditor = new AnimationEditor( object, "spring" );
	//return;
	// //For animationEditor

	const auto collider = new Collider(object, false, Vec2(0, 0), Size(24, 15));
	collider->setTag(ENEMY_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	const auto timer = new Timer(object);
	const auto stateManager = new StateManager(object, "standstill");
	const auto controller = new RestartPointController(object);
	const auto transform = object->getTransform();

	// configurations
	object->setTag(ENEMY_TAG);
	object->setLayer("Background");

	// states
	new State(stateManager, "stand",
		[=] {
		animator->setAction("idle_1");
	}, NULL, NULL);

	new State(stateManager, "standstill",
		[=] {
		animator->setAction("idle_0");
	}, NULL, NULL);

	new State(stateManager, "jump_up",
		[=] {
		animator->setAction("jump");
		transform->setPosition(transform->getPositionX(), transform->getPositionY() + 20);
	}, NULL, NULL);

	new State(stateManager, "smile",
		[=] {
		animator->setAction("idle_2");
		transform->setPosition(transform->getPositionX(), transform->getPositionY() - 20);
	}, NULL, NULL);

	new StateTransition(stateManager, "stand", "jump_up", [=] {
		return !animator->isPlaying();
	});

	new StateTransition(stateManager, "standstill", "stand", [=] {
		return controller->isNearAladdin();
	});

	new StateTransition(stateManager, "jump_up", "smile", [=] {
		return !animator->isPlaying();
	});

	/*new StateTransition(stateManager, "smile", "stand", [=] {
		return !animator->isPlaying();
	});*/

}