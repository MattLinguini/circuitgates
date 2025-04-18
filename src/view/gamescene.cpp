#include "gamescene.h"
#include "gateslotitem.h"
#include "Box2D/Common/b2Draw.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include "qgraphicsitem.h"
#include "src/view/logicgateitem.h"

GameScene::GameScene(QObject* parent) : QGraphicsScene(parent), world(b2Vec2(0.0f, -9.8f)), cellSize(64), gridSize(7) {
    // How much padding around the grid (in pixels)
    const int padding = 10;

    // Calculate total scene size
    int sceneWidth  = gridSize * cellSize + 2 * padding;
    int sceneHeight = gridSize * cellSize + 2 * padding;

    setSceneRect(0, 0, sceneWidth, sceneHeight);

    // set up debug draw
    debugDraw.SetFlags(b2Draw::e_shapeBit);
    world.SetDebugDraw(&debugDraw);

    // start the simulation timer
    timer.setInterval(16);
    connect(&timer, &QTimer::timeout, this, &GameScene::physicsLoop);
    timer.start();

    createWorldBounds();
}

void GameScene::physicsLoop() {
    float timeStep = 1.0f / 60.0f;
    int velIters = 8;
    int posIters = 3;

    world.Step(timeStep, velIters, posIters);

    for (QGraphicsItem* item : items()) {
        LogicGateItem* gate = dynamic_cast<LogicGateItem*>(item);
        if (gate) {
            b2Body* body = gate->getBody();
            if (body) {
                b2Vec2 bodyPos = body->GetPosition();
                gate->setPos(bodyPos.x * SCALE, -bodyPos.y * SCALE);
                gate->setRotation(body->GetAngle() * 180.0f / b2_pi);
            }
        }
    }

    update();
}

void GameScene::addGateSlot(int x, int y) {
    float size  = static_cast<float>(cellSize) / SCALE;
    float scenePosX = (padding + x * cellSize + cellSize / 2) / SCALE;
    float scenePosY = -(padding + y * cellSize + cellSize / 2) / SCALE;

    GateSlotItem* item = new GateSlotItem(scenePosX, scenePosY, size, size, cellSize, padding);
    addItem(item);
}

void GameScene::addLogicGate(int x, int y) {
    float size  = static_cast<float>(cellSize) / SCALE;
    float scenePosX = (padding + x * cellSize + cellSize / 2) / SCALE;
    float scenePosY = -(padding + y * cellSize + cellSize / 2) / SCALE;

    LogicGateItem* gate = new LogicGateItem(&world, scenePosX, scenePosY, size, size, padding, cellSize);
    addItem(gate);
}

void GameScene::drawBackground(QPainter* painter, const QRectF& rect) {
    Q_UNUSED(rect);

    painter->setPen(QPen(Qt::lightGray, 0));

    // Draw vertical grid lines
    for (int i = 0; i <= gridSize; ++i) {
        int x = padding + i * cellSize;
        painter->drawLine(x, padding, x, padding + gridSize * cellSize);
    }

    // Draw horizontal grid lines
    for (int j = 0; j <= gridSize; ++j) {
        int y = padding + j * cellSize;
        painter->drawLine(padding, y, padding + gridSize * cellSize, y);
    }
}

void GameScene::drawForeground(QPainter* painter, const QRectF&) {
    debugDraw.setPainter(painter);
    world.DrawDebugData();
}

void GameScene::createWorldBounds() {
    float left_px   = padding;
    float top_px    = padding;
    float right_px  = padding + gridSize * cellSize;
    float bottom_px = padding + gridSize * cellSize;

    float thickness_m = 0.5f;

    float left_m   = left_px / SCALE;
    float top_m    = -top_px / SCALE; 
    float right_m  = right_px / SCALE;
    float bottom_m = -bottom_px / SCALE;

    float width_m  = (right_px - left_px) / SCALE;
    float height_m = (bottom_px - top_px) / SCALE;

    struct WallDef {
        b2Vec2 center;
        b2Vec2 halfSize;
    };

    QVector<WallDef> walls = {
        { b2Vec2((left_m + right_m) / 2, bottom_m - thickness_m), b2Vec2(width_m/2, thickness_m) }, // Floor
        { b2Vec2((left_m + right_m) / 2, top_m + thickness_m),     b2Vec2(width_m/2, thickness_m) }, // Ceiling
        { b2Vec2(left_m - thickness_m, (top_m + bottom_m) / 2),    b2Vec2(thickness_m, height_m/2) }, // Left wall
        { b2Vec2(right_m + thickness_m, (top_m + bottom_m) / 2),   b2Vec2(thickness_m, height_m/2) }  // Right wall
    };

    for (const WallDef& def : walls) {
        b2BodyDef bodyDef;
        bodyDef.position = def.center;
        b2Body* body = world.CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(def.halfSize.x, def.halfSize.y);

        body->CreateFixture(&shape, 0.0f);
    }
}

