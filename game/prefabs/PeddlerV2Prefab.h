#ifndef __PEDDLER_V2_PREFAB_H__
#define __PEDDLER_V2_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(PeddlerV2Prefab, ala::PrefabV2)
public:
  PeddlerV2Prefab()
    : PrefabV2( "Peddler V2" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__PEDDLER_V2_PREFAB_H__
