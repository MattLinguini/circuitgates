#include "level.h"

Level::Level()
{
    gameObjs = QMap<int, GameObject*>();
    budget = QMap<GateType, int>();
}

void Level::addToGameObjs(GameObject *obj) {
    this->gameObjs.insert(obj->objectID, obj);
}

GameObject* Level::objectLookup(int id) {
    return this->gameObjs.value(id);
}

void Level::cleanLevel() {
    nextID = 1;

    for (auto& obj : gameObjs) {
        delete obj;
    }

    gameObjs.clear();
    budget.clear();
}

InputOutput* Level::addIO(int x, int y, bool toggleable) {
    InputOutput* IO = new InputOutput(x, y, nextID, toggleable, this);
    gameObjs.insert(nextID, IO);
    nextID++;
    return IO;
}

LogicGate* Level::addGate(int x, int y, GateType type) {
    LogicGate* gate = new LogicGate(x, y, nextID, type, this);
    gameObjs.insert(nextID, gate);
    nextID++;
    return gate;
}

Wire* Level::addWire(int x, int y, int endX, int endY) {
    Wire* wire = new Wire(x, y, endX, endY, nextID, this);
    gameObjs.insert(nextID, wire);
    nextID ++;
    return wire;
}

void Level::setGateBudget(GateType type, int num) {
    this->budget.insert(type, num);
}

Level::~Level() {
    qDeleteAll(gameObjs);
    gameObjs.clear();
}
