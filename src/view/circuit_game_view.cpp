// * Checked by ?

/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        24 April, 2025
 * Description: ?
 */

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
#include <QDialog>

CircuitGameView::CircuitGameView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), model(new CircuitGameModel(this)) {
    ui->setupUi(this);
    this->setFixedSize(1200, 675);
    this->setStyleSheet(R"(
        QMainWindow {
            background-image: url(:/ui/resources/bg.png);
            background-repeat: no-repeat;
            background-position: center;
            background-color: black;
        }
    )");

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
    connect(model, &CircuitGameModel::sendWinToView, this, &CircuitGameView::triggerWin);
    connect(model, &CircuitGameModel::emitObjectState, this, &CircuitGameView::receiveObjectUpdate);

    // @brief Sends information to the model as the game scene progresses.
    connect(this, &CircuitGameView::updateGateInModel, model, &CircuitGameModel::updateGate);
    connect(this, &CircuitGameView::updateIOInModel, model, &CircuitGameModel::updateIO);
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
    scene->addGateSlot(8, 0, -1);
    scene->addGateSlot(8, 2, -1);
    scene->addGateSlot(8, 4, -1);
    scene->addGateSlot(8, 6, -1);

    IOItem* IO;
    for (GameObject* gameObj : modelGameObjs->values()) {
        if (gameObj->objType == GameObject::GameObjectType::IO) {
            InputOutput* io = dynamic_cast<InputOutput*>(gameObj);
            IO = scene->addIOItem(gameObj->x, gameObj->y, gameObj->objectID, io->state, io->getInputType(), io->getExpectedState());
            gameObj->asItem = IO;
            gameObj->inView = true;
            IO->setView(this);
        } else if (gameObj->objType == GameObject::GameObjectType::GATE) {
            gameObj->asItem = scene->addGateSlot(gameObj->x, gameObj->y, gameObj->objectID);
            gameObj->inView = true;
        }
    }

    for (GameObject* gameObj : modelGameObjs->values()) {
        for (int i : *gameObj->getDestinations()) {
            scene->addWireItem(gameObj->asItem, modelGameObjs->value(i)->asItem);
            gameObj->asItem->togglePower(gameObj->state);
        }
    }

    int count = 0;
    LogicGateItem* gateItem;
    for (GateType type : budget->keys()) {
        int amount = budget->value(type);
        for (int i = 0; i < amount; i ++) {
            gateItem = scene->addLogicGate(8, count, type);
            gateItem->setView(this);
            count+=2;
        }
    }

    const int fixedGrid = 7;  // or whatever you use as max grid width
    const int padding = 10;
    const int cellSize = 64;

    int sceneWidth  = (fixedGrid + 2) * cellSize + 2 * padding;
    int sceneHeight = (fixedGrid + 2) * cellSize + 2 * padding;
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);

    gameView->setScene(scene);
    gameView->setFixedSize(1100, 675); // Or calculated based on grid
    gameView->setAlignment(Qt::AlignCenter);
    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    gameView->centerOn(scene->sceneRect().center());

    tutorialView->setScene(scene);
    tutorialView->resetTransform();
    tutorialView->setAlignment(Qt::AlignCenter);
    tutorialView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tutorialView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


void CircuitGameView::sendGateToModel(int id, LogicGate::GateType gateType) {
    emit updateGateInModel(id, gateType);
}


void CircuitGameView::sendIOToModel(int id, bool state) {
    emit updateIOInModel(id, state);
}


void CircuitGameView::triggerWin() {
    winDialog = new QDialog;
    QLabel *lbl = new QLabel;
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setText("Puzzle Solved");
    QPushButton *btn = new QPushButton("OK");
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(lbl);
    layout->addWidget(btn);
    winDialog->setLayout(layout);
    winDialog->setMinimumSize(200, 100);

    connect(btn, &QPushButton::clicked, winDialog, &QDialog::close);

    winDialog->show();
}


void CircuitGameView::receiveObjectUpdate(int id, bool state) {
    GameObject* gameObj = modelGameObjs->value(id);
    gameObj->asItem->togglePower(state);
    gameObj->asItem->update();
}


void CircuitGameView::setupHomePage() {
    homePage = new QWidget(this);
    homePage->setFixedSize(1200, 675);

    QLabel* titleImage = new QLabel;
    titleImage->setPixmap(QPixmap(":/ui/resources/title.png"));
    titleImage->setAlignment(Qt::AlignCenter);
    titleImage->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QPushButton *playButton = new QPushButton("PLAY");
    playButton->setFixedSize(330, 95);
    connect(playButton, &QPushButton::clicked, this, &CircuitGameView::displayLevels);

    playButton->setStyleSheet(R"(
        QPushButton {
            color: white;
            font: bold 32px 'Arial';
            background-color: qlineargradient(
                x1:0, y1:0, x2:0, y2:1,
                stop:0 #3a8f3a,
                stop:1 #2e6e2e
            );
            border: 5px solid #00ff00;
            border-radius: 40px;
            padding: 20px 40px;
        }

        QPushButton:hover {
            border: 5px solid #66ff66;
        }

        QPushButton:pressed {
            background-color: #265e26;
        }
    )");

    QVBoxLayout *layout = new QVBoxLayout(homePage);
    layout->addStretch();
    layout->addWidget(titleImage, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(playButton, 0, Qt::AlignCenter);
    layout->addStretch();

    homePage->setLayout(layout);
    ui->stackedWidget->addWidget(homePage);
}


void CircuitGameView::setupLevelSelectPage() {
    levelPage = new QWidget(this);
    levelPage->setStyleSheet("background-color: transparent;");

    // Title Image
    QLabel* levelTitle = new QLabel;
    levelTitle->setPixmap(QPixmap(":/ui/resources/text_levels.png"));
    levelTitle->setAlignment(Qt::AlignCenter);
    levelTitle->setStyleSheet("background-color: transparent;");
    levelTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    // Styled button template
    auto styleButton = [](QPushButton* button) {
        button->setFixedSize(200, 50);
        button->setStyleSheet(R"(
            QPushButton {
                color: white;
                font: bold 14px 'Arial';
                background-color: qlineargradient(
                    x1:0, y1:0, x2:0, y2:1,
                    stop:0 #3a8f3a,
                    stop:1 #2e6e2e
                );
                border: 5px solid #00ff00;
                border-radius: 25px;
                padding: 10px 20px;
            }

            QPushButton:hover {
                border: 5px solid #66ff66;
            }

            QPushButton:pressed {
                background-color: #265e26;
            }
        )");
    };

    // Grid of level buttons
    QWidget* levelSelect = new QWidget(this);
    QGridLayout* levelLayout = new QGridLayout(levelSelect);
    levelLayout->setSpacing(20);
    levelLayout->setContentsMargins(0, 0, 0, 0);

    for (int i = 1; i <= 10; ++i) {
        QPushButton* levelButton = new QPushButton(QString("LEVEL %1").arg(i));
        styleButton(levelButton);
        connect(levelButton, &QPushButton::clicked, this, [this, i]() {
            emit createLevel(i);
        });
        connect(levelButton, &QPushButton::clicked, this, &CircuitGameView::displayGame);
        levelLayout->addWidget(levelButton, (i - 1) / 2, (i - 1) % 2, Qt::AlignCenter); // 2 per row
    }

    // Menu + Tutorial buttons
    QPushButton* menuButton = new QPushButton("MAIN MENU");
    QPushButton* tutorialButton = new QPushButton("TUTORIAL");
    styleButton(menuButton);
    styleButton(tutorialButton);

    connect(menuButton, &QPushButton::clicked, this, &CircuitGameView::displayMenu);
    connect(tutorialButton, &QPushButton::clicked, this, &CircuitGameView::displayTutorial);
    connect(tutorialButton, &QPushButton::clicked, this, [this]() {
        emit createLevel(-1);
    });

    QHBoxLayout* bottomButtons = new QHBoxLayout;
    bottomButtons->addStretch();
    bottomButtons->addWidget(menuButton);
    bottomButtons->addSpacing(40);
    bottomButtons->addWidget(tutorialButton);
    bottomButtons->addStretch();

    // Outer layout with title, levels, and bottom buttons
    QVBoxLayout* levelOuterLayout = new QVBoxLayout(levelPage);
    levelOuterLayout->addWidget(levelTitle);
    levelOuterLayout->addWidget(levelSelect, 0, Qt::AlignCenter);
    levelOuterLayout->addStretch();
    levelOuterLayout->addLayout(bottomButtons);
    levelOuterLayout->setContentsMargins(40, 40, 40, 40);
    levelOuterLayout->setSpacing(20);

    ui->stackedWidget->addWidget(levelPage);
}



void CircuitGameView::setupGamePage() {
    gamePage = new QWidget(this);

    // Configure the game view
    gameView = new QGraphicsView;
    gameView->setStyleSheet("background: transparent;");
    gameView->setBackgroundBrush(Qt::NoBrush);
    gameView->setFrameStyle(QFrame::NoFrame);
    gameView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    gameView->viewport()->setAttribute(Qt::WA_TranslucentBackground);
    gameView->setAttribute(Qt::WA_TranslucentBackground);

    // Return button styled and centered
    QPushButton* levelButton = new QPushButton("LEVEL SELECT");
    levelButton->setFixedSize(200, 50);
    levelButton->setStyleSheet(R"(
        QPushButton {
            color: white;
            font: bold 18px 'Arial';
            background-color: qlineargradient(
                x1:0, y1:0, x2:0, y2:1,
                stop:0 #3a8f3a,
                stop:1 #2e6e2e
            );
            border: 3px solid #00ff00;
            border-radius: 25px;
            padding: 10px 20px;
        }

        QPushButton:hover {
            border: 3px solid #66ff66;
        }

        QPushButton:pressed {
            background-color: #265e26;
        }
    )");
    connect(levelButton, &QPushButton::clicked, this, &CircuitGameView::displayLevels);

    // Layout for the button to center it
    QHBoxLayout* buttonRow = new QHBoxLayout;
    buttonRow->addStretch();
    buttonRow->addWidget(levelButton);
    buttonRow->addStretch();

    QHBoxLayout* centeredViewRow = new QHBoxLayout;
    centeredViewRow->addStretch();
    centeredViewRow->addWidget(gameView);
    centeredViewRow->addStretch();

    QHBoxLayout* centeredButtonRow = new QHBoxLayout;
    centeredButtonRow->addStretch();
    centeredButtonRow->addWidget(levelButton);
    centeredButtonRow->addStretch();

    QVBoxLayout* gameLayout = new QVBoxLayout;
    gameLayout->addLayout(centeredViewRow);
    gameLayout->addLayout(centeredButtonRow);
    gameLayout->setContentsMargins(20, 20, 20, 20);
    gameLayout->setSpacing(20);

    gamePage->setLayout(gameLayout);
    ui->stackedWidget->addWidget(gamePage);
}


void CircuitGameView::setupTutorialPage() {
    tutorialPage = new QWidget(this);

    // Configure the tutorial view (QGraphicsView)
    tutorialView = new QGraphicsView;
    tutorialView->setStyleSheet("background: transparent;");
    tutorialView->setBackgroundBrush(Qt::NoBrush);
    tutorialView->setFrameStyle(QFrame::NoFrame);
    tutorialView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    tutorialView->viewport()->setAttribute(Qt::WA_TranslucentBackground);
    tutorialView->setAttribute(Qt::WA_TranslucentBackground);

    // Instructional text
    QTextEdit* tutorialText = new QTextEdit;
    tutorialText->setFontPointSize(12);
    tutorialText->setPlainText(
        "Here is pictured a basic circuit puzzle.\n\n"
        "In the center of the puzzle is a gate, with an input above and an output below.\n\n"
        "Inputs and outputs send and receive their state as indicated by wires and their color.\n\n"
        "Your objective is to solve each puzzle such that the outputs match their expected state, which can be seen in the upper right corner of each output.\n\n"
        "Click the inputs at the top to change their signal. You can slot the gates into a socket by dragging them into the socket.\n\n"
        "The top gate is an OR gate. This gate passes on positive state if one or either input is positive.\n\n"
        "The 2nd gate is an AND gate. This gate only passes positive state if both inputs are positive.\n\n"
        "The 3rd gate is a NOT gate. This gate passes on the opposite signal of its input.\n\n"
        "The last gate is an XOR gate. This gate only passes on state if some, but not all, inputs are positive.\n\n"
        );
    tutorialText->setReadOnly(true);
    tutorialText->setMaximumWidth(300);

    // Horizontal layout with view + text
    QHBoxLayout* tutorialContent = new QHBoxLayout;
    tutorialContent->addWidget(tutorialView);
    tutorialContent->addWidget(tutorialText);

    // Return button styled and centered
    QPushButton* levelButton = new QPushButton("LEVEL SELECT");
    levelButton->setFixedSize(200, 50);
    levelButton->setStyleSheet(R"(
        QPushButton {
            color: white;
            font: bold 18px 'Arial';
            background-color: qlineargradient(
                x1:0, y1:0, x2:0, y2:1,
                stop:0 #3a8f3a,
                stop:1 #2e6e2e
            );
            border: 3px solid #00ff00;
            border-radius: 25px;
            padding: 10px 20px;
        }

        QPushButton:hover {
            border: 3px solid #66ff66;
        }

        QPushButton:pressed {
            background-color: #265e26;
        }
    )");
    connect(levelButton, &QPushButton::clicked, this, &CircuitGameView::displayLevels);

    QHBoxLayout* buttonRow = new QHBoxLayout;
    buttonRow->addStretch();
    buttonRow->addWidget(levelButton);
    buttonRow->addStretch();

    // Main vertical layout
    QVBoxLayout* tutorialLayout = new QVBoxLayout(tutorialPage);
    tutorialLayout->addLayout(tutorialContent);
    tutorialLayout->addSpacing(20);
    tutorialLayout->addLayout(buttonRow);
    tutorialLayout->setContentsMargins(20, 20, 20, 20);
    tutorialLayout->setSpacing(20);

    ui->stackedWidget->addWidget(tutorialPage);
}

