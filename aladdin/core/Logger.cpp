/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Logger.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Logger )

int Logger::__logLevel( ALA_LOG_DEBUG );

void Logger::setLogLevel( int level ) {
  ALA_ASSERT(level >= ALA_LOG_DEBUG && level <= ALA_LOG_ERROR);
  __logLevel = level;
}

Logger::Logger( const std::string& className ) : _className( className ) {
  TOTAL_LOGGERS_CREATED++;
}

Logger::~Logger() {
  TOTAL_LOGGERS_DELETED++;
}

void Logger::debug( char const* const format, ... ) const {
  if ( __logLevel > ALA_LOG_DEBUG ) return;

  char buffer[256];

  va_list args;
  va_start(args, format);
  vsprintf( buffer, format, args );
  va_end(args);

  std::string logString = "[D] [" + _className + "] : " + buffer;
  if ( logString.back() != '\n' )logString += "\n";

  printf( logString.c_str() );
}

void Logger::info( char const* const format, ... ) const {
  if ( __logLevel > ALA_LOG_INFO ) return;

  va_list args;
  va_start(args, format);

  char buffer[256];
  vsprintf( buffer, format, args );

  std::string logString = "[I] [" + _className + "] : " + buffer;
  if ( logString.back() != '\n' )logString += "\n";

  printf( logString.c_str() );
  va_end(args);
}

void Logger::error( char const* const format, ... ) const {
  if ( __logLevel > ALA_LOG_ERROR ) return;

  va_list args;
  va_start(args, format);

  char buffer[256];
  vsprintf( buffer, format, args );

  std::string logString = "[E] [" + _className + "]: " + buffer;
  if ( logString.back() != '\n' )logString += "\n";

  printf( logString.c_str() );
  va_end(args);
}

// =============================================
// Debug memory allocation
// =============================================
long Logger::TOTAL_LOGGERS_CREATED( 0 );
long Logger::TOTAL_LOGGERS_DELETED( 0 );
}
