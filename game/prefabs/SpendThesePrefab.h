#ifndef _SPEND_THESE_PREFAB_H__
#define _SPEND_THESE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(SpendThesePrefab, ala::PrefabV2)
public:
  SpendThesePrefab() : PrefabV2( "Spend These" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !_SPEND_THESE_PREFAB_H__
