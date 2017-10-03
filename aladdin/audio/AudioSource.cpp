#include "AudioSource.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1( ala::AudioSource, ala::GameObjectComponent )

AudioSource::AudioSource( GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ) {}

AudioSource::~AudioSource() {}

void AudioSource::pause() {
  throw "Not implemented";
}

void AudioSource::stop() {
  throw "Not implemented";
}

void AudioSource::play() {
  throw "Not implemented";
}

void AudioSource::playOneShot() {
  throw "Not implemented";
}

void AudioSource::unPause() {
  throw "Not implemented";
}
}
