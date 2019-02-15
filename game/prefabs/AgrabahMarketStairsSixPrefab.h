#ifndef __AGRABAH_MARKET_STAIRS_SIX_PREFAB_H__
#define __AGRABAH_MARKET_STAIRS_SIX_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AgrabahMarketStairsSixPrefab, ala::PrefabV2)
public:
	AgrabahMarketStairsSixPrefab()
		: PrefabV2("Agrabah Market Stairs 6") {}

protected:
	void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};


#endif //!__AGRABAH_MARKET_STAIRS_SIX_PREFAB_H__
