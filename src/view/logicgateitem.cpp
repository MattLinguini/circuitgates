#include "logicgateitem.h"
#include "circuit_game_view.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include <QGraphicsScene>
#include <QLineF>

static constexpr float SCALE = 30.0f;

LogicGateItem::LogicGateItem(LogicGate::GateType gateType, b2World* world, float centerX_meters, float centerY_meters, float width_meters, float height_meters, float padding, float cellSize, QGraphicsItem* parent) : QGraphicsRectItem(parent), body(nullptr), snapDistancePixels(40.0f), padding(padding), cellSize(cellSize), gateType(gateType) {
    // Allow the item to be moved. When it is moved, send the position changes to itemChange().
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    // Setup invisible Box2D static body
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
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
    switch (gateType) {
        case LogicGate::GateType::OR: setBrush(Qt::green); break;
        case LogicGate::GateType::AND: setBrush(Qt::yellow); break;
        case LogicGate::GateType::NOT: setBrush(Qt::red); break;
        case LogicGate::GateType::XOR: setBrush(Qt::blue); break;
        case LogicGate::GateType::DEFAULT: setBrush(Qt::gray); break;
    }
    setPos(centerX_meters * SCALE, -centerY_meters * SCALE);

    // Load the gate icon corresponding to the GateType.
    switch (gateType) {
        case LogicGate::GateType::AND:
            texture.load(":/gates/resources/and_gate.png");
            qDebug("AND!!!");
            break;
        case LogicGate::GateType::OR:
            texture.load(":/gates/resources/or_gate.png");
            qDebug("OR!!!");
            break;
        case LogicGate::GateType::NOT:
            texture.load(":/gates/resources/not_gate.png");
            qDebug("NOT!!!");
            break;
        case LogicGate::GateType::XOR:
            texture.load(":/gates/resources/xor_gate.png");
            qDebug("XOR!!!");
            break;
        case LogicGate::GateType::DEFAULT:
            texture.load(":/gates/resources/default_gate.png");
            qDebug("DEFAULT!!!");
            break;
    }
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

            if (view) {
            view->sendViewToModel( closestSlot->getID(), this->gateType);
            }

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

int LogicGateItem::getID() const {
    return id;
}

void LogicGateItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if (!texture.isNull()) {
        painter->drawPixmap(boundingRect().toRect(), texture);
    } else {
        painter->setBrush(Qt::gray);
        painter->drawRect(boundingRect());
    }
}
