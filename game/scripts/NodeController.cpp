#include "NodeController.h"

USING_NAMESPACE_ALA;

NodeController::NodeController(ala::GameObject * gameObject, const std::string & name)
	: GameObjectComponent(gameObject, name), _logger("NodeController") { }

void NodeController::onUpdate(const float delta)
{
	const auto input = Input::get();

	const auto halfVisibleSize = Size(GameManager::get()->getVisibleWidth() / 2, GameManager::get()->getVisibleHeight() / 2);
	const auto transform = getGameObject()->getTransform();
	const auto rectRenderer = getGameObject()->getComponentT<RectRenderer>();
	const auto collider = getGameObject()->getComponentT<Collider>();

	if (input->getKey(ALA_KEY_RIGHT_ARROW))
	{
		transform->setPosition(transform->getPositionX() + _speed, transform->getPositionY());
	}

	if (input->getKey(ALA_KEY_LEFT_ARROW))
	{
		transform->setPosition(transform->getPositionX() - _speed, transform->getPositionY());
	}

	if (input->getKey(ALA_KEY_DOWN_ARROW))
	{
		transform->setPosition(transform->getPositionX(), transform->getPositionY() - _speed);
	}

	if (input->getKey(ALA_KEY_UP_ARROW))
	{
		transform->setPosition(transform->getPositionX(), transform->getPositionY() + _speed);
	}

	if (input->getKey(ALA_KEY_KEYPAD_PLUS) && !input->getKey(ALA_KEY_LEFT_SHIFT))
	{
		if (rectRenderer != NULL) {
			rectRenderer->setSize(Size(rectRenderer->getSize().getWidth() + 1, rectRenderer->getSize().getHeight()));
		}

		if (collider != NULL) {
			collider->setSize(Size(collider->getSize().getWidth() + 1, collider->getSize().getHeight()));
		}
	}

	if (input->getKey(ALA_KEY_KEYPAD_MINUS) && !input->getKey(ALA_KEY_LEFT_SHIFT))
	{
		if (rectRenderer != NULL) {
			rectRenderer->setSize(Size(rectRenderer->getSize().getWidth() - 1, rectRenderer->getSize().getHeight()));
		}

		if (collider != NULL) {
			collider->setSize(Size(collider->getSize().getWidth() - 1, collider->getSize().getHeight()));
		}
	}

	if (input->getKey(ALA_KEY_KEYPAD_PLUS) && input->getKey(ALA_KEY_LEFT_SHIFT))
	{
		if (rectRenderer != NULL) {
			rectRenderer->setSize(Size(rectRenderer->getSize().getWidth(), rectRenderer->getSize().getHeight() + 1));
		}

		if (collider != NULL) {
			collider->setSize(Size(collider->getSize().getWidth(), collider->getSize().getHeight() + 1));
		}
	}

	if (input->getKey(ALA_KEY_KEYPAD_MINUS) && input->getKey(ALA_KEY_LEFT_SHIFT))
	{
		if (rectRenderer != NULL) {
			rectRenderer->setSize(Size(rectRenderer->getSize().getWidth(), rectRenderer->getSize().getHeight() - 1));
		}

		if (collider != NULL) {
			collider->setSize(Size(collider->getSize().getWidth(), collider->getSize().getHeight() - 1));
		}
	}

	if (input->getKeyDown(ALA_KEY_F3)) {
		_speed++;
		_logger.info("Speed = %d\n", _speed);
	}

	if (input->getKeyDown(ALA_KEY_F2)) {
		_speed--;
		_logger.info("Speed = %d\n", _speed);
	}

	if (input->getKeyDown(ALA_KEY_F1)) {
		_logger.info("X: %f; Y: %f \n", transform->getPositionX(), transform->getPositionY());
		if (rectRenderer != NULL)
		{
			_logger.info("Rect Size (%f , %f) \n", rectRenderer->getSize().getWidth(), rectRenderer->getSize().getHeight());
		}

		if (collider != NULL)
		{
			_logger.info("Collider Size (%f , %f) \n", collider->getSize().getWidth(), collider->getSize().getHeight());
		}
	}

	if (input->getKeyDown(ALA_KEY_F4))
	{
		if (collider != NULL)
		{
			_logger.info("\n->instantiate();\n->setLayer(\"Background\");\n->getTransform()->setPosition(Vec2( %.0f, %.0f));\n->getComponentT<Collider>()->setSize(Size(%.0f, %.0f));", transform->getPositionX(), transform->getPositionY(), collider->getSize().getWidth(), collider->getSize().getHeight());
		}
	}
}
