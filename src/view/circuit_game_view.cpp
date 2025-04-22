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

    /// @brief Creates connections to transfer level data to the view.
    connect(model, &CircuitGameModel::sendLevelPointer, this, &CircuitGameView::receiveLevelPointer);
    connect(model, &CircuitGameModel::sendLevelDescription, this, &CircuitGameView::recieveLevelDescription);

    // @brief Sends information to the model as the game scene progresses.
    connect(this, &CircuitGameView::updateModel, model, &CircuitGameModel::updateGate);
}

void CircuitGameView::receiveLevelPointer(Level* lvl) {
    modelGameObjs = lvl->getGameObjs();
    budget = lvl->getBudget();

    drawLevel();
}

void CircuitGameView::recieveLevelDescription(QString levelName, QString levelDescription) {
    ui->LevelLabel->setText(levelName);
    ui->LevelDescription->setText(levelDescription);
}

void CircuitGameView::drawLevel() {
    if (scene) delete scene;
    scene = new GameScene(this);

    for (GameObject* gameObj : modelGameObjs->values()) {
        if (gameObj->objType == GameObject::GameObjectType::IO) {
            gameObj->asItem = scene->addIOItem(gameObj->x, gameObj->y, gameObj->objectID);
            gameObj->inView = true;
        } else if (gameObj->objType == GameObject::GameObjectType::GATE) {
            gameObj->asItem = scene->addGateSlot(gameObj->x, gameObj->y, gameObj->objectID);
            gameObj->inView = true;
        }
    }

    for (GameObject* gameObj : modelGameObjs->values()) {
        for (int i : *gameObj->getDestinations()) {
            scene->addWireItem(gameObj->asItem, modelGameObjs->value(i)->asItem);
        }
    }

        LogicGateItem* gateItem;
        for (GateType type : budget->keys()) {
            int amount = budget->value(type);
            for (int i = 0; i < amount; i ++) {
                gateItem = scene->addLogicGate(5,5, type);
                gateItem->view = this;
            }
        }

    ui->graphicsView->setScene(scene);
}

void CircuitGameView::sendViewToModel(int id, LogicGate::GateType gateType) {
    emit updateModel(id, gateType);
}

CircuitGameView::~CircuitGameView() {
    delete ui;
}
