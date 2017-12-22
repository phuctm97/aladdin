#ifndef __AGRABAH_MARKET_PARALLAX_PREFAB_H__
#define __AGRABAH_MARKET_PARALLAX_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AgrabahMarketParallaxPrefab, ala::PrefabV2)
public:
  AgrabahMarketParallaxPrefab()
    : PrefabV2( "Agrabah Market Parallax" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__AGRABAH_MARKET_PARALLAX_PREFAB_H__
