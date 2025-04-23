#include "logic_gate.h"
#include "level.h"

LogicGate::LogicGate(int x, int y, int objectID, GateType type, Level* lvl) {
    this->x = x;
    this->y = y;
    this->objectID = objectID;
    this->gateType = type;
    this->parentLevel = lvl;
    this->destinations = std::vector<int>();
}

void LogicGate::setState(bool state, int senderID) {
    if (leftID == -1) {
        leftID = senderID;
    } else if (rightID == -1 && senderID != leftID) {
        rightID = senderID;
    }

    if (senderID == leftID) {
        leftState = state;
        verifyGate();
        return;
    } else if (senderID == rightID) {
        rightState = state;
        verifyGate();
        return;
    }
}

void LogicGate::verifyGate() {
    switch(gateType) {
        case GateType::OR:
            if (leftState == 1 | rightState == 1) {
                state = 1;
            } else {
                state = 0;
            }
            break;
        case GateType::AND:
            if (leftState == 1 & rightState == 1) {
                state = 1;
            } else {
                state = 0;
            }
            break;
        case GateType::NOT:
            if (leftState == 1) {
                state = 0;
            } else {
                state = 1;
            }
            break;
        case GateType::XOR:
            if (leftState != rightState) {
                state = 1;
            } else {
                state = 0;
            }
            break;
        case GateType::DEFAULT:
            state = 0;
            break;
    }
    sendState();
}

void LogicGate::sendState() {
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

void LogicGate::updateType(GateType type) {
    this->gateType = type;
}

void LogicGate::addDestination(int objectID) {
    this->destinations.push_back(objectID);
}

///@brief Returns the gates gateType.
GateType LogicGate::getGateType() {
    return gateType;
}

void LogicGate::setGateType(GateType gateType) {
    this->gateType = gateType;
}

std::vector<int>* LogicGate::getDestinations() {
    return &destinations;
}

void LogicGate::checkState() {
    qDebug() << state;
}
