#ifndef __SMALL_FIREWORK_PREFAB_H__
#define __SMALL_FIREWORK_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(SmallFireworkPrefab, ala::PrefabV2)
public:
  SmallFireworkPrefab() : PrefabV2( "Small Firework" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__SMALL_FIREWORK_PREFAB_H__
