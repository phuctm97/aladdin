#ifndef __JAFAR_PALACE_PARALLAX_PREFAB_H__
#define __JAFAR_PALACE_PARALLAX_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarPalaceParallaxPrefab, ala::PrefabV2)
public:
  JafarPalaceParallaxPrefab()
    : PrefabV2( "Jafar Palace Parallax" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__JAFAR_PALACE_PARALLAX_PREFAB_H__
