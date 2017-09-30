#ifndef __BALL_PREFAB_H__
#define __BALL_PREFAB_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include <aladdin.h>

class BallPrefab : public ala::Prefab {
public:
  BallPrefab(): Prefab( "Ball" ) {}

  ala::GameObject* doInstantiate() override;
};

#endif //!__BALL_PREFAB_H__
