#ifndef __PEDDLER_TEXT_PREFAB_H__
#define __PEDDLER_TEXT_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(PeddlerTextPrefab, ala::PrefabV2)
public:
  PeddlerTextPrefab()
    : PrefabV2( "Peddler Text" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__PEDDLER_TEXT_PREFAB_H__
