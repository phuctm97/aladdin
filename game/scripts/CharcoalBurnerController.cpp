#include "CharcoalBurnerController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

CharcoalBurnerController::CharcoalBurnerController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _firing( false ), _firingTimer( 0 ), _firingInterval( 0.4f ),
    _firingMinX( 0 ), _firingMaxX( 0 ), _firingOffsetY( 21 ) {}

void CharcoalBurnerController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == ALADDIN_TAG && otherCollider->getTag() == ALADDIN_TAG ) {
    _firing = true;
    _firingTimer = 0;
  }
}

void CharcoalBurnerController::onTriggerStay( const ala::CollisionInfo& collision ) { }

void CharcoalBurnerController::onTriggerExit( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == ALADDIN_TAG && otherCollider->getTag() == ALADDIN_TAG ) {
    _firing = false;
  }
}

void CharcoalBurnerController::onInitialize() {
  const auto collider = getGameObject()->getComponentT<Collider>();
  if ( collider == NULL ) return;

  const auto colliderBox = collider->getBoundingRect();
  _firingMinX = colliderBox.getMinX();
  _firingMaxX = colliderBox.getMaxX();
}

void CharcoalBurnerController::onUpdate( const float delta ) {
  if ( _firing ) {
    _firingTimer -= delta;

    if ( _firingTimer <= 0 ) {
      _firingTimer = _firingInterval;

      const auto gameManager = GameManager::get();
      const auto aladdin = gameManager->getObjectByTag( ALADDIN_TAG );
      if ( aladdin != NULL ) {
        fire( aladdin->getTransform()->getPositionX() );
      }
    }
  }
}

void CharcoalBurnerController::fire( const float x ) const {
  const auto firePosition = Vec2( MAX(MIN(x, _firingMaxX), _firingMinX),
                                  getGameObject()->getTransform()->getPositionY() + _firingOffsetY );

  GameManager::get()->getPrefab( "Fire" )->instantiate( firePosition );
}
