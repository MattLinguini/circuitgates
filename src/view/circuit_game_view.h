#ifndef CIRCUIT_GAME_VIEW_H
#define CIRCUIT_GAME_VIEW_H

#include <QMainWindow>
#include <QShowEvent>
#include <QResizeEvent>
#include <QWidget>
#include "src/model/circuit_game_model.h"

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

private:
    Ui::MainWindow *ui;
    CircuitGameModel *model;
    QMap<int, GameObject*>* modelGameObjs;
    QMap<GateType, int>* budget;

    void drawLevel();

signals:
    void createLevel(int levelId);

public slots:
    void receiveLevelPointer(Level* lvl);
    void recieveLevelDescription(QString levelName, QString levelDescription);
};
#endif // CIRCUIT_GAME_VIEW_H
