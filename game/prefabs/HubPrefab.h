#ifndef __HUB_PREFAB_H__
#define __HUB_PREFAB_H__

#include <aladdin.h>

class HubPrefab : public ala::Prefab
{
public:
  HubPrefab();

protected:
  void doInstantiate( ala::GameObject* object ) const override;
};

#endif //!__HUB_PREFAB_H__
