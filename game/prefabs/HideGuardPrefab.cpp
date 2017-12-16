#include "HideGuardPrefab.h"
#include "../scripts/HideGuardController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void HideGuardPrefab::doInstantiate(ala::GameObject* object) const
{
	// constants
	const auto gameManager = GameManager::get();
	const auto input = Input::get();

	const auto density = 5.0f;
	const auto runVelocity = 100.0f;

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "guards2.png");
	const auto animator = new Animator(object, "hide_guard_stand", "guards2.anm");

	// For animationEditor
	//const auto animationEditor = new AnimationEditor(object, "nake_guard_stand");
	//return;
	// For animationEditor

	const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_DYNAMIC, 1.0f);
	const auto collider = new Collider(object, false, Vec2(0, 0), Size(40, 50));
	collider->setTag(ENEMY_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	const auto colliderRenderer = new ColliderRenderer(collider);
	const auto timer1 = new Timer(object);
	const auto stateManager = new StateManager(object, "hide_guard_stand_left");
	const auto controller = new HideGuardController(object);
	const auto transform = object->getTransform();
	// states

	new State(stateManager, "hide_guard_stand_left",
		[=] {
		animator->setAction("hide_guard_stand");
		transform->setScaleX(-ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0,0));
	}, NULL, NULL);
	new State(stateManager, "hide_guard_stand_right",
		[=] {
		animator->setAction("hide_guard_stand");
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
	}, NULL, NULL);
	new State(stateManager, "hide_guard_run_left",
		[=] {
		animator->setAction("hide_guard_run");
		transform->setScaleX(-ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(-runVelocity, body->getVelocity().getY()));
	}, NULL, NULL);
	new State(stateManager, "hide_guard_run_right",
		[=] {
		animator->setAction("hide_guard_run");
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(runVelocity, body->getVelocity().getY()));
	}, NULL, NULL);
	new State(stateManager, "hide_guard_attack_left",
		[=] {
		animator->setAction("hide_guard_attack");
		transform->setScaleX(-ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0,0));
	}, NULL, NULL);
	new State(stateManager, "hide_guard_attack_right",
		[=] {
		animator->setAction("hide_guard_attack");
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
	}, NULL, NULL);

	//states transition
	new StateTransition(stateManager, "hide_guard_stand_left", "hide_guard_stand_right", [=] {
		return !controller->isOnRightOfAladdin();
	});
	new StateTransition(stateManager, "hide_guard_stand_right", "hide_guard_stand_left", [=] {
		return controller->isOnRightOfAladdin();
	});
	new StateTransition(stateManager,"hide_guard_stand_left","hide_guard_run_left", [=] {
		return controller->coundSeeAladdin() && controller->isOnRightOfAladdin();
	});
	new StateTransition(stateManager, "hide_guard_stand_right", "hide_guard_run_right", [=] {
		return controller->coundSeeAladdin() && !controller->isOnRightOfAladdin();
	});
	new StateTransition(stateManager, "hide_guard_run_left", "hide_guard_attack_left", [=] {
		return controller->couldAttackAladdin() && controller->isOnRightOfAladdin();
	});
	new StateTransition(stateManager, "hide_guard_run_right", "hide_guard_attack_right", [=] {
		return controller->couldAttackAladdin() && !controller->isOnRightOfAladdin();
	});
	new StateTransition(stateManager, "hide_guard_attack_left", "hide_guard_attack_right", [=] {
		return controller->couldAttackAladdin() && !controller->isOnRightOfAladdin();
	});
	new StateTransition(stateManager, "hide_guard_attack_right", "hide_guard_attack_left", [=] {
		return controller->couldAttackAladdin() && controller->isOnRightOfAladdin();
	});
	new StateTransition(stateManager, "hide_guard_attack_left", "hide_guard_run_left", [=] {
		return !controller->couldAttackAladdin() && controller->isOnRightOfAladdin();
	});
	new StateTransition(stateManager, "hide_guard_attack_right", "hide_guard_run_right", [=] {
		return !controller->couldAttackAladdin() && !controller->isOnRightOfAladdin();
	});

}
