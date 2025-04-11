#include "src/view/circuit_game_view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CircuitGameView w;
    w.show();
    return a.exec();
}
