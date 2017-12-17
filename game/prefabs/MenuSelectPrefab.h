#ifndef __MENU_SELECT_PREFAB_H__
#define __MENU_SELECT_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(MenuSelectPrefab, ala::PrefabV2)
public:
  MenuSelectPrefab()
    : PrefabV2( "Menu Select" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__MENU_SELECT_PREFAB_H__
