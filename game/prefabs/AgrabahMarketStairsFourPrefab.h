#ifndef __AGRABAH_MARKET_STAIRS_FOUR_PREFAB_H__
#define __AGRABAH_MARKET_STAIRS_FOUR_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AgrabahMarketStairsFourPrefab, ala::PrefabV2)
public:
	AgrabahMarketStairsFourPrefab()
		: PrefabV2("Agrabah Market Stairs 4") {}

protected:
	void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif //!__AGRABAH_MARKET_STAIRS_FOUR_PREFAB_H__
