#include "TextExamplePrefab.h"

void TextExamplePrefab::doInstantiate( ala::GameObject* object ) const {
  // layer
  object->setLayer( "UI" );

  // create rect transform for ui element rendering
  auto transform = new ala::RectTransform( object, ala::Rect(
                                             ala::Vec2( -ala::GameManager::get()->getVisibleWidth() / 2,
                                                        ala::GameManager::get()->getVisibleHeight() / 2 ),
                                             ala::Size( ala::GameManager::get()->getVisibleWidth(),
                                                        ala::GameManager::get()->getVisibleHeight() ) ) );

  // text component
  auto text = new ala::Text( object, ala::FontInfo( ALA_FONT_WEIGHT_BOLD, 80, false ), "crackman.ttf" );

  text->setText( "Aladdin" );
  text->setTextColor( ala::Color( 255, 255, 255 ) );

  transform->setPosition( 0, 50 );
}
