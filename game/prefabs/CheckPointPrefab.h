#ifndef __CHECKPOINT_PREFAB_H__
#define __CHECKPOINT_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(CheckpointPrefab, ala::PrefabV2)
public:
  CheckpointPrefab()
    : PrefabV2( "Checkpoint" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__CHECKPOINT_PREFAB_H__
