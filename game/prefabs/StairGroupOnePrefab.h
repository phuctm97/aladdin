#ifndef _STAIR_GROUP_ONE_PREFAB_H
#define _STAIR_GROUP_ONE_PREFAB_H

#include <aladdin.h>

class StairGroupOnePrefab : public ala::Prefab {
public:
	StairGroupOnePrefab() : Prefab("StairGroupOne") {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif //!_STAIR_GROUP_ONE_PREFAB_H