#ifndef __HOLDABLE_BAR_PREFAB_H__
#define __HOLDABLE_BAR_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(HoldableBarPrefab, ala::PrefabV2)
public:
  HoldableBarPrefab()
    : PrefabV2( "Holdable Bar" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__HOLDABLE_BAR_PREFAB_H__
