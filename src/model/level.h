#ifndef LEVEL_H
#define LEVEL_H

#include <QJsonObject>
#include <vector>
#include "logic_gate.h"
#include "input_output.h"
#include "wire.h"
#include <QMap>

#include "game_object.h"

class Level
{
public:
    Level();

    ///@brief Gate types.
    enum class GateType {OR, AND, NOT, XOR, DEFAULT};

    /// @brief Constructor for a level object using a QJsonObject as reference.
    /// @param QJsonObject - the json structure to base this level off of.
    Level(const QJsonObject& obj);

    /// @brief Generates a json representation of this object.
    /// @return A QJsonObject containing this level.
    QJsonObject toJson();

  //  std::vector<GameObject*> gameObjs;

    void addToGameObjs(GameObject *obj);

    GameObject* objectLookup(int id);

private:

    /// @brief Contains all the GameObjects within a level.
    QMap<int, GameObject*> gameObjs;

    /// @brief Map containing the allowed budget for certain gates.
    QMap<GateType, int> budget;

};

#endif // LEVEL_H
