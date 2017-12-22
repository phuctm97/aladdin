#ifndef __PENDAL_V2_PREFAB_H__
#define __PENDAL_V2_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(PendalV2Prefab, ala::PrefabV2)
public:
  PendalV2Prefab()
    : PrefabV2( "Pendal V2" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__PENDAL_V2_PREFAB_H__
