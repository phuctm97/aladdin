#include "CharcoalBurnerPrefab.h"
#include "../Define.h"
#include "../scripts/CharcoalBurnerController.h"

USING_NAMESPACE_ALA;

void CharcoalBurnerPrefab::doInstantiate( ala::GameObject* object ) const {
  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC, 0 );

  const auto collider = new Collider( object, true, Vec2(), Size( 90, 4 ) );
  collider->setTag( CHARCOAL_BURNER_TAG );
  collider->ignoreTag( GROUND_TAG );

  const auto controller = new CharcoalBurnerController( object );

  // configurations
  object->setTag( CHARCOAL_BURNER_TAG );
  object->setLayer( "Background" );
}
