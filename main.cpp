// * Checked by Andrew Kellmer

/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        24 April, 2025
 * Description: Main method for Circuit Game Application.
 */

#include "src/view/circuit_game_view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CircuitGameView w;
    w.setWindowTitle("Circuit Game");
    w.show();
    return a.exec();
}
