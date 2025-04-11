#ifndef WIRE_H
#define WIRE_H

#include "game_object.h"
class Wire : public GameObject
{
public:
    Wire();

    ///@brief Sets the wire's state.
    void setState(bool state, int senderID) override;

    ///@brief Sends the wire's state.
    void sendState();
};

#endif // WIRE_H
