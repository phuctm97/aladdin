#ifndef __TIMER_H__
#define __TIMER_H__

#include <aladdin.h>

class Timer : public ala::GameObjectComponent
{
private:
  float _timer;

public:
  Timer( ala::GameObject* gameObject, const std::string& name = "" );

  void start( const float time );

  bool isDone() const;

protected:
  void onPreUpdate( const float delta ) override;

  void onUpdate( const float delta ) override;
};

#endif //!__TIMER_H__
