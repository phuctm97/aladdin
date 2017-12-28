#ifndef __SFX_CONTROLLER_PREFAB_H__
#define __SFX_CONTROLLER_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(SfxControllerPrefab, ala::PrefabV2)
public:
  SfxControllerPrefab()
    : PrefabV2( "Sfx Controller" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__SFX_CONTROLLER_PREFAB_H__
