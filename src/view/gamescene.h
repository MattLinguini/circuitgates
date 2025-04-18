#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include "qtimer.h"
#include "box2ddebug.h"
#include <QGraphicsScene>
#include <QHash>

// 30 Pixels per Box2D Meter.
static const float SCALE = 30.0f;

class GameScene : public QGraphicsScene {
    Q_OBJECT

public:
    GameScene(QObject* parent = nullptr);
    void addGateSlot(int x, int y);

private slots:
    void physicsLoop();

private:
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void drawForeground(QPainter* painter, const QRectF&) override;

    b2World world;
    Box2DDebugDraw debugDraw;
    QTimer timer;
    QHash<b2Body*, QGraphicsItem*> bodyItemMap;
    int cellSize;
    int gridSize;
    int padding;

};

#endif // GAMESCENE_H
