// * Checked by Alex Johnson

/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        24 April, 2025
 * Description: This class manages and tracks currently used gameobjects and provides
 * methods for interactin with the level.
 */

#ifndef LEVEL_H
#define LEVEL_H

#include <QJsonObject>
#include "logic_gate.h"
#include "input_output.h"
#include <QMap>

#include "game_object.h"

using GateType = LogicGate::GateType;

class CircuitGameModel;
class Level
{
public:
    Level();

    /// @brief Gate types.
    //enum class GateType {OR, AND, NOT, XOR, DEFAULT};

    /// @brief Returns a pointer to a requested object.
    /// @id ID of object to lookup.
    GameObject* objectLookup(int id);

    /// @brief Cleans out gameObjs and budget for a new level.
    void cleanLevel();

    /// @brief Adds an IO to the level.
    /// @param x X coordinate
    /// @param y Y coordinate
    /// @param expectedState Used for outputs. When all currentState == expectedState, the is complete.
    InputOutput* addIO(int x, int y, bool inputType, bool expectedState = 0);

    /// @brief Adds a gate to the level.
    /// @param x X coordinate
    /// @param y Y coordinate
    /// @param type The type of the gate.
    LogicGate* addGate(int x, int y, GateType type);

    /// @brief Allows you to modify the level budget.
    /// @param type The type of the gate
    /// @param num The allowed amount of the given gate type.
    void setGateBudget(GateType type, int num);

    /// @brief Returns a pointer to the QMap containing all current gameObjs.
    QMap<int, GameObject*>* getGameObjs();

    /// @brief Returns a pointer to the QMap containing the current level's budget.
    QMap<GateType, int>* getBudget();

    /// @brief Returns true if the level's current solution is valid.
    bool validateSolution();

    /// @brief Connects the level's gameObjs to the model.
    void connectObjsToModel(CircuitGameModel* model);

    /// @brief Cleans up level and it's dependencies.
    ~Level();

private:

    /// @brief Contains all the GameObjects within a level.
    QMap<int, GameObject*> gameObjs;

    /// @brief Map containing the allowed budget for certain gates.
    QMap<GateType, int> budget;

    /// @brief Adds a GameObject to the level's map.
    void addToGameObjs(GameObject *obj);

    /// @brief Tracks the next GameObject ID.
    int nextID = 1;

    /// @brief List of all output IDs.
    QList<int> outputIDs;

};

#endif // LEVEL_H
