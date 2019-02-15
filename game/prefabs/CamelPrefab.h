#ifndef __CAMEL_PREFAB_H__
#define __CAMEL_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(CamelPrefab, ala::PrefabV2)
public:
  CamelPrefab() : PrefabV2( "Camel" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__CAMEL_PREFAB_H__
