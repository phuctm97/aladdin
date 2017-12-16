#ifndef __AGRABAH_MARKET_STAIR_ONE_PREFAB_H__
#define __AGRABAH_MARKET_STAIR_ONE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AgrabahMarketStairOnePrefab, ala::PrefabV2)
public:
  AgrabahMarketStairOnePrefab() : PrefabV2( "Agrabah Market Stair 1" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__AGRABAH_MARKET_STAIR_ONE_PREFAB_H__
