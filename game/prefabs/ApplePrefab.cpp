#include "ApplePrefab.h"
#include "../Define.h"
#include "../scripts/AppleController.h"

USING_NAMESPACE_ALA;

void ApplePrefab::doInstantiate(ala::GameObject * object) const
{
	// Constants
	new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);
	const auto collider = new Collider(object, true, Vec2(0, 0), Size(10, 10), 1, 0);

	// Render
	const auto spriteRenderer = new SpriteRenderer(object, "items.png");
	const auto appleAnimator = new Animator(object, "apple", "apple.anm");
	new ColliderRenderer(collider);

	// Controller
	new AppleController(object);

	object->setTag(APPLE_TAG);

	// State
	const auto stateManager = new StateManager(object, "static");

	new State(stateManager, "static",
		[=] {
		appleAnimator->setAction("apple");
	}, NULL, NULL);

	new State(stateManager, "ate",
		[=] {
		collider->setActive(false);
		appleAnimator->setAction("florish");
	},
		[=](float delta) {
		if (!appleAnimator->isPlaying())
			object->release();
	}, NULL);
}
