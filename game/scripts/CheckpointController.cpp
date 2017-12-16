#include "CheckpointController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(CheckpointController, ala::GameObjectComponent)

CheckpointController::
CheckpointController( ala::GameObject* gameObject, const int index, const std::string& name ):
  GameObjectComponent( gameObject, name ), _index( index ), _checked( false ), _myAppData( NULL ) {}

bool CheckpointController::isChecked() const {
  return _checked;
}

void CheckpointController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  if ( _checked ) return;

  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  const auto selfCollider = collision.getColliderA() == otherCollider
                              ? collision.getColliderB()
                              : collision.getColliderA();

  if ( otherObject->getTag() == ALADDIN_TAG ) {
    setChecked();
  }
}

void CheckpointController::setChecked() {
  _checked = true;

  if ( _myAppData->getCurrentCheckpoint() < _index ) {
    _myAppData->setCurrentCheckpoint( _index );
  }
}

void CheckpointController::onInitialize() {
  _myAppData = static_cast<MyAppData*>(GameManager::get()->getResource( "My App Data" ));
}
