#ifndef __SCENE_INFO_QUERIER_H__
#define __SCENE_INFO_QUERIER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(SceneInfoQuerier, ala::GameObjectComponent)
private:
  ala::Transform* _cameraTransform;

public:
  SceneInfoQuerier( ala::GameObject* gameObject, const std::string& name = "" );

  std::vector<ala::GameObject*> getAllEnemiesInCamera() const;

protected:
  void onInitialize() override;
};

#endif //!__SCENE_INFO_QUERIER_H__
