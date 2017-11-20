#ifndef __ROPE_PREFAB_H__
#define __ROPE_PREFAB_H__

#include <aladdin.h>

class RopePrefab : public ala::Prefab {

public:
	RopePrefab() :Prefab("Rope") {}

protected:
	void doInstantiate(ala::GameObject* object) const override;

};

#endif // !__ROPE_PREFAB_H__