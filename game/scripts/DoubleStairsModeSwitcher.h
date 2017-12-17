#ifndef __DOUBLE_STAIRS_MODE_SWITCHER_H__
#define __DOUBLE_STAIRS_MODE_SWITCHER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(DoubleStairsModeSwitcher, ala::GameObjectComponent)
private:
	char _turnSide;
	ala::StateManager* _stairsStateManager;

public:
	DoubleStairsModeSwitcher(ala::GameObject* gameObject, const std::string& name = "");

	void onTriggerEnter(const ala::CollisionInfo& collision) override;

protected:
	void onInitialize() override;
};

#endif //!__DOUBLE_STAIRS_MODE_SWITCHER_H__
