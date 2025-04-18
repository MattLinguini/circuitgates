#include "logicgateitem.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include <QGraphicsScene>
#include <QLineF>

static constexpr float SCALE = 30.0f;

LogicGateItem::LogicGateItem(b2World* world, float centerX_meters, float centerY_meters, float width_meters, float height_meters, float padding, float cellSize, QGraphicsItem* parent) : QGraphicsRectItem(parent), body(nullptr), padding(padding), cellSize(cellSize) {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
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

b2Body* LogicGateItem::getBody() const {
    return body;
}

QVariant LogicGateItem::itemChange(GraphicsItemChange change, const QVariant& value) {
    if (change == QGraphicsItem::ItemPositionHasChanged && body) {
        QPointF pos = value.toPointF();
        body->SetTransform(
            b2Vec2(pos.x() / SCALE, -pos.y() / SCALE),
            body->GetAngle()
            );
    }
    return QGraphicsRectItem::itemChange(change, value);
}

GateSlotItem* LogicGateItem::findClosestSlot() {
    GateSlotItem* closest = nullptr;
    float closestDistanceSquared = std::numeric_limits<float>::max();

    for (QGraphicsItem* item : scene()->items()) {
        GateSlotItem* slot = dynamic_cast<GateSlotItem*>(item);
        if (slot) {
            QPointF delta = pos() - slot->pos();
            float distSq = delta.x() * delta.x() + delta.y() * delta.y();

            if (distSq < closestDistanceSquared) {
                closest = slot;
                closestDistanceSquared = distSq;
            }
        }
    }

    return closest;
}

bool LogicGateItem::isWithinSnapRange(GateSlotItem* slot) {
    const float maxSnapDistance = 40.0f;

    return QLineF(pos(), slot->pos()).length() <= maxSnapDistance;
}

void LogicGateItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsRectItem::mousePressEvent(event);

    if (body) {
        body->SetType(b2_kinematicBody);
    }
}

void LogicGateItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsRectItem::mouseReleaseEvent(event);

    GateSlotItem* closestSlot = findClosestSlot();
    if (closestSlot && isWithinSnapRange(closestSlot)) {
        setPos(closestSlot->pos());

        if (body) {
            body->SetTransform(
                b2Vec2(pos().x() / SCALE, -pos().y() / SCALE),
                body->GetAngle()
                );

            body->SetType(b2_staticBody);
        }
    } else {
        if (body) {
            body->SetType(b2_dynamicBody);
        }
    }
}

