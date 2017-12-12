#include "NakeGuardPrefab.h"
#include "../scripts/NakeGuardController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void NakeGuardPrefab::doInstantiate(ala::GameObject* object) const {
	// constants
	const auto gameManager = GameManager::get();
	const auto input = Input::get();

	const auto density = 5.0f;
	const auto runVelocity = 100.0f;

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "guards2.png");
	const auto animator = new Animator(object, "nake_guard_stand", "guards2.anm");

	// For animationEditor
	/*const auto animationEditor = new AnimationEditor( object, "nake_guard_stand" );
	return;*/
	// For animationEditor

	const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_DYNAMIC, 1.0f);
	const auto collider = new Collider(object, false, Vec2(0, 0), Size(40, 50));
	collider->setTag(ENEMY_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	const auto colliderRenderer = new ColliderRenderer(collider);
	const auto timer1 = new Timer(object);
	const auto timer2 = new Timer(object);
	const auto timer3 = new Timer(object);
	const auto timer4 = new Timer(object);
	const auto stateManager = new StateManager(object, "nake_guard_stand_left");
	const auto controller = new NakeGuardController(object);
	const auto transform = object->getTransform();
	// states
	new State(stateManager, "nake_guard_stand_left",
		[=] {
		animator->setAction("nake_guard_stand");
		transform->setScaleX(-ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
	}, NULL, NULL);
	new State(stateManager, "nake_guard_stand_right",
		[=] {
		animator->setAction("nake_guard_stand");
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
	}, NULL, NULL);
	new State(stateManager, "nake_guard_attack1_left",
		[=] {
		animator->setAction("nake_guard_stand");
		transform->setScaleX(-ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
		timer1->start(0.1f);
		timer2->start(0.5f);
	}, [=] (float) {
		if (timer1->isDone()) {
			controller->throwKnife('L', 0.0f, 0.0f, -20000.0f, 1000.0f);
			timer1->start(5.0f);
		}
	}, NULL);

	new State(stateManager, "nake_guard_attack1_right",
		[=] {
		animator->setAction("nake_guard_stand");
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
		timer1->start(0.1f);
		timer2->start(0.5f);
	}, [=](float) {
		if (timer1->isDone()) {
			controller->throwKnife('R', collider->getSize().getWidth(), 0.0f, 20000.0f, 1000.0f);
			timer1->start(5.0f);
		}
	}, NULL);
	new State(stateManager, "nake_guard_attack2_left",
		[=] {
		animator->setAction("nake_guard_stand");
		transform->setScaleX(-ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
		timer3->start(0.1f);
		timer4->start(0.5f);
	}, [=](float) {
		if (timer3->isDone()) {
			controller->throwKnife('L', 0.0f, 0.0f, -10000.0f, 14000.0f);
			timer3->start(5.0f);
		}
	}, NULL);
	new State(stateManager, "nake_guard_attack2_right",
		[=] {
		animator->setAction("nake_guard_stand");
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
		timer3->start(0.1f);
		timer4->start(0.5f);
	}, [=](float) {
		if (timer3->isDone()) {
			controller->throwKnife('R', collider->getSize().getWidth(), 0.0f, 10000.0f, 14000.0f);
			timer3->start(5.0f);
		}
	}, NULL);

	//states transition
	new StateTransition(stateManager, "nake_guard_stand_left", "nake_guard_stand_right", [=] {
		return !controller->isOnRightOfAladdin();
	});
	new StateTransition(stateManager, "nake_guard_stand_right", "nake_guard_stand_left", [=] {
		return controller->isOnRightOfAladdin();
	});
	new StateTransition(stateManager, "nake_guard_stand_left", "nake_guard_attack1_left", [=] {
		return controller->coundSeeAladdin() && controller->isOnRightOfAladdin();
	});
	new StateTransition(stateManager, "nake_guard_attack1_left", "nake_guard_attack1_left", [=] {
		if (timer2->isDone())
			return true;
		else return false;
	});
	new StateTransition(stateManager, "nake_guard_stand_right", "nake_guard_attack1_right", [=] {
		return controller->coundSeeAladdin() && !controller->isOnRightOfAladdin();
	});
	new StateTransition(stateManager, "nake_guard_attack1_right", "nake_guard_attack1_right", [=] {
		if (timer2->isDone())
			return true;
		else return false;
	});
	new StateTransition(stateManager, "nake_guard_attack1_left", "nake_guard_attack1_right", [=] {
		if (controller->coundSeeAladdin() && !controller->isOnRightOfAladdin())
			return true;
		else return false;
	});
	new StateTransition(stateManager, "nake_guard_attack1_right", "nake_guard_attack1_left", [=] {
		if (controller->coundSeeAladdin() && controller->isOnRightOfAladdin())
			return true;
		else return false;
	});
	new StateTransition(stateManager, "nake_guard_stand_left", "nake_guard_attack2_left", [=] {
		if (controller->couldThrowToSky() && controller->isOnRightOfAladdin())
			return true;
		else return false;
	});
	new StateTransition(stateManager, "nake_guard_attack2_left", "nake_guard_attack2_left", [=] {
		if (timer4->isDone())
			return true;
		else return false;
	});
	new StateTransition(stateManager, "nake_guard_stand_right", "nake_guard_attack2_right", [=] {
		if (controller->couldThrowToSky() && !controller->isOnRightOfAladdin())
			return true;
		else return false;
	});
	new StateTransition(stateManager, "nake_guard_attack2_right", "nake_guard_attack2_right", [=] {
		if (timer4->isDone())
			return true;
		else return false;
	});
	new StateTransition(stateManager, "nake_guard_attack2_left", "nake_guard_attack1_left", [=] {
		if (controller->coundSeeAladdin() && controller->isOnRightOfAladdin())
			return true;
		else return false;
	});
	new StateTransition(stateManager, "nake_guard_attack2_right", "nake_guard_attack1_right", [=] {
		if (controller->coundSeeAladdin() && !controller->isOnRightOfAladdin())
			return true;
		else return false;
	});
	new StateTransition(stateManager, "nake_guard_attack1_left", "nake_guard_attack2_left", [=] {
		if (controller->couldThrowToSky() && controller->isOnRightOfAladdin())
			return true;
		else return false;
	});
	new StateTransition(stateManager, "nake_guard_attack1_right", "nake_guard_attack2_right", [=] {
		if (controller->couldThrowToSky() && !controller->isOnRightOfAladdin())
			return true;
		else return false;
	});
	new StateTransition(stateManager, "nake_guard_attack2_right", "nake_guard_stand_right", [=] {
		if (!controller->couldThrowToSky() && !controller->isOnRightOfAladdin())
			return true;
		else return false;
	});
	new StateTransition(stateManager, "nake_guard_attack2_left", "nake_guard_stand_left", [=] {
		if (!controller->couldThrowToSky() && controller->isOnRightOfAladdin())
			return true;
		else return false;
	});
}