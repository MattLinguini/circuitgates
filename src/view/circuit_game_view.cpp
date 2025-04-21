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
    GameScene* scene = new GameScene(this);
    GameItem* source = nullptr;

    for (GameObject* gameObj : modelGameObjs->values()) {
        if (gameObj->objType == GameObject::GameObjectType::IO) {
            source = scene->addIOItem(gameObj->x, gameObj->y);
            gameObj->inView = true;
            addChildren(source, gameObj, scene);
        } else if (gameObj->objType == GameObject::GameObjectType::GATE) {
            source = scene->addGateSlot(gameObj->x, gameObj->y);
            gameObj->inView = true;
            addChildren(source, gameObj, scene);
        }
    }

    for (GateType type : budget->keys()) {
        int amount = budget->value(type);
        for (int i = 0; i < amount; i ++) {
            //NEEDS EXTRA PARAM FOR GATETYPE
            scene->addLogicGate(5,5);
        }
    }

    ui->graphicsView->setScene(scene);
}

void CircuitGameView::addChildren(GameItem* source, GameObject* sourceObject, GameScene* scene) {
    GameItem* dest;
    GameObject* destObj;

    for (int i: *sourceObject->getDestinations()) {
        destObj = modelGameObjs->value(i);
        if(!destObj->inView && destObj->objType == GameObject::GameObjectType::IO) {
            dest = scene->addIOItem(destObj->x, destObj->y);
            destObj->inView = true;
            scene->addWireItem(source, dest);
            addChildren(dest, destObj, scene);
        } else if (!destObj->inView && destObj->objType == GameObject::GameObjectType::GATE) {
            dest = scene->addGateSlot(destObj->x, destObj->y);
            destObj->inView = true;
            scene->addWireItem(source, dest);
            addChildren(dest, destObj, scene);
        }
    }
}

CircuitGameView::~CircuitGameView() {
    delete ui;
}
