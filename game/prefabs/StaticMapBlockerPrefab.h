#ifndef __MAP_BLOCKER_PREFAB_H__
#define __MAP_BLOCKER_PREFAB_H__

#include <aladdin.h>

class StaticMapBlockerPrefab : public ala::Prefab {

public:
	StaticMapBlockerPrefab() :Prefab("MapBlocker") {}

protected:
	void doInstantiate(ala::GameObject* object) const override;

};

#endif // !__MAP_BLOCKER_PREFAB_H__
