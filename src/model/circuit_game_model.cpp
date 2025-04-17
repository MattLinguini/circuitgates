#include "src/model/circuit_game_model.h"
#include <QJsonDocument>
#include <QFile>
#include <QByteArray>

CircuitGameModel::CircuitGameModel(QObject *parent) : QObject(parent) {}

void CircuitGameModel::saveLevel() {
    QJsonDocument jsonDoc(currentLevel.toJson());
    QFile file(":test.txt");
    QByteArray data = jsonDoc.toJson();

    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();
}

void CircuitGameModel::loadLevel() {
    QFile file(":test.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject levelJson = doc.object();

        currentLevel = Level(levelJson);
    }
}

void CircuitGameModel::createLevel() {
    InputOutput in = InputOutput(0,0, 1, 0);
    Wire w1 = Wire(0,0,1,2,2);
    LogicGate notGate = LogicGate(0,0,3,LogicGate::GateType::NOT);
    Wire w2 = Wire(0,0,4,1,3);
    InputOutput out = InputOutput(0,0,5,0);
    in.addDestination(&w1);
    w1.addDestination(&notGate);
    notGate.addDestination(&w2);
    w2.addDestination(&out);

    in.checkState();
    out.checkState();
    in.setState(1, 0);
    in.checkState();
    out.checkState();

    // in.checkState();
    // out.checkState();
    in.setState(0, 0);
    in.checkState();
    out.checkState();

}

