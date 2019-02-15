#ifndef __AGRABAH_MARKET_STAIRS_FIVE_PREFAB_H__
#define __AGRABAH_MARKET_STAIRS_FIVE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AgrabahMarketStairsFivePrefab, ala::PrefabV2)
public:
	AgrabahMarketStairsFivePrefab()
		: PrefabV2("Agrabah Market Stairs 5") {}

protected:
	void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};


#endif //!__AGRABAH_MARKET_STAIRS_FIVE_PREFAB_H__
