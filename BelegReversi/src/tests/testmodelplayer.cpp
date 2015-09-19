#include "testmodelplayer.h"

TestModelPlayer::testingPlayerName() {
    modelPlayer *test = new modelPlayer();
    test->setPlayerName(QString("Test"));
    QCOMPARE(test->getPlayerName(), QString("Test"));
    delete test;
}

TestModelPlayer::testingPlayerStoneCount() {
    modelPlayer *test = new modelPlayer();
    test->setPlayerStoneCount(42);
    QCOMPARE(test->getPlayerStoneCount(), 42);
    delete test;
}

