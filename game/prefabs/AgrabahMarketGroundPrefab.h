#ifndef __AGRABAH_MARKET_GROUND_PREFAB_H__
#define __AGRABAH_MARKET_GROUND_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1( AgrabahMarketGroundPrefab, ala::PrefabV2)
public:
  AgrabahMarketGroundPrefab()
    : PrefabV2( "Agrabah Market Ground" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__AGRABAH_MARKET_GROUND_PREFAB_H__
