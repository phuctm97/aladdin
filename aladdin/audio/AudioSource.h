#ifndef __ALADDIN_AUDIO_AUDIO_SOURCE_H__
#define __ALADDIN_AUDIO_AUDIO_SOURCE_H__

#include "AudioInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(AudioSource, ala::GameObjectComponent)
public:
  AudioSource( GameObject* gameObject, const std::string& name );

  virtual ~AudioSource();

  void pause();

  void stop();

  void play();

  void playOneShot();

  void unPause();
};
}

#endif //!__ALADDIN_AUDIO_AUDIO_SOURCE_H__
