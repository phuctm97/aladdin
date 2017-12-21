#ifndef __JAFAR_FOOT_FIRE_PREFAB_H__
#define __JAFAR_FOOT_FIRE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarFootFirePrefab, ala::PrefabV2)
public:
	JafarFootFirePrefab()
		: PrefabV2("Jafar foot fire") {}

protected:
	void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif //!__JAFAR_FOOT_FIRE_PREFAB_H__
