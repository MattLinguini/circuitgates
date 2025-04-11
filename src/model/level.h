#ifndef LEVEL_H
#define LEVEL_H

#include <QJsonObject>
#include <vector>
#include "game_object.h"

class Level
{
public:
    Level();

    /// @brief Generates a json representation of this object.
    /// @return A QJsonObject containing this level.
    QJsonObject toJson();

    /// @brief Contains all the GameObjects within a level.
    std::vector<GameObject*> gameObjs;
};

#endif // LEVEL_H
