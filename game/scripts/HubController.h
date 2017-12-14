#ifndef __HUB_CONTROLLER_H__
#define __HUB_CONTROLLER_H__

#include <aladdin.h>
#include "PlayableAladdinController.h"

class HubController : public ala::GameObjectComponent
{
private:
  ala::BitmapText* _livesLabel;
  ala::BitmapText* _applesLabel;
  ala::BitmapText* _scoresLabel;
  PlayableAladdinController *_aladdinController;

public:
  HubController( ala::GameObject* gameObject, const std::string& name = "" );

  void setLives( const int lives ) const;

  void setApples( const int apples ) const;

  void setScores( const int scores ) const;

protected:
  void onInitialize() override;
  void onUpdate( const float delta ) override;
};


#endif //!__HUB_CONTROLLER_H__
