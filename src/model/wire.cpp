#include "wire.h"
#include "level.h"

Wire::Wire(int x, int y, int endX, int endY, int objectID, Level* lvl) {
    this->x = x;
    this->y = y;
    this->endX = endX;
    this->endY = endY;
    this->objectID = objectID;
    this->parentLevel = lvl;
    destinations = std::vector<int>();
}

void Wire::setState(bool state, int senderID) {
    this->state = state;
    sendState();
}

void Wire::sendState() {
    for (int i : destinations) {
        GameObject* obj = dynamic_cast<GameObject*>(this->parentLevel->objectLookup(i));
        if (obj) {
            emit obj->stateChanged(this->objectID, this->state);
            obj->setState(this->state, this->objectID);
        } else {
            qDebug() << "Warning: object ID" << i << "not found in Level!";
        }
    }
}

void Wire::addDestination(int objectID) {
    this->destinations.push_back(objectID);
}

void Wire::checkState() {
    qDebug() << state;
}
