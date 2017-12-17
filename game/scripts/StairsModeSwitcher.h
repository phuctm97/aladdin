#ifndef __STAIRS_MODE_SWITCHER_H__
#define __STAIRS_MODE_SWITCHER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(StairsModeSwitcher, ala::GameObjectComponent)
private:
  char _turnSide;
  ala::StateManager* _stairsStateManager;

public:
  StairsModeSwitcher( ala::GameObject* gameObject, const char turnSide = 'C', const std::string& name = "" );

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

protected:
  void onInitialize() override;
};

#endif //!__STAIRS_MODE_SWITCHER_H__
