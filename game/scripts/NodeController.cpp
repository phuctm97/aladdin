#include "NodeController.h"

USING_NAMESPACE_ALA;

NodeController::NodeController(ala::GameObject * gameObject, const std::string & name)
	: GameObjectComponent(gameObject, name), _logger("NodeController") { }

void NodeController::onUpdate(const float delta)
{
	const auto input = Input::get();

	const auto halfVisibleSize = Size(GameManager::get()->getVisibleWidth() / 2, GameManager::get()->getVisibleHeight() / 2);
	const auto transform = getGameObject()->getTransform();

	if (input->getKey(ALA_KEY_RIGHT_ARROW))
	{
		transform->setPosition(transform->getPositionX() + speed, transform->getPositionY());
	}

	if (input->getKey(ALA_KEY_LEFT_ARROW))
	{
		transform->setPosition(transform->getPositionX() - speed, transform->getPositionY());
	}

	if (input->getKey(ALA_KEY_DOWN_ARROW))
	{
		transform->setPosition(transform->getPositionX(), transform->getPositionY() - speed);
	}

	if (input->getKey(ALA_KEY_UP_ARROW))
	{
		transform->setPosition(transform->getPositionX(), transform->getPositionY() + speed);
	}


	if (input->getKeyDown(ALA_KEY_F3)) {
		speed++;
		_logger.info("Speed = %d\n", speed);
	}

	if (input->getKeyDown(ALA_KEY_F2)) {
		speed--;
		_logger.info("Speed = %d\n", speed);
	}

	if (input->getKeyDown(ALA_KEY_F1)) {
		_logger.info("X: %f; Y: %f \n", transform->getPositionX() + 160, transform->getPositionY() + 128);
	}

}
