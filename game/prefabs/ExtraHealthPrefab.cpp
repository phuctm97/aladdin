#include"ExtraHealthPrefab.h"
#include"../scripts/ExtraHealthController.h"
#include"../Define.h"


USING_NAMESPACE_ALA;

void ExtraHealthPrefab::doInstantiate(ala::GameObject* object) const {



	const auto gameManager = GameManager::get();

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "items.png");
	const auto animator = new Animator(object, "extra_health", "items.anm");

	// //For animationEditor
	//const auto animationEditor = new AnimationEditor( object, "spring" );
	//return;
	// //For animationEditor

	const auto collider = new Collider(object, false, Vec2(0, 0), Size(24, 15));
	collider->setTag(ENEMY_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	const auto timer = new Timer(object);
	//const auto colliderRenderer = new ColliderRenderer(collider);
	const auto stateManager = new StateManager(object, "normal");
	const auto controller = new ExtraHealthController(object);
	const auto transform = object->getTransform();

	// configurations
	object->setTag(ENEMY_TAG);
	object->setLayer("Charactor");

	// states
	new State(stateManager, "normal",
		[=] {
		animator->setAction("extra_health");
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