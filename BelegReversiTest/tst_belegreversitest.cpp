#include <QString>
#include <QtTest>
#include "../BelegReversi/src/modelPlayer.h"
#include "../BelegReversi/src/modelField.h"
#include "../BelegReversi/src/controllerField.h"

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
    void testingControllerFieldInit();
    void testingControllerFieldFindPossibleTurn();
    void testingControllerFieldFlipStones();
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

void BelegReversiTest::testingControllerFieldInit() {
    controllerField *field = new controllerField(true);
    field->initControllerFieldForTest(6);
    QCOMPARE(field->getGamingFieldElementValue(2,2), 1);
    QCOMPARE(field->getGamingFieldElementValue(3,3), 1);
    QCOMPARE(field->getGamingFieldElementValue(2,3), 2);
    QCOMPARE(field->getGamingFieldElementValue(3,2), 2);
}

void BelegReversiTest::testingControllerFieldFindPossibleTurn() {
    controllerField *field = new controllerField(true);
    field->initControllerFieldForTest(6);
    field->searchPossibleTurns();
    QCOMPARE(field->getGamingFieldElementValue(1,3), 3);
    QCOMPARE(field->getGamingFieldElementValue(2,4), 3);
    QCOMPARE(field->getGamingFieldElementValue(3,1), 3);
    QCOMPARE(field->getGamingFieldElementValue(4,2), 3);

}

void BelegReversiTest::testingControllerFieldFlipStones() {
    controllerField *field = new controllerField(true);
    field->initControllerFieldForTest(6);
    field->searchPossibleTurns();
    field->turn(1, 3);
    field->flipStones(1, 3);
    QCOMPARE(field->getGamingFieldElementValue(1,3), 1);
    QCOMPARE(field->getGamingFieldElementValue(2,3), 1);
}

QTEST_APPLESS_MAIN(BelegReversiTest)
#include "tst_belegreversitest.moc"
