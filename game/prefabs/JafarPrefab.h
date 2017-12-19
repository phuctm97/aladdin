#ifndef __JAFAR_PREFAB_H__
#define __JAFAR_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarPrefab, ala::PrefabV2)
public:
	JafarPrefab()
		: PrefabV2("Jafar") {}

protected:
	void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif //!__JAFAR_PREFAB_H__

