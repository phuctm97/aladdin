#include "PlatformController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PlatformController, ala::GameObjectComponent)

PlatformController::PlatformController( ala::GameObject* gameObject, const string& name )
  : GameObjectComponent( gameObject, name ), _other( NULL ), _logger( "PlatformController" ),
    _uponCollider( NULL ) { }

void PlatformController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  _other = otherObject;

  if ( collision.getNormal() == Vec2( 0, 1 ) ) {

    _oldPosition = _other->getTransform()->getPosition();

    float height = getGameObject()->getTransform()->getPositionY() +
      _uponCollider->getSize().getHeight() +
      _uponCollider->getOffset().getY() +
      otherCollider->getSize().getHeight() / 2 +
      otherCollider->getOffset().getY() / 2 + 1;

    _oldPosition.setY( height );
    return;
  }

  if ( _other->getTag() == ALADDIN_TAG ) {
    _uponCollider->setActive( false );
  }


}

void PlatformController::onTriggerExit( const ala::CollisionInfo& collision ) {
  _uponCollider->setActive( true );
}


void PlatformController::onUpdate( const float delta ) {
  if ( _isChangePosition ) {
    _other->getTransform()->setPosition( _oldPosition );
  }
}

void PlatformController::onInitialize() {
  _uponCollider = static_cast<Collider*>(getGameObject()->getComponent( "Upon" ));
}