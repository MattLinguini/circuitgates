#include "input_output.h"

using std::vector;

InputOutput::InputOutput() {}

void InputOutput::setState(bool state, int) {
    this->state = state;
}

void InputOutput::sendState() {
    for (GameObject* object : destinations) {
        object->setState(state);
    }
}
