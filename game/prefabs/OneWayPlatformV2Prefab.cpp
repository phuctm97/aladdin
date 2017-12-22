#include "OneWayPlatformV2Prefab.h"
#include "../Define.h"
#include "../scripts/OneWayPlatformV2Controller.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(OneWayPlatformV2Prefab, ala::PrefabV2)

void OneWayPlatformV2Prefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto width = nextFloat( argsStream );
  const auto height = 5.0f;

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, false, Vec2( 0, 0 ), Size( width, height ), 1, 0, "Aladdin" );
  collider->ignoreTag( PLATFORM_TAG );

  const auto controller = new OneWayPlatformV2Controller( object );

  const auto stateManager = new StateManager( object, "off" );

  // collider renderers
  new ColliderRenderer( collider );

  // states
  new State( stateManager, "off", [=] {
    collider->setFlags( COLLIDE_ENEMY_FLAG | COLLIDE_FREE_OBJECT_FLAG | STATIC_FLAG );
  }, NULL, NULL );

  new State( stateManager, "on", [=] {
    collider->setFlags(
      COLLIDE_ALADDIN_FLAG | STANDABLE_FLAG | COLLIDE_ENEMY_FLAG | COLLIDE_FREE_OBJECT_FLAG | STATIC_FLAG );
  }, NULL, NULL );

  new StateTransition( stateManager, "off", "on", [=] {
    return controller->isAladdinAbove();
  } );

  new StateTransition( stateManager, "on", "off", [=] {
    return !controller->isAladdinAbove();
  } );

  // flags
  collider->setFlags( COLLIDE_ENEMY_FLAG | COLLIDE_FREE_OBJECT_FLAG | STATIC_FLAG );
  collider->ignoreIfHasAnyFlags( STATIC_FLAG );

  // configurations
  object->setLayer( "Debug" );
}
