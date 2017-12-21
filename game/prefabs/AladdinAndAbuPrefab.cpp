#include "AladdinAndAbuPrefab.h"
#include "../scripts/DirectionController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AladdinAndAbuPrefab, ala::PrefabV2)

void AladdinAndAbuPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto dir = nextChar( argsStream );
  const auto speed = nextFloat( argsStream );

  // constants
  const auto gameManager = GameManager::get();

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "aladdin.png" );

  const auto animator = new Animator( object, "happy_run", "aladdin.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_DYNAMIC, 0 );
  body->setVelocity( Vec2( speed, 0 ) );

  const auto direction = new DirectionController( object, false );
  if ( dir == 'L' ) direction->setLeft();
  else if ( dir == 'R' ) direction->setRight();

  const auto abu = new GameObject( object );

  const auto abuSpriteRenderer = new SpriteRenderer( abu, "abu.png" );

  const auto abuAnimator = new Animator( abu, "run", "abu.anm" );

  abu->getTransform()->setPosition( -48, -12 );
}
