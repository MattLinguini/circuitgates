#include "logicgateitem.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include <QGraphicsScene>
#include <QLineF>

static constexpr float SCALE = 30.0f;

LogicGateItem::LogicGateItem(b2World* world, float centerX_meters, float centerY_meters, float width_meters, float height_meters, float padding, float cellSize, QGraphicsItem* parent) : QGraphicsRectItem(parent), body(nullptr), snapDistancePixels(40.0f), padding(padding), cellSize(cellSize) {
    // Allow the item to be moved. When it is moved, send the position changes to itemChange().
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    // Setup invisible Box2D static body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(centerX_meters, centerY_meters);
    body = world->CreateBody(&bodyDef);

    // Attach a rectangle to the body
    b2PolygonShape shape;
    shape.SetAsBox(width_meters/2, height_meters/2);

    // Set the physics properties of the rectangle.
    b2FixtureDef fixDef;
    fixDef.shape = &shape;
    fixDef.density = 1.0f;
    fixDef.friction = 0.3f;
    body->CreateFixture(&fixDef);

    // Create the Qt Rectangle with the same position as the box2d body.
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

    // Search all the items in the scene and find the cloest slot.
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
        // Snap to the center of the closest slot.
        setPos(closestSlot->pos());

        if (body) {
            body->SetTransform(
                b2Vec2(pos().x() / SCALE, -pos().y() / SCALE),
                body->GetAngle()
                );

            // Freeze the body after it has snapped
            body->SetType(b2_staticBody);
            //EMIT TO MODEL
        }
    } else {
        if (body) {
            // Let the body fall is not snapped.
            body->SetType(b2_dynamicBody);
        }
    }
}

void LogicGateItem::updateGate() {
    if (body) {
        b2Vec2 bodyPos = body->GetPosition();
        setPos(bodyPos.x * SCALE, -bodyPos.y * SCALE);
        setRotation(-body->GetAngle() * 180.0f / b2_pi);
    }
}

