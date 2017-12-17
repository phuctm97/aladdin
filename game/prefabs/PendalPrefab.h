#ifndef __PENDAL_PREFAB_H__
#define __PENDAL_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(PendalPrefab, ala::PrefabV2)
public:
  PendalPrefab() : PrefabV2( "Pendal" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};


#endif //!__PENDAL_PREFAB_H__
