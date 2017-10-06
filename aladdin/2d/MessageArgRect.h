#ifndef __MESSAGE_ARG_RECT_H__
#define __MESSAGE_ARG_RECT_H__

#include "../core/MessageArgs.h"
#include "Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1 ( MessageArgRect, MessageArgs )
private:
  Rect _rect;
public:
  MessageArgRect(const Rect &rect);

  const Rect& getRect() const;
};
}

#endif //!__MESSAGE_ARG_RECT_H__