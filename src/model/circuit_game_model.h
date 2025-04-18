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
    Level currentLevel;

    void loadLvl1();

    void loadLvl2();

    void loadLvl3();

    void loadLvl4();

public slots:
    void createLevel(int levelId);
};

#endif // CIRCUIT_GAME_MODEL_H
