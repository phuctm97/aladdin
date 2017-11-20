#ifndef __NORMAL_TEXT_PREFAB_H__
#define __MAIN_MENU_OPTION_PREFAB_H__

#include <aladdin.h>

class NormalTextPrefab : public ala::Prefab
{
public:
  NormalTextPrefab() : Prefab( "Normal Text" ) {}

protected:
  void doInstantiate( ala::GameObject* object ) const override;
};


#endif //!__NORMAL_TEXT_PREFAB_H__
