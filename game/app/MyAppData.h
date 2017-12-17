#ifndef __MY_APP_DATA_H__
#define __MY_APP_DATA_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1( MyAppData, ala::GameResource )
private:
  int _currentLevel;
  int _currentCheckpoint;
  int _aladdinLives;
  int _retryTimes;

public:
  MyAppData( const int currentLevel, const int aladdinLives, const int retryTimes )
    : GameResource( "My App Data" ),
      _currentLevel( currentLevel ), _currentCheckpoint( 0 ), _aladdinLives( aladdinLives ),
      _retryTimes( retryTimes ) {}

  int getAladdinLives() const;

  void setAladdinLives( const int aladdinLives );

  int getCurrentLevel() const;

  void setCurrentLevel( const int currentLevel );

  int getRetryTimes() const;

  void setRetryTimes( const int retryTimes );

  int getCurrentCheckpoint() const;

  void setCurrentCheckpoint( const int currentCheckPoint );

protected:
  void onLoad() override;

  void onRelease() override;
};

#endif //!__MY_APP_DATA_H__
