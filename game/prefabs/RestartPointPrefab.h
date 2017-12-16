#ifndef _RESTART_POINT_PREFAB_H__
#define _RESTART_POINT_PREFAB_H__

#include<aladdin.h>

class RestartPointPrefab : ala::Prefab {
public :
	RestartPointPrefab() : Prefab("restart point") {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif // !_RESTART_POINT_PREFAB_H__
