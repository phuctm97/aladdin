#include "SpritePrefab.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(SpritePrefab, ala::PrefabV2)

void SpritePrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto spriteName = nextString( argsStream );
  const auto hasAnimator = nextBool( argsStream );
  const auto animationName = nextString( argsStream );
  const auto actionName = nextString( argsStream );

  // components
  new SpriteRenderer( object, spriteName );

  if ( hasAnimator ) {
    new Animator( object, actionName, animationName );
  }
}
