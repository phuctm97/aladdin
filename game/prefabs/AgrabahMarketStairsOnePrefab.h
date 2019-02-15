#ifndef __AGRABAH_MARKET_STAIRS_ONE_PREFAB_H__
#define __AGRABAH_MARKET_STAIRS_ONE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AgrabahMarketStairsOnePrefab, ala::PrefabV2)
public:
  AgrabahMarketStairsOnePrefab()
    : PrefabV2( "Agrabah Market Stairs 1" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};


#endif //!__AGRABAH_MARKET_STAIRS_ONE_PREFAB_H__
