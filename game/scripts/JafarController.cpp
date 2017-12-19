#include "JafarController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarController, ala::GameObjectComponent)

JafarController::JafarController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _aladdinTransform( NULL ), _selfTransform( NULL ) {}

char JafarController::getDirectionToFaceAladdin() const {
  if ( _aladdinTransform->getPositionX() < _selfTransform->getPositionX() ) return 'L';
  return 'R';
}

void JafarController::onInitialize() {
  const auto gameManager = GameManager::get();

  _selfTransform = getGameObject()->getTransform();

  const auto aladdin = gameManager->getObjectByTag( ALADDIN_TAG );
  if ( aladdin != NULL ) {
    _aladdinTransform = aladdin->getTransform();
  }

}

