#include <QString>
#include <QtTest>
#include "../BelegReversi/src/modelPlayer.h"

class BelegReversiTest : public QObject
{
    Q_OBJECT

public:
    BelegReversiTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testingModelPlayerName();
    void testingModelPlayerStoneCount();
};

BelegReversiTest::BelegReversiTest()
{
}

void BelegReversiTest::initTestCase()
{
}

void BelegReversiTest::cleanupTestCase()
{
}

void BelegReversiTest::testingModelPlayerName()
{
    modelPlayer *player = new modelPlayer();
    player->setPlayerName(QString("Test"));
    QCOMPARE(player->getPlayerName(), QString("Test"));
    delete player;
}

void BelegReversiTest::testingModelPlayerStoneCount()
{
    modelPlayer *player = new modelPlayer();
    player->setPlayerStoneCount(42);
    QCOMPARE(player->getPlayerStoneCount(), 42);
    delete player;
}

QTEST_APPLESS_MAIN(BelegReversiTest)

#include "tst_belegreversitest.moc"
