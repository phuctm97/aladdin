#include "StaticMapBlockerPrefab.h"
#include "../scripts/StaticMapBlockerController.h"
USING_NAMESPACE_ALA;

void StaticMapBlockerPrefab::doInstantiate(ala::GameObject * object) const
{
	// Constants
	new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);

	// Components
	const auto mapWallAtStairGroupOne = new Collider(object, false,
		Vec2(), Size(11, 81), 1, 0, "MapWallAtStairGroupOne");
	new StaticMapBlockerController(object);

	// Render
	const auto mapWallAtStairGroupOneColliderRenderer = new ColliderRenderer(mapWallAtStairGroupOne);

	object->setLayer("Foreground");
}
