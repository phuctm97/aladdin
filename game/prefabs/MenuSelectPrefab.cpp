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

  // constants
  const auto gameManager = GameManager::get();
  const auto input = Input::get();
  const auto myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));
  const auto sceneFadeOutTransitionPrefab = gameManager->getPrefabV2( "Scene Fade Out Transition" );

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
             },
             [=]( float dt ) {
               if ( input->getKeyDown( ALA_KEY_A )
                 || input->getKeyDown( ALA_KEY_S )
                 || input->getKeyDown( ALA_KEY_D ) ) {
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
             [=]( float dt ) {
               if ( input->getKeyDown( ALA_KEY_A )
                 || input->getKeyDown( ALA_KEY_S )
                 || input->getKeyDown( ALA_KEY_D ) ) {
                 GameManager::get()->exit();
               }
             }, NULL );

  new StateTransition( stateManager, "initial", "menu_1", [=] {
    return true;
  } );

  new StateTransition( stateManager, "menu_1", "menu_2", [=] {
    return input->getKeyDown( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "menu_2", "menu_3", [=] {
    return input->getKeyDown( ALA_KEY_DOWN_ARROW );
  } );

  new StateTransition( stateManager, "menu_2", "menu_1", [=] {
    return input->getKeyDown( ALA_KEY_UP_ARROW );
  } );

  new StateTransition( stateManager, "menu_3", "menu_2", [=] {
    return input->getKeyDown( ALA_KEY_UP_ARROW );
  } );
}
