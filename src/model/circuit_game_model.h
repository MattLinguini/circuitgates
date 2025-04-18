#ifndef CIRCUIT_GAME_MODEL_H
#define CIRCUIT_GAME_MODEL_H

#include "level.h"

class CircuitGameModel : public QObject
{
    Q_OBJECT
public:
    CircuitGameModel(QObject *parent = nullptr);

    /// @brief Saves the level object held in the modeL.
    void saveLevel();

    /// @brief Loads the level object and holds it in the model.
    void loadLevel();

   ///@brief Builds a level
    void createLevel();
private:
    Level currentLevel;
};

#endif // CIRCUIT_GAME_MODEL_H
