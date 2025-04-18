#include "gamescene.h"
#include "gameobjects.h"
#include "Box2D/Common/b2Draw.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include "qgraphicsitem.h"

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

    // start the simulation timer (60 Hz)
    timer.setInterval(16);
    connect(&timer, &QTimer::timeout, this, &GameScene::physicsLoop);
    timer.start();
}

void GameScene::physicsLoop() {
    float timeStep = 1.0f / 60.0f;
    int velIters = 8;
    int posIters = 3;

    world.Step(timeStep, velIters, posIters);

    for (auto it = bodyItemMap.begin(); it != bodyItemMap.end(); ++it) {
        b2Body* body = it.key();
        QGraphicsItem* item = it.value();

        b2Vec2 pos = body->GetPosition();
        float  ang = body->GetAngle();

        item->setPos(pos.x * SCALE, -pos.y * SCALE);
        item->setRotation(ang * 180.0f / b2_pi);
    }

    update();
}

void GameScene::addGateSlot(int x, int y) {
    float size  = static_cast<float>(cellSize) / SCALE;
    float scenePosX = (padding + x * cellSize + cellSize / 2) / SCALE;
    float scenePosY = -(padding + y * cellSize + cellSize / 2) / SCALE;

    GateSlotItem* item = new GateSlotItem(&world, scenePosX, scenePosY, size, size, cellSize, padding);
    addItem(item);
    bodyItemMap.insert(item->getBody(), item);
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
