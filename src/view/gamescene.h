#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Box2D/Dynamics/b2World.h"
#include "box2ddebug.h"
#include "gateslotitem.h"
#include "logicgateitem.h"
#include "src/view/ioitem.h"
#include "wireitem.h"
#include <QGraphicsScene>
#include <QHash>
#include <QTimer>

// 30 Pixels per Box2D Meter.
static const float SCALE = 30.0f;

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
        void addLogicGate(int x, int y, LogicGate::GateType gateType);

        /// @brief Creates a input/output at the specific x and y coordinates on the grid.
        /// @param x X coordinate of the gate slot.
        /// @param y Y coordinate of the gate slot.
        IOItem* addIOItem(int x, int y, int ID);

        /// @brief Creates a gate slot at the specific x and y coordinates on the grid.
        /// @param startSlot The gate slot the wire will be starting from.
        /// @param endSlot The gate slot the wire will end at.
        void addWireItem(GameItem* startSlot, GameItem* endSlot);

    private slots:
        /// @brief Steps through each physics movement.
        void physicsLoop();

    private:
        /// @brief Draws the grid background of the game scene.
        void drawBackground(QPainter* painter, const QRectF& rect) override;

        /// @brief Draws the debug boxes on the Box2D physics objects.
        void drawForeground(QPainter* painter, const QRectF&) override;

        /// @brief Creates the walls around the grid to keep physics objects in.
        void createWorldBounds();

        b2World world;
        Box2DDebugDraw debugDraw;
        QTimer timer;
        QVector<IOItem*> ioitems;
        QVector<WireItem*> wires;
        QVector<LogicGateItem*> gates;
        QVector<GateSlotItem*> gateSlots;
        int cellSize;
        int gridSize;
        int padding;
};

#endif // GAMESCENE_H
