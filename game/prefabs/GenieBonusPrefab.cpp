#include "GenieBonusPrefab.h"
#include "../Define.h"
#include "../scripts/CollisionTracker.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(GenieBonusPrefab, ala::PrefabV2)

void GenieBonusPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto smallFireworkPrefab = gameManager->getPrefabV2( "Small Firework" );
  const auto minDelay = 1000;
  const auto maxDelay = 5000;

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "items.png" );
	  //audio
	const auto EatenSound = new AudioSource(object, "Wow!.wav");

  const auto animator = new Animator( object, "genie_bonus", "items.anm" );

  const auto actionManager = new ActionManager( object );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2( 0, -5 ), Size( 25, 35 ), 1, 0 );
  collider->setTag( BONUS_TAG );
  collider->ignoreTag( APPLE_TAG );
  collider->ignoreTag( ENEMY_TAG );

  const auto stateManager = new StateManager( object, "static" );

  const auto collision = new CollisionTracker( object );

  // helpers
  const auto timer = new Timer( object );

  const auto transform = object->getTransform();

  // collider renderers
  //  new ColliderRenderer( collider );

  // flags
  collider->setFlags( COLLIDE_ALADDIN_FLAG | STATIC_FLAG );
  collider->ignoreIfHasAnyFlags( STATIC_FLAG );

  // configurations
  object->setTag( BONUS_TAG );
  object->setLayer( "Foreground" );

  // states
  new State( stateManager, "static",
             [=] {
               // animation effect 
               {
                 actionManager->stopAll();
                 actionManager->play( new Repeat(
                   new Sequence( {
                     new MoveBy( Vec2( 0, 6 ), 0.5f ),
                     new MoveBy( Vec2( 0, -6 ), 0.5f )
                   } )
                 ) );
               }
             },
             [=]( float dt ) {
               // animation effect 
               {
                 if ( timer->isDone() ) {
                   animator->playFromStart();
                   timer->start( (rand() % (maxDelay - minDelay)) / 1000.0f );
                 }
               }

               // collision
               {
                 if ( collision->collidedWithObjectTag( ALADDIN_TAG ) ) {
                   smallFireworkPrefab->instantiate( transform->getPosition() );
					EatenSound->play();
                   object->release();
                 }
               }
             }, NULL );
}
