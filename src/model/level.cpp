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
    outputIDs.clear();
}

InputOutput* Level::addIO(int x, int y, bool toggleable,bool inputType, bool expectedState) {
    InputOutput* IO = new InputOutput(x, y, nextID, this, inputType, expectedState);
    IO->objType = GameObject::GameObjectType::IO;
    gameObjs.insert(nextID, IO);
    if (!IO->getInputType()) {
        outputIDs.append(nextID);
    }
    nextID++;
    return IO;
}

LogicGate* Level::addGate(int x, int y, GateType type) {
    LogicGate* gate = new LogicGate(x, y, nextID, type, this);
    gate->objType = GameObject::GameObjectType::GATE;
    gameObjs.insert(nextID, gate);
    nextID++;
    return gate;
}

void Level::setGateBudget(GateType type, int num) {
    this->budget.insert(type, num);
}

QMap<int, GameObject*>* Level::getGameObjs() {
    return &gameObjs;
}

QMap<GateType, int>* Level::getBudget() {
    return &budget;
}

bool Level::validateSolution() {
    qDebug() << "validating...";
    bool win = true;
    InputOutput* IO;

    for (int i : gameObjs.keys()) {
        IO = dynamic_cast<InputOutput*>(gameObjs.value(i));
        if (IO && IO->getInputType()==1) {
            IO->setState(IO->state, -1);
        }
    }


    //Check if all outputs contain the expected state
    for (int i : outputIDs) {
        IO = dynamic_cast<InputOutput*>(gameObjs.value(i));
        if (IO) {
            qDebug() << IO->objectID;
            IO->checkState();
            qDebug() << IO->getExpectedState();
            if (IO->state != IO->getExpectedState()) {
                win = false;
            }
        } else {
            qDebug() << "Warning: Output object " << i << " is not an InputOutput!";
            win = false; // safer fallback
        }
    }
    return win;
}

Level::~Level() {
    qDeleteAll(gameObjs);
    gameObjs.clear();
    outputIDs.clear();
    budget.clear();
}
