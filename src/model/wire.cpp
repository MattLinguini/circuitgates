#include "wire.h"

Wire::Wire(int x, int y, int endX, int endY, int objectID) {
    this->x = x;
    this->y = y;
    this->endX = endX;
    this->endY = endY;
    this->objectID = objectID;
    destinations = std::vector<GameObject*>();
}

void Wire::setState(bool state, int senderID) {
    this->state = state;
    sendState();
}

void Wire::sendState() {
    for(GameObject* object : destinations) {
        object->setState(state, this->objectID);
        emit object->stateChanged(this->objectID, this->state);
    }
}

void Wire::addDestination(GameObject* address) {
    this->destinations.push_back(address);
}

