#include "StandablePlatformPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(StandablePlatformPrefab, ala::PrefabV2)

void StandablePlatformPrefab::doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const {
	// args
	const auto width = nextFloat(argsStream);
	const auto height = nextFloat(argsStream);
	// components
	new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);
	const auto collider = new Collider(object, false, Vec2(), Size(width, height), 1, 0);

	// render
	new ColliderRenderer(collider);

	// flags
	collider->setFlags(STANDABLE_FLAG | COLLIDE_ALADDIN_FLAG);

	// configurations
	object->setTag(GROUND_TAG);
	object->setLayer("Debug");
}
