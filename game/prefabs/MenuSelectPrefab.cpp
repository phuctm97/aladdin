#include "MenuSelectPrefab.h"
#include "../scenes/AgrabahMarketScene.h"

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

  new SpriteRenderer( object, "items.png" );
  new Animator( object, "menu_select", "items.anm" );
  const auto menuSelectActionManager = new ActionManager( object );
  const auto menuSelectStateManager = new StateManager( object, "menu_1" );
  const auto menuSelectTransform = object->getTransform();

  new State( menuSelectStateManager, "menu_1",
             [=] {
               menuSelectTransform->setPosition( -84, menuOneY - 8 );

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
                 gameManager->replaceScene( new AgrabahMarketScene() );
               }
             },
             NULL );

  new State( menuSelectStateManager, "menu_2",
             [=] {
               menuSelectTransform->setPosition( -84, menuTwoY - 8 );

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
               menuSelectTransform->setPosition( -84, menuThreeY - 8 );

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
                 GameManager::get()->exit();
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
