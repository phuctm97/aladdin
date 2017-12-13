#ifndef __THINGUARD_CONTROLLER_H__
#define __THINGUARD_CONTROLLER_H__

#include <aladdin.h>

class ThinGuardController : public ala::GameObjectComponent
{
private:
	bool _couldAttackAladdin;
	bool _couldSeeAladdin;
	bool _onRightOfAladdin;
	bool _tooFarFromAladdin;
	float _minX;
	float _maxX;

protected:
	void onUpdate(const float delta) override;

public:
	ThinGuardController(ala::GameObject* gameObject, const std::string& name = "");
	bool couldAttackAladdin() const;
	bool couldSeeAladdin() const;
	bool isOnRightOfAladdin() const;
	bool isTooFarFromAladdin() const;

	float getMinX() const;
	void setMinX(const float minX);
	float getMaxX() const;
	void setMaxX(const float maxX);
	void set(const float minX, const float maxX);
};

#endif //!__THINGUARD_CONTROLLER_H__
