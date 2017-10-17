#include "AladdinPrefab.h"

void AladdinPrefab::doInstantiate( ala::GameObject* object ) {
	object->getTransform()->setPosition(ala::GameManager::get()->getScreenWidth() / 2, ala::GameManager::get()->getScreenHeight() / 2);

	new ala::SpriteRenderer(object, "aladdin.png");
	new ala::Animator(object, "idle1", "aladdin.animation");
	auto stateManager = new ala::StateManager(object, "stand_right");
	auto animator = object->getComponentT<ala::Animator>();

	// State Stand
	new ala::State(stateManager, "stand_right",
		[=] {
		animator->setAction("idle1");
	}, NULL, NULL);
	new ala::State(stateManager, "stand_left",
		[=] {
		animator->setAction("idle1");
	}, NULL, NULL);

	// State Go
	new ala::State(stateManager, "go_right",
		[=] {
		animator->setAction("run_1");
		object->getTransform()->setScaleX(1);
	},
		[=](float dt) {
		if (animator->getAction() == "run_1" && !animator->isPlaying())
			animator->setAction("run_2");
		auto position = object->getTransform()->getPosition();
		position.setX(position.getX() + 100 * dt);
		object->getTransform()->setPosition(position);
	}, NULL);
	new ala::State(stateManager, "go_left",
		[=] {
		animator->setAction("run_1");
		object->getTransform()->setScaleX(-1);
	},
		[=](float dt) {
		if (animator->getAction() == "run_1" && !animator->isPlaying())
			animator->setAction("run_2");
		auto position = object->getTransform()->getPosition();
		position.setX(position.getX() - 100 * dt);
		object->getTransform()->setPosition(position);
	}, NULL);

	// State Sit
	new ala::State(stateManager, "sit_left",
		[=] {
		animator->setAction("sit");
	}, NULL, NULL);
	new ala::State(stateManager, "sit_right",
		[=] {
		animator->setAction("sit");
	}, NULL, NULL);

	new ala::StateTransition(stateManager, "stand_right", "go_right",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_RIGHT_ARROW);
	});
	new ala::StateTransition(stateManager, "stand_right", "go_left",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_LEFT_ARROW);
	});
	new ala::StateTransition(stateManager, "go_right", "go_left",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_LEFT_ARROW);
	});
	new ala::StateTransition(stateManager, "go_right", "stand_right",
		[] {
		return ala::Input::get()->getKeyUp(ALA_KEY_RIGHT_ARROW);
	});
	new ala::StateTransition(stateManager, "stand_left", "go_left",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_LEFT_ARROW);
	});
	new ala::StateTransition(stateManager, "stand_left", "go_right",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_RIGHT_ARROW);
	});
	new ala::StateTransition(stateManager, "go_left", "stand_left",
		[] {
		return ala::Input::get()->getKeyUp(ALA_KEY_LEFT_ARROW);
	});
	new ala::StateTransition(stateManager, "stand_left", "sit_left",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW);
	});
	new ala::StateTransition(stateManager, "stand_right", "sit_right",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW);
	});
	new ala::StateTransition(stateManager, "sit_left", "stand_left",
		[] {
		return ala::Input::get()->getKeyUp(ALA_KEY_DOWN_ARROW);
	});
	new ala::StateTransition(stateManager, "sit_right", "stand_right",
		[] {
		return ala::Input::get()->getKeyUp(ALA_KEY_DOWN_ARROW);
	});
}
