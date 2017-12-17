#include "PlatformPrefab.h"
#include "../Define.h"
#include "../scripts/PlatformController.h"
USING_NAMESPACE_ALA;

void PlatformPrefab::doInstantiate(ala::GameObject * object) const
{

	// Constants
	new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);

	// Components
	const auto upon = new Collider(object, false, Vec2(), Size(0, 0), 1, 0, "Upon");
	const auto below = new Collider(object, true, Vec2(), Size(0, 0), 1, 0, "Below");

	new PlatformController(object);

	// Render
	new ColliderRenderer(upon);
	new ColliderRenderer(below);

	upon->ignoreTag(PLATFORM_TAG);
	below->ignoreTag(PLATFORM_TAG);

	object->setLayer("Foreground");
	object->setTag(GROUND_TAG);
}


