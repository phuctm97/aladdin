#include "Throwable_applePrefab.h"
#include "core/CoreMacros.h"
#include "../scripts/Throwable_appleController.h"

USING_NAMESPACE_ALA;

void Throwable_applePrefab::doInstantiate(ala::GameObject* object) const
{
	// constants
	const auto gameManager = GameManager::get();
	const auto input = Input::get();

	const auto density = 3.0f;
	const auto runVelocity = 150.0f;
	const auto stopAcceleration = 4.0f;

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "throwable_apple.png");
	const auto animator = new Animator(object, "apple_explode", "aladdin.anm");

	const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_DYNAMIC, 1.0f);
	const auto collider = new Collider(object, true, Vec2(0, 0), Size(4, 5));
	new ColliderRenderer(collider);
	const auto timer = new Timer(object);
	const auto stateManager = new StateManager(object, "apple");

	//body->setGravityScale(0);

	const auto controller = new Throwable_appleController(object);
	const auto transform = object->getTransform();

	// configurations
	object->setLayer("Apple");
	//transform->setPosition(-80, -38);

	// states

	new State(stateManager,"apple",
		 [=]{
		animator->setAction("apple");
		controller->resetCollidedWithGround();
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->addImpulse(Vec2(0, 7000.0f));
		body->setVelocity(Vec2(runVelocity, body->getVelocity().getY()));
	}, NULL, NULL);
	new State(stateManager,"apple_explode",
		[=] {
		animator->setAction("apple_explode");	
		}, NULL
		, [=]
		{
			//object->release();
		});

	new StateTransition(stateManager,"apple","apple_explode", [=]{
		return controller->isCollidedWithGround();
	});



}



