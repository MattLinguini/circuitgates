#include "logicgateitem.h"
#include "circuit_game_view.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include "src/view/gamescene.h"
#include <QGraphicsScene>
#include <QLineF>

LogicGateItem::LogicGateItem(LogicGate::GateType gateType, b2World* world, float centerX_meters, float centerY_meters, float width_meters, float height_meters, float padding, float cellSize, QGraphicsItem* parent)
    : QGraphicsRectItem(parent), body(nullptr), snapDistancePixels(40.0f), padding(padding), cellSize(cellSize), gateType(gateType) {
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
    originalPosition = b2Vec2(centerX_meters, centerY_meters);

    togglePower(false);
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
    const QList<QGraphicsItem*>& items = scene()->items();
    for (QGraphicsItem* item : items) {
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
        body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
        body->SetAngularVelocity(0.0f);
    }
}


void LogicGateItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsRectItem::mouseReleaseEvent(event);

    GateSlotItem* closestSlot = findClosestSlot();
    if (closestSlot && isWithinSnapRange(closestSlot) && !closestSlot->isOccupied()) {
        // Snap to the center of the closest slot.
        if (snappedSlot && snappedSlot != closestSlot) {
            snappedSlot->setOccupied(false);  // Clear previous slot if moving to new one
            view->sendGateToModel(snappedSlot->getID(), GateType::DEFAULT);
        }

        // Set the slot to occupied
        setPos(closestSlot->pos());
        closestSlot->setOccupied(true);
        snappedSlot = closestSlot;


        if (body) {
            body->SetTransform(b2Vec2(pos().x() / SCALE, -pos().y() / SCALE), 0.0f);

            // Freeze the body after it has snapped
            body->SetType(b2_staticBody);
            snappedSlot->setCurrentGate(this);


            if (view) {
                view->sendGateToModel(closestSlot->getID(), this->gateType);
            }

        }
    }
    else {
        body->SetType(b2_dynamicBody);

        // Clear any slot that was previously occupied by this gate
        if (snappedSlot) {
            view->sendGateToModel(snappedSlot->getID(), GateType::DEFAULT);
            snappedSlot->setCurrentGate(nullptr);
            snappedSlot->setOccupied(false);
            snappedSlot = nullptr;
        }
    }
}


void LogicGateItem::updateGate() {
    if (body) {
        b2Vec2 bodyPos = body->GetPosition();

        GameScene* gameScene = qobject_cast<GameScene*>(scene());
        if (gameScene) {
            float wallThickness = 0.5f;

            if (bodyPos.y < (gameScene->getBottomWallY() - wallThickness)) {
                body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
                body->SetAngularVelocity(0.0f);
                body->SetTransform(originalPosition, 0.0f);
                body->SetType(b2_staticBody);
                bodyPos = body->GetPosition();
            }
        }

        setPos(bodyPos.x * SCALE, -bodyPos.y * SCALE);
        setRotation(-body->GetAngle() * 180.0f / b2_pi);
    }
}


int LogicGateItem::getID() const {
    return id;
}


void LogicGateItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if (!icon.isNull()) {
        painter->drawPixmap(boundingRect().toRect(), icon);
    } else {
        painter->setBrush(Qt::gray);
        painter->drawRect(boundingRect());
    }
}


void LogicGateItem::setView(CircuitGameView* viewObj) {
    view = viewObj;
}


CircuitGameView* LogicGateItem::getView() const {
    return view;
}


void LogicGateItem::addWire(WireItem* /*wire*/) {}


void LogicGateItem::togglePower(bool state) {
    if (state) {
        switch (gateType) {
            case LogicGate::GateType::AND:
                icon.load(":/gates/resources/and_gate_power.png");
                break;
            case LogicGate::GateType::OR:
                icon.load(":/gates/resources/or_gate_power.png");
                break;
            case LogicGate::GateType::NOT:
                icon.load(":/gates/resources/not_gate_power.png");
                break;
            case LogicGate::GateType::XOR:
                icon.load(":/gates/resources/xor_gate_power.png");
                break;
            case LogicGate::GateType::DEFAULT:
                break;
        }
    } else {
        switch (gateType) {
        case LogicGate::GateType::AND:
            icon.load(":/gates/resources/and_gate.png");
            break;
        case LogicGate::GateType::OR:
            icon.load(":/gates/resources/or_gate.png");
            break;
        case LogicGate::GateType::NOT:
            icon.load(":/gates/resources/not_gate.png");
            break;
        case LogicGate::GateType::XOR:
            icon.load(":/gates/resources/xor_gate.png");
            break;
        case LogicGate::GateType::DEFAULT:
            break;
        }
    }
}
