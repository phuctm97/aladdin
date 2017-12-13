#include "MenuScene.h"

USING_NAMESPACE_ALA;

void MenuScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();
  const auto input = Input::get();

  // initial objects
  const auto background = new GameObject( this );
  background->setLayer( "Background" );
  new SpriteRenderer( background, "cutscenes.png" );
  new Animator( background, "cutscene_1", "cutscenes.anm" );

  const auto title = new GameObject( this );
  background->setLayer( "Sub Background" );
  new SpriteRenderer( title, "title.png" );
  title->getTransform()->setPositionY( 59 );

  const auto agrabahMarket = new GameObject( this, "Menu 1" );
  agrabahMarket->setLayer( "Sub Background" );
  const auto agrabahMarketText = new BitmapText( agrabahMarket, "font_one.png", "one.fnt" );
  agrabahMarketText->setText( "AGRABAH MARKET" );
  agrabahMarketText->setCharacterAlignment( BitmapText::TOP );
  agrabahMarketText->setTextAlignment( BitmapText::LEFT );
  agrabahMarketText->setCharacterSpacing( 0.75f );
  agrabahMarket->getTransform()->setPosition( -51, 0 );

  const auto jafarQuarters = new GameObject( this, "Menu 2" );
  jafarQuarters->setLayer( "Sub Background" );
  const auto jafarQuartersText = new BitmapText( jafarQuarters, "font_one.png", "one.fnt" );
  jafarQuartersText->setText( "JAFAR QUARTERS" );
  jafarQuartersText->setCharacterAlignment( BitmapText::TOP );
  jafarQuartersText->setTextAlignment( BitmapText::LEFT );
  jafarQuartersText->setCharacterSpacing( 0.75f );
  jafarQuarters->getTransform()->setPosition( -51, -18 );

  const auto exit = new GameObject( this, "Menu 3" );
  exit->setLayer( "Sub Background" );
  const auto exitText = new BitmapText( exit, "font_one.png", "one.fnt" );
  exitText->setText( "EXIT" );
  exitText->setCharacterAlignment( BitmapText::TOP );
  exitText->setTextAlignment( BitmapText::LEFT );
  exitText->setCharacterSpacing( 0.75f );
  exit->getTransform()->setPosition( -51, -36 );

  const auto licenseOne = new GameObject( this );
  licenseOne->setLayer( "Sub Background" );
  const auto licenseOneText = new BitmapText( licenseOne, "font_one.png", "one.fnt" );
  licenseOneText->setText( "(C) 1993 SEGA (C) 1993 VIRGIN GAMES" );
  licenseOneText->setCharacterAlignment( BitmapText::TOP );
  licenseOneText->setCharacterSpacing( 0.75f );
  licenseOne->getTransform()->setPosition( 0, -75 );

  const auto licenseTwo = new GameObject( this );
  licenseTwo->setLayer( "Sub Background" );
  const auto licenseTwoText = new BitmapText( licenseTwo, "font_one.png", "one.fnt" );
  licenseTwoText->setText( "(C) 1993 THE WALT DISNEY COMPANY" );
  licenseTwoText->setCharacterAlignment( BitmapText::TOP );
  licenseTwoText->setCharacterSpacing( 0.75f );
  licenseTwo->getTransform()->setPosition( 0, -92 );

  const auto menuSelect = new GameObject( this );
  menuSelect->setLayer( "UI" );
  new SpriteRenderer( menuSelect, "menu_select.png" );
  const auto menuSelectActionManager = new ActionManager( menuSelect );
  const auto menuSelectTransform = menuSelect->getTransform();
  const auto menuSelectStateManager = new StateManager( menuSelect, "menu_1" );

  new State( menuSelectStateManager, "menu_1",
             [=] {
               menuSelectTransform->setPosition( -84, agrabahMarket->getTransform()->getPositionY() - 8 );

               menuSelectActionManager->stopAll();
               menuSelectActionManager->play( new Repeat(
                 new Sequence( {
                   new MoveBy( Vec2( 10, 0 ), 0.175f ),
                   new MoveBy( Vec2( -10, 0 ), 0.175f ),
                 } )
               ) );
             },
             [=]( float dt ) {
               if ( input->getKeyDown( ALA_KEY_A )
                 || input->getKeyDown( ALA_KEY_S )
                 || input->getKeyDown( ALA_KEY_D ) ) {
                 Logger( "MenuScene" ).info( "To Argrabah Market Scene" );
               }
             },
             NULL );

  new State( menuSelectStateManager, "menu_2",
             [=] {
               menuSelectTransform->setPosition( -84, jafarQuarters->getTransform()->getPositionY() - 8 );

               menuSelectActionManager->stopAll();
               menuSelectActionManager->play( new Repeat(
                 new Sequence( {
                   new MoveBy( Vec2( 10, 0 ), 0.175f ),
                   new MoveBy( Vec2( -10, 0 ), 0.175f ),
                 } )
               ) );
             },
             [=]( float dt ) {
               if ( input->getKeyDown( ALA_KEY_A )
                 || input->getKeyDown( ALA_KEY_S )
                 || input->getKeyDown( ALA_KEY_D ) ) {
                 Logger( "MenuScene" ).info( "To Jafar's Quarters Scene" );
               }
             },
             NULL );

  new State( menuSelectStateManager, "menu_3",
             [=] {
               menuSelectTransform->setPosition( -84, exit->getTransform()->getPositionY() - 8 );

               menuSelectActionManager->stopAll();
               menuSelectActionManager->play( new Repeat(
                 new Sequence( {
                   new MoveBy( Vec2( 10, 0 ), 0.175f ),
                   new MoveBy( Vec2( -10, 0 ), 0.175f ),
                 } )
               ) );
             },
             [=]( float dt ) {
               if ( input->getKeyDown( ALA_KEY_A )
                 || input->getKeyDown( ALA_KEY_S )
                 || input->getKeyDown( ALA_KEY_D ) ) {
                 Logger( "MenuScene" ).info( "Exit" );
               }
             }, NULL );

  new StateTransition( menuSelectStateManager, "menu_1", "menu_2", [=] {
    return input->getKeyDown( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( menuSelectStateManager, "menu_2", "menu_3", [=] {
    return input->getKeyDown( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( menuSelectStateManager, "menu_2", "menu_1", [=] {
    return input->getKeyDown( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( menuSelectStateManager, "menu_3", "menu_2", [=] {
    return input->getKeyDown( ALA_KEY_UP_ARROW );
  } );
}
