#include "PendalPrefab.h"
#include "../Define.h"
#include "../scripts/PendalController.h"
USING_NAMESPACE_ALA;

void PendalPrefab::doInstantiate(ala::GameObject * object) const
{
	// constants
	const auto body = new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_DYNAMIC, 0.f);

	// components
	const auto collider = new Collider(object, false, Vec2(), Size(37.0f, 9.0f), 1, 0);

	// render
	new ColliderRenderer(collider);
	new PendalController(object);
	
	object->setLayer("Foreground");
	object->setTag(GROUND_TAG);

	// State
	const auto stateManager = new StateManager(object, "idle");

	new State(stateManager, "idle",
		NULL, NULL, 
		[=] {
	});

	new State(stateManager, "drop",
		[=] {
		body->setGravityScale(1.0f);
	}, NULL, NULL);

	new State(stateManager, "disappear",
		[=] {
		object->release();
	}, NULL, NULL);
}

