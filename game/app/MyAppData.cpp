#include "MyAppData.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(MyAppData, ala::GameResource)

int MyAppData::getAladdinLives() const { return _aladdinLives; }

void MyAppData::setAladdinLives( const int aladdinLives ) { _aladdinLives = aladdinLives; }

int MyAppData::getCurrentLevel() const { return _currentLevel; }

void MyAppData::setCurrentLevel( const int currentLevel ) { _currentLevel = currentLevel; }

int MyAppData::getRetryTimes() const { return _retryTimes; }

void MyAppData::setRetryTimes( const int retryTimes ) { _retryTimes = retryTimes; }

int MyAppData::getCurrentCheckpoint() const { return _currentCheckpoint; }

void MyAppData::setCurrentCheckpoint( const int currentCheckPoint ) { _currentCheckpoint = currentCheckPoint; }

void MyAppData::onLoad() {}

void MyAppData::onRelease() {}
