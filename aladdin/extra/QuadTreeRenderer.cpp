#include "QuadTreeRenderer.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::QuadTreeRenderer, ala::GameObjectComponent)

QuadTreeRenderer::QuadTreeRenderer( GameObject* gameObject, const std::string& name ): GameObjectComponent(
  gameObject, name ) {}

void QuadTreeRenderer::onRender() {
  Scene* scene = getGameObject()->getParentScene();


}
}
