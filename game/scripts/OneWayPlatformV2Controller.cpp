#include "OneWayPlatformV2Controller.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(OneWayPlatformV2Controller, ala::GameObjectComponent)

OneWayPlatformV2Controller::OneWayPlatformV2Controller( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _aladdinTransform( NULL ), _aladdinBodyCollider( NULL ),
    _selfTransform( NULL ) {}

void OneWayPlatformV2Controller::onInitialize() {
  const auto gameManager = GameManager::get();

  _selfTransform = getGameObject()->getTransform();

  const auto aladdin = gameManager->getObjectByTag( ALADDIN_TAG );

  _aladdinTransform = aladdin->getTransform();

  _aladdinBodyCollider = static_cast<Collider*>(aladdin->getComponentT<Collider>());
}

bool OneWayPlatformV2Controller::isAladdinAbove() const {
  const auto aladdinBottom = _aladdinTransform->getPositionY() - _aladdinBodyCollider->getSize().getHeight() / 2;
  return aladdinBottom > _selfTransform->getPositionY();
}
