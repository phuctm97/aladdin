#include "JafarPalaceParallaxPrefab.h"
#include "../scripts/SingleLayerParallaxController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarPalaceParallaxPrefab, ala::PrefabV2)

void JafarPalaceParallaxPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // components
  const auto spriteRenderer = new SpriteRenderer( object, "jafar_palace_parallax.png" );

  const auto controller = new SingleLayerParallaxController( object );
  controller->setCoef( Vec2( 0.6f, 0.6f ) );

  // configurations
  object->getTransform()->setScale( Vec2( 1.25f, 1.25f ) );

  object->setLayer( "Parallax" );
}
