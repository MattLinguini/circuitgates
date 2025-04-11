#include "input_output.h"

using std::vector;

InputOutput::InputOutput() {}

void InputOutput::setState(bool state, int) {
    this->state = state;
    sendState();
}

void InputOutput::sendState() {
    //TODO: May need destinations != nullptr check.
    for (GameObject* object : destinations) {
        object->setState(state);
    }
}
