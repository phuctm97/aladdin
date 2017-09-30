#ifndef __ALADDIN_CORE_BASE_H__
#define __ALADDIN_CORE_BASE_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "ClassMeta.h"

NAMESPACE_ALA
{
class Logger;

class Base {
  // ==============================================
  // Basic
  // ==============================================
public:
  Base();

  virtual ~Base();

  // ==============================================
  // Class Meta
  // ==============================================
public:
  ALA_DECLARE_CLASS_META
  template <class T>
  bool isInstanceOf() const;

  // ==============================================
  // References Counter
  // ==============================================
private:
  int _referenceCount;

public:
  int getReferenceCount() const;

  void increaseReferenceCount();

  void decreaseReferenceCount();

  // =============================================
  // Logger
  // =============================================
private:
  Logger* _logger;

public:
  Logger* getLogger();

  // =============================================
  // Debug memory allocation
  // =============================================
public:
  static long TOTAL_BASE_CREATED;
  static long TOTAL_BASE_DELETED;
};

// TEMPLATE DEFINITIONS

// ==============================================
// Class Meta
// ==============================================

template <class T>
bool Base::isInstanceOf() const {
  return getClassMeta().isExactly( T::CLASS_META ) || getClassMeta().isDerived( T::CLASS_META );
}
}

#endif //!__ALADDIN_CORE_BASE_H__
