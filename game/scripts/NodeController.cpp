#include "NodeController.h"

USING_NAMESPACE_ALA;

NodeController::NodeController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _logger("NodeController"), _speed(1) { }

void NodeController::onUpdate(const float delta) {
	const auto input = Input::get();

	const auto halfVisibleSize = Size(GameManager::get()->getVisibleWidth() / 2,
		GameManager::get()->getVisibleHeight() / 2);
	const auto transform = getGameObject()->getTransform();
	const auto rectRenderer = getGameObject()->getComponentT<RectRenderer>();
	const auto collider = getGameObject()->getComponentT<Collider>();

	if (input->getKey(ALA_KEY_L)) {
		transform->setPosition(transform->getPositionX() + _speed, transform->getPositionY());
	}

	if (input->getKey(ALA_KEY_J)) {
		transform->setPosition(transform->getPositionX() - _speed, transform->getPositionY());
	}

	if (input->getKey(ALA_KEY_K)) {
		transform->setPosition(transform->getPositionX(), transform->getPositionY() - _speed);
	}

	if (input->getKey(ALA_KEY_I)) {
		transform->setPosition(transform->getPositionX(), transform->getPositionY() + _speed);
	}

	if (input->getKey(ALA_KEY_KEYPAD_PLUS) && !input->getKey(ALA_KEY_LEFT_SHIFT)) {
		if (rectRenderer != NULL) {
			rectRenderer->setSize(Size(rectRenderer->getSize().getWidth() + 1, rectRenderer->getSize().getHeight()));
		}

		if (collider != NULL) {
			collider->setSize(Size(collider->getSize().getWidth() + 1, collider->getSize().getHeight()));
		}
	}

	if (input->getKey(ALA_KEY_KEYPAD_MINUS) && !input->getKey(ALA_KEY_LEFT_SHIFT)) {
		if (rectRenderer != NULL) {
			rectRenderer->setSize(Size(rectRenderer->getSize().getWidth() - 1, rectRenderer->getSize().getHeight()));
		}

		if (collider != NULL) {
			collider->setSize(Size(collider->getSize().getWidth() - 1, collider->getSize().getHeight()));
		}
	}

	if (input->getKey(ALA_KEY_KEYPAD_PLUS) && input->getKey(ALA_KEY_LEFT_SHIFT)) {
		if (rectRenderer != NULL) {
			rectRenderer->setSize(Size(rectRenderer->getSize().getWidth(), rectRenderer->getSize().getHeight() + 1));
		}

		if (collider != NULL) {
			collider->setSize(Size(collider->getSize().getWidth(), collider->getSize().getHeight() + 1));
		}
	}

	if (input->getKey(ALA_KEY_KEYPAD_MINUS) && input->getKey(ALA_KEY_LEFT_SHIFT)) {
		if (rectRenderer != NULL) {
			rectRenderer->setSize(Size(rectRenderer->getSize().getWidth(), rectRenderer->getSize().getHeight() - 1));
		}

		if (collider != NULL) {
			collider->setSize(Size(collider->getSize().getWidth(), collider->getSize().getHeight() - 1));
		}
	}

	if (input->getKeyDown(ALA_KEY_F3)) {
		_speed += 0.5f;
		_logger.info("Moving speed = %f\n", _speed);
	}

	if (input->getKeyDown(ALA_KEY_F2)) {
		_speed -= 0.5f;
		_logger.info("Moving speed = %f\n", _speed);
	}

	if (input->getKeyDown(ALA_KEY_F1)) {
		_logger.info("X: %f; Y: %f \n", transform->getPositionX(), transform->getPositionY());
		if (rectRenderer != NULL) {
			_logger.info("Rect Size (%f , %f) \n", rectRenderer->getSize().getWidth(), rectRenderer->getSize().getHeight());
		}

		if (collider != NULL) {
			_logger.info("Collider Size (%f , %f) \n", collider->getSize().getWidth(), collider->getSize().getHeight());
		}
	}

	if (input->getKeyDown(ALA_KEY_F4)) {
		if (collider != NULL) {
			_logger.info("Position: Vec2(%.1ff, %.1ff), Size(%.1ff, %.1ff)", transform->getPositionX(), transform->getPositionY(), collider->getSize().getWidth(), collider->getSize().getHeight());
		}

		if (rectRenderer != NULL) {
			_logger.info("Position: Vec2(%.1ff, %.1ff), Size(%.1ff, %.1ff)", transform->getPositionX(), transform->getPositionY(), rectRenderer->getSize().getWidth(), rectRenderer->getSize().getHeight());
		}
	}

	if (input->getKeyDown(ALA_KEY_F5)) {
		if (collider != NULL) {
			_logger.info(
				//StairNoob//"\n->getTransform()->setPosition(Vec2(%.0f,%.0f));\n((Collider*)->getComponent(\"first\"))->setSize(Size(%.0f, %.0f));\n((Collider*)->getComponent(\"first\"))->setOffset(Vec2(%.0f, %.0f));\n((Collider*)->getComponent(\"second\"))->setSize(Size(%.0f, %.0f));\n((Collider*)->getComponent(\"second\"))->setOffset(Vec2(%.0f, %.0f)); ",
				"\n->getTransform()->setPosition(Vec2(%.1ff, %.1ff));\n->getComponentT<Collider>()->setSize(Size(%.1ff, %.1ff));",
				transform->getPositionX(),
				transform->getPositionY(),
				collider->getSize().getWidth(),
				collider->getSize().getHeight());
		}
	}

	if (input->getKeyDown(ALA_KEY_F6)) {
			if (collider != NULL) {
				if (_rectObject != NULL) _rectObject->release();
				_rectObject = new GameObject(GameManager::get()->getRunningScene());
				new RectRenderer(_rectObject, collider->getOffset(), collider->getSize(), Color(0, 255, 255), "");
				_rectObject->getTransform()->setPosition(transform->getPosition());
				_logger.info(
					//StairNoob//"\n->getTransform()->setPosition(Vec2(%.0f,%.0f));\n((Collider*)->getComponent(\"first\"))->setSize(Size(%.0f, %.0f));\n((Collider*)->getComponent(\"first\"))->setOffset(Vec2(%.0f, %.0f));\n((Collider*)->getComponent(\"second\"))->setSize(Size(%.0f, %.0f));\n((Collider*)->getComponent(\"second\"))->setOffset(Vec2(%.0f, %.0f)); ",
					//Stair??//"\n->getTransform()->setPosition(Vec2(%.1ff, %.1ff));\n->getComponentT<Collider>()->setSize(Size(%.1ff, %.1ff));",
					//Stair Group 2 //"\nconst auto = gameManager->getPrefab(\"StairGroupTwo\")->instantiate();\n->getTransform()->setPosition(Vec2(%.1ff, %.1ff));\n->getComponentT<Collider>()->setSize(Size(%.1ff, %.1ff)); ",
					//Somthing//"\nconst auto = gameManager->getPrefab(\"\")->instantiate();\n->getTransform()->setPosition(Vec2(%.1ff, %.1ff));\n->getComponentT<Collider>()->setSize(Size(%.1ff, %.1ff)); ",
					"\nconst auto = gameManager->getPrefab(\"Platform\")->instantiate();\n->getTransform()->setPosition(Vec2(%.2ff, %.2ff));\nstatic_cast<Collider*>(->getComponent(\"Upon\"))->setSize(Size(%.2ff, %.2ff));\nstatic_cast<Collider*>(->getComponent(\"Below\"))->setSize(Size(%.2ff, %.2ff));\nstatic_cast<Collider*>(->getComponent(\"Upon\"))->setOffset(Vec2(0, %.2ff));\nstatic_cast<Collider*>(->getComponent(\"Below\"))->setOffset(Vec2(0, -%.2ff));",
					transform->getPositionX(),
					transform->getPositionY(),
					collider->getSize().getWidth(),
					collider->getSize().getHeight() / 2,
					collider->getSize().getWidth(),
					collider->getSize().getHeight() / 2,
					collider->getSize().getHeight() / 4,
					collider->getSize().getHeight() / 4 + 0.75f	);
			}
		

	}
}

bool NodeController::onPreInitialize() {
	_logger.info(
		"NodeController used\n\t- I, J, K, L to move\n\t- [+], [-] to change width, along side with Left Shift to change height\n\t- F2, F3 to decrease and increase moving speed\n\t- F1 to print transform information.");
	return true;
}

