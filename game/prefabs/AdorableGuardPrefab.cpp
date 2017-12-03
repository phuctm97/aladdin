#include "AdorableGuardPrefab.h"
#include "../scripts/FatGuardController.h"
#include "../Define.h"
#include "../scripts/AdorableGuardController.h"

USING_NAMESPACE_ALA;

void AdorableGuardPrefab::doInstantiate(ala::GameObject* object) const
{
	// constants
	const auto gameManager = GameManager::get();
	const auto input = Input::get();

	const auto density = 5.0f;
	const auto runVelocity = 100.0f;

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "guards.png");
	const auto animator = new Animator(object, "adorable_guard_throw", "guards.anm");

	// For animationEditor
	//const auto animationEditor = new AnimationEditor( object, "fat_guard_attack2" );
	//object->getTransform()->setPosition( 80, -40 );
	//return;
	// For animationEditor

	const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_DYNAMIC, 1.0f);
	const auto collider = new Collider(object, false, Vec2(0, 0), Size(40, 50));
	collider->setTag(ENEMY_TAG);

	const auto colliderRenderer = new ColliderRenderer(collider);
	const auto timer1 = new Timer(object);
	const auto stateManager = new StateManager(object, "adorable_guard_throw_left");
	const auto controller = new AdorableGuardController(object);
	const auto transform = object->getTransform();

	new State(stateManager, "adorable_guard_throw_left",
		[=] {
		animator->setAction("adorable_guard_throw");
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
		timer1->start(0.1f);
	}, [=](float) {
		if (timer1->isDone()) {
			controller->throwKnife('L', 0.0f, 0.0f, -20000.0f, 1000.0f);
			timer1->start(5.0f);
		}
	}, NULL);
}

