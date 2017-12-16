#ifndef __NODE_PREFAB_H__
#define __NODE_PREFAB_H__

#include <aladdin.h>

class NodePrefab : public ala::Prefab
{
public:
  NodePrefab() : Prefab( "Node" ) {}

protected:
  void doInstantiate( ala::GameObject* object ) const override;
};

#endif // !__NODE_PREFAB_H__
