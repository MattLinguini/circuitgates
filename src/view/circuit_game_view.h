#ifndef CIRCUIT_GAME_VIEW_H
#define CIRCUIT_GAME_VIEW_H

#include <QMainWindow>

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
};
#endif // CIRCUIT_GAME_VIEW_H
