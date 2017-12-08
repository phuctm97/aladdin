#ifndef __HUB_CONTROLLER_H__
#define __HUB_CONTROLLER_H__

#include <aladdin.h>

class HubController : public ala::GameObjectComponent
{
private:
  int _lives;
  int _apples;

public:
  HubController( ala::GameObject* gameObject, const std::string& name = "" );

  void setLives( const int lives );

  int getLives() const;

  void setApples( const int apples );

  int getApples() const;

protected:
  void onInitialize() override;

  void onUpdate( const float delta ) override;
  
  void onRender() override;
};


#endif //!__HUB_CONTROLLER_H__
