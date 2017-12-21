#ifndef __JAFAR_PALACE_GROUND_PREFAB_H__
#define __JAFAR_PALACE_GROUND_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarPalaceGroundPrefab, ala::PrefabV2)
public:
  JafarPalaceGroundPrefab()
    : PrefabV2( "Jafar Palace Ground" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__JAFAR_PALACE_GROUND_PREFAB_H__
