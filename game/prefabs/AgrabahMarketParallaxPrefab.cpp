#include "AgrabahMarketParallaxPrefab.h"
#include "../scripts/ParallaxController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AgrabahMarketParallaxPrefab, ala::PrefabV2)

void AgrabahMarketParallaxPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "agrabah_market_parallax.png" );

  const auto animator = new Animator( object, "1", "agrabah_market_parallax.anm" );

  const auto parallax = new ParallaxController( object );
  parallax->setOffset( Vec2( 0, -68 ) );

  float layerOffsets[] = { 43, 62, 73, 84, 103, 130, 157, 176 };
  const int numberOfLayers = sizeof(layerOffsets) / sizeof(float);

  for ( auto i = 0; i < numberOfLayers; i++ ) {
    const auto layer = new GameObject( object );

    std::stringstream stringBuilder;
    stringBuilder << i + 2;

    new SpriteRenderer( layer, "agrabah_market_parallax.png" );
    new Animator( layer, stringBuilder.str(), "agrabah_market_parallax.anm" );
    layer->getTransform()->setPosition( Vec2( 0, layerOffsets[i] ) );
    layer->setLayer( "Background" );
  }

  object->setLayer( "Background" );
}
