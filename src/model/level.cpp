#include "level.h"

Level::Level() {}

void Level::addToGameObjs(GameObject *obj) {
    this->gameObjs.insert(obj->objectID, obj);
}

GameObject* Level::objectLookup(int id) {
    return this->gameObjs.value(id);
}
