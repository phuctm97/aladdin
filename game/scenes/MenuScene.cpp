#include "MenuScene.h"
#include "AgrabahMarketScene.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(MenuScene, ala::Scene)

void MenuScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();

  // initial objects
  gameManager->getPrefabV2( "Sprite" )->instantiateWithArgs( "cutscenes.png 1 cutscenes.anm cutscene_1" )
             ->setLayer( "Background" );

  gameManager->getPrefabV2( "Sprite" )->instantiateWithArgs( "title.png 0" )
             ->setLayer( "Second Background" )
             ->getTransform()->setPositionY( 59 );

  gameManager->getPrefabV2( "Bitmap Text" )->instantiateWithArgs(
               "font_one.png one.fnt AGRABAH MARKET\n T L 0.75", "Menu 1" )
             ->setLayer( "Second Background" )
             ->getTransform()->setPosition( -51, 0 );

  gameManager->getPrefabV2( "Bitmap Text" )->instantiateWithArgs(
               "font_one.png one.fnt JAFAR QUARTERS\n T L 0.75", "Menu 2" )
             ->setLayer( "Second Background" )
             ->getTransform()->setPosition( -51, -18 );

  gameManager->getPrefabV2( "Bitmap Text" )->instantiateWithArgs(
               "font_one.png one.fnt EXIT\n T L 0.75", "Menu 3" )
             ->setLayer( "Second Background" )
             ->getTransform()->setPosition( -51, -36 );

  gameManager->getPrefabV2( "Bitmap Text" )->instantiateWithArgs(
               "font_one.png one.fnt (C) 1993 SEGA (C) 1993 VIRGIN GAMES\n T C 0.75" )
             ->setLayer( "Second Background" )
             ->getTransform()->setPosition( 0, -75 );

  gameManager->getPrefabV2( "Bitmap Text" )->instantiateWithArgs(
               "font_one.png one.fnt (C) 1993 THE WALT DISNEY COMPANY\n T C 0.75" )
             ->setLayer( "Second Background" )
             ->getTransform()->setPosition( 0, -92 );

  gameManager->getPrefabV2( "Menu Select" )->instantiateWithArgs( "0 -18 -36" )
             ->setLayer( "UI" );
}
