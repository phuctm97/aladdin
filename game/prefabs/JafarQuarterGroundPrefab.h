#ifndef __JAFAR_QUARTER_GROUND_PREFAB_H__
#define __JAFAR_QUARTER_GROUND_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarQuarterGroundPrefab, ala::PrefabV2)
public:
  JafarQuarterGroundPrefab()
    : PrefabV2( "Jafar Quarter Ground" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__JAFAR_QUARTER_GROUND_PREFAB_H__
