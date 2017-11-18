#include "AladdinController.h"

USING_NAMESPACE_ALA;

AladdinController::AladdinController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _logger( "AladdinController" ), _collidedWithGround( false ) {}

bool AladdinController::isCollidedWithGround() const { return _collidedWithGround; }

void AladdinController::resetCollidedWithGround() { _collidedWithGround = false; }

void AladdinController::onUpdate( const float delta ) {}

void AladdinController::onCollisionEnter( const ala::CollisionInfo& collision ) {
  if ( collision.getColliderA()->getGameObject()->getName() == "Ground" || collision.getColliderA()->getGameObject()->getName() == "Ground" ) {
    _collidedWithGround = true;
  }
}
