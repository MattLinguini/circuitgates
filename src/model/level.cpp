#include "level.h"

Level::Level() {}

Level::Level(const QJsonObject& obj) {

}

QJsonObject Level::toJson() {
    return QJsonObject();
}

void Level::addToGameObjs(GameObject *obj) {
    this->gameObjs.insert(obj->objectID, obj);
}

GameObject* Level::objectLookup(int id) {
    return this->gameObjs.value(id);
}
