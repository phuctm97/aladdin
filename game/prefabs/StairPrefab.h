#ifndef _STAIR_PREFAB_H__
#define _STAIR_PREFAB_H__

#include <aladdin.h>

class StairPrefab : public ala::Prefab
{
public:
	StairPrefab() : Prefab("Stair") {}

protected:
	void doInitianate(ala::GameObject* object) const override;
};

#endif // !_STAIR_PREFAB_H__