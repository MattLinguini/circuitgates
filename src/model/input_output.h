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
    InputOutput(int x, int y, int objectID, bool toggleable, Level* lvl);

    ///@brief Sends the current state to it's destinations.
    void sendState();

    ///@brief Sets the state of the object.
    void setState(bool state, int senderID = 0) override;

    ///@brief Adds a destination to this objects destinations list.
    void addDestination(int objectID) override;

    ///@brief Gets a gameObject's destinations.
    std::vector<int>* getDestinations() override;

    //TEST METHOD
    void checkState();

private:
    ///@brief Sets whether the object is clickable. (
    bool toggleable;
};

#endif // INPUT_OUTPUT_H
