#ifndef WIRE_H
#define WIRE_H

#include "game_object.h"
class Wire : public GameObject
{
public:
    Wire(int x, int y, int endX, int endY, int objectID);

    ///@brief Sets the wire's state.
    void setState(bool state, int senderID) override;

    ///@brief Sends the wire's state.
    void sendState();

    ///@brief The end X for the wire.
    int endX;

    ///@brief The end Y for the wire.
    int endY;

    ///@brief Adds a destination to this objects destinations list.
    void addDestination(GameObject* address) override;
};

#endif // WIRE_H
