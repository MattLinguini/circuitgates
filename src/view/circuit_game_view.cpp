#include "src/view/circuit_game_view.h"
#include "ui_circuit_game_view.h"
#include "gamescene.h"

CircuitGameView::CircuitGameView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GameScene* scene = new GameScene(this);
    scene->setGridSize(10);

    ui->graphicsView->setScene(scene);
}

CircuitGameView::~CircuitGameView()
{
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
