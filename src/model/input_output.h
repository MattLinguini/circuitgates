/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        10 April, 2025
 * Description: Input/Output game object that sends or receives a signal.
 */

#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include "game_object.h"

class InputOutput : public GameObject
{
public:
    ///@brief Constructor.
    InputOutput();

    ///@brief Sends the current state to it's destinations.
    void sendState();

    void setState(bool state, int senderID = 0) override;
};

#endif // INPUT_OUTPUT_H
