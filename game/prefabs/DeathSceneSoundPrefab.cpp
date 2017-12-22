#include "DeathSceneSoundPrefab.h"
#include"../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(DeathSceneSoundPrefab, ala::PrefabV2)

void DeathSceneSoundPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  const auto gameManager = GameManager::get();

  const auto stateManager = new StateManager( object, "static" );

  const auto abuAudio = new AudioSource( object, "Abu Waving.wav" );

  const auto bellAudio = new AudioSource( object, "Boxing Bell.wav" );

  const auto timer1 = new Timer( object );

  const auto timer2 = new Timer( object );

  new State( stateManager, "static", [=] {
               timer1->start( 0.1f );
               timer2->start( 2.0f );
             },
             [=]( float dt ) {
               if ( timer1->isDone() ) {
                 abuAudio->play();
                 timer1->start( 0.6f );
               }
               if ( timer2->isDone() ) {
                 bellAudio->play();
                 timer2->start( 20.0f );
               }
             }, NULL );
}
