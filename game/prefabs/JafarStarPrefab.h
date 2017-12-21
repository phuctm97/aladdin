#ifndef __JAFAR_STAR_PREFAB_H__
#define __JAFAR_STAR_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarStarPrefab, ala::PrefabV2)
public:
  JafarStarPrefab()
    : PrefabV2( "Jafar Star" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__JAFAR_STAR_PREFAB_H__
