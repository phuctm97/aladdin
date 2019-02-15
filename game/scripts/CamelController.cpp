#include "CamelController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(CamelController, ala::GameObjectComponent)

CamelController::CamelController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _aladdinJumpingOn( false ), _selfCollider( NULL ),
    _selfTransform( NULL ), _selfDirection( NULL ),
    _aladdinStateManager( NULL ), _floatingSavilaPrefab( NULL ) {}

void CamelController::resetAladdinJumpingOn() {
  _aladdinJumpingOn = false;
}

bool CamelController::isAladdinJumpingOn() const { return _aladdinJumpingOn; }

void CamelController::onInitialize() {
  const auto gameManager = GameManager::get();

  const auto aladdin = gameManager->getObjectByTag( ALADDIN_TAG );
  if ( aladdin != NULL ) {
    _aladdinStateManager = aladdin->getComponentT<StateManager>();
  }

  _selfTransform = getGameObject()->getTransform();

  _selfCollider = getGameObject()->getComponentT<Collider>();

  _selfDirection = getGameObject()->getComponentT<DirectionController>();

  _floatingSavilaPrefab = gameManager->getPrefabV2( "Floating Saliva" );
}

void CamelController::puffSaliva( const float directX, const float directY ) const {
  const auto coef = _selfDirection->isLeft() ? -1 : 1;

  _floatingSavilaPrefab->instantiateWithArgs( _selfDirection->isLeft() ? "L" : "R" )
                       ->getTransform()
                       ->setPosition( _selfTransform->getPosition() +
                         Vec2( coef * (_selfCollider->getSize().getWidth() / 2 + directX),
                               _selfCollider->getSize().getHeight() / 2 + directY ) );
}

void CamelController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == ALADDIN_TAG && otherCollider->getTag() == ALADDIN_TAG ) {
    if ( collision.getNormal() == Vec2( 0, 1 ) ) {
      _aladdinJumpingOn = true;
    }
  }
}
