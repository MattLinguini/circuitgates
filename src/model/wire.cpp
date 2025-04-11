#include "wire.h"

Wire::Wire() {}

void Wire::setState(bool state, int senderID) {
    this->state = state;
    sendState();
}

void Wire::sendState() {
    for(GameObject* object : destinations) {
        object->setState(state, this->senderID);
    }
}


