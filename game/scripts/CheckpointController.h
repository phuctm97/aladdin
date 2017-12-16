#ifndef __CHECKPOINT_CONTROLLER_H__
#define __CHECKPOINT_CONTROLLER_H__

#include <aladdin.h>
#include "../app/MyAppData.h"

ALA_CLASS_HEADER_1(CheckpointController, ala::GameObjectComponent)
private:
  int _index;
  bool _checked;
  MyAppData* _myAppData;

public:
  CheckpointController( ala::GameObject* gameObject, const int index, const std::string& name = "" );

  bool isChecked() const;

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

  void setChecked();

protected:
  void onInitialize() override;
};

#endif // !__CHECKPOINT_CONTROLLER_H__
