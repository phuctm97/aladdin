#ifndef __ALADDIN_AUDIO_AUDIO_LISTENER_H__
#define __ALADDIN_AUDIO_AUDIO_LISTENER_H__

#include "AudioInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(AudioListener, ala::GameObjectComponent)
public:
  AudioListener( GameObject* gameObject, const std::string& name );

  virtual ~AudioListener();
};
}
#endif //!__ALADDIN_AUDIO_AUDIO_LISTENER_H__
