#ifndef __ALADDIN_AUDIO_AUDIO_H__
#define __ALADDIN_AUDIO_AUDIO_H__

#include "AudioInclude.h"
#include "AudioClip.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_2(Audio, ala::Initializable, ala::Releasable)
  // =====================================================
  // Basics
  // =====================================================

  friend class Application;

private:
  static Audio* __instance;
  Logger _logger;

public:
  Audio();

  virtual ~Audio();

  static Audio* get();

  void load( AudioClip* clip );

  void play( AudioClip* clip, bool loop );

  void stop( AudioClip* clip );

public:
  void initialize() override;

  void release() override;

  // =====================================================
  // Platform specific
  // =====================================================
private:
  HWND _hWnd;
  CSoundManager* _directXSound;

  void initDirectXSound();

  void releaseDirectXSound();

};
}

#endif //!__ALADDIN_AUDIO_AUDIO_H__
