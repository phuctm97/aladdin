#ifndef _STAIR_GROUP_THREE_PREFAB_H
#define _STAIR_GROUP_THREE_PREFAB_H

#include <aladdin.h>

class StairGroupThreePrefab : public ala::Prefab {
public:
	StairGroupThreePrefab() : Prefab("StairGroupThree") {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif //!_STAIR_GROUP_THREE_PREFAB_H