#ifndef __SPRITE_PREFAB_H__
#define __SPRITE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(SpritePrefab, ala::PrefabV2)
public:
  SpritePrefab()
    : PrefabV2( "Sprite" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};


#endif //!__SPRITE_PREFAB_H__
