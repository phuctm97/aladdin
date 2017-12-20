#ifndef __ALADDIN_AND_ABU_PREFAB_H__
#define __ALADDIN_AND_ABU_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AladdinAndAbuPrefab, ala::PrefabV2)
public:
  AladdinAndAbuPrefab(  )
    : PrefabV2( "Aladdin And Abu" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__ALADDIN_AND_ABU_PREFAB_H__
