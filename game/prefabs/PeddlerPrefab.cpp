#include "PeddlerPrefab.h"
#include "../Define.h"
#include "../scripts/CollisionTracker.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PeddlerPrefab, ala::PrefabV2)

void PeddlerPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "peddler.png" );

  const auto animator = new Animator( object, "idle_1", "peddler.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 25, 50 ) );
  collider->ignoreTag( APPLE_TAG );

  const auto stateManager = new StateManager( object, "static" );

  const auto collisionTracker = new CollisionTracker( object );

  const auto child = new GameObject( object );

  const auto childSpriteRenderer = new SpriteRenderer( child, "peddler.png" );
  childSpriteRenderer->setVisible( false );

  const auto childAnimator = new Animator( child, "idle_1", "peddler.anm" );

  const auto childTransform = child->getTransform();
  childTransform->setPositionX( 50 );

  // helpers
  const auto transform = object->getTransform();

  // collider renderers
  new ColliderRenderer( collider );


  // configurations
  object->setLayer( "Mass Character" );

  // states
  new State( stateManager, "static",
             NULL,
             [=]( float dt ) {
               if ( collisionTracker->collidedWithObjectTag( ALADDIN_TAG ) && animator->getActionName() == "idle_1"
               ) {
                 animator->setAction( "pavilion_1" );
                 collider->release();
               }
               else if ( animator->getActionName() == "pavilion_1" ) {
                 if ( animator->getCurrentFrameIndex() == 24 ) {
                   childSpriteRenderer->setVisible( true );
                   childAnimator->setAction( "idle_2" );
                 }

                 if ( !animator->isPlaying() ) {
                   animator->setAction( "pavilion_2" );
                 }
               }
             }, NULL );
}
