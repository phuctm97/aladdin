#ifndef __AGRABAH_MARKET_SKY_PARALLAX_PREFAB_H__
#define __AGRABAH_MARKET_SKY_PARALLAX_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AgrabahMarketSkyParallaxPrefab, ala::PrefabV2)
public:
  AgrabahMarketSkyParallaxPrefab()
    : PrefabV2( "Agrabah Market Sky Parallax" ) {}

private:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__AGRABAH_MARKET_SKY_PARALLAX_PREFAB_H__
