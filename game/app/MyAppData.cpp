#include "MyAppData.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(MyAppData, ala::GameResource)

int MyAppData::getNumberOfLevels() const {
  return _numberOfLevels;
}

int MyAppData::getAladdinLives() const { return _aladdinLives; }

void MyAppData::setAladdinLives( const int aladdinLives ) { _aladdinLives = aladdinLives; }

int MyAppData::getAladdinApples() const {
  return _aladdinApples;
}

void MyAppData::setAladdinApples( const int apples ) {
  _aladdinApples = apples;
}

int MyAppData::getCurrentLevel() const { return _currentLevel; }

void MyAppData::setCurrentLevel( const int currentLevel ) { _currentLevel = currentLevel; }

int MyAppData::getRetryTimes() const { return _retryTimes; }

void MyAppData::setRetryTimes( const int retryTimes ) { _retryTimes = retryTimes; }

int MyAppData::getCurrentCheckpoint() const { return _currentCheckpoint; }

void MyAppData::setCurrentCheckpoint( const int currentCheckPoint ) { _currentCheckpoint = currentCheckPoint; }

std::string MyAppData::getSceneName( const int level ) {
  if ( level < 1 || level > static_cast<int>(_levelScenes.size()) ) return "";
  return _levelScenes[level - 1];
}

void MyAppData::onLoad() {}

void MyAppData::onRelease() {}
