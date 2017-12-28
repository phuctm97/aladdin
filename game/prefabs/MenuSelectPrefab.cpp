#include "MenuSelectPrefab.h"
#include "../scenes/AutoLoadScene.h"
#include "../app/MyAppData.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(MenuSelectPrefab, ala::PrefabV2)

void MenuSelectPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto menuOneY = nextFloat( argsStream );
  const auto menuTwoY = nextFloat( argsStream );
  const auto menuThreeY = nextFloat( argsStream );
  const auto menuFourY = nextFloat( argsStream );

  // constants
  const auto gameManager = GameManager::get();
  const auto input = Input::get();
  const auto myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));
  const auto sceneFadeOutTransitionPrefab = gameManager->getPrefabV2( "Scene Fade Out Transition" );

  std::vector<BitmapText*> menuTexts;
  for ( int i = 0; i < 11; i++ ) {
    std::stringstream menuNameBuilder;
    menuNameBuilder << "Menu " << i + 1;

    const auto menu = gameManager->getObjectByName( menuNameBuilder.str() );
    menuTexts.push_back( menu->getComponentT<BitmapText>() );
  }
  const auto sfxMenu = menuTexts[8];
  const auto musicMenu = menuTexts[9];
  const auto difficultyMenu = menuTexts[10];

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "items.png" );

  const auto animator = new Animator( object, "menu_select", "items.anm" );

  const auto menuChangeAudio = new AudioSource( object, "Menu Change.wav" );

  const auto sceneAudio = new AudioSource( object, "A Whole New World.wav" );

  const auto actionManager = new ActionManager( object );

  const auto stateManager = new StateManager( object, "initial" );

  // helpers
  const auto transform = object->getTransform();

  new State( stateManager, "initial",
             [=] {
               // reset app data
               {
                 myAppData->setCurrentLevel( 1 );
                 myAppData->setCurrentCheckpoint( 0 );
                 myAppData->setAladdinLives( 3 );
                 myAppData->setAladdinApples( 5 );
                 myAppData->setRetryTimes( 1 );
               }

               // audio
               {
                 sceneAudio->play();
               }
             }, NULL, NULL );

  new State( stateManager, "menu_1",
             [=] {
               // animation effect
               {
                 transform->setPosition( -84, menuOneY - 8 );

                 actionManager->stopAll();
                 actionManager->play( new Repeat(
                   new Sequence( {
                     new MoveBy( Vec2( 10, 0 ), 0.175f ),
                     new MoveBy( Vec2( -10, 0 ), 0.175f ),
                   } )
                 ) );
               }

               // audio
               {
                 if ( stateManager->getPreviousStateName() != "initial" ) {
                   menuChangeAudio->play();
                 }
               }

               // reset menu
               {
                 for ( const auto menuText : menuTexts ) menuText->setVisible( false );
                 for ( size_t i = 0; i < 4; i++ ) {
                   menuTexts[i]->setVisible( true );
                 }
               }
             },
             [=]( float dt ) {
               if ( input->getKeyDown( ALA_KEY_A )
                 || input->getKeyDown( ALA_KEY_S )
                 || input->getKeyDown( ALA_KEY_D ) ) {
                 myAppData->setCurrentLevel( 1 );
                 sceneFadeOutTransitionPrefab->instantiateWithArgs( "0.5 agrabah_market.scene\n1" );
               }
             },
             NULL );

  new State( stateManager, "menu_2",
             [=] {
               // animation effect
               {
                 transform->setPosition( -84, menuTwoY - 8 );

                 actionManager->stopAll();
                 actionManager->play( new Repeat(
                   new Sequence( {
                     new MoveBy( Vec2( 10, 0 ), 0.175f ),
                     new MoveBy( Vec2( -10, 0 ), 0.175f ),
                   } )
                 ) );
               }

               // audio
               {
                 if ( stateManager->getPreviousStateName() != "initial" ) {
                   menuChangeAudio->play();
                 }
               }
             },
             [=]( float dt ) {
               if ( input->getKeyDown( ALA_KEY_A )
                 || input->getKeyDown( ALA_KEY_S )
                 || input->getKeyDown( ALA_KEY_D ) ) {
                 myAppData->setCurrentLevel( 2 );
                 sceneFadeOutTransitionPrefab->instantiateWithArgs( "0.5 jafar_palace.scene\n1" );
               }
             },
             NULL );

  new State( stateManager, "menu_3",
             [=] {
               // animation effect
               {
                 transform->setPosition( -84, menuThreeY - 8 );

                 actionManager->stopAll();
                 actionManager->play( new Repeat(
                   new Sequence( {
                     new MoveBy( Vec2( 10, 0 ), 0.175f ),
                     new MoveBy( Vec2( -10, 0 ), 0.175f ),
                   } )
                 ) );
               }

               // audio
               {
                 if ( stateManager->getPreviousStateName() != "initial" ) {
                   menuChangeAudio->play();
                 }
               }
             },
             NULL, NULL );

  new State( stateManager, "menu_4",
             [=] {
               // animation effect
               {
                 transform->setPosition( -84, menuFourY - 8 );

                 actionManager->stopAll();
                 actionManager->play( new Repeat(
                   new Sequence( {
                     new MoveBy( Vec2( 10, 0 ), 0.175f ),
                     new MoveBy( Vec2( -10, 0 ), 0.175f ),
                   } )
                 ) );
               }

               // audio
               {
                 if ( stateManager->getPreviousStateName() != "initial" ) {
                   menuChangeAudio->play();
                 }
               }
             },
             [=]( float dt ) {
               if ( input->getKeyDown( ALA_KEY_A )
                 || input->getKeyDown( ALA_KEY_S )
                 || input->getKeyDown( ALA_KEY_D ) ) {
                 GameManager::get()->exit();
               }
             }, NULL );

  new State( stateManager, "menu_5",
             [=] {
               // animation effect
               {
                 transform->setPosition( -84, menuOneY - 8 );

                 actionManager->stopAll();
                 actionManager->play( new Repeat(
                   new Sequence( {
                     new MoveBy( Vec2( 10, 0 ), 0.175f ),
                     new MoveBy( Vec2( -10, 0 ), 0.175f ),
                   } )
                 ) );
               }

               // audio
               {
                 if ( stateManager->getPreviousStateName() != "initial" ) {
                   menuChangeAudio->play();
                 }
               }

               // reset menu
               {
                 for ( const auto menuText : menuTexts ) menuText->setVisible( false );
                 for ( size_t i = 4; i < menuTexts.size(); i++ ) {
                   menuTexts[i]->setVisible( true );
                 }
               }
             },
             [=]( float dt ) {
               // switch
               {
                 if ( input->getKeyDown( ALA_KEY_A ) || input->getKeyDown( ALA_KEY_S ) || input->getKeyDown( ALA_KEY_D )
                 ) {
                   myAppData->setSfxOn( !myAppData->isSfxOn() );
                   menuChangeAudio->play();
                 }
               }

               // display 
               {
                 if ( myAppData->isSfxOn() ) {
                   sfxMenu->setText( "ON" );
                 }
                 else {
                   sfxMenu->setText( "OFF" );
                 }
               }
             },
             NULL );

  new State( stateManager, "menu_6",
             [=] {
               // animation effect
               {
                 transform->setPosition( -84, menuTwoY - 8 );

                 actionManager->stopAll();
                 actionManager->play( new Repeat(
                   new Sequence( {
                     new MoveBy( Vec2( 10, 0 ), 0.175f ),
                     new MoveBy( Vec2( -10, 0 ), 0.175f ),
                   } )
                 ) );
               }

               // audio
               {
                 if ( stateManager->getPreviousStateName() != "initial" ) {
                   menuChangeAudio->play();
                 }
               }
             },
             [=]( float dt ) {
               // switch
               {
                 if ( input->getKeyDown( ALA_KEY_A ) || input->getKeyDown( ALA_KEY_S ) || input->getKeyDown( ALA_KEY_D )
                 ) {
                   myAppData->setMusicOn( !myAppData->isMusicOn() );
                   menuChangeAudio->play();
                 }
               }

               // display 
               {
                 if ( myAppData->isMusicOn() ) {
                   musicMenu->setText( "ON" );
                 }
                 else {
                   musicMenu->setText( "OFF" );
                 }
               }
             },
             NULL );

  new State( stateManager, "menu_7",
             [=] {
               // animation effect
               {
                 transform->setPosition( -84, menuThreeY - 8 );

                 actionManager->stopAll();
                 actionManager->play( new Repeat(
                   new Sequence( {
                     new MoveBy( Vec2( 10, 0 ), 0.175f ),
                     new MoveBy( Vec2( -10, 0 ), 0.175f ),
                   } )
                 ) );
               }

               // audio
               {
                 if ( stateManager->getPreviousStateName() != "initial" ) {
                   menuChangeAudio->play();
                 }
               }
             },
             [=]( float dt ) {
               // switch
               {
                 if ( input->getKeyDown( ALA_KEY_A ) || input->getKeyDown( ALA_KEY_S ) || input->getKeyDown( ALA_KEY_D )
                 ) {
                   myAppData->setDifficulty( (myAppData->getDifficulty() + 1) % 3 );
                   menuChangeAudio->play();
                 }
               }

               // display 
               {
                 switch ( myAppData->getDifficulty() ) {
                 case 0: difficultyMenu->setText( "EASY" );
                   break;
                 case 1: difficultyMenu->setText( "NORMAL" );
                   break;
                 case 2: difficultyMenu->setText( "HARD" );
                   break;
                 default: break;
                 }
               }
             }, NULL );

  new State( stateManager, "menu_8",
             [=] {
               // animation effect
               {
                 transform->setPosition( -84, menuFourY - 8 );

                 actionManager->stopAll();
                 actionManager->play( new Repeat(
                   new Sequence( {
                     new MoveBy( Vec2( 10, 0 ), 0.175f ),
                     new MoveBy( Vec2( -10, 0 ), 0.175f ),
                   } )
                 ) );
               }

               // audio
               {
                 if ( stateManager->getPreviousStateName() != "initial" ) {
                   menuChangeAudio->play();
                 }
               }
             },
             NULL, NULL );

  new StateTransition( stateManager, "initial", "menu_1", [=] {
    return true;
  } );

  new StateTransition( stateManager, "menu_1", "menu_2", [=] {
    return input->getKeyDown( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "menu_2", "menu_1", [=] {
    return input->getKeyDown( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( stateManager, "menu_2", "menu_3", [=] {
    return input->getKeyDown( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "menu_3", "menu_2", [=] {
    return input->getKeyDown( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( stateManager, "menu_3", "menu_4", [=] {
    return input->getKeyDown( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "menu_4", "menu_3", [=] {
    return input->getKeyDown( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( stateManager, "menu_3", "menu_5", [=] {
    return input->getKeyDown( ALA_KEY_A ) || input->getKeyDown( ALA_KEY_S ) || input->getKeyDown( ALA_KEY_D );
  } );

  new StateTransition( stateManager, "menu_5", "menu_6", [=] {
    return input->getKeyDown( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "menu_6", "menu_5", [=] {
    return input->getKeyDown( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( stateManager, "menu_6", "menu_7", [=] {
    return input->getKeyDown( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "menu_7", "menu_6", [=] {
    return input->getKeyDown( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( stateManager, "menu_7", "menu_8", [=] {
    return input->getKeyDown( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "menu_8", "menu_7", [=] {
    return input->getKeyDown( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( stateManager, "menu_8", "menu_1", [=] {
    return input->getKeyDown( ALA_KEY_A ) || input->getKeyDown( ALA_KEY_S ) || input->getKeyDown( ALA_KEY_D );
  } );
}
