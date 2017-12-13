#include"GenieLampPrefab.h"
#include"../scripts/GenieLampController.h"
#include"../Define.h"


USING_NAMESPACE_ALA;

void GenieLampPrefab::doInstantiate(ala::GameObject* object) const {



	const auto gameManager = GameManager::get();

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "items.png");
	const auto animator = new Animator(object, "idle_lamp", "items.anm");


	// //For animationEditor
	//const auto animationEditor = new AnimationEditor( object, "abu_bonus" );
	//return;
	// //For animationEditor

	const auto collider = new Collider(object, false, Vec2(0, 0), Size(24, 15));
	collider->setTag(ENEMY_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	const auto timer = new Timer(object);
	//const auto colliderRenderer = new ColliderRenderer(collider);
	const auto stateManager = new StateManager(object, "normal");
	const auto controller = new GenieLampController(object);
	const auto transform = object->getTransform();

	// configurations
	object->setTag(ENEMY_TAG);
	object->setLayer("Background");

	// states
	new State(stateManager, "normal",
		[=] {
		animator->setAction("idle_lamp");
	}, NULL, NULL);

	new State(stateManager, "explosion",
		[=] {
		spriteRenderer->setVisible(false);
		controller->explosionEffect();
		object->release();
	}, NULL, NULL);


	new StateTransition(stateManager, "normal", "explosion", [=] {
		return controller->isCollisionAladdin();
	});
}