#include "input_output.h"
#include <QDebug>
#include "level.h"

using std::vector;

InputOutput::InputOutput(int x, int y, int objectID, bool toggleable, Level* lvl)
{
    this->x = x;
    this->y = y;
    this->objectID = objectID;
    this->toggleable = toggleable;
    this->parentLevel = lvl;
    destinations = std::vector<int>();
}

void InputOutput::setState(bool state, int) {
    this->state = state;
    sendState();
}

void InputOutput::sendState() {
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

void  InputOutput::addDestination(int objectID) {
    this->destinations.push_back(objectID);
}

void InputOutput::checkState() {
    qDebug() << state;
}

std::vector<int>* InputOutput::getDestinations() {
    return &destinations;
}
