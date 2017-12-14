#include "StaticMapBlockerPrefab.h"
#include "../scripts/StaticMapBlockerController.h"
#include "../Define.h"
USING_NAMESPACE_ALA;

void StaticMapBlockerPrefab::doInstantiate(ala::GameObject * object) const
{
	// Constants
	new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);

	// Components
	const auto mapWallAtStairGroupOne = new Collider(object, false,
		Vec2(), Size(0, 0), 1, 0, "MapWallAtStairGroupOne");
	mapWallAtStairGroupOne->ignoreTag(GROUND_TAG);
	new StaticMapBlockerController(object);

	// Render
	const auto mapWallAtStairGroupOneColliderRenderer = new ColliderRenderer(mapWallAtStairGroupOne);

	object->setLayer("Foreground");
}
