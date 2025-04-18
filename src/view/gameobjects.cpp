#include "gameobjects.h"
#include "Box2D/Dynamics/b2World.h"
#include "src/view/gamescene.h"

GateSlotItem::GateSlotItem(b2World* world, float centerX_meters, float centerY_meters, float width_meters, float height_meters, float cellSize, float padding, QGraphicsItem* parent) : QGraphicsRectItem(parent), body(nullptr), padding(padding), cellSize(cellSize) {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(centerX_meters, centerY_meters);
    body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(width_meters/2, height_meters/2);

    b2FixtureDef fixDef;
    fixDef.shape = &shape;
    fixDef.density = 1.0f;
    fixDef.friction = 0.3f;
    body->CreateFixture(&fixDef);

    setRect(-width_meters/2 * SCALE, -height_meters/2 * SCALE, width_meters * SCALE, height_meters * SCALE);
    setBrush(Qt::yellow);

    setPos(centerX_meters * SCALE, -centerY_meters * SCALE);
}

b2Body* GateSlotItem::getBody() const {
    return body;
}

QVariant GateSlotItem::itemChange(GraphicsItemChange change, const QVariant& value) {
    if (change == QGraphicsItem::ItemPositionHasChanged && body) {
        QPointF pos = value.toPointF();
        body->SetTransform(
            b2Vec2(pos.x() / SCALE, -pos.y() / SCALE),
            body->GetAngle()
            );
    }
    return QGraphicsRectItem::itemChange(change, value);
}

// Eventually this will go in the logic gate object itself
void GateSlotItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsRectItem::mouseReleaseEvent(event);

    float x = pos().x();
    float y = pos().y();

    // Offset by half a cell to center rounding properly
    float snappedCol = std::round((x - padding - cellSize/2) / cellSize);
    float snappedRow = std::round((y - padding - cellSize/2) / cellSize);

    float snappedX = padding + snappedCol * cellSize + cellSize/2;
    float snappedY = padding + snappedRow * cellSize + cellSize/2;

    setPos(snappedX, snappedY);

    if (body) {
        body->SetTransform(
            b2Vec2(snappedX / SCALE, -snappedY / SCALE),
            body->GetAngle()
            );
    }
}
