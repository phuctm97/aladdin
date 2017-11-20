#include "NormalTextPrefab.h"

USING_NAMESPACE_ALA;

void NormalTextPrefab::doInstantiate( ala::GameObject* object ) const {
  const auto transform = new RectTransform( object, Rect( Vec2( 0, 0 ),
                                                          GameManager::get()->getVisibleWidth(),
                                                          GameManager::get()->getVisibleHeight() ), NULL, "rect" );
  const auto text = new Text( object, FontInfo( ALA_FONT_WEIGHT_BOLD, 20 ), "arcade.ttf", Color( 255, 255, 255 ) );
}
