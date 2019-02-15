#ifndef __AUDIO_PLAYER_PREFAB_H__
#define __AUDIO_PLAYER_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AudioPlayerPrefab, ala::PrefabV2)
public:
  AudioPlayerPrefab()
    : PrefabV2( "Audio Player" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__AUDIO_PLAYER_PREFAB_H__
