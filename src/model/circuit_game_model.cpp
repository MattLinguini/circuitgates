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

    }
}

void CircuitGameModel::loadLvl1() {
    InputOutput* io1 = currentLevel.addIO(2, 0, 0);
    InputOutput* io2 = currentLevel.addIO(4, 0, 0);

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

