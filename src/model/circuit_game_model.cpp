// * Checked by ?

/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        24 April, 2025
 * Description: ?
 */

#include "src/model/circuit_game_model.h"
#include <QJsonDocument>
#include <QFile>
#include <QByteArray>
#include "game_object.h"

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
    case 5:
        loadLvl5();
        break;
    case 6:
        loadLvl6();
        break;
    case 7:
        loadLvl7();
        break;
    case 8:
        loadLvl8();
        break;
    case 9:
        loadLvl9();
        break;
    case 10:
        loadLvl10();
        break;
    case -1:
        loadTutorial();
        break;
    }
}

void CircuitGameModel::receiveObjectUpdate(int id, bool state) {
    emit emitObjectState(id, state);
}

void CircuitGameModel::updateGate(int id, LogicGate::GateType gateType) {
    GameObject* obj = currentLevel.getGameObjs()->value(id);
    LogicGate* gate = dynamic_cast<LogicGate*>(obj);
    if (gate != nullptr) {
        gate->setGateType(gateType);
        if (currentLevel.validateSolution()) {
            emit sendWinToView();
        }
    }
}

void CircuitGameModel::updateIO(int id, bool state) {
    InputOutput* obj = dynamic_cast<InputOutput*>(this->currentLevel.objectLookup(id));
    if (obj->getInputType()) {
        obj->setState(state, 0);
        if (currentLevel.validateSolution()) {
            emit sendWinToView();
        }
    }
}

void CircuitGameModel::loadTutorial() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 1);
    currentLevel.setGateBudget(GateType::OR, 1);
    currentLevel.setGateBudget(GateType::XOR, 1);
    currentLevel.setGateBudget(GateType::NOT, 1);

    InputOutput* in1 = currentLevel.addIO(3, 1, 1, 1);
    LogicGate* g1 = currentLevel.addGate(3, 3, GateType::DEFAULT);
    InputOutput* out1 = currentLevel.addIO(3, 5, 0, 1);

    in1->addDestination(g1->objectID);
    g1->addDestination(out1->objectID);

    in1->setState(0, 0);
    out1->setState(0, 0);

    currentLevel.connectObjsToModel(this);

    emit sendLevelPointer(&currentLevel);
}

void CircuitGameModel::loadLvl1() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 0);
    currentLevel.setGateBudget(GateType::OR, 1);
    currentLevel.setGateBudget(GateType::XOR, 0);
    currentLevel.setGateBudget(GateType::NOT, 0);

    InputOutput* in1 = currentLevel.addIO(2, 1,1, 1);
    InputOutput* in2 = currentLevel.addIO(4, 1, 1, 1);

    LogicGate* g1 = currentLevel.addGate(3,3,GateType::DEFAULT);

    InputOutput* out1 = currentLevel.addIO(3, 5, 0, 1);

    in1->addDestination(g1->objectID);
    in2->addDestination(g1->objectID);

    g1->addDestination(out1->objectID);

    in1->setState(0,0);
    in2->setState(0,0);

    currentLevel.connectObjsToModel(this);

    //Sends a pointer of the created level to the view
    emit sendLevelPointer(&currentLevel);
}

void CircuitGameModel::loadLvl2() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 1);
    currentLevel.setGateBudget(GateType::OR, 0);
    currentLevel.setGateBudget(GateType::XOR, 0);
    currentLevel.setGateBudget(GateType::NOT, 0);

    InputOutput* in1 = currentLevel.addIO(2, 1, 1, 1);
    InputOutput* in2 = currentLevel.addIO(4, 1, 1, 1);

    LogicGate* g1 = currentLevel.addGate(3, 3, GateType::DEFAULT);

    InputOutput* out1 = currentLevel.addIO(3, 5, 0, 1);

    in1->addDestination(g1->objectID);
    in2->addDestination(g1->objectID);

    g1->addDestination(out1->objectID);

    in1->setState(0,0);
    in2->setState(0,0);

    currentLevel.connectObjsToModel(this);

    //Sends a pointer of the created level to the view
    emit sendLevelPointer(&currentLevel);
}

void CircuitGameModel::loadLvl3() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 2);
    currentLevel.setGateBudget(GateType::OR, 1);
    currentLevel.setGateBudget(GateType::XOR, 0);
    currentLevel.setGateBudget(GateType::NOT, 0);

    InputOutput* in1 = currentLevel.addIO(2, 1, 1, 1);
    InputOutput* in2 = currentLevel.addIO(4, 1, 1, 1);

    //TOGGLEABLE GATE -> EXPECTED: AND
    LogicGate* g1 = currentLevel.addGate(2, 3, GateType::DEFAULT);
    //TOGGLEABLE GATE -> EXPECTED: OR
    LogicGate* g2 = currentLevel.addGate(4, 3, GateType::DEFAULT);

    InputOutput* out1 = currentLevel.addIO(2, 5, 0, 1);
    InputOutput* out2 = currentLevel.addIO(4, 5, 0, 1);

    //Inputs to wires
    in1->addDestination(g1->objectID);
    in2->addDestination(g2->objectID);
    in2->addDestination(g1->objectID);

    //Gates to wires
    g1->addDestination(out1->objectID);
    g2->addDestination(out2->objectID);

    in1->setState(0,0);
    in2->setState(0,0);

    currentLevel.connectObjsToModel(this);

    //Sends a pointer of the created level to the view
    emit sendLevelPointer(&currentLevel);
}

void CircuitGameModel::loadLvl4() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 2);
    currentLevel.setGateBudget(GateType::OR, 0);
    currentLevel.setGateBudget(GateType::XOR, 0);
    currentLevel.setGateBudget(GateType::NOT, 0);

    InputOutput* in1 = currentLevel.addIO(1, 0, 1, 1);
    InputOutput* in2 = currentLevel.addIO(3, 0, 1, 1);
    InputOutput* in3 = currentLevel.addIO(5, 0, 1, 1);

    LogicGate* g1 = currentLevel.addGate(4, 2, GateType::DEFAULT);
    LogicGate* g2 = currentLevel.addGate(3, 4, GateType::DEFAULT);

    InputOutput* out1 = currentLevel.addIO(3, 6, 0, 1);


    in1->addDestination(g2->objectID);
    in2->addDestination(g1->objectID);
    in3->addDestination(g1->objectID);

    g1->addDestination(g2->objectID);
    g2->addDestination(out1->objectID);

    currentLevel.connectObjsToModel(this);

    emit sendLevelPointer(&currentLevel);
}

void CircuitGameModel::loadLvl5() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 2);
    currentLevel.setGateBudget(GateType::OR, 0);
    currentLevel.setGateBudget(GateType::XOR, 1);
    currentLevel.setGateBudget(GateType::NOT, 0);

    InputOutput* in1 = currentLevel.addIO(0, 0, 1, 1);
    InputOutput* in2 = currentLevel.addIO(2, 0, 1, 1);
    InputOutput* in3 = currentLevel.addIO(4, 0 ,1, 1);
    InputOutput* in4 = currentLevel.addIO(6, 0, 1, 1);

    //TOGGLEABLE GATE -> EXPECTED: AND
    LogicGate* g1 = currentLevel.addGate(1, 2, GateType::DEFAULT);
    //TOGGLEABLE GATE -> EXPECTED: XOR
    LogicGate* g2 = currentLevel.addGate(5, 2, GateType::DEFAULT);

    in1->addDestination(g1->objectID);
    in2->addDestination(g1->objectID);
    in3->addDestination(g2->objectID);
    in4->addDestination(g2->objectID);

    //TOGGLEABLE GATE -> EXPECTED: AND
    LogicGate* g3 = currentLevel.addGate(3, 4, GateType::DEFAULT);

    in2->addDestination(g3->objectID);
    g2->addDestination(g3->objectID);

    InputOutput* out1 = currentLevel.addIO(1,6, 0, 0);
    InputOutput* out2 = currentLevel.addIO(5, 6, 0, 1);

    g1->addDestination(out1->objectID);
    g3->addDestination(out2->objectID);

    currentLevel.connectObjsToModel(this);

    emit sendLevelPointer(&currentLevel);
}

void CircuitGameModel::loadLvl6() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 1);
    currentLevel.setGateBudget(GateType::OR, 0);
    currentLevel.setGateBudget(GateType::XOR, 0);
    currentLevel.setGateBudget(GateType::NOT, 1);

    InputOutput* in1 = currentLevel.addIO(2, 1, 1,1);
    InputOutput* in2 = currentLevel.addIO(4, 1, 1, 1);

    //TOGGLEABLE GATE -> EXPECTED: AND
    LogicGate* g1 = currentLevel.addGate(2, 3, GateType::DEFAULT);
    //TOGGLEABLE GATE -> EXPECTED: NOT
    LogicGate* g2 = currentLevel.addGate(4, 3, GateType::DEFAULT);

    InputOutput* out1 = currentLevel.addIO(2, 5, 0, 1);
    InputOutput* out2 = currentLevel.addIO(4, 5, 0, 0);

    //Inputs to wires
    in1->addDestination(g1->objectID);
    in1->addDestination(g2->objectID);
    in2->addDestination(g2->objectID);

    //Gates to wires
    g1->addDestination(out1->objectID);
    g2->addDestination(out2->objectID);

    in1->setState(0,0);
    in2->setState(1,0);

    currentLevel.connectObjsToModel(this);

    //Sends a pointer of the created level to the view
    emit sendLevelPointer(&currentLevel);
}

void CircuitGameModel::loadLvl7() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 0);
    currentLevel.setGateBudget(GateType::OR, 1);
    currentLevel.setGateBudget(GateType::XOR, 1);
    currentLevel.setGateBudget(GateType::NOT, 0);

    InputOutput* in1 = currentLevel.addIO(1, 1, 1, 1);
    InputOutput* in2 = currentLevel.addIO(3, 1, 1, 1);
    InputOutput* in3 = currentLevel.addIO(5, 1, 1, 1);

    //TOGGLEABLE GATE -> EXPECTED: XOR
    LogicGate* g1 = currentLevel.addGate(2, 3, GateType::DEFAULT);
    //TOGGLEABLE GATE -> EXPECTED: OR
    LogicGate* g2 = currentLevel.addGate(4, 3, GateType::DEFAULT);

    InputOutput* out1 = currentLevel.addIO(2, 5, 0, 1);
    InputOutput* out2 = currentLevel.addIO(4, 5, 0, 0);

    //Inputs to wires
    in1->addDestination(g1->objectID);
    in2->addDestination(g1->objectID);
    in2->addDestination(g2->objectID);
    in3->addDestination(g2->objectID);

    //Gates to wires
    g1->addDestination(out1->objectID);
    g2->addDestination(out2->objectID);

    in1->setState(1,0);
    in2->setState(1,0);
    in3->setState(0,0);

    currentLevel.connectObjsToModel(this);

    //Sends a pointer of the created level to the view
    emit sendLevelPointer(&currentLevel);
}

void CircuitGameModel::loadLvl8() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 1);
    currentLevel.setGateBudget(GateType::OR, 0);
    currentLevel.setGateBudget(GateType::XOR, 1);
    currentLevel.setGateBudget(GateType::NOT, 1);

    InputOutput* in1 = currentLevel.addIO(1, 0, 1, 1);
    InputOutput* in2 = currentLevel.addIO(3, 0, 1, 1);
    InputOutput* in3 = currentLevel.addIO(5, 0, 1, 1);

    //TOGGLEABLE GATE -> EXPECTED: XOR
    LogicGate* g1 = currentLevel.addGate(2, 2, GateType::DEFAULT);
    //TOGGLEABLE GATE -> EXPECTED: AND
    LogicGate* g2 = currentLevel.addGate(4, 2, GateType::DEFAULT);
    //TOGGLEABLE GATE -> EXPECTED: NOT
    LogicGate* g3 = currentLevel.addGate(4, 4, GateType::DEFAULT);

    InputOutput* out1 = currentLevel.addIO(2, 4, 0, 1);
    InputOutput* out2 = currentLevel.addIO(4, 6, 0, 1);

    //Inputs to wires
    in1->addDestination(g1->objectID);
    in2->addDestination(g2->objectID);
    in2->addDestination(g1->objectID);
    in3->addDestination(g3->objectID);

    //Gates to wires
    g1->addDestination(out1->objectID);
    g2->addDestination(g3->objectID);
    g3->addDestination(out2->objectID);

    in1->setState(0,0);
    in2->setState(1,0);
    in3->setState(0,0);

    currentLevel.connectObjsToModel(this);

    //Sends a pointer of the created level to the view
    emit sendLevelPointer(&currentLevel);
}

void CircuitGameModel::loadLvl9() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 1);
    currentLevel.setGateBudget(GateType::OR, 0);
    currentLevel.setGateBudget(GateType::XOR, 1);
    currentLevel.setGateBudget(GateType::NOT, 1);

    InputOutput* in1 = currentLevel.addIO(1, 0, 1, 1);
    InputOutput* in2 = currentLevel.addIO(3, 0, 1, 1);
    InputOutput* in3 = currentLevel.addIO(5, 0, 1, 1);

    //TOGGLEABLE GATE -> EXPECTED: NOT
    LogicGate* g1 = currentLevel.addGate(5, 1, GateType::DEFAULT);
    //TOGGLEABLE GATE -> EXPECTED: XOR
    LogicGate* g2 = currentLevel.addGate(3, 2, GateType::DEFAULT);
    //TOGGLEABLE GATE -> EXPECTED: AND
    LogicGate* g3 = currentLevel.addGate(2, 4, GateType::DEFAULT);

    InputOutput* out1 = currentLevel.addIO(1, 6, 0, 1);

    //Inputs to wires
    in1->addDestination(g3->objectID);
    in2->addDestination(g2->objectID);
    in3->addDestination(g1->objectID);

    //Gates to wires
    g1->addDestination(g2->objectID);
    g2->addDestination(g3->objectID);
    g3->addDestination(out1->objectID);

    in1->setState(1,0);
    in2->setState(0,0);
    in3->setState(0,0);

    currentLevel.connectObjsToModel(this);

    //Sends a pointer of the created level to the view
    emit sendLevelPointer(&currentLevel);
}

void CircuitGameModel::loadLvl10() {
    //Set the level's budget
    currentLevel.setGateBudget(GateType::AND, 0);
    currentLevel.setGateBudget(GateType::OR, 1);
    currentLevel.setGateBudget(GateType::XOR, 2);
    currentLevel.setGateBudget(GateType::NOT, 0);

    InputOutput* in1 = currentLevel.addIO(1, 0, 1, 1);
    InputOutput* in2 = currentLevel.addIO(3, 0, 1, 1);
    InputOutput* in3 = currentLevel.addIO(5, 0, 1, 1);

    //TOGGLEABLE GATE -> EXPECTED: XOR
    LogicGate* g1 = currentLevel.addGate(2, 2, GateType::DEFAULT);
    //TOGGLEABLE GATE -> EXPECTED: OR
    LogicGate* g2 = currentLevel.addGate(4, 2, GateType::DEFAULT);
    //TOGGLEABLE GATE -> EXPECTED: XOR
    LogicGate* g3 = currentLevel.addGate(3, 4, GateType::DEFAULT);

    InputOutput* out1 = currentLevel.addIO(3, 6, 0, 0);

    //Inputs to wires
    in1->addDestination(g1->objectID);
    in2->addDestination(g1->objectID);
    in2->addDestination(g2->objectID);
    in3->addDestination(g2->objectID);

    //Gates to wires
    g1->addDestination(g3->objectID);
    g2->addDestination(g3->objectID);
    g3->addDestination(out1->objectID);

    in1->setState(0,0);
    in2->setState(1,0);
    in3->setState(1,0);

    currentLevel.connectObjsToModel(this);

    //Sends a pointer of the created level to the view
    emit sendLevelPointer(&currentLevel);
}
