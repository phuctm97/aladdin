#include "TextExamplePrefab.h"
#include "../scripts/BallController.h"
#include "ui/Text.h"

void TextExamplePrefab::doInstantiate(ala::GameObject* object) {
  auto text = new ala::Text(object, ala::FontInfo(), static_cast < ala::Font* > ( ala::GameManager::get ( ) -> getResource ( "Sail-Regular" ) ));
  text->setText("Day la font ^^ ~");
  text->setFontInfo(ala::FontInfo(ALA_FONT_WEIGHT_BOLD, 20, true));
}
