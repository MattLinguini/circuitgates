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
    void resizeEvent(QResizeEvent* event);
    void showEvent(QShowEvent* event);

private:
    Ui::MainWindow *ui;
    CircuitGameModel *model;
};
#endif // CIRCUIT_GAME_VIEW_H
