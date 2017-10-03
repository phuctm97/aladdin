#ifndef __ALADDIN_AUDIO_AUDIO_CLIP_H__
#define __ALADDIN_AUDIO_AUDIO_CLIP_H__

#include "AudioInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(AudioClip, ala::GameResource)
public:
  AudioClip( const std::string& name, Scene* sceneScope )
    : GameResource( name, sceneScope ) {}

  virtual ~AudioClip();

protected:
  void onLoad() override;

  void onRelease() override;
};
}

#endif //!__ALADDIN_AUDIO_AUDIO_CLIP_H__
