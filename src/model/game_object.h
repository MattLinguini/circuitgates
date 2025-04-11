/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        10 April, 2025
 * Description: Pure virtual game object class. Does not contain a concrete implementation.
 */

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>

class GameObject
{
public:
    ///@brief Sets the state of the object.
    virtual void setState(bool state, int senderID = 0) = 0;

protected:
    ///@brief On or off.
    bool state;

    ///@brief Object ID.
    int senderID;

    ///@brief Where this game object points to.
    std::vector<GameObject*> destinations;
};

#endif // GAME_OBJECT_H
