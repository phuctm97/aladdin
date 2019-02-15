#include "AgrabahMarketStairsTwoPrefab.h"
#include "../Define.h"
#include "../scripts/StairsModeSwitcher.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AgrabahMarketStairsTwoPrefab, ala::PrefabV2)

void AgrabahMarketStairsTwoPrefab::doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const {
	// args
	const auto initialOn = nextBool(argsStream);

	// constants
	vector<Vec2> position{
	  Vec2(2445.0f - 2445.0f, -87.5f + 87.5f),
	  Vec2(2411.5f - 2445.0f, -79.5f + 87.5f),
	  Vec2(2387.5f - 2445.0f, -71.0f + 87.5f),
	  Vec2(2356.0f - 2445.0f, -63.0f + 87.5f),
	  Vec2(2323.5f - 2445.0f, -55.0f + 87.5f),
	  Vec2(2291.5f - 2445.0f, -47.0f + 87.5f),
	  Vec2(2252.5f - 2445.0f, -39.0f + 87.5f),
	  Vec2(2212.0f - 2445.0f, -31.5f + 87.5f),
	  Vec2(2179.5f - 2445.0f, -23.5f + 87.5f),
	  Vec2(2148.0f - 2445.0f, -15.0f + 87.5f),
	  Vec2(2108.0f - 2445.0f, -7.0f + 87.5f),
	};

	vector<Size> size{
	  Size(34.0f, 7.0f),
	  Size(34.0f, 7.0f),
	  Size(34.0f, 7.0f),
	  Size(34.0f, 7.0f),
	  Size(34.0f, 7.0f),
	  Size(34.0f, 7.0f),
	  Size(47.0f, 7.0f),
	  Size(33.0f, 7.0f),
	  Size(33.0f, 7.0f),
	  Size(33.0f, 7.0f),
	  Size(47.0f, 7.0f)
	};

	// components
	const auto body = new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);

	std::vector<Collider*> stairColliders;
	for (size_t i = 0; i < position.size(); i++) {
		const auto collider = new Collider(object, false, position[i], size[i], 1, 0, "M");

		stairColliders.push_back(collider);
	}

	const auto switchCollider = new Collider(object, true, Vec2(2513.0f - 2445.0f, -33.0f + 87.5), Size(15.0f, 118.0f), 1, 0, "S");

	const auto stateManager = new StateManager(object, initialOn ? "on" : "off");

	const auto switcher = new StairsModeSwitcher(object, 'L');

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
