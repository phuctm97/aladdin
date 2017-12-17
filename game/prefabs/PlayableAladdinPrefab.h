#ifndef __PLAYABLE_ALADDIN_PREFAB_H__
#define __PLAYABLE_ALADDIN_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(PlayableAladdinPrefab, ala::PrefabV2)
public:
  PlayableAladdinPrefab()
    : PrefabV2( "Playable Aladdin" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__ALADDIN_PLAYABLE_ALADDIN_PREFAB_H__
