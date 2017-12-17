#include "PlatformPrefab.h"
#include "../Define.h"
#include "../scripts/PlatformController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PlatformPrefab, ala::PrefabV2)

void PlatformPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto width = nextFloat( argsStream );
  const auto uponHeight = 5.0f;
  const auto belowHeight = 2.0f;

  // constants

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto uponCollider = new Collider( object, false, Vec2( 0, 0 ), Size( width, uponHeight ), 1, 0,
                                          "Upon" );
  uponCollider->ignoreTag( PLATFORM_TAG );

  const auto belowCollider = new Collider( object, true, Vec2( 0, -uponHeight / 2 - belowHeight / 2 - 1 ),
                                           Size( width, belowHeight ), 1, 0,
                                           "Below" );
  belowCollider->ignoreTag( PLATFORM_TAG );

  const auto controller = new PlatformController( object );

  // collider renderers
  new ColliderRenderer( uponCollider );
  new ColliderRenderer( belowCollider );

  // configurations
  object->setTag( GROUND_TAG );
  object->setLayer( "Debug" );
}
