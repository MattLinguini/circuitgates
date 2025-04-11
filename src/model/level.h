#ifndef LEVEL_H
#define LEVEL_H

#include <QJsonObject>

class Level
{
public:
    Level();

    /// @brief Generates a json representation of this object.
    /// @return A QJsonObject containing this level.
    QJsonObject toJson();
};

#endif // LEVEL_H
