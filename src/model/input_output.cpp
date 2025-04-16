#include "input_output.h"

using std::vector;

InputOutput::InputOutput(int x, int y, int objectID, bool toggleable)
{
    this->x = x;
    this->y = y;
    this->objectID = objectID;
    this->toggleable = toggleable;
    destinations = std::vector<GameObject*>();
}

void InputOutput::setState(bool state, int) {
    this->state = state;
    sendState();
}

void InputOutput::sendState() {
    //TODO: May need destinations != nullptr check.
    for (GameObject* object : destinations) {
        object->setState(state);
        emit object->stateChanged(this->objectID, this->state);
    }
}
