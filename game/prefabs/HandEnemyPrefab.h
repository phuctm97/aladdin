#ifndef __HAND_ENEMY_PREFAB_H__
#define __HAND_ENEMY_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(HandEnemyPrefab, ala::PrefabV2)
public:
  HandEnemyPrefab() : PrefabV2( "Hand Enemy" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__HAND_ENEMY_PREFAB_H__
