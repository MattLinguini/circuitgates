#ifndef CIRCUIT_GAME_MODEL_H
#define CIRCUIT_GAME_MODEL_H

#include "level.h"

class CircuitGameModel : public QObject
{
    Q_OBJECT
public:
    CircuitGameModel(QObject *parent = nullptr);

signals:
    void sendLevelPointer(Level* lvl);

private:
    /// @brief The current level object held in the model.
    Level currentLevel;
    /// @brief Loads level one to the current model.
    void loadLvl1();
    /// @brief Loads level two to the current model.
    void loadLvl2();
    /// @brief Loads level three to the current model.
    void loadLvl3();
    /// @brief Loads level four to the current model.
    void loadLvl4();
    /// @brief Loads level five to the current model.
    void loadLvl5();
    /// @brief Loads level six to the current model.
    void loadLvl6();
    /// @brief Loads level seven to the current model.
    void loadLvl7();
    /// @brief Loads level eight to the current model.
    void loadLvl8();
    /// @brief Loads level nine to the current model.
    void loadLvl9();
    /// @brief Loads level ten to the current model.
    void loadLvl10();

public slots:
    void createLevel(int levelId);
};

#endif // CIRCUIT_GAME_MODEL_H
