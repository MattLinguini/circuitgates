// * Checked by Alex Johnson

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
    InputOutput(int x, int y, int objectID, Level* lvl,bool inputType, bool expectedState = 0);

    ///@brief Sends the current state to it's destinations.
    void sendState();

    ///@brief Sets the state of the object.
    void setState(bool state, int senderID = 0) override;

    ///@brief Adds a destination to this objects destinations list.
    void addDestination(int objectID) override;

    ///@brief Gets a gameObject's destinations.
    std::vector<int>* getDestinations() override;

    ///@brief Returns the outputs expected state.
    bool getExpectedState() const;

    /// @brief Returns the inputType;
    bool getInputType();

private:

    ///@brief State that an output must be in for the level to be won.
    bool expectedState;

    ///@brief 1 if IO is an input, 0 if IO is an output.
    bool inputType;
};

#endif // INPUT_OUTPUT_H
