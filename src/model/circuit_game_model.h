#ifndef CIRCUIT_GAME_MODEL_H
#define CIRCUIT_GAME_MODEL_H

#include "level.h"

class CircuitGameModel : public QObject
{
    Q_OBJECT
public:
    CircuitGameModel(QObject *parent = nullptr);

    //TEST METHOD
    void createLevel();
private:
    Level currentLevel;
};

#endif // CIRCUIT_GAME_MODEL_H
