#include "CheckpointPrefab.h"
#include "../Define.h"
#include "../scripts/CheckpointController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(CheckpointPrefab, ala::PrefabV2)

void CheckpointPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto index = nextInt( argsStream );

  // constants
  const auto gameManager = GameManager::get();

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "items.png" );

  const auto animator = new Animator( object, "checkpoint_off", "items.anm" );

  const auto onAudio = new AudioSource( object, "Continue Point.wav" );

  const auto stateManager = new StateManager( object, "off" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 20, 30 ), 1, 0 );

  const auto controller = new CheckpointController( object, index );

  // helpers
  const auto transform = object->getTransform();

  // collider renderers
  new ColliderRenderer( collider );

  // flags
  collider->setFlags( COLLIDE_ALADDIN_FLAG | STATIC_FLAG );
  collider->ignoreIfHasAnyFlags( STATIC_FLAG );

  // configurations
  object->setLayer( "Mass Character" );

  // states
  new State( stateManager, "off",
             [=] {
               animator->setAction( "checkpoint_off" );
             }, NULL, NULL );

  new State( stateManager, "on",
             [=] {
               // animation effect
               {
                 animator->setAction( "checkpoint_on" );
               }

               // audio
               {
                 onAudio->play();
               }
             }, NULL, NULL );

  new StateTransition( stateManager, "off", "on", [=] {
    return controller->isChecked();
  } );
}
