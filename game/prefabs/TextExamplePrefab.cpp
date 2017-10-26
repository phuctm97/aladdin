#include "TextExamplePrefab.h"
#include "../scripts/BallController.h"
#include "ui/Text.h"
#include "ui/RectTransform.h"

void TextExamplePrefab::doInstantiate(ala::GameObject* object) {
  new ala::RectTransform(object, ala::Rect(ala::Vec2(-ala::GameManager::get()->getScreenWidth()/2, ala::GameManager::get()->getScreenHeight()/2), ala::Size(ala::GameManager::get()->getScreenWidth(), ala::GameManager::get()->getScreenHeight())));
  auto text = new ala::Text(object, ala::FontInfo(), static_cast <ala::Font*> (ala::GameManager::get()->getResource("Sail-Regular")));
  text->setText("Hello");
  text->setFontInfo(ala::FontInfo(ALA_FONT_WEIGHT_BOLD, 20, true));
  object->getTransform()->setPosition(200,200);
  object->getComponentT<ala::RectTransform>()->setScale(3);
}
