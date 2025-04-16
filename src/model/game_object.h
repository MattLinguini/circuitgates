/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        10 April, 2025
 * Description: Pure virtual game object class. Does not contain a concrete implementation.
 */

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <QObject>

class GameObject : public QObject
{
    Q_OBJECT
public:
    explicit GameObject(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~GameObject() = default;

    ///@brief Sets the state of the object.
    virtual void setState(bool state, int senderID = 0) = 0;

signals:
    void stateChanged(int objectID, bool state);

protected:
    ///@brief On or off.
    bool state = 0;

    ///@brief Object ID.
    int objectID;

    ///@brief Object's x coordinate.
    int x;

    ///@brief Object's y coordinate.
    int y;

    ///@brief Where this game object points to.
    std::vector<GameObject*> destinations;
};

#endif // GAME_OBJECT_H
