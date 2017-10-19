#include "CameraPrefab.h"
#include "Camera.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1 ( CameraPrefab, Prefab )
void CameraPrefab::doInstantiate(ala::GameObject* object) {
  new ala::Camera(object, "Camera 2D",
    ala::GameManager::get()->getScreenWidth(),
    ala::GameManager::get()->getScreenHeight(),
    ala::Vec2(1.0f, 1.0f));
  object->getTransform()->setPosition(0,0);
}
}

