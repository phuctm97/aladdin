#include"GenieLampPrefab.h"
#include"../Define.h"
#include "../scripts/CollisionTracker.h"
#include "../scripts/SceneInfoQuerier.h"
#include "../scripts/GuardController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(GenieLampPrefab, ala::PrefabV2)

void GenieLampPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto smallFireworkPrefab = gameManager->getPrefabV2( "Small Firework" );

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "items.png" );

  const auto animator = new Animator( object, "idle_lamp", "items.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 24, 15 ) );
  collider->setTag( LAMP_TAG );
  collider->ignoreTag( APPLE_TAG );
  collider->ignoreTag( ENEMY_TAG );

  const auto stateManager = new StateManager( object, "static" );

  const auto collision = new CollisionTracker( object );

  // helpers
  const auto sceneInfo = new SceneInfoQuerier( object );

  const auto transform = object->getTransform();


  // collider renderes
  new ColliderRenderer( collider );

  // configurations
  object->setTag( LAMP_TAG );
  object->setLayer( "Foreground" );

  // states
  new State( stateManager, "static", NULL,
             [=]( float dt ) {
               if ( collision->collidedWithObjectTag( ALADDIN_TAG ) ) {
                 smallFireworkPrefab->instantiate( transform->getPosition() );
                 object->release();

                 // destroy enemy
                 const auto& enemies = sceneInfo->getAllEnemiesInCamera();
                 for ( const auto& enemy : enemies ) {
                   const auto guardController = enemy->getComponentT<GuardController>();
                   if ( guardController != NULL ) {
                     guardController->onDie( 2 );
                   }
                   else {
                     enemy->release();
                   }
                 }
               }
             }, NULL );
}
