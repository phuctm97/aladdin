#include "CameraPrefab.h"
#include "Camera.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1 ( CameraPrefab, Prefab )
void CameraPrefab::doInstantiate(ala::GameObject* object) {
  new ala::Camera(object, ALA_MAIN_CAMERA,
    ala::GameManager::get()->getScreenWidth(),
    ala::GameManager::get()->getScreenHeight(),
    ala::Vec2(1.0f, 1.0f));
}
}

