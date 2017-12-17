#ifndef __PEDDLER_PREFAB_H__
#define __PEDDLER_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(PeddlerPrefab, ala::PrefabV2)
public:
  PeddlerPrefab() : PrefabV2( "Peddler" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__PEDDLER_PREFAB_H__
