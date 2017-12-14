#ifndef __HORIZONTAL_BAR_PREFAB_H__
#define __HORIZONTAL_BAR_PREFAB_H__

#include <aladdin.h>

class HorizontalBarPrefab : public ala::Prefab {
public:
	HorizontalBarPrefab():Prefab("HorizontalBar"){}
protected: 
	void doInstantiate(ala::GameObject* gameObject) const override;
};


#endif //!__HORIZONTAL_BAR_PREFAB_H__