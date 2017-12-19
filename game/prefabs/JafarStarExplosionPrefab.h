#ifndef __JAFAR_STAR_EXPLOSION_PREFAB_H__
#define __JAFAR_STAR_EXPLOSION_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarStarExplosionPrefab, ala::PrefabV2)
public:
  JafarStarExplosionPrefab()
    : PrefabV2( "Jafar Star Explosion" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};


#endif //!__JAFAR_STAR_EXPLOSION_PREFAB_H__
