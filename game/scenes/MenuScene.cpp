#include "MenuScene.h"

USING_NAMESPACE_ALA;

void MenuScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();

  // initial objects
  const auto background = new GameObject( this );
  new SpriteRenderer( background, "cutscenes.png" );
  new Animator( background, "cutscene_1", "cutscenes.anm" );

  const auto textPressStart = gameManager->getPrefab( "Normal Text" )->instantiate();
  textPressStart->getTransform()->setPosition( Vec2( -50, -50 ) );
  textPressStart->getComponentT<Text>()->setText( "PRESS START" );
  textPressStart->getComponentT<Text>()->setTextColor( Color( 255, 187, 49 ) );

}
