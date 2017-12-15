#ifndef __FLOATING_SALIVA_PREFAB_H__
#define __FLOATING_SALIVA_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(FloatingSalivaPrefab, ala::PrefabV2)
public:
  FloatingSalivaPrefab() : PrefabV2( "Floating Saliva" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__FLOATING_SALIVA_PREFAB_H__
