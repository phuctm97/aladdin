#include "CharcoalBurnerPrefab.h"
#include "../Define.h"
#include "../scripts/CharcoalBurnerController.h"
#include "../app/MyAppData.h"

USING_NAMESPACE_ALA;

void CharcoalBurnerPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto width = nextFloat( argsStream );

  // constants
  const auto gameManager = GameManager::get();
  const auto myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));
  const auto flamePrefab = gameManager->getPrefab( "Flame" );

  // components
  const auto coalAudio = new AudioSource( object, "Fire From Coal.wav" );
  coalAudio->setActive( myAppData->isSfxOn() );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC, 0 );

  const auto collider = new Collider( object, true, Vec2(), Size( width, 4 ) );
  collider->setTag( CHARCOAL_BURNER_TAG );
  collider->ignoreTag( CHARCOAL_BURNER_TAG );
  collider->ignoreTag( GROUND_TAG );
  collider->ignoreTag( APPLE_TAG );

  const auto stateManager = new StateManager( object, "nothing" );

  const auto controller = new CharcoalBurnerController( object );

  // helpers
  const auto timer = new Timer( object );

  const auto transform = object->getTransform();

  // collider renderers
  //    new ColliderRenderer( collider );

  // flags
  const auto burnerFlags = COLLIDE_ENEMY_FLAG | COLLIDE_ALADDIN_FLAG | STATIC_FLAG;
  collider->setFlags( burnerFlags );
  collider->ignoreIfHasAnyFlags( STATIC_FLAG );

  // configurations
  object->setTag( CHARCOAL_BURNER_TAG );
  object->setLayer( "Debug" );

  // states
  new State( stateManager, "nothing",
             NULL, NULL, NULL );

  new State( stateManager, "fire",
             [=] {
               timer->start( 0 );
             },
             [=]( float dt ) {
               if ( timer->isDone() ) {
                 const auto firePosition = Vec2( controller->getFiringX(), transform->getPositionY() + 21 );
                 flamePrefab->instantiate( firePosition );
                 timer->start( 0.4f );
               }
               // audio
               {
                 if ( !coalAudio->isPlaying() ) {
                   coalAudio->play();
                 }
               }
             }, NULL );

  new StateTransition( stateManager, "nothing", "fire", [=] {
    return controller->isTouchingAladdin();
  } );

  new StateTransition( stateManager, "fire", "nothing", [=] {
    return !controller->isTouchingAladdin();
  } );
}
