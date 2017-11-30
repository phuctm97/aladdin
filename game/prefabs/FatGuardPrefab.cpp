#include "FatGuardPrefab.h"
#include "../scripts/FatGuardController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void FatGuardPrefab::doInstantiate(ala::GameObject* object) const
{
	// constants
	const auto gameManager = GameManager::get();
	const auto input = Input::get();

	const auto density = 5.0f;
	const auto runVelocity = 100.0f;

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "guards.png");
	const auto animator = new Animator(object, "fat_guard_provocative", "guards.anm");

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
	const auto stateManager = new StateManager(object, "fat_guard_provocative_left");
	const auto controller = new FatGuardController(object);
	const auto transform = object->getTransform();
	const auto aladdin = GameManager::get()->getObjectByName("Aladdin");

	new State(stateManager, "fat_guard_provocative_left",
		[=] {
		animator->setAction("fat_guard_provocative");
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0,0));
	}, NULL, NULL);

	new State(stateManager, "fat_guard_provocative_right",
		[=] {
		animator->setAction("fat_guard_provocative");
		transform->setScaleX(-ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
	}, NULL, NULL);

	new State(stateManager, "fat_guard_run_left",
		[=] {
		animator->setAction("fat_guard_run");
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(-runVelocity, body->getVelocity().getY()));
	}, NULL, NULL);
	new State(stateManager, "fat_guard_run_right",
		[=] {
		animator->setAction("fat_guard_run");
		transform->setScaleX(-ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(runVelocity, body->getVelocity().getY()));
	}, NULL, NULL);

	new State(stateManager, "fat_guard_attack_left",
		[=]{
		animator->setAction("fat_guard_attack2");
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
		timer1->start(0.8);
	}, [=](float dt)
	{
		if(timer1->isDone() && animator->isPlaying())
		{
			auto var = rand() % 7;
			if(var == 2)
			{
				animator->setAction("fat_guard_attack1");
				timer1->start(0.8);
			}
			else
			{
				animator->setAction("fat_guard_attack2");
				timer1->start(0.8);
			}
		}
	}, NULL);

	new State(stateManager, "fat_guard_attack_right",
		[=] {
		animator->setAction("fat_guard_attack2");
		transform->setScaleX(-ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
		timer1->start(0.8);
	}, [=](float dt)
	{
		if (timer1->isDone() && animator->isPlaying())
		{
			auto var = rand() % 7;
			if (var == 2)
			{
				animator->setAction("fat_guard_attack1");
				timer1->start(0.8);
			}
			else
			{
				animator->setAction("fat_guard_attack2");
				timer1->start(0.8);
			}
		}
	}, NULL);

	new StateTransition(stateManager, "fat_guard_provocative_left", "fat_guard_provocative_right", [=] {
		return !controller->isInTheLeftAladdin();
	});
	new StateTransition(stateManager, "fat_guard_provocative_right", "fat_guard_provocative_left", [=] {
		return controller->isInTheLeftAladdin();
	});
	new StateTransition(stateManager, "fat_guard_provocative_left", "fat_guard_run_left", [=] {
		return controller->isSeeingWithAladdin();
	});
	new StateTransition(stateManager, "fat_guard_provocative_right", "fat_guard_run_right", [=] {
		return controller->isSeeingWithAladdin();
	});
	new StateTransition(stateManager, "fat_guard_run_left", "fat_guard_attack_left", [=] {
		return controller->isCollidedWithAladdin();
	});
	new StateTransition(stateManager, "fat_guard_run_right", "fat_guard_attack_right", [=] {
		return controller->isCollidedWithAladdin();
	});
	new StateTransition(stateManager, "fat_guard_attack_right", "fat_guard_run_right", [=]{
		if (controller->isCollidedWithAladdin() == false && controller->isInTheLeftAladdin() == false)
			return true;
		else return false;
	});
	new StateTransition(stateManager, "fat_guard_attack_right", "fat_guard_run_left", [=] {
		if (controller->isCollidedWithAladdin() == false && controller->isInTheLeftAladdin() == true)
			return true;
		else return false;
	});
	new StateTransition(stateManager, "fat_guard_attack_left", "fat_guard_run_left", [=] {
		if (controller->isCollidedWithAladdin() == false && controller->isInTheLeftAladdin() == true)
			return true;
		else return false;
	});
	new StateTransition(stateManager, "fat_guard_attack_left", "fat_guard_run_right", [=] {
		if (controller->isCollidedWithAladdin() == false && controller->isInTheLeftAladdin() == false)
			return true;
		else return false;
	});
	
}

