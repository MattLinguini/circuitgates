#include "src/model/circuitgame_model.h"
#include <QJsonDocument>
#include <QFile>

CircuitGame_Model::CircuitGame_Model() {}

void CircuitGame_Model::saveLevel() {
    QJsonDocument jsonDoc(currentLevel.toJson());
    QFile file(":test.txt");
    QByteArray data = jsonDoc.toJson();

    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();
}
