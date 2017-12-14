#ifndef _STAIR_GROUP_TWO_PREFAB_H
#define _STAIR_GROUP_TWO_PREFAB_H

#include <aladdin.h>

class StairGroupTwoPrefab : public ala::Prefab {
public:
	StairGroupTwoPrefab() : Prefab("StairGroupTwo") {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif //!_STAIR_GROUP_TWO_PREFAB_H