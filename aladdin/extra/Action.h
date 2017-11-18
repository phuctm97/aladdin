#ifndef __ALADDIN_EXTRA_ACTION_H__
#define __ALADDIN_EXTRA_ACTION_H__

#include "ExtraInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Action, ala::Releasable)
private:
  bool _done;

public:
  Action();

  virtual ~Action();

  bool isDone() const;

  void update( const float delta );

  void release() override;

protected:
  void done();

  virtual void onUpdate( float delta );

  virtual void onRelease();
};
}

#endif //!__ALADDIN_EXTRA_ACTION_H__
