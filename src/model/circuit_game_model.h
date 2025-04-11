#ifndef CIRCUIT_GAME_MODEL_H
#define CIRCUIT_GAME_MODEL_H

#include "level.h"

class CircuitGame_Model
{
public:
    CircuitGame_Model();

    /// @brief Saves the level object held in the modeL.
    void saveLevel();

    /// @brief Loads the level object and holds it in the model.
    void loadLevel();

private:
    Level currentLevel;
};

#endif // CIRCUIT_GAME_MODEL_H
