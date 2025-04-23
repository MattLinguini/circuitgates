#ifndef CIRCUIT_GAME_MODEL_H
#define CIRCUIT_GAME_MODEL_H

#include "level.h"

class CircuitGameModel : public QObject
{
    Q_OBJECT
public:
    /// @brief Constructor for a CircuitGameModel.
    /// @param parent: The parent object.
    CircuitGameModel(QObject *parent = nullptr);

signals:
    /// @brief Signal to send the level to the view.
    /// @param lvl: the level pointer to send.
    void sendLevelPointer(Level* lvl);
    /// @brief Signal to send the level flavor text to the view.
    /// @param levelName: The title of the level.
    /// @param levelDesc: The description of the level.
    void sendLevelDescription(QString levelName, QString levelDescription);

    void sendWinToView();

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
    /// @brief Slot to  select a level to generate.
    /// @param levelId: The id of the level to generate.
    void createLevel(int levelId);

    void updateGate(int id, LogicGate::GateType gateType);
};

#endif // CIRCUIT_GAME_MODEL_H
