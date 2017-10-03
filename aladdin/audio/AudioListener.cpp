#include "AudioListener.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::AudioListener, ala::GameObjectComponent)

AudioListener::AudioListener( GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ) {}

AudioListener::~AudioListener() {}
}
