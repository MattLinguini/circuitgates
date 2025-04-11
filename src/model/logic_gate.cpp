#include "logic_gate.h"

LogicGate::LogicGate() {}

void LogicGate::setState(bool state, int senderID) {
    if (senderID == leftID) {
        leftState = state;
        verifyGate();
        return;
    } else if (senderID == rightID) {
        rightState = state;
        verifyGate();
        return;
    }

    if (leftID == 0) {
        leftID = senderID;
    } else if (rightID == 0) {
        rightID = senderID;
    }
}

void LogicGate::verifyGate() {
    switch(type) {
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
        case GateType::XOR: // TODO: Might have incosistent timing that leads to bugs.
            if (leftState != rightState) {
                state = 1;
            } else {
                state = 0;
            }
            break;
    }
    sendState();
}
