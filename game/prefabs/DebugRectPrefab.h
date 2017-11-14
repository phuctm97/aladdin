#ifndef __DEBUG_RECT_PREFAB_H__
#define __DEBUG_RECT_PREFAB_H__

#include <aladdin.h>

class DebugRectPrefab : ala::Prefab
{
public:
  DebugRectPrefab()
    : Prefab( "Debug Rect" ) {}

protected:
  void doInstantiate( ala::GameObject* object ) const override;
};

#endif //!__DEBUG_RECT_PREFAB_H__
