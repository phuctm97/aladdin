#include "HandEnemyPrefab.h"
#include "../scripts/HandEnemyController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(HandEnemyPrefab, ala::PrefabV2)

void HandEnemyPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto dir = nextChar( argsStream );
  const auto zoneWidth = nextFloat( argsStream );
  const auto zoneHeight = nextFloat( argsStream );
  const auto zoneOffsetX = nextFloat( argsStream );
  const auto zoneOffsetY = nextFloat( argsStream );

  // constants
  const auto gameManager = GameManager::get();

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "civilian_enemies.png" );

  const auto animator = new Animator( object, "throw", "civilian_enemies.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2( 0, 5 ), Size( 30, 30 ), 1, 0, "Body" );
  collider->setTag( ENEMY_TAG );
  collider->ignoreTag( ENEMY_TAG );
  collider->ignoreTag( ALADDIN_TAG );
  collider->ignoreTag( GROUND_TAG );

  const auto zoneCollider = new Collider( object, true, Vec2( zoneOffsetX, zoneOffsetY ), Size( zoneWidth, zoneHeight ),
                                          1, 0, "Zone" );
  zoneCollider->ignoreTag( ENEMY_TAG );
  zoneCollider->ignoreTag( GROUND_TAG );

  const auto stateManager = new StateManager( object, "hide" );

  const auto direction = new DirectionController( object, true, 1 );
  if ( dir == 'L' ) direction->setLeft();
  else if ( dir == 'R' ) direction->setRight();

  const auto controller = new HandEnemyController( object );

  // helpers
  const auto timer = new Timer( object );

  const auto transform = object->getTransform();

  // collider renderers
  new ColliderRenderer( collider );

  new ColliderRenderer( zoneCollider );

  // configurations
  object->setTag( ENEMY_TAG );
  object->setLayer( "Mass Character" );

  // states
  new State( stateManager, "hide",
             [=] {
               // animation effect
               {
                 spriteRenderer->setVisible( false );
               }

               // collision 
               {
                 collider->setActive( false );
               }
             }, NULL, NULL );

  new State( stateManager, "throw_vase",
             [=] {
               // animation effect
               {
                 spriteRenderer->setVisible( true );
                 animator->setAction( "throw" );
               }

               // collision
               {
                 collider->setActive( true );
               }

               // throw
               {
                 timer->start( 0.68f );
               }
             },
             [=]( float dt ) {
               // throw 
               {
                 if ( timer->isDone() ) {
                   controller->throwVase( 0.0f, -30.0f );
                   timer->start( 10.f );
                 }
               }
             }, NULL );

  new StateTransition( stateManager, "hide", "throw_vase", [=] {
    return controller->isAladdinInZone();
  } );

  new StateTransition( stateManager, "throw_vase", "hide", [=] {
    return !animator->isPlaying();
  } );
}
