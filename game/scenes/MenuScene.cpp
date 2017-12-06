#include "MenuScene.h"

USING_NAMESPACE_ALA;

void MenuScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();

  // initial objects
  const auto background = new GameObject( this );
  new SpriteRenderer( background, "cutscenes.png" );
  new Animator( background, "cutscene_1", "cutscenes.anm" );

  const auto textAladdin = gameManager->getPrefab( "Big Text" )->instantiate();
  textAladdin->getTransform()->setPosition( Vec2( 0, gameManager->getVisibleHeight() * 0.25f ) );
  textAladdin->getComponentT<Text>()->setText( "Aladdin" );
  textAladdin->getComponentT<Text>()->setTextColor( Color( 255, 187, 49 ) );

  const auto textPressStart = gameManager->getPrefab( "Normal Text" )->instantiate();
  textPressStart->getTransform()->setPosition( Vec2( gameManager->getVisibleWidth() * 0.33f, 0 ) );
  textPressStart->getComponentT<Text>()->setText( "PRESS START" );
  textPressStart->getComponentT<Text>()->setTextColor( Color( 255, 187, 49 ) );

  const auto textOptions = gameManager->getPrefab( "Normal Text" )->instantiate();
  textOptions->getTransform()->setPosition( Vec2( gameManager->getVisibleWidth() * 0.33f, -25 ) );
  textOptions->getComponentT<Text>()->setText( "OPTIONS" );
  textOptions->getComponentT<Text>()->setTextColor( Color( 255, 187, 49 ) );
}
