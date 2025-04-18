/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        10 April, 2025
 * Description: Pure virtual game object class. Does not contain a concrete implementation.
 */

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <QObject>
//TODO: REMOVE
#include <QDebug>

class Level;

class GameObject : public QObject
{
    Q_OBJECT
public:
    explicit GameObject(QObject* parent = nullptr, Level* lvl = nullptr) : QObject(parent), parentLevel(lvl) {}
    virtual ~GameObject() = default;

    ///@brief Sets the state of the object.
    virtual void setState(bool state, int senderID = 0) = 0;

    ///@brief Adds a destination to this objects destinations list.
    virtual void addDestination(int objectID) = 0;

    ///@brief Gets a gameObject's destinations.
    virtual std::vector<int>* getDestinations() = 0;

    ///@brief Describes the type of game object
    enum class GameObjectType {GATE, IO};

    ///@brief Object ID.
    int objectID;

    ///@brief On or off.
    bool state = 0;

    GameObjectType objType;

    ///@brief Object's x coordinate.
    int x;

    ///@brief Object's y coordinate.
    int y;

    bool inView = 0;

signals:
    ///@brief Signals to the view to update object state.
    void stateChanged(int objectID, bool state);

protected:
    ///@brief Reference to the level that this object is stored in.
    Level* parentLevel;

    ///@brief Where this game object points to.
    std::vector<int> destinations;

};

#endif // GAME_OBJECT_H
