#include "src/model/circuit_game_model.h"
#include <QJsonDocument>
#include <QFile>
#include <QByteArray>

CircuitGameModel::CircuitGameModel(QObject *parent) : QObject(parent) {}

void CircuitGameModel::createLevel(int levelId) {
    Level lvl = Level();

    InputOutput in1 = InputOutput(0,0, 1, 0, &lvl);
    InputOutput in2 = InputOutput(0,0, 2, 0, &lvl);
    Wire w1 = Wire(0,0,1,2,3, &lvl);
    Wire w2 = Wire(0,0,4,1,4, &lvl);
    LogicGate orGate = LogicGate(0,0,5,LogicGate::GateType::OR, &lvl);
    InputOutput out = InputOutput(0,0,6,0, &lvl);

    lvl.addToGameObjs(&in1);
    lvl.addToGameObjs(&in2);
    lvl.addToGameObjs(&w1);
    lvl.addToGameObjs(&w2);
    lvl.addToGameObjs(&orGate);
    lvl.addToGameObjs(&out);

    in1.addDestination(w1.objectID);
    in2.addDestination(w2.objectID);
    w1.addDestination(orGate.objectID);
    w2.addDestination(orGate.objectID);
    orGate.addDestination(out.objectID);

    //out.checkState();

    in1.setState(1,0);
    in1.checkState();
    w1.checkState();
    out.checkState();

   in2.setState(1,0);
    in2.checkState();
    w2.checkState();
   out.checkState();

    in1.setState(0,0);
    out.checkState();

    in2.setState(0,0);
    out.checkState();


}

