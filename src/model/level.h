#ifndef LEVEL_H
#define LEVEL_H

#include <QJsonObject>
#include <vector>
#include "game_object.h"
#include <map>

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

    /// @brief Contains all the GameObjects within a level.
    std::vector<GameObject*> gameObjs;

    /// @brief Map containing the allowed budget for certain gates.
    std::map<GateType, int> budget;

};

#endif // LEVEL_H
