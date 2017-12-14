#include "StairGroupTwoPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void StairGroupTwoPrefab::doInstantiate(ala::GameObject * object) const
{
	//Constants
	const auto body = new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);
	
	//Components
	const auto collider = new Collider(object, false, Vec2(), Size(0,0), 1, 0, "first");

	//Renderer
	new ColliderRenderer(collider);

	object->setTag(GROUND_TAG);
	object->setLayer("Foreground");
}

