#include "HorizontalBarPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void HorizontalBarPrefab::doInstantiate(ala::GameObject * gameObject) const
{
	// constants
	new Rigidbody(gameObject, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);
	const auto collider = new Collider(gameObject, true, Vec2(), Size(0,0), 1, 0);

	// Components
	gameObject->setLayer("Foreground");
	gameObject->setTag(HORIZONTALBAR_TAG);

	// Renderer
	new ColliderRenderer(collider);
}
