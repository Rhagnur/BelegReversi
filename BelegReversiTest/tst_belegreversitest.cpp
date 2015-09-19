#include <QString>
#include <QtTest>
#include "../BelegReversi/src/modelPlayer.h"
#include "../BelegReversi/src/modelField.h"

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
    void testingModelFieldValue();
    void testingModelFieldSize();
    void testingModelFieldRatio();
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

void BelegReversiTest::testingModelFieldValue() {
    modelField *field = new modelField(4);
    field->setFieldValue(1, 3, 42);
    QCOMPARE(field->getFieldValue(1, 3), 42);
    delete field;
}

void BelegReversiTest::testingModelFieldSize() {
    modelField *field = new modelField(20);
    QCOMPARE(field->getFieldSize(), 20);
    delete field;
}

void BelegReversiTest::testingModelFieldRatio() {
    modelField *field = new modelField(20);
    field->setFieldHeight(50);
    field->setFieldWidth(100);
    QCOMPARE(field->getFieldWidth(), 100);
    QCOMPARE(field->getFieldHeight(), 50);
    delete field;
}

QTEST_APPLESS_MAIN(BelegReversiTest)
#include "tst_belegreversitest.moc"
