#include "HandEnemyController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

HandEnemyController::HandEnemyController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _aladdinInZone( false ), _selfTransform( NULL ), _selfDirection( NULL ),
    _selfBodyCollider( NULL ),
    _enemyExplosionPrefab( NULL ), _fallingVasePrefab( NULL ) {}

bool HandEnemyController::isAladdinInZone() const { return _aladdinInZone; }

void HandEnemyController::throwVase( const float directX, const float directY ) const {
  const auto coef = _selfDirection->isLeft() ? -1 : 1;

  _fallingVasePrefab->instantiateWithArgs( _selfDirection->isLeft() ? "L" : "R" )
                      ->getTransform()
                      ->setPosition( _selfTransform->getPosition() +
                        Vec2( coef * (_selfBodyCollider->getSize().getWidth() / 2 + directX),
                              _selfBodyCollider->getSize().getHeight() / 2 + directY ) );
}

void HandEnemyController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();
  const auto selfCollider = collision.getColliderA() == otherCollider
                              ? collision.getColliderB()
                              : collision.getColliderA();

  if ( otherObject->getTag() == ALADDIN_TAG && otherCollider->getTag() == ALADDIN_TAG &&
    selfCollider->getName() == "Zone" ) {
    _aladdinInZone = true;
  }


  if ( otherObject->getTag() == ALADDIN_TAG &&
    (otherCollider->getTag() == SWORD_TAG || otherCollider->getTag() == APPLE_TAG) &&
    selfCollider->getTag() == ENEMY_TAG ) {
    onDie();
  }
}

void HandEnemyController::onTriggerExit( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();
  const auto selfCollider = collision.getColliderA() == otherCollider
                              ? collision.getColliderB()
                              : collision.getColliderA();

  if ( otherObject->getTag() == ALADDIN_TAG && otherCollider->getTag() == ALADDIN_TAG &&
    selfCollider->getName() == "Zone" ) {
    _aladdinInZone = false;
  }
}

void HandEnemyController::onDie() const {
  _enemyExplosionPrefab->instantiate( _selfTransform->getPosition() );

  getGameObject()->release();
}

void HandEnemyController::onInitialize() {
  const auto gameManager = GameManager::get();

  _selfTransform = getGameObject()->getTransform();

  _selfDirection = getGameObject()->getComponentT<DirectionController>();

  _selfBodyCollider = static_cast<Collider*>(getGameObject()->getComponent( "Body" ));

  _enemyExplosionPrefab = gameManager->getPrefabV2( "Enemy Explosion" );

  _fallingVasePrefab = gameManager->getPrefabV2( "Falling Vase" );
}
