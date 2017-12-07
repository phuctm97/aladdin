#include "CharcoalBurnerPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void CharcoalBurnerPrefab::doInstantiate( ala::GameObject* object ) const {
  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC, 0 );

  const auto collider = new Collider( object, true, Vec2(), Size( 101, 4 ) );
  collider->setTag( CHARCOAL_BURNER_TAG );
  collider->ignoreTag( GROUND_TAG );

  const auto colliderRenderer = new ColliderRenderer( collider );

  // configurations
  object->setTag( CHARCOAL_BURNER_TAG );
  object->setLayer( "Background" );
}