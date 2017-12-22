#include "AgrabahMarketStairsFourPrefab.h"
#include "../Define.h"
#include "../scripts/DoubleStairsModeSwitcher.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AgrabahMarketStairsFourPrefab, ala::PrefabV2)

void AgrabahMarketStairsFourPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto initialOn = nextBool( argsStream );

  // constants
  vector<Vec2> positionBelow{
    Vec2( 2445.0f - 2445.0f, -87.5f + 87.5f ),
    Vec2( 2411.5f - 2445.0f, -79.5f + 87.5f ),
    Vec2( 2387.5f - 2445.0f, -71.0f + 87.5f ),
    Vec2( 2356.0f - 2445.0f, -63.0f + 87.5f ),
    Vec2( 2323.5f - 2445.0f, -55.0f + 87.5f ),
    Vec2( 2291.5f - 2445.0f, -47.0f + 87.5f ),
    Vec2( 2252.5f - 2445.0f, -39.0f + 87.5f ),
    Vec2( 2212.0f - 2445.0f, -31.5f + 87.5f ),
    Vec2( 2179.5f - 2445.0f, -23.5f + 87.5f ),
    Vec2( 2148.0f - 2445.0f, -15.0f + 87.5f ),
    Vec2( 2108.0f - 2445.0f, -7.0f + 87.5f ),
  };

  vector<Size> sizeBelow{
    Size( 34.0f, 7.0f ),
    Size( 34.0f, 7.0f ),
    Size( 34.0f, 7.0f ),
    Size( 34.0f, 7.0f ),
    Size( 34.0f, 7.0f ),
    Size( 34.0f, 7.0f ),
    Size( 47.0f, 7.0f ),
    Size( 33.0f, 7.0f ),
    Size( 33.0f, 7.0f ),
    Size( 33.0f, 7.0f ),
    Size( 47.0f, 7.0f )
  };

  vector<Vec2> positionUpon{
    Vec2( 2152.5f - 2152.5f - 292.5f, -4.0f + 87.5f ),
    Vec2( 2190.5f - 2152.5f - 292.5f, 3.5f + 87.5f ),
    Vec2( 2221.5f - 2152.5f - 292.5f, 11.5f + 87.5f ),
    Vec2( 2254.5f - 2152.5f - 292.5f, 19.0f + 87.5f ),
    Vec2( 2286.5f - 2152.5f - 292.5f, 27.0f + 87.5f ),
    Vec2( 2326.5f - 2152.5f - 292.5f, 35.0f + 87.5f ),
    Vec2( 2382.5f - 2152.5f - 292.5f, 43.0f + 87.5f ),
    Vec2( 2494.5f - 2152.5f - 292.5f, 51.0f + 87.5f )
  };

  vector<Size> sizeUpon{
    Size( 39.0f, 5.0f ),
    Size( 39.0f, 5.0f ),
    Size( 39.0f, 5.0f ),
    Size( 39.0f, 5.0f ),
    Size( 39.0f, 5.0f ),
    Size( 55.0f, 5.0f ),
    Size( 55.0f, 5.0f ),
    Size( 182.0f, 5.0f )
  };

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  std::vector<Collider*> stairBelowColliders;
  for ( size_t i = 0; i < positionBelow.size(); i++ ) {
    const auto collider = new Collider( object, false, positionBelow[i], sizeBelow[i], 1, 0, "M" );

    stairBelowColliders.push_back( collider );
  }

  std::vector<Collider*> stairUponColliders;
  for ( size_t i = 0; i < positionUpon.size(); i++ ) {
    const auto collider = new Collider( object, false, positionUpon[i], sizeUpon[i], 1, 0, "M" );

    stairUponColliders.push_back( collider );
  }

  const auto firstSwitchCollider = new Collider( object, true, Vec2( 2513.0f - 2445.0f, -33.0f + 87.5 ),
                                                 Size( 15.0f, 118.0f ), 1, 0, "B" );

  const auto secondSwitchCollider = new Collider( object, true, Vec2( 2090.0f - 2152.5f - 292.5f, 33.0f + 87.5f ),
                                                  Size( 11.0f, 73.0f ), 1, 0, "U" );

  const auto stateManager = new StateManager( object, "OnOff" );

  const auto switcher = new DoubleStairsModeSwitcher( object );

  // collider renderers
//  for ( auto collider : stairBelowColliders ) new ColliderRenderer( collider );
//  for ( auto collider : stairUponColliders ) new ColliderRenderer( collider );
//  new ColliderRenderer( firstSwitchCollider );
//  new ColliderRenderer( secondSwitchCollider );

  // flags
  const auto stairFlags = COLLIDE_ALADDIN_FLAG |
    COLLIDE_ENEMY_FLAG |
    COLLIDE_FREE_OBJECT_FLAG |
    STANDABLE_FLAG |
    STATIC_FLAG;
  for ( const auto collider : stairUponColliders ) {
    collider->setFlags( stairFlags );
    collider->ignoreIfHasAnyFlags( STATIC_FLAG );
  }
  for ( const auto collider : stairBelowColliders ) {
    collider->setFlags( stairFlags );
    collider->ignoreIfHasAnyFlags( STATIC_FLAG );
  }
  firstSwitchCollider->setFlags( COLLIDE_ALADDIN_FLAG | STATIC_FLAG );
  firstSwitchCollider->ignoreIfHasAnyFlags( STATIC_FLAG );
  secondSwitchCollider->setFlags( COLLIDE_ALADDIN_FLAG | STATIC_FLAG );
  secondSwitchCollider->ignoreIfHasAnyFlags( STATIC_FLAG );

  // configurations
  object->setTag( GROUND_TAG );
  object->setLayer( "Debug" );


  // states
  new State( stateManager, "OnOff",
             [=] {
               object->getComponent( "U" )->setActive( true );
               for ( const auto collider : stairBelowColliders ) collider->setActive( true );
               for ( const auto collider : stairUponColliders ) collider->setActive( false );
             }, NULL, NULL );

  new State( stateManager, "OnOn",
             [=] {
               for ( const auto collider : stairBelowColliders ) collider->setActive( true );
               for ( const auto collider : stairUponColliders ) collider->setActive( true );
             }, NULL, NULL );

  new State( stateManager, "OffOff",
             [=] {
               object->getComponent( "U" )->setActive( false );
               for ( const auto collider : stairBelowColliders ) collider->setActive( false );
               for ( const auto collider : stairUponColliders ) collider->setActive( false );
             }, NULL, NULL );

  new State( stateManager, "OffOn",
             [=] {
               for ( const auto collider : stairBelowColliders ) collider->setActive( false );
               for ( const auto collider : stairUponColliders ) collider->setActive( true );
             }, NULL, NULL );
}
