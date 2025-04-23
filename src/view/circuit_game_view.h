#ifndef CIRCUIT_GAME_VIEW_H
#define CIRCUIT_GAME_VIEW_H

#include <QMainWindow>
#include <QMap>
#include <QGraphicsView>
#include <QWidget>
#include "gamescene.h"
#include "src/model/level.h"

class CircuitGameModel;

QT_BEGIN_NAMESPACE
    namespace Ui {
        class MainWindow;
    }
QT_END_NAMESPACE

/// @class CircuitGameView
/// @brief Main GUI class for the Circuit Game application.
/// Handles the switching of pages, displays game levels, and manages interaction
/// between the UI and the model.
class CircuitGameView : public QMainWindow {
    Q_OBJECT
    public:
        /// @brief Constructs the CircuitGameView window.
        CircuitGameView(QWidget *parent = nullptr);

        /// @brief Destroys the CircuitGameView and cleans up UI.
        ~CircuitGameView();

        /// @brief Sends a gate update to the model.
        /// @param id The unique ID of the object being updated.
        /// @param gateType The gate type being placed or updated.
        void sendGateToModel(int id, LogicGate::GateType gateType);

        ///@brief Sends a IO update to the model.
        /// @param id ID of IO gate to be updated.
        /// @param state State to be sent to IO.
        void sendIOToModel(int id, bool state);

    signals:
        /// @brief Signal to request creation of a new level.
        /// @param levelId The ID of the level to load.
        void createLevel(int levelId);

        /// @brief Signal to update the model with a selected gate.
        /// @param id The ID of the slot where the gate is placed.
        /// @param gateType The logic gate type placed.
        void updateGateInModel(int id, LogicGate::GateType gateType);

        /// @brief Signals to update the state of a given IO in model.
        /// @param id The ID of the IO to be updated.
        /// @param state State to be sent to IO.
        void updateIOInModel(int id, bool state);

    public slots:
        /// @brief Receives a pointer to the level object from the model.
        /// @param lvl The loaded level.
        void receiveLevelPointer(Level* lvl);

        void triggerWin();

        void receiveObjectUpdate(int id, bool state);

    private:
        /// @brief Draws the current level's objects into the scene.
        void drawLevel();

        /// @brief Displays the main menu.
        void displayMenu();

        /// @brief Displays the level selection page.
        void displayLevels();

        /// @brief Displays the game page.
        void displayGame();

        /// @brief Displays the tutorial page.
        void displayTutorial();

        /// @brief Resets game state and user progress.
        void resetGameProgress();

        /// @brief Creates the UI for the home page.
        void setupHomePage();

        /// @brief Creates the UI for the level select page.
        void setupLevelSelectPage();

        /// @brief Creates the UI for the game page.
        void setupGamePage();

        /// @brief Creates the UI for the tutorial page.
        void setupTutorialPage();

        /// @brief Handles the creation of all the connections.
        void createConnections();

        // UI components
        Ui::MainWindow *ui;
        QWidget *homePage;
        QWidget *levelPage;
        QWidget *gamePage;
        QWidget *tutorialPage;
        QGraphicsView *gameView;
        QGraphicsView *tutorialView;
        QDialog *winDialog;

        // Model and game state
        CircuitGameModel *model;
        QMap<int, GameObject*>* modelGameObjs;
        QMap<GateType, int>* budget;
        GameScene* scene = nullptr;
};
#endif // CIRCUIT_GAME_VIEW_H
