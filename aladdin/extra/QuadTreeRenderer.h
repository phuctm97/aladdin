#ifndef __ALADDIN_EXTRA_QUAD_TREE_RENDERER_H__
#define __ALADDIN_EXTRA_QUAD_TREE_RENDERER_H__

#include "ExtraInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(QuadTreeRenderer, ala::GameObjectComponent)
public:
  QuadTreeRenderer( GameObject* gameObject, const std::string& name = "" );

protected:
  void onRender() override;
};
}

#endif //!__ALADDIN_EXTRA_QUAD_TREE_RENDERER_H__
