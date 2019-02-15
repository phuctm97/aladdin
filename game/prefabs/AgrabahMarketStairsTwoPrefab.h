#ifndef __AGRABAH_MARKET_STAIRS_TWO_PREFAB_H__
#define __AGRABAH_MARKET_STAIRS_TWO_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AgrabahMarketStairsTwoPrefab, ala::PrefabV2)
public:
  AgrabahMarketStairsTwoPrefab()
    : PrefabV2( "Agrabah Market Stairs 2" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__AGRABAH_MARKET_STAIRS_TWO_PREFAB_H__
