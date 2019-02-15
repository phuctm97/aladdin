#ifndef __JAFAR_FIRE_PREFAB_H__
#define __JAFAR_FIRE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarFirePrefab, ala::PrefabV2)
public:
  JafarFirePrefab()
    : PrefabV2( "Jafar Fire" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__JAFAR_FIRE_PREFAB_H__
