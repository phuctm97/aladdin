#include "HandEnemyPrefab.h"
#include "../scripts/HandEnemyController.h" 
#include "../scripts/ThrowVaseController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void HandEnemyPrefab::doInstantiate(ala::GameObject* object) const {
	// constants
	const auto gameManager = GameManager::get();

	const auto density = 1.0f;

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "civilian-enemies.png");
	const auto animator = new Animator(object, "throw", "civilian-enemies.anm");

	// //For animationEditor
	//const auto animationEditor = new AnimationEditor( object, "run_attack" );
	//object->setLayer( "Character" );
	//object->getTransform()->setPosition( -80, -40 );
	//return;
	// //For animationEditor

	const auto timer = new Timer(object);
	//const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_DYNAMIC, 1.0f);
	const auto collider = new Collider(object, false, Vec2(0, 0), Size(40, 50));
	collider->setTag(ENEMY_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	//const auto colliderRenderer = new ColliderRenderer(collider);

	const auto stateManager = new StateManager(object, "hide");
	const auto controller = new HandEnemyController(object);
	const auto controller_Vase = new ThrowVaseController(object);
	const auto transform = object->getTransform();

	// configurations
	object->setTag(ENEMY_TAG);
	object->setLayer( "Background" );

	// states
	new State(stateManager, "throw_vase",
		[=] {
		spriteRenderer->setVisible(true);
		animator->setAction("throw");
		timer->start(0.68f);
	}, [=](float dt) {
		if (timer->isDone()) {
			controller_Vase->throwVase('R', 0.0f, -30.0f, 195.0f, 1000.0f);
			timer->start(10.f);
		}
	}, NULL);

	new State(stateManager, "hide",
		[=] {
		spriteRenderer->setVisible(false);
	}, [=](float dt) {
		
	}, NULL);

	new StateTransition(stateManager, "throw_vase", "hide", [=] {
		return !animator->isPlaying();
	});

	new StateTransition(stateManager, "hide", "throw_vase", [=] {
		return controller->isAladdinNear();
	});
}

