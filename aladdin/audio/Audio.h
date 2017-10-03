#ifndef __ALADDIN_AUDIO_AUDIO_H__
#define __ALADDIN_AUDIO_AUDIO_H__

#include "AudioInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_2(Audio, ala::Initializable, ala::Releasable)
  friend class Application;

private:
  static Audio* __instance;
  Logger _logger;

public:
  Audio();

  virtual ~Audio();

  static Audio* get();

public:
  void initialize() override;

  void release() override;
};
}

#endif //!__ALADDIN_AUDIO_AUDIO_H__
