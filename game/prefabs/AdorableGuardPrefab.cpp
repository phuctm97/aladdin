#include "AdorableGuardPrefab.h"
#include "../scripts/AdorableGuardController.h"
#include "../Define.h"

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
	//const auto animationEditor = new AnimationEditor( object, "adorable_guard_run" );
	//object->getTransform()->setPosition( 80, -40 );
	//return;
	// For animationEditor

	const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_DYNAMIC, 1.0f);
	const auto collider = new Collider(object, false, Vec2(0, 0), Size(40, 50));
	collider->setTag(ENEMY_TAG);

	const auto colliderRenderer = new ColliderRenderer(collider);
	const auto timer1 = new Timer(object);
	const auto timer2 = new Timer(object);
	const auto stateManager = new StateManager(object, "adorable_guard_throw_right");
	const auto controller = new AdorableGuardController(object);
	const auto transform = object->getTransform();

	new State(stateManager, "adorable_guard_throw_left",
		[=] {
		animator->setAction("adorable_guard_throw");
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
		timer1->start(0.1f);
		timer2->start(0.5f);
	}, [=](float) {
		if (timer1->isDone()) {
			controller->throwKnife('L', 0.0f, 0.0f, -20000.0f, 1000.0f);
			timer1->start(5.0f);
		}
	}, NULL);

	new State(stateManager, "adorable_guard_throw_right",
		[=] {
		animator->setAction("adorable_guard_throw");
		transform->setScaleX(-ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
		timer1->start(0.1f);
		timer2->start(0.5f);
	}, [=](float) {
		if (timer1->isDone()) {
			controller->throwKnife('R', collider->getSize().getWidth(), 0.0f, 20000.0f, 1000.0f);
			timer1->start(5.0f);
		}
	}, NULL);

	new State(stateManager, "adorable_guard_run_left",
		[=] {
			animator->setAction("adorable_guard_run");
			transform->setScaleX(ABS(transform->getScale().getX()));
			body->setVelocity(Vec2(-runVelocity, body->getVelocity().getY()));
	}, NULL, NULL);
	new State(stateManager, "adorable_guard_run_right",
		[=] {
			animator->setAction("adorable_guard_run");
			transform->setScaleX(-ABS(transform->getScale().getX()));
			body->setVelocity(Vec2(runVelocity, body->getVelocity().getY()));
	}, NULL, NULL);
	
	new StateTransition(stateManager, "adorable_guard_throw_left", "adorable_guard_throw_right", [=] {
		if (!controller->isInTheLeftAladdin() && controller->isSeeingWithAladdin())
		{
			return true;
		}
		else return false;
	});
	new StateTransition(stateManager, "adorable_guard_throw_right", "adorable_guard_throw_left", [=] {
		if (controller->isInTheLeftAladdin() && controller->isSeeingWithAladdin())
		{
			return true;
		}
		else return false;
	});
	new StateTransition(stateManager, "adorable_guard_throw_right", "adorable_guard_run_right", [=] {
		if(!controller->isInTheLeftAladdin() && controller->isRunFromEnemy() && !animator->isPlaying())
		{
			return true;
		}
		return false;
	});
	new StateTransition(stateManager, "adorable_guard_throw_left", "adorable_guard_run_left", [=] {
		if (controller->isInTheLeftAladdin() && controller->isRunFromEnemy() && !animator->isPlaying())
		{
			return true;
		}
		return false;
	});
	new StateTransition(stateManager, "adorable_guard_run_left", "adorable_guard_throw_left", [=] {
		if (controller->isInTheLeftAladdin() && controller->isSeeingWithAladdin() )
		{
			return true;
		}
		else return false;
	});
	new StateTransition(stateManager, "adorable_guard_run_right", "adorable_guard_throw_right", [=] {
		if (!controller->isInTheLeftAladdin() && controller->isSeeingWithAladdin())
		{
			return true;
		}
		else return false;
	});
	new StateTransition(stateManager, "adorable_guard_throw_left", "adorable_guard_throw_left", [=] {
		if(timer2->isDone())
		{
			return true;
		}
		else return false;
	});
	new StateTransition(stateManager, "adorable_guard_throw_right", "adorable_guard_throw_right", [=] {
		if (timer2->isDone())
		{
			return true;
		}
		else return false;
	});
}

