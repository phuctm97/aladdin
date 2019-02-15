#ifndef __AGRABAH_MARKET_STAIRS_THREE_PREFAB_H__
#define __AGRABAH_MARKET_STAIRS_THREE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AgrabahMarketStairsThreePrefab, ala::PrefabV2)
public:
  AgrabahMarketStairsThreePrefab()
    : PrefabV2( "Agrabah Market Stairs 3" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__AGRABAH_MARKET_STAIRS_THREE_PREFAB_H__
