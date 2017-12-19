#ifndef __JAFAR_CONTROLLER_H__
#define __JAFAR_CONTROLLER_H__

#include <aladdin.h>
#include "DirectionController.h"

ALA_CLASS_HEADER_1(JafarController, ala::GameObjectComponent)
private:
	int _health;
	ala::Transform* _aladdinTransform;
	ala::Transform* _selfTransform;
	ala::StateManager* _selfStateManager;
	DirectionController* _selfDirection;

public:
	JafarController(ala::GameObject* gameObject, const std::string& name = "");
	char getDirectionToFaceToAladdin() const;
	int	 getHealth() const;
	void setHealth(const int health);

protected:
	void onInitialize() override;

public:
	void onDie(const int explosionType = 1) const;

	void onHit();

	void onTriggerEnter(const ala::CollisionInfo& collision) override;
};

#endif //!__JAFAR_CONTROLLER_H__

