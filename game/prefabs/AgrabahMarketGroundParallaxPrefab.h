#ifndef __AGRABAH_MARKET_GROUND_PARALLAX_PREFAB_H__
#define __AGRABAH_MARKET_GROUND_PARALLAX_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AgrabahMarketGroundParallaxPrefab, ala::PrefabV2)
public:
  AgrabahMarketGroundParallaxPrefab()
    : PrefabV2( "Agrabah Market Ground Parallax" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__AGRABAH_MARKET_GROUND_PARALLAX_PREFAB_H__
