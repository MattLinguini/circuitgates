#include "src/model/circuit_game_model.h"
#include <QJsonDocument>
#include <QFile>
#include <QByteArray>

CircuitGameModel::CircuitGameModel(QObject *parent) : QObject(parent), currentLevel() {}

void CircuitGameModel::createLevel(int levelId) {
    //Clears out currentLevel's memory for a new level to take place.
    currentLevel.cleanLevel();

    switch (levelId) {
    case 1:
        loadLvl1();
        break;
    case 2:
        loadLvl2();
        break;
    case 3:
        loadLvl3();
        break;
    case 4:
        loadLvl4();
        break;
    }
}

void CircuitGameModel::loadLvl1() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 0);
    currentLevel.setGateBudget(GateType::OR, 1);
    currentLevel.setGateBudget(GateType::XOR, 0);
    currentLevel.setGateBudget(GateType::NOT, 0);

    InputOutput* in1 = currentLevel.addIO(2, 0, 1);
    InputOutput* in2 = currentLevel.addIO(4, 0, 1);

    LogicGate* g1 = currentLevel.addGate(3,2,GateType::DEFAULT);

    InputOutput* out1 = currentLevel.addIO(3, 4, 0);

    in1->addDestination(g1->objectID);
    in2->addDestination(g1->objectID);

    g1->addDestination(out1->objectID);

    in1->setState(0,0);
    in2->setState(0,0);

    //Sends a pointer of the created level to the view
    emit sendLevelPointer(&currentLevel);
}

void CircuitGameModel::loadLvl2() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 1);
    currentLevel.setGateBudget(GateType::OR, 0);
    currentLevel.setGateBudget(GateType::XOR, 0);
    currentLevel.setGateBudget(GateType::NOT, 0);

    InputOutput* in1 = currentLevel.addIO(2, 0, 1);
    InputOutput* in2 = currentLevel.addIO(4, 0, 1);

    LogicGate* g1 = currentLevel.addGate(3,2,GateType::DEFAULT);

    InputOutput* out1 = currentLevel.addIO(3, 4, 0);

    in1->addDestination(g1->objectID);
    in2->addDestination(g1->objectID);

    g1->addDestination(out1->objectID);

    in1->setState(0,0);
    in2->setState(0,0);

    //Sends a pointer of the created level to the view
    emit sendLevelPointer(&currentLevel);
}

void CircuitGameModel::loadLvl3() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 2);
    currentLevel.setGateBudget(GateType::OR, 1);
    currentLevel.setGateBudget(GateType::XOR, 0);
    currentLevel.setGateBudget(GateType::NOT, 0);

    InputOutput* in1 = currentLevel.addIO(2, 0, 1);
    InputOutput* in2 = currentLevel.addIO(4, 0, 1);

    //TOGGLEABLE GATE -> EXPECTED: AND
    LogicGate* g1 = currentLevel.addGate(2, 2, GateType::DEFAULT);
    //TOGGLEABLE GATE -> EXPECTED: OR
    LogicGate* g2 = currentLevel.addGate(4, 2, GateType::DEFAULT);

    InputOutput* out1 = currentLevel.addIO(2, 4, 0);
    InputOutput* out2 = currentLevel.addIO(4, 4, 0);

    //Inputs to wires
    in1->addDestination(g1->objectID);
    in2->addDestination(g2->objectID);
    in2->addDestination(g1->objectID);

    //Gates to wires
    g1->addDestination(out1->objectID);
    g2->addDestination(out2->objectID);

    in1->setState(0,0);
    in2->setState(0,0);

    //Sends a pointer of the created level to the view
    emit sendLevelPointer(&currentLevel);
}

void CircuitGameModel::loadLvl4() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 2);
    currentLevel.setGateBudget(GateType::OR, 0);
    currentLevel.setGateBudget(GateType::XOR, 0);
    currentLevel.setGateBudget(GateType::NOT, 0);

    InputOutput* in1 = currentLevel.addIO(1, 0, 1);
    InputOutput* in2 = currentLevel.addIO(3, 0, 1);
    InputOutput* in3 = currentLevel.addIO(5, 0, 1);

    LogicGate* g1 = currentLevel.addGate(4, 2, GateType::DEFAULT);
    LogicGate* g2 = currentLevel.addGate(3, 4, GateType::DEFAULT);

    InputOutput* out1 = currentLevel.addIO(3, 6, 0);


    in1->addDestination(g2->objectID);
    in2->addDestination(g1->objectID);
    in3->addDestination(g1->objectID);

    g1->addDestination(g2->objectID);
    g2->addDestination(out1->objectID);

    emit sendLevelPointer(&currentLevel);
}
