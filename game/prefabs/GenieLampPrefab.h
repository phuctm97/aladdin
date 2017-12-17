#ifndef __GENIE_LAMP_PREFAB_H__
#define __GENIE_LAMP_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(GenieLampPrefab, ala::PrefabV2)
public:
  GenieLampPrefab() : PrefabV2( "Genie Lamp" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__GENIE_LAMP_PREFAB_H__
