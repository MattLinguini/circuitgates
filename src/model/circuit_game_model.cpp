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
    }
}

void CircuitGameModel::loadLvl1() {
    InputOutput* io1 = currentLevel.addIO(2, 0, 1);
    InputOutput* io2 = currentLevel.addIO(4, 0, 1);

    Wire* w1 = currentLevel.addWire(2, 0, 3, 2);
    Wire* w2 = currentLevel.addWire(4, 0, 3, 2);

    LogicGate* g1 = currentLevel.addGate(3,2,GateType::OR);

    Wire* w3 = currentLevel.addWire(3,2,3,4);

    InputOutput* io3 = currentLevel.addIO(3, 4, 0);

    io1->addDestination(w1->objectID);
    io2->addDestination(w2->objectID);

    w1->addDestination(g1->objectID);
    w2->addDestination(g1->objectID);

    g1->addDestination(w3->objectID);

    w3->addDestination(io3->objectID);

    io1->setState(0,0);
    io2->setState(0,0);

    io3->checkState();
}

void CircuitGameModel::loadLvl2() {
    InputOutput* in1 = currentLevel.addIO(2, 0, 1);
    InputOutput* in2 = currentLevel.addIO(4, 0, 1);

    Wire* w1 = currentLevel.addWire(2, 0, 3, 2);
    Wire* w2 = currentLevel.addWire(4, 0, 3, 2);

    LogicGate* g1 = currentLevel.addGate(3,2,GateType::AND);

    Wire* w3 = currentLevel.addWire(3,2,3,4);

    InputOutput* out1 = currentLevel.addIO(3, 4, 0);

    in1->addDestination(w1->objectID);
    in2->addDestination(w2->objectID);

    w1->addDestination(g1->objectID);
    w2->addDestination(g1->objectID);

    g1->addDestination(w3->objectID);

    w3->addDestination(out1->objectID);

    in1->setState(0,0);
    in2->setState(0,0);

    out1->checkState();
}

void CircuitGameModel::loadLvl3() {
    InputOutput* in1 = currentLevel.addIO(2, 0, 1);
    InputOutput* in2 = currentLevel.addIO(4, 0, 1);

    //From input1 to gate1
    Wire* w1 = currentLevel.addWire(2, 0, 2, 2);
    //From intput2 to gate1
    Wire* w2 = currentLevel.addWire(4, 0, 4, 2);
    //From input2 to gate2
    Wire* w3 = currentLevel.addWire(4, 0, 2, 2);

    //TOGGLEABLE GATE -> EXPECTED: AND
    LogicGate* g1 = currentLevel.addGate(2, 2, GateType::AND);
    //TOGGLEABLE GATE -> EXPECTED: OR
    LogicGate* g2 = currentLevel.addGate(4, 2, GateType::OR);

    //From gate1 to output1
    Wire* w4 = currentLevel.addWire(2, 2, 2, 4);
    //From gate2 to output2
    Wire* w5 = currentLevel.addWire(4, 2, 4, 4);

    InputOutput* out1 = currentLevel.addIO(2, 4, 0);
    InputOutput* out2 = currentLevel.addIO(4, 4, 0);

    //Inputs to wires
    in1->addDestination(w1->objectID);
    in2->addDestination(w2->objectID);
    in2->addDestination(w3->objectID);

    //Wires to gates
    w1->addDestination(g1->objectID);
    w2->addDestination(g2->objectID);
    w3->addDestination(g1->objectID);

    //Gates to wires
    g1->addDestination(w4->objectID);
    g2->addDestination(w5->objectID);

    //Wires to outputs
    w4->addDestination(out1->objectID);
    w5->addDestination(out2->objectID);

    in1->setState(0,0);
    in2->setState(0,0);
    out1->checkState();
    out2->checkState();
}

