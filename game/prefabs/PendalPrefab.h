#ifndef __PENDAL_PREFAB_H__
#define __PENDAL_PREFAB_H__

#include <aladdin.h>

class PendalPrefab : public ala::Prefab
{
private:
	ala::Logger _logger;
	ala::Vec2 _resetPoint;
public:
	PendalPrefab() :Prefab("Pendal"),_logger("Pendal"){};

protected:
	void doInstantiate(ala::GameObject* object) const override;
};



#endif //!__PENDAL_PREFAB_H__