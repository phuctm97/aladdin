#ifndef __PEDDLER_CONTROLLER_H__
#define __PEDDLER_CONTROLLER_H__

#include <aladdin.h>

class PeddlerController : public ala::GameObjectComponent
{
private:
	bool showedPavilion;

public:
	PeddlerController(ala::GameObject* gameObject, const std::string& name = "");
	bool isShowedPavilion() const;
	void ShowedPavilion();
};

#endif //!__PEDDLER_CONTROLLER_H__

