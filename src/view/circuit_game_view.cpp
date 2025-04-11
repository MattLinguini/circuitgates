#include "src/view/circuit_game_view.h"
#include "ui_circuit_game_view.h"

CircuitGameView::CircuitGameView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

CircuitGameView::~CircuitGameView()
{
    delete ui;
}
