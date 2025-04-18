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
