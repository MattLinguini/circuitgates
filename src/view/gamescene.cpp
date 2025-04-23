#include "gamescene.h"
#include "gateslotitem.h"
#include "Box2D/Common/b2Draw.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include "qgraphicsitem.h"
#include "src/view/ioitem.h"
#include "src/view/logicgateitem.h"
#include "src/view/wireitem.h"

GameScene::GameScene(QObject* parent) : QGraphicsScene(parent), world(b2Vec2(0.0f, -50.0f)), cellSize(64), gridSize(7) {
    // How much padding around the grid (in pixels)
    const int padding = 10;

    // Calculate total scene size and set it.
    int sceneWidth  = (gridSize + 2) * cellSize + 2 * padding;
    int sceneHeight = gridSize * cellSize + 2 * padding;
    setSceneRect(0, 0, sceneWidth, sceneHeight);

    // Allow Debug drawing for the Box2D bodies.
    debugDraw.SetFlags(b2Draw::e_shapeBit);
    world.SetDebugDraw(&debugDraw);

    // Start the simulation, will run the loop every 16ms.
    timer.setInterval(16);
    connect(&timer, &QTimer::timeout, this, &GameScene::physicsLoop);
    timer.start();

    // Creates the boxes around the grid to prevent objects from falling out.
    createWorldBounds();
}

void GameScene::physicsLoop() {
    float timeStep = 1.0f / 60.0f; // About 60 steps (frames) per second
    int velIters = 5; // Each frame, the loop will update the velocity of each body 5 times.
    int posIters = 5; // Each frame, the loop will update the position of each body 5 times.

    world.Step(timeStep, velIters, posIters); // Updates all the Box2D bodies.

    // Update the position of the Qt Object to match the Box2D bodies.
    for (LogicGateItem* gate : gates) {
        gate->updateGate();
    }

    // Update the position of the QPath to match the Box2D bodies.
    for (WireItem* wire : wires) {
        wire->updateWirePath();
    }

    update();
}

GateSlotItem* GameScene::addGateSlot(int x, int y, int id) {
    // Calculates the size and postion of the slot (in meters)
    float sizeMeters  = static_cast<float>(cellSize) / SCALE;
    float sceneXMeters = (padding + (x * cellSize) + (cellSize / 2)) / SCALE;
    float sceneYMeters = -(padding + (y * cellSize) + (cellSize / 2)) / SCALE;

    // Creates a slot and adds it to the scene and the vector containing all the current slots.
    GateSlotItem* slot = new GateSlotItem(&world, sceneXMeters, sceneYMeters, sizeMeters, sizeMeters, cellSize, padding, id);
    addItem(slot);
    gateSlots.append(slot);

    // Returns a pointer to this specific slot (needed to connect wires later)
    return slot;
}

LogicGateItem* GameScene::addLogicGate(int x, int y, LogicGate::GateType gateType) {
    // Calculates the size and postion of the slot (in meters)
    float sizeMeters  = static_cast<float>(cellSize) / SCALE;
    float sceneXMeters = (padding + (x * cellSize) + (cellSize / 2)) / SCALE;
    float sceneYMeters = -(padding + (y * cellSize) + (cellSize / 2)) / SCALE;

    // Creates a gate and adds it to the scene and the vector containing all the current gates.
    LogicGateItem* gate = new LogicGateItem(gateType, &world, sceneXMeters, sceneYMeters, sizeMeters, sizeMeters, padding, cellSize);
    addItem(gate);
    gates.append(gate);

    return gate;
}

void GameScene::addWireItem(GameItem* startSlot, GameItem* endSlot) {
    WireItem* wire = new WireItem(&world, startSlot, endSlot, 10);
    addItem(wire);
    wires.append(wire);
}

IOItem* GameScene::addIOItem(int x, int y, int id) {
    // Calculates the size and postion of the slot (in meters)
    float sizeMeters  = static_cast<float>(cellSize) / SCALE;
    float sceneXMeters = (padding + (x * cellSize) + (cellSize / 2)) / SCALE;
    float sceneYMeters = -(padding + (y * cellSize) + (cellSize / 2)) / SCALE;

    IOItem* io = new IOItem(&world, sceneXMeters, sceneYMeters, sizeMeters, sizeMeters, padding, cellSize, id);
    addItem(io);
    ioitems.append(io);

    return io;
}

void GameScene::drawBackground(QPainter* painter, const QRectF& rect) {
    Q_UNUSED(rect);
    painter->setPen(QPen(Qt::lightGray, 0));

    // Draw vertical grid lines
    for (int i = 0; i <= gridSize+2; ++i) {
        int x = padding + i * cellSize;
        painter->drawLine(x, padding, x, padding + gridSize * cellSize);
    }

    // Draw horizontal grid lines
    for (int j = 0; j <= gridSize; ++j) {
        int y = padding + j * cellSize;
        painter->drawLine(padding, y, padding + (gridSize) * cellSize, y);
        painter->drawLine(padding + (gridSize+1) * cellSize, y, padding + (gridSize+2) * cellSize, y);
    }
}

void GameScene::drawForeground(QPainter* painter, const QRectF&) {
    debugDraw.setPainter(painter);
    world.DrawDebugData();
}

void GameScene::createWorldBounds() {
    // Define the pixel coordinates for the walls.
    float left_px   = padding;
    float top_px    = padding;
    float right_px  = padding + gridSize * cellSize;
    float bottom_px = padding + gridSize * cellSize;

    // Wall thickness
    float thickness_m = 0.5f;

    // Calcuate the coordinates of the walls in meters
    float left_m   = left_px / SCALE;
    float top_m    = -top_px / SCALE; 
    float right_m  = right_px / SCALE;
    float bottom_m = -bottom_px / SCALE;
    bottomWallY = bottom_m;

    // Calculate the width and height of the walls in meters.
    float width_m  = (right_px - left_px) / SCALE;
    float height_m = (bottom_px - top_px) / SCALE;

    // Struct for the definition of walls. Box2D uses half-widths and center coordinates.
    struct WallDef {
        b2Vec2 center;
        b2Vec2 halfSize;
    };

    // Defines all the walls.
    QVector<WallDef> walls = {
        { b2Vec2((left_m + right_m) / 2, bottom_m - thickness_m), b2Vec2(width_m/2, thickness_m) }, // Top wall
        { b2Vec2((left_m + right_m) / 2, top_m + thickness_m),     b2Vec2(width_m/2, thickness_m) }, // Bottom wall
        { b2Vec2(left_m - thickness_m, (top_m + bottom_m) / 2),    b2Vec2(thickness_m, height_m/2) }, // Left wall
        { b2Vec2(right_m + thickness_m, (top_m + bottom_m) / 2),   b2Vec2(thickness_m, height_m/2) }  // Right wall
    };

    // Loops through all the wall definitions and creates Box2D bodies for them.
    for (const WallDef& def : walls) {
        b2BodyDef bodyDef;
        bodyDef.position = def.center;
        b2Body* body = world.CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(def.halfSize.x, def.halfSize.y);

        body->CreateFixture(&shape, 0.0f);
    }
}

float GameScene::getBottomWallY() const {
    return bottomWallY;
}
