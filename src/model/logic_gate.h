// * Checked by Alex JOhnson

/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        10 April, 2025
 * Description: Logic gate object.
 */

#ifndef LOGIC_GATE_H
#define LOGIC_GATE_H

#include "game_object.h"

class LogicGate : public GameObject
{
public:
    ///@brief Gate types.
    enum class GateType {OR, AND, NOT, XOR, DEFAULT};

    ///@brief Constructor.
    LogicGate(int x, int y, int objectID, GateType type, Level* lvl);

    ///@brief Sets the state of the logic gate object.
    void setState(bool state, int senderID = 0) override;

    ///@brief Checks incoming signals and determines appropriate logic gate output.
    void verifyGate();

    ///@brief Sends the current state to it's destinations.
    void sendState();

    ///@brief Updates the gate type.
    void updateType(GateType type);

    ///@brief Adds a destination to this objects destinations list.
    void addDestination(int objectID) override;

    ///@brief Gets a gameObject's destinations.
    std::vector<int>* getDestinations() override;

    ///@brief Returns the gates type.
    GateType getGateType();

    void setGateType(GateType gateType);

private:
    ///@brief Type of the gate.
    GateType gateType;

    ///@brief ID of left wire.
    int leftID = -1;

    ///@brief ID of right wire.
    int rightID = -1;

    ///@brief State of left wire.
    bool leftState = 0;

    ///@brief State of right wire.
    bool rightState = 0;
};

#endif // LOGIC_GATE_H
