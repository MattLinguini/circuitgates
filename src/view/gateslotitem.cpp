#include "gateslotitem.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

static constexpr float SCALE = 30.0f;

GateSlotItem::GateSlotItem(b2World* world, float centerX, float centerY, float width, float height, float cellSize, float padding, int id, QGraphicsItem* parent) : QGraphicsRectItem(parent), padding(padding), cellSize(cellSize) {
    this->id = id;
    // Setup invisible Box2D static body
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(centerX, centerY);
    body = world->CreateBody(&bodyDef);

    // Attach a rectangle to the body
    b2PolygonShape shape;
    shape.SetAsBox(width/2.0f, height/2.0f);

    // Set the physics properties of the rectangle.
    b2FixtureDef fixDef;
    fixDef.shape = &shape;
    fixDef.density = 1.0f;
    fixDef.friction = 0.3f;
    body->CreateFixture(&fixDef);

    // Create the Qt Rectangle with the same position as the box2d body.
    setRect(-width/2 * SCALE, -height/2 * SCALE, width * SCALE, height * SCALE);
    setBrush(Qt::gray);
    setPos(centerX * SCALE, -centerY * SCALE);

    // Load the gate slot icon
    icon.load(":/gates/resources/default_gate.png");
}

b2Body* GateSlotItem::getBody() const {
    return body;
}

QVariant GateSlotItem::itemChange(GraphicsItemChange change, const QVariant& value) {
    return QGraphicsRectItem::itemChange(change, value);
}

void GateSlotItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsRectItem::mouseReleaseEvent(event);
}

int GateSlotItem::getID() const {
    return id;
}

bool GateSlotItem::isOccupied() const {
    return occupied;
}

void GateSlotItem::setOccupied(bool occ) {
    occupied = occ;
}

void GateSlotItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QGraphicsRectItem::paint(painter, option, widget);

    if (!icon.isNull()) {
        QRectF bounds = boundingRect();
        painter->drawPixmap(bounds.toRect(), icon);
    }
}

