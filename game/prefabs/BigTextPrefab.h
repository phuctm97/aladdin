#ifndef __BIG_TEXT_PREFAB_H__
#define __BIG_TEXT_PREFAB_H__

#include <aladdin.h>

class BigTextPrefab : public ala::Prefab
{
public:
  BigTextPrefab() : Prefab( "Big Text" ) {}

protected:
  void doInstantiate( ala::GameObject* object ) const override;
};


#endif //!__BIG_TEXT_PREFAB_H__
