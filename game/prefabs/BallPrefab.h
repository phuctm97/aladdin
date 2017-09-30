#ifndef __BALL_PREFAB_H__
#define __BALL_PREFAB_H__

#include <aladdin.h>

class BallPrefab : public ala::Prefab {
public:
  BallPrefab(): Prefab( "Ball" ) {}

  ala::GameObject* doInstantiate() override;
};

#endif //!__BALL_PREFAB_H__
