#include "circuit_game_view.h"       // <-- your class declaration
#include "qgraphicsitem.h"
#include "ui_circuit_game_view.h"    // <-- must come AFTER your class declaration
#include "src/model/circuit_game_model.h"
#include "gamescene.h"

CircuitGameView::CircuitGameView(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), model(new CircuitGameModel(this)) {
    ui->setupUi(this);

    GameScene* scene = new GameScene(this);

    scene->addGateSlot(1, 1);

    model->createLevel();
    ui->graphicsView->setScene(scene);
}

CircuitGameView::~CircuitGameView() {
    delete ui;
}
