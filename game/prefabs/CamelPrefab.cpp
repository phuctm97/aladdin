#include "CamelPrefab.h"
#include "../scripts/CamelController.h"
#include "../Define.h"
#include "../scripts/DirectionController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(CamelPrefab, ala::PrefabV2)

void CamelPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto dir = nextChar( argsStream );

  // constants
  const auto gameManager = GameManager::get();

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "camel.png" );

  const auto animator = new Animator( object, "idle", "camel.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 24, 15 ) );
  collider->setTag( CAMEL_TAG );
  collider->ignoreTag( CAMEL_TAG );
  collider->ignoreTag( ENEMY_TAG );
  collider->ignoreTag( SWORD_TAG );
  collider->ignoreTag( APPLE_TAG );

  const auto stateManager = new StateManager( object, "idle" );

  const auto direction = new DirectionController( object, true, 1 );
  if ( dir == 'L' ) direction->setLeft();
  else if ( dir == 'R' ) direction->setRight();

  const auto controller = new CamelController( object );

  // helpers
  const auto timer = new Timer( object );

  const auto transform = object->getTransform();

  // collider renderers
  new ColliderRenderer( collider );

  // flags
  collider->setFlags( COLLIDE_ALADDIN_FLAG | STATIC_FLAG );
  collider->ignoreIfHasAnyFlags( STATIC_FLAG );

  // configurations
  object->setTag( CAMEL_TAG );
  object->setLayer( "Mass Character" );

  // states
  new State( stateManager, "idle",
             [=] {
               // animation effect
               {
                 animator->setAction( "idle" );
               }

               // aladdin collision
               {
                 controller->resetAladdinJumpingOn();
               }
             }, NULL, NULL );

  new State( stateManager, "puff",
             [=] {
               // animation effect
               {
                 animator->setAction( "puff" );
               }

               // puff
               {
                 timer->start( 0.3f );
               }
             }, [=]( float dt ) {
               // puff
               {
                 if ( timer->isDone() ) {
                   controller->puffSaliva( 90.0f, -10.0f );
                   timer->start( 10.f );
                 }
               }
             }, NULL );

  new StateTransition( stateManager, "idle", "puff", [=] {
    return controller->isAladdinJumpingOn();
  } );

  new StateTransition( stateManager, "puff", "idle", [=] {
    return !animator->isPlaying();
  } );
}
