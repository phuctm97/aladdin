#include "DeathSceneSoundPrefab.h"
#include"../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(DeathSceneSoundPrefab, ala::PrefabV2)

void DeathSceneSoundPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const
{
	const auto gameManager = GameManager::get();
	const auto stateManager = new StateManager( object, "static" );
	const auto Abu = new AudioSource(object, "Abu Waving.wav");
	const auto Bell = new AudioSource(object, "Boxing Bell.wav");
	
	const auto timer1 = new Timer(object);
	const auto timer2 = new Timer(object);
	new State( stateManager, "static", [=] { timer1->start(0.1); timer2->start(2);},
             [=]( float dt ) {
               if(timer1->isDone())
			   {	
               	Abu->play();
				timer1->start(0.6);
			   }
			  if(timer2->isDone())
			  {
			  	Bell->play();
				 timer2->start(20);
			  }
             }, NULL );
}