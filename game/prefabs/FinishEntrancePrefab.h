#ifndef __FINISH_ENTRANCE_H__
#define __FINISH_ENTRANCE_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(FinishEntrancePrefab, ala::PrefabV2)
public:
  FinishEntrancePrefab()
    : PrefabV2( "Finish Entrance" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__FINISH_ENTRANCE_H__
