#include "BigTextPrefab.h"

USING_NAMESPACE_ALA;

void BigTextPrefab::doInstantiate( ala::GameObject* object ) const {
  const auto transform = new RectTransform( object, Rect( Vec2( 0, 0 ),
                                                          GameManager::get()->getVisibleWidth(),
                                                          GameManager::get()->getVisibleHeight() ) );
  const auto text = new Text( object, FontInfo( ALA_FONT_WEIGHT_BOLD, 100 ), "aladdin.ttf", Color( 255, 255, 255 ) );
}
