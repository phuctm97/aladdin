#include "AudioSource.h"
#include "Audio.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1( ala::AudioSource, ala::GameObjectComponent )

AudioSource::AudioSource( GameObject* gameObject, AudioClip* audioClip, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _audioClip( audioClip ), _loop( false ) {}

AudioSource::AudioSource( GameObject* gameObject, const std::string& audioClipName, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _audioClip( NULL ), _loop( false ) {
  _audioClip = static_cast<AudioClip*>(GameManager::get()->getResource( audioClipName ));
}

void AudioSource::setLoop( const bool val ) {
  _loop = val;
}

bool AudioSource::isLoop() const {
  return _loop;
}

AudioSource::~AudioSource() {}

void AudioSource::pause() {
  throw "Not implemented";
}

void AudioSource::stop() {
  if ( _audioClip ) {
    Audio::get()->stop( _audioClip );
  }
}

void AudioSource::play() {
  if ( _audioClip ) {
    Audio::get()->play( _audioClip, _loop );
  }
}

void AudioSource::playOneShot() {
  if ( _audioClip ) {
    Audio::get()->play( _audioClip, false );
  }
}

void AudioSource::unPause() {
  throw "Not implemented";
}

void AudioSource::setAudioClip( AudioClip* clip ) {
  _audioClip = clip;
}

AudioClip* AudioSource::getAudioClip() const {
  return _audioClip;
}
}
