// * Checked by Adam Wightman

/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        10 April, 2025
 * Description: Input/Output game object that sends or receives a signal.
 */

#include "input_output.h"
#include <QDebug>
#include "level.h"

using std::vector;

InputOutput::InputOutput(int x, int y, int objectID, Level* lvl, bool inputType, bool expectedState)
{
    this->x = x;
    this->y = y;
    this->objectID = objectID;
    this->parentLevel = lvl;
    this->inputType = inputType;
    this->expectedState = expectedState;
    destinations = std::vector<int>();
}

void InputOutput::setState(bool state, int) {
    this->state = state;
    emit this->stateChanged(this->objectID, this->state);
    sendState();
}

void InputOutput::sendState() {
    for (int i : destinations) {
        GameObject* obj = dynamic_cast<GameObject*>(this->parentLevel->objectLookup(i));
        if (obj) {
            obj->setState(this->state, this->objectID);
        } else {
            qDebug() << "Warning: object ID" << i << "not found in Level!";
        }
    }
}

void  InputOutput::addDestination(int objectID) {
    this->destinations.push_back(objectID);
}


bool InputOutput::getExpectedState() const{
    return expectedState;
}

std::vector<int>* InputOutput::getDestinations() {
    return &destinations;
}

bool InputOutput::getInputType() {
    return inputType;
}
