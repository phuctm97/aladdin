#ifndef __AUTO_LOAD_SCENE_H__
#define __AUTO_LOAD_SCENE_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AutoLoadScene, ala::Scene)
private:
  std::string _sceneName;
  bool _useCameraController;

public:
  AutoLoadScene( const std::string& sceneName, const bool useCameraController = false )
    : _sceneName( sceneName ),
      _useCameraController( useCameraController ) {}

protected:
  void onPreInitialize() override;
};

#endif //!__AUTO_LOAD_SCENE_H__
