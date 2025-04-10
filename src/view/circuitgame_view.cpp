#include "src/view/circuitgame_view.h"
#include "ui_circuitgame_view.h"

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
