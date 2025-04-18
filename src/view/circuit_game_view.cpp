#include "circuit_game_view.h"
#include "qgraphicsitem.h"
#include "ui_circuit_game_view.h"
#include "src/model/circuit_game_model.h"
#include "gamescene.h"

CircuitGameView::CircuitGameView(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), model(new CircuitGameModel(this)) {
    ui->setupUi(this);

    GameScene* scene = new GameScene(this);

    scene->addGateSlot(1, 1);
    scene->addGateSlot(4, 2);
    scene->addLogicGate(5, 1);

    // model->createLevel();
    ui->graphicsView->setScene(scene);
}

CircuitGameView::~CircuitGameView() {
    delete ui;
}
