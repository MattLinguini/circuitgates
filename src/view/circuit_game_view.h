#ifndef CIRCUIT_GAME_VIEW_H
#define CIRCUIT_GAME_VIEW_H

#include <QMainWindow>
#include <QShowEvent>
#include <QResizeEvent>
#include <QWidget>
#include <QGraphicsView>
#include "src/model/circuit_game_model.h"
#include <vector>

class GameItem;
class GameScene;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class CircuitGameView : public QMainWindow
{
    Q_OBJECT

public:
    CircuitGameView(QWidget *parent = nullptr);
    ~CircuitGameView();
    void sendViewToModel(int id, LogicGate::GateType gateType);

private:
    Ui::MainWindow *ui;
    QWidget *homePage;
    QWidget *levelPage;
    QWidget *gamePage;
    QGraphicsView *gameView;
    CircuitGameModel *model;
    QMap<int, GameObject*>* modelGameObjs;
    QMap<GateType, int>* budget;
    GameScene* scene = nullptr;

    void addChildren(GameItem* source, GameObject* sourceObject, GameScene* scene);
    void drawLevel();

    void displayMenu();
    void displayLevels();
    void resetGameProgress();

signals:
    void createLevel(int levelId);
    void updateModel(int id, LogicGate::GateType gateType);

public slots:
    void receiveLevelPointer(Level* lvl);
    void recieveLevelDescription(QString levelName, QString levelDescription);
    void triggerWin();
};
#endif // CIRCUIT_GAME_VIEW_H
