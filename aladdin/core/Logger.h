/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_LOGGER_H__
#define __ALADDIN_CORE_LOGGER_H__

#include "Base.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Logger)
private:
  static int __logLevel;
  std::string _className;

public:
  enum {
    LOG_DEBUG = 0,
    LOG_INFO = 1,
    LOG_ERROR = 2
  };

  static void setLogLevel( int level );

  Logger( const std::string& className );

  void debug( char const* const format, ... ) const;

  void info(char const* const format, ...) const;

  void error(char const* const format, ...) const;

};
}

#endif //!__ALADDIN_CORE_LOGGER_H__
