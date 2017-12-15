#ifndef __HUB_PREFAB_H__
#define __HUB_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(HubPrefab, ala::PrefabV2)
public:
  HubPrefab() : PrefabV2( "Hub" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__HUB_PREFAB_H__
