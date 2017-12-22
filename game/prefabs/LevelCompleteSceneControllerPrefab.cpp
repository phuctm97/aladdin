#include "LevelCompleteSceneControllerPrefab.h"
#include "../app/MyAppData.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(LevelCompleteSceneControllerPrefab, ala::PrefabV2)

void LevelCompleteSceneControllerPrefab::doInstantiate( ala::GameObject* object,
                                                        std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();

  const auto myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));

  const auto sceneFadeOutTransitionPrefab = gameManager->getPrefabV2( "Scene Fade Out Transition" );

  // components
  const auto sceneAudio = new AudioSource( object, "Level Complete.wav" );

  const auto timer = new Timer( object );

  const auto stateManager = new StateManager( object, "default" );

  // states
  new State( stateManager, "default",
             [=] {
               // animation effect
               {
                 timer->start( 5.7f );
               }

               // audio
               {
                 sceneAudio->play();
               }
             },
             [=]( float dt ) {
               if ( timer->isDone() ) {
                 if ( myAppData->getCurrentLevel() < myAppData->getNumberOfLevels() ) {
                   myAppData->setCurrentLevel( myAppData->getCurrentLevel() + 1 );
                   myAppData->setCurrentCheckpoint( 0 );

                   std::stringstream args;
                   args << 0.5 << ' ' << myAppData->getSceneName( myAppData->getCurrentLevel() ) << '\n' << 1;
                   sceneFadeOutTransitionPrefab->instantiateWithArgs( args.str() );
                 }
                 else {
                   // TODO: to end scene
                   sceneFadeOutTransitionPrefab->instantiateWithArgs( "0.5 menu.scene\n0" );
                 }
               }
             },
             NULL );
}
