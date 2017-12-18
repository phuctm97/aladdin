#include "PlatformController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PlatformController, ala::GameObjectComponent)

PlatformController::PlatformController( ala::GameObject* gameObject, const string& name )
  : GameObjectComponent( gameObject, name ), _other( NULL ), _logger( "PlatformController" ) { }

void PlatformController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  getCollisionObject( collision );
  
  if ( collision.getNormal() == Vec2( 0, 1 ) ) {

    _oldPosition = _other->getTransform()->getPosition();

    float height = getGameObject()->getTransform()->getPositionY() +
      static_cast<Collider*>(getGameObject()->getComponent( "Upon" ))->getSize().getHeight() +
      static_cast<Collider*>(getGameObject()->getComponent( "Upon" ))->getOffset().getY() +
      _other->getComponentT<Collider>()->getSize().getHeight() / 2 +
      _other->getComponentT<Collider>()->getOffset().getY() / 2 + 1;

    _oldPosition.setY( height );
    return;
  }

  if ( _other->getTag() == ALADDIN_TAG ) {
    const auto alaStateManager = _other->getComponentT<StateManager>();
    getGameObject()->getComponent( "Upon" )->setActive( false );
  }


}

void PlatformController::onTriggerExit( const ala::CollisionInfo& collision ) {
  getGameObject()->getComponent( "Upon" )->setActive( true );
}


void PlatformController::onUpdate( const float delta ) {
  if ( _isChangePosition ) {
    _other->getTransform()->setPosition( _oldPosition );
  }
}


void PlatformController::getCollisionObject( const ala::CollisionInfo& collision ) {
  _other = collision.getColliderA()->getGameObject() == getGameObject()
             ? collision.getColliderB()->getGameObject()
             : collision.getColliderA()->getGameObject();
}
