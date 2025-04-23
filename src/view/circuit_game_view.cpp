#include "circuit_game_view.h"
#include "ui_circuit_game_view.h"
#include "gamescene.h"
#include "src/model/circuit_game_model.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QPixmap>

CircuitGameView::CircuitGameView(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), model(new CircuitGameModel(this)) {
    ui->setupUi(this);
    ui->stackedWidget->setStyleSheet("QPushButton {height: 50;}");

    createConnections();

    setupHomePage();
    setupLevelSelectPage();
    setupGamePage();
    setupTutorialPage();
}


CircuitGameView::~CircuitGameView() { delete ui; }


void CircuitGameView::createConnections() {
    connect(this, &CircuitGameView::createLevel, model, &CircuitGameModel::createLevel);
    connect(model, &CircuitGameModel::sendLevelPointer, this, &CircuitGameView::receiveLevelPointer);
    // connect(model, &CircuitGameModel::sendLevelDescription, this, &CircuitGameView::recieveLevelDescription);
    connect(model, &CircuitGameModel::sendWinToView, this, &CircuitGameView::triggerWin);

    // @brief Sends information to the model as the game scene progresses.
    connect(this, &CircuitGameView::updateModel, model, &CircuitGameModel::updateGate);
}


void CircuitGameView::displayMenu() {
    ui->stackedWidget->setCurrentWidget(homePage);
}


void CircuitGameView::displayLevels() {
    ui->stackedWidget->setCurrentWidget(levelPage);
}


void CircuitGameView::displayGame() {
    ui->stackedWidget->setCurrentWidget(gamePage);
}


void CircuitGameView::displayTutorial() {
    ui->stackedWidget->setCurrentWidget(tutorialPage);
}


void CircuitGameView::receiveLevelPointer(Level* lvl) {
    modelGameObjs = lvl->getGameObjs();
    budget = lvl->getBudget();

    drawLevel();
}


void CircuitGameView::drawLevel() {
    if (scene) delete scene;
    scene = new GameScene(this);
    scene->addGateSlot(8, 1, -1);
    scene->addGateSlot(8, 3, -1);
    scene->addGateSlot(8, 5, -1);

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

    int count = 1;
    LogicGateItem* gateItem;
    for (GateType type : budget->keys()) {
        int amount = budget->value(type);
        for (int i = 0; i < amount; i ++) {
            gateItem = scene->addLogicGate(8, count, type);
            gateItem->view = this;
            count+=2;
        }
    }

    scene->setSceneRect(scene->itemsBoundingRect()); // <- instead of manually setting dimensions if you can

    gameView->setScene(scene);
    gameView->resetTransform();
    gameView->setAlignment(Qt::AlignCenter);
    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    tutorialView->setScene(scene);
    tutorialView->resetTransform();
    tutorialView->setAlignment(Qt::AlignCenter);
    tutorialView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    tutorialView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}


void CircuitGameView::sendViewToModel(int id, LogicGate::GateType gateType) {
    emit updateModel(id, gateType);
}

void CircuitGameView::triggerWin() {
//TODO ADD WIN SCREEN
    qDebug() << "You win!";
}


void CircuitGameView::setupHomePage() {
    homePage = new QWidget(this);
    QWidget *homeInnerPage = new QWidget(this);

    QTextEdit *gameTitle = new QTextEdit("Circuit Game");
    QTextCursor cursor = gameTitle->textCursor();
    gameTitle->selectAll();
    gameTitle->setAlignment(Qt::AlignCenter);
    gameTitle->setMaximumHeight(63);
    gameTitle->setFontPointSize(30);
    gameTitle->setTextCursor(cursor);
    gameTitle->setStyleSheet("background: transparent; border: 0;");
    gameTitle->setReadOnly(true);

    QPushButton *startButton = new QPushButton("Start Game");
    QPushButton *quitButton = new QPushButton("Quit Game");
    connect(startButton, &QPushButton::clicked, this, &CircuitGameView::displayLevels);
    connect(quitButton, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);

    QVBoxLayout *homeInnerLayout = new QVBoxLayout;
    homeInnerLayout->addWidget(gameTitle);
    homeInnerLayout->addWidget(startButton);
    homeInnerLayout->addWidget(quitButton);
    homeInnerPage->setLayout(homeInnerLayout);
    homeInnerPage->setMaximumSize(275, 250);

    QBoxLayout *homeLayout = new QBoxLayout(QBoxLayout::LeftToRight, homePage);
    homeLayout->addWidget(homeInnerPage, Qt::AlignCenter);
    homePage->setLayout(homeLayout);

    ui->stackedWidget->addWidget(homePage);
}


void CircuitGameView::setupLevelSelectPage() {
    levelPage = new QWidget(this);

    QTextEdit *levelTitle = new QTextEdit("Levels");
    QTextCursor cursor = levelTitle->textCursor();
    levelTitle->selectAll();
    levelTitle->setMaximumHeight(63);
    levelTitle->setFontPointSize(30);
    levelTitle->setTextCursor(cursor);
    levelTitle->setStyleSheet("background: transparent; border: 0;");
    levelTitle->setReadOnly(true);

    QWidget *levelSelect = new QWidget(this);
    QGridLayout *levelLayout = new QGridLayout;
    for (int i = 1; i <= 10; ++i) {
        QPushButton *levelButton = new QPushButton(QString("Level %1").arg(i));
        connect(levelButton, &QPushButton::clicked, this, [this, i]() {
            emit createLevel(i);
        });
        connect(levelButton, &QPushButton::clicked, this, &CircuitGameView::displayGame);
        levelLayout->addWidget(levelButton, (i - 1) / 5, (i - 1) % 5);
    }

    QPushButton *menuButton = new QPushButton("Return to Menu");
    QPushButton *tutorialButton = new QPushButton("Tutorial");

    connect(menuButton, &QPushButton::clicked, this, &CircuitGameView::displayMenu);
    connect(tutorialButton, &QPushButton::clicked, this, &CircuitGameView::displayTutorial);
    connect(tutorialButton, &QPushButton::clicked, this, [this]() {emit createLevel(-1);});

    levelLayout->addWidget(menuButton, 2, 0);
    levelLayout->addWidget(tutorialButton, 2, 1);
    levelSelect->setLayout(levelLayout);

    QVBoxLayout *levelOuterLayout = new QVBoxLayout;
    levelOuterLayout->addWidget(levelTitle);
    levelOuterLayout->addWidget(levelSelect);
    levelPage->setLayout(levelOuterLayout);

    ui->stackedWidget->addWidget(levelPage);
}


void CircuitGameView::setupGamePage() {
    gamePage = new QWidget(this);

    gameView = new QGraphicsView;
    gameView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    gameView->viewport()->setAttribute(Qt::WA_AlwaysStackOnTop, true);
    gameView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    gameView->setBackgroundBrush(Qt::NoBrush);

    QPushButton *levelButton = new QPushButton("Return to Levels");
    connect(levelButton, &QPushButton::clicked, this, &CircuitGameView::displayLevels);

    QVBoxLayout *gameLayout = new QVBoxLayout;
    gameLayout->addWidget(gameView);
    gameLayout->addWidget(levelButton);
    gamePage->setLayout(gameLayout);

    ui->stackedWidget->addWidget(gamePage);
}


void CircuitGameView::setupTutorialPage() {
    tutorialPage = new QWidget(this);
    QWidget *tutorialInnerPage = new QWidget(this);

    tutorialView = new QGraphicsView;
    tutorialView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    tutorialView->viewport()->setAttribute(Qt::WA_AlwaysStackOnTop, true);
    tutorialView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    tutorialView->setBackgroundBrush(Qt::NoBrush);

    QTextEdit *tutorialText = new QTextEdit;
    tutorialText->setFontPointSize(12);
    tutorialText->setPlainText("Here is pictured a basic circuit puzzle.\n\n"
                                "In the center of the puzzle is a gate, with an input above and an output below.\n\n"
                                "Inputs and outputs send and recieve their state as indicated by wires and their color.\n\n"
                                "Your objective is to solve each puzzle such that the outputs match their expected state.\n\n"
                                "You can slot the gates into a socket by dragging them into the socket.\n\n"
                                "The top gate is an OR gate. This gate passes on positive state if one or either input is positive.\n\n"
                                "The 2nd gate is an AND gate. This gate only passes positive state if both inputs are positive.\n\n"
                                "The 3rd gate is a NOT gate. This gate passes on the opposite signal of its input.\n\n"
                                "The last gate is an XOR gate. This gate only passes on state if some, but not all, inputs are positive.\n\n");
    tutorialText->setReadOnly(true);
    tutorialText->setMaximumWidth(275);

    QPushButton *levelButton = new QPushButton("Return to Levels");
    connect(levelButton, &QPushButton::clicked, this, &CircuitGameView::displayLevels);

    QGridLayout *tutorialInnerLayout = new QGridLayout;
    tutorialInnerLayout->addWidget(tutorialView, 0, 0);
    tutorialInnerLayout->addWidget(tutorialText, 0, 1);
    tutorialInnerPage->setLayout(tutorialInnerLayout);

    QVBoxLayout *tutorialLayout = new QVBoxLayout;
    tutorialLayout->addWidget(tutorialInnerPage);
    tutorialLayout->addWidget(levelButton);
    tutorialPage->setLayout(tutorialLayout);

    ui->stackedWidget->addWidget(tutorialPage);
}
