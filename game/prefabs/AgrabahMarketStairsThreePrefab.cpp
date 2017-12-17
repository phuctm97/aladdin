#include "AgrabahMarketStairsThreePrefab.h"
#include "../Define.h"
#include "../scripts/StairsModeSwitcher.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AgrabahMarketStairsThreePrefab, ala::PrefabV2)

void AgrabahMarketStairsThreePrefab::doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const {
	// args
	const auto initialOn = nextBool(argsStream);

	// constants
	vector<Vec2> position{
	  Vec2(2152.5f - 2152.5f, -4.0f),
	  Vec2(2190.5f - 2152.5f, 3.5f),
	  Vec2(2221.5f - 2152.5f, 11.5f),
	  Vec2(2254.5f - 2152.5f, 19.0f),
	  Vec2(2286.5f - 2152.5f, 27.0f),
	  Vec2(2326.5f - 2152.5f, 35.0f),
	  Vec2(2382.5f - 2152.5f, 43.0f),
	  Vec2(2494.5f - 2152.5f, 51.0f)
	};

	vector<Size> size{
	  Size(39.0f, 5.0f),
	  Size(39.0f, 5.0f),
	  Size(39.0f, 5.0f),
	  Size(39.0f, 5.0f),
	  Size(39.0f, 5.0f),
	  Size(55.0f, 5.0f),
	  Size(55.0f, 5.0f),
	  Size(182.0f, 5.0f)
	};

	// components
	const auto body = new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);

	std::vector<Collider*> stairColliders;
	for (size_t i = 0; i < position.size(); i++) {
		const auto collider = new Collider(object, false, position[i], size[i], 1, 0, "M");

		stairColliders.push_back(collider);
	}

	const auto switchCollider = new Collider(object, true, Vec2(2090.0f - 2152.5f, 33.0f), Size(11.0f, 73.0f), 1, 0, "S");

	const auto stateManager = new StateManager(object, initialOn ? "on" : "off");

	const auto switcher = new StairsModeSwitcher(object, 'R');

	// collider renderers
	for (auto collider : stairColliders) new ColliderRenderer(collider);
	new ColliderRenderer(switchCollider);

	// configurations
	object->setTag(GROUND_TAG);
	object->setLayer("Debug");


	// states
	new State(stateManager, "off",
		[=] {
		for (const auto collider : stairColliders) collider->setActive(false);
	}, NULL, NULL);

	new State(stateManager, "on",
		[=] {
		for (const auto collider : stairColliders) collider->setActive(true);
	}, NULL, NULL);
}
