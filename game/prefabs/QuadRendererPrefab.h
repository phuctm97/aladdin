#ifndef __QUAD_RENDERER_PREFAB_H__
#define __QUAD_RENDERER_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(QuadRendererPrefab, ala::PrefabV2)
public:
  QuadRendererPrefab()
    : PrefabV2( "Quad Renderer" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__QUAD_RENDERER_PREFAB_H__
