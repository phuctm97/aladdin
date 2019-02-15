#include "SfxControllerPrefab.h"
#include "../app/MyAppData.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(SfxControllerPrefab, ala::PrefabV2)

void SfxControllerPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  const auto gameManager = GameManager::get();

  const auto myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));

  const auto stateManager = new StateManager( object, "default" );

  new State( stateManager, "default", [=] {
               const auto& objects = gameManager->getAllObjects();
               for ( const auto o : objects ) {
                 const auto& audioSources = o->getAllComponentTs<AudioSource>();

                 for ( const auto audioSource : audioSources ) {
                   if ( audioSource->getName() == "M" ) {
                     audioSource->setActive( myAppData->isMusicOn() );
                   }
                   else {
                     audioSource->setActive( myAppData->isSfxOn() );
                   }
                 }
               }
             },
             [=]( float dt ) { object->release(); }, NULL );
}
