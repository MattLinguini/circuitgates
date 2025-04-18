#include "circuit_game_view.h"
#include "qgraphicsitem.h"
#include "ui_circuit_game_view.h"
#include "src/model/circuit_game_model.h"
#include "gamescene.h"

CircuitGameView::CircuitGameView(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), model(new CircuitGameModel(this)) {
    ui->setupUi(this);


    // CONNECTIONS

    /// @brief Creates connections between each level button and the model.
    connect(this, &CircuitGameView::createLevel, model, &CircuitGameModel::createLevel);
    connect(ui->level_1, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(1);});
    connect(ui->level_2, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(2);});
    connect(ui->level_3, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(3);});
    connect(ui->level_4, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(4);});
    connect(ui->level_5, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(5);});
    connect(ui->level_6, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(6);});
    connect(ui->level_7, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(7);});
    connect(ui->level_8, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(8);});
    connect(ui->level_9, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(9);});
    connect(ui->level_10, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(10);});

    connect(model, &CircuitGameModel::sendLevelPointer, this, &CircuitGameView::receiveLevelPointer);
}

void CircuitGameView::receiveLevelPointer(Level* lvl) {
    modelGameObjs = lvl->getGameObjs();
    budget = lvl->getBudget();

    drawLevel();
}

void CircuitGameView::drawLevel() {
    GameScene* scene = new GameScene(this);

    for (auto* gameObj : modelGameObjs->values()) {
        if (gameObj->objType == GameObject::GameObjectType::IO) {
            //ADD IO TO SCENE
        } else if (gameObj->objType == GameObject::GameObjectType::GATE) {
            if (static_cast<LogicGate*>(gameObj)->getGateType() == GateType::DEFAULT) {
                scene->addGateSlot(gameObj->x, gameObj->y);
            }
        } else if (gameObj->objType == GameObject::GameObjectType::WIRE) {
            //ADD WIRES TO SCENE
        }

    }




    // GateSlotItem* slot1 = scene->addGateSlot(1, 1);
    // GateSlotItem* slot2 = scene->addGateSlot(4, 3);
    // scene->addLogicGate(5, 1);
    // scene->addWireItem(slot1, slot2);

    // model->createLevel();
    ui->graphicsView->setScene(scene);
}

CircuitGameView::~CircuitGameView() {
    delete ui;
}
