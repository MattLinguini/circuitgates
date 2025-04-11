#ifndef LEVEL_H
#define LEVEL_H

#include <QJsonObject>

class Level
{
public:
    Level();

    /// @brief Constructor for a level object using a QJsonObject as reference.
    /// @param QJsonObject - the json structure to base this level off of.
    Level(const QJsonObject& obj);

    /// @brief Generates a json representation of this object.
    /// @return A QJsonObject containing this level.
    QJsonObject toJson();
};

#endif // LEVEL_H
