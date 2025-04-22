#include "circuit_game_view.h"
#include "qgraphicsitem.h"
#include "ui_circuit_game_view.h"
#include "src/model/circuit_game_model.h"
#include "gamescene.h"
#include <QPushButton>
#include <QTextEdit>
#include <QBoxLayout>
#include <QGridLayout>

CircuitGameView::CircuitGameView(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), model(new CircuitGameModel(this)) {
    ui->setupUi(this);

    ui->stackedWidget->setStyleSheet("QPushButton {height: 50;}");

    // PAGES

    /// Setup homepage.
    homePage = new QWidget(this);
    QWidget *homeInnerPage = new QWidget(this);

    /// Setup homepage's contents.
    QTextEdit *gameTitle = new QTextEdit("Circuit Game");
    QTextCursor gameCursor = gameTitle->textCursor();
    gameTitle->selectAll();
    gameTitle->setAlignment(Qt::AlignCenter);
    gameTitle->setMaximumHeight(63);
    gameTitle->setFontPointSize(30);
    gameTitle->setTextCursor(gameCursor);
    gameTitle->setStyleSheet("background: transparent; border: 0;");
    gameTitle->setReadOnly(true);
    QPushButton *startButton = new QPushButton("Start Game");
    QPushButton *quitButton = new QPushButton("Quit Game");

    /// Connect buttons to functionality.
    connect(startButton, &QPushButton::clicked, this, &CircuitGameView::displayLevels);
    connect(quitButton, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);

    /// Add layout to inner home page.
    QVBoxLayout *homeInnerLayout = new QVBoxLayout;
    homeInnerLayout->addWidget(gameTitle);
    homeInnerLayout->addWidget(startButton);
    homeInnerLayout->addWidget(quitButton);
    homeInnerPage->setLayout(homeInnerLayout);
    homeInnerPage->setMaximumSize(260, 250);

    /// Add layout to home page.
    QBoxLayout *homeLayout = new QBoxLayout(QBoxLayout::LeftToRight, homePage);
    homeLayout->addWidget(homeInnerPage, Qt::AlignCenter);
    homePage->setLayout(homeLayout);

    /// Setup level page.
    levelPage = new QWidget(this);

    /// Setup level page contents.
    QWidget *levelSelect = new QWidget(this);
    QTextEdit *levelTitle = new QTextEdit("Levels");
    QTextCursor levelCursor = levelTitle->textCursor();
    levelTitle->selectAll();
    levelTitle->setMaximumHeight(63);
    levelTitle->setFontPointSize(30);
    levelTitle->setTextCursor(levelCursor);
    levelTitle->setStyleSheet("background: transparent; border: 0;");
    levelTitle->setReadOnly(true);
    QPushButton *level_1 = new QPushButton("Level 1");
    QPushButton *level_2 = new QPushButton("Level 2");
    QPushButton *level_3 = new QPushButton("Level 3");
    QPushButton *level_4 = new QPushButton("Level 4");
    QPushButton *level_5 = new QPushButton("Level 5");
    QPushButton *level_6 = new QPushButton("Level 6");
    QPushButton *level_7 = new QPushButton("Level 7");
    QPushButton *level_8 = new QPushButton("Level 8");
    QPushButton *level_9 = new QPushButton("Level 9");
    QPushButton *level_10 = new QPushButton("Level 10");
    QPushButton *menuButton = new QPushButton("Return to Menu");

    /// Connect buttons to functionality.
    connect(this, &CircuitGameView::createLevel, model, &CircuitGameModel::createLevel);
    connect(level_1, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(1);});
    connect(level_2, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(2);});
    connect(level_3, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(3);});
    connect(level_4, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(4);});
    connect(level_5, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(5);});
    connect(level_6, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(6);});
    connect(level_7, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(7);});
    connect(level_8, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(8);});
    connect(level_9, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(9);});
    connect(level_10, &QPushButton::clicked, this, [this]() {emit CircuitGameView::createLevel(10);});
    connect(menuButton, &QPushButton::clicked, this, &CircuitGameView::displayMenu);

    /// Add layout to level page.
    QGridLayout *levelLayout = new QGridLayout;
    levelLayout->addWidget(level_1, 0, 0);
    levelLayout->addWidget(level_2, 0, 1);
    levelLayout->addWidget(level_3, 0, 2);
    levelLayout->addWidget(level_4, 0, 3);
    levelLayout->addWidget(level_5, 0, 4);
    levelLayout->addWidget(level_6, 1, 0);
    levelLayout->addWidget(level_7, 1, 1);
    levelLayout->addWidget(level_8, 1, 2);
    levelLayout->addWidget(level_9, 1, 3);
    levelLayout->addWidget(level_10, 1, 4);
    levelLayout->addWidget(menuButton, 2, 0);
    levelSelect->setLayout(levelLayout);

    QVBoxLayout *levelOuterLayout = new QVBoxLayout;
    levelOuterLayout->addWidget(levelTitle);
    levelOuterLayout->addWidget(levelSelect);
    levelPage->setLayout(levelOuterLayout);

    /// Setup game page.
    gamePage = new QWidget(this);

    /// Setup game page contents.
    gameView = new QGraphicsView;
    QPushButton *levelButton = new QPushButton("Return to Levels");

    /// Connect buttons to functionality.
    connect(levelButton, &QPushButton::clicked, this, &CircuitGameView::displayLevels);

    /// Add layout to game page.
    QVBoxLayout *gameLayout = new QVBoxLayout;
    gameLayout->addWidget(gameView);
    gameLayout->addWidget(levelButton);
    gamePage->setLayout(gameLayout);


    /// Add pages to stacked widget.
    ui->stackedWidget->addWidget(homePage);
    ui->stackedWidget->addWidget(levelPage);
    ui->stackedWidget->addWidget(gamePage);

    // CONNECTIONS

    /// @brief Creates connections to transfer level data to the view.
    connect(model, &CircuitGameModel::sendLevelPointer, this, &CircuitGameView::receiveLevelPointer);
    connect(model, &CircuitGameModel::sendLevelDescription, this, &CircuitGameView::recieveLevelDescription);
}

void CircuitGameView::displayMenu() {
    ui->stackedWidget->setCurrentWidget(homePage);
}

void CircuitGameView::displayLevels() {
    ui->stackedWidget->setCurrentWidget(levelPage);
}

void CircuitGameView::receiveLevelPointer(Level* lvl) {
    modelGameObjs = lvl->getGameObjs();
    budget = lvl->getBudget();

    drawLevel();
}

void CircuitGameView::recieveLevelDescription(QString levelName, QString levelDescription) {
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

    for (GateType type : budget->keys()) {
        int amount = budget->value(type);
        for (int i = 0; i < amount; i ++) {
            scene->addLogicGate(5,5, type);
        }
    }

    gameView->setScene(scene);
    //ui->graphicsView->setScene(scene);
    ui->stackedWidget->setCurrentWidget(gamePage);
}

CircuitGameView::~CircuitGameView() {
    delete ui;
}
