#include "src/view/circuit_game_view.h"
#include "ui_circuit_game_view.h"
#include "gamescene.h"
#include "gameobjects.h"

CircuitGameView::CircuitGameView(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    GameScene* scene = new GameScene(this);
    LogicGateItem* item = new LogicGateItem(0, 0, LogicGateItem::AND);
    LogicGateItem* item1 = new LogicGateItem(1, 1, LogicGateItem::OR);
    LogicGateItem* item2 = new LogicGateItem(2, 2, LogicGateItem::XOR);
    LogicGateItem* item3 = new LogicGateItem(3, 3, LogicGateItem::NOT);
    scene->setGridSize(5);
    scene->addGateItem(item);
    scene->addGateItem(item1);
    scene->addGateItem(item2);
    scene->addGateItem(item3);

    ui->graphicsView->setScene(scene);
}

CircuitGameView::~CircuitGameView() {
    delete ui;
}

void CircuitGameView::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);

    if (ui->graphicsView->scene()) {
        auto* gameScene = qobject_cast<GameScene*>(ui->graphicsView->scene());
        if (gameScene) {
            gameScene->resizeToFit(ui->graphicsView->viewport()->size());
        }
    }
}

void CircuitGameView::showEvent(QShowEvent* event) {
    QMainWindow::showEvent(event);

    if (ui->graphicsView->scene()) {
        auto* scene = qobject_cast<GameScene*>(ui->graphicsView->scene());
        if (scene) {
            scene->resizeToFit(ui->graphicsView->viewport()->size());
        }
    }
}
