#ifndef TESTMODELPLAYER_H
#define TESTMODELPLAYER_H

#include <QtTest>
#include "../modelPlayer.h"

class TestModelPlayer : public QObject
{
    Q_OBJECT

private slots:
    void testingPlayerName();
    void testingPlayerStoneCount();
};

DECLARE_TEST (TestModelPlayer);

#endif // TESTMODELPLAYER_H
