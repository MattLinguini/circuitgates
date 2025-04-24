// * Checked by ?

/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        24 April, 2025
 * Description: ?
 */

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QHash>
#include <QTimer>
#include "Box2D/Dynamics/b2World.h"
#include "gateslotitem.h"
#include "logicgateitem.h"
#include "src/view/ioitem.h"
#include "wireitem.h"

// 30 Pixels per Box2D Meter.
static const float SCALE = 30.0f;

/// @class GameScene
/// @brief A QGraphicsScene that integrates Box2D physics and displays circuit components.
class GameScene : public QGraphicsScene {
    Q_OBJECT
    public:
        /// @brief Creates a game scene and starts all the logic needed to loop through a Box2D world.
        GameScene(QObject* parent = nullptr);

        /// @brief Creates a gate slot at the specific x and y coordinates on the grid.
        /// @param x X coordinate of the gate slot.
        /// @param y Y coordinate of the gate slot.
        GateSlotItem* addGateSlot(int x, int y, int ID);

        /// @brief Creates a logic gate at the specific x and y coordinates on the grid.
        /// @param x X coordinate of the gate slot.
        /// @param y Y coordinate of the gate slot.
        LogicGateItem* addLogicGate(int x, int y, LogicGate::GateType gateType);

        /// @brief Creates a input/output at the specific x and y coordinates on the grid.
        /// @param x X coordinate of the gate slot.
        /// @param y Y coordinate of the gate slot.
        /// @param isOutput Whether the IO should be an output or not.
        /// @param expectedState 0 if off, 1 if on.
        IOItem* addIOItem(int x, int y, int ID, bool state, bool isOutput, bool expectedState);

        /// @brief Creates a gate slot at the specific x and y coordinates on the grid.
        /// @param startSlot The gate slot the wire will be starting from.
        /// @param endSlot The gate slot the wire will end at.
        void addWireItem(GameItem* startSlot, GameItem* endSlot);

        /// @brief Returns the y value of the bottom wall.
        float getBottomWallY() const;

    private slots:
        /// @brief Steps through each physics movement.
        void physicsLoop();

    private:
        /// @brief Draws the grid background of the game scene.
        void drawBackground(QPainter* painter, const QRectF& rect) override;

        /// @brief Creates the walls around the grid to keep physics objects in.
        void createWorldBounds();

        // Simulation control
        QTimer timer;

        // Scene components
        QVector<IOItem*> ioitems;
        QVector<WireItem*> wires;
        QVector<LogicGateItem*> gates;
        QVector<GateSlotItem*> gateSlots;

        // Physics and debug
        b2World world;
        float bottomWallY;

        // Layout constants
        int cellSize;
        int gridSize;
        int padding;
};

#endif // GAMESCENE_H
