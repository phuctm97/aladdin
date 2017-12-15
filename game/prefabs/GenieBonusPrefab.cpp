#include"GenieBonusPrefab.h"
#include"../scripts/GenieBonusController.h"
#include"../Define.h"


USING_NAMESPACE_ALA;

void GenieBonusPrefab::doInstantiate(ala::GameObject* object) const {



	const auto gameManager = GameManager::get();

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "items.png");
	const auto animator = new Animator(object, "idle_genie", "items.anm");


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
	const auto controller = new GenieBonusController(object);
	const auto transform = object->getTransform();

	// configurations
	object->setTag(ENEMY_TAG);
	object->setLayer("Character");

	// states
	new State(stateManager, "normal",
		[=] {
		animator->setAction("idle_genie");
	}, [=](float dt) {
		if (!animator->isPlaying() && timer->isDone()) {
			const auto way = rand() % 4;
			if (way == 0 && !animator->isPlaying()) {
				animator->setAction("wink");
			}
			else {
				animator->setAction("idle_genie");
				timer->start(1.0f * (200 + rand() % 900) / 1000);
			}
		}
		/*auto positionY = transform->getPositionY();
		if (controller->getOrient()) {
			transform->setPosition(transform->getPositionX(), positionY + 0.5);
			if(transform->getPositionY() >= -8)
			controller->setOrient(false);
		}
		else {
			transform->setPosition(transform->getPositionX(), positionY - 0.5);
			if (transform->getPositionY() <= -15)
				controller->setOrient(true);
		}*/
		
		
	}, NULL);

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