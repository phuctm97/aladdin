#ifndef __ALADDIN_PREFAB_H__
#define __ALADDIN_PREFAB_H__

#include <aladdin.h>

class AladdinPrefab : ala::Prefab
{
public:
  AladdinPrefab() : Prefab( "Aladdin" ) {}

protected:
  void doInstantiate( ala::GameObject* object ) override;
};

#endif //!__ALADDIN_PREFAB_H__
