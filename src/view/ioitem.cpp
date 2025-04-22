#include "ioitem.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include "qpainter.h"
#include <QGraphicsScene>
#include <QLineF>

static constexpr float SCALE = 30.0f;

IOItem::IOItem(b2World* world, float centerX_meters, float centerY_meters, float width_meters, float height_meters, float padding, float cellSize, int id, QGraphicsItem* parent) : QGraphicsRectItem(parent), body(nullptr), snapDistancePixels(40.0f), padding(padding), cellSize(cellSize) {
    this->id = id;

    // When it is moved, send the position changes to itemChange().
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    // Setup invisible Box2D static body
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(centerX_meters, centerY_meters);
    body = world->CreateBody(&bodyDef);

    // Attach a rectangle to the body
    b2PolygonShape shape;
    shape.SetAsBox(width_meters/3, height_meters/3);

    // Set the physics properties of the rectangle.
    b2FixtureDef fixDef;
    fixDef.shape = &shape;
    fixDef.density = 1.0f;
    fixDef.friction = 0.3f;
    body->CreateFixture(&fixDef);

    // Create the Qt Rectangle with the same position as the box2d body.
    setRect(-width_meters/3 * SCALE, -height_meters/3 * SCALE, width_meters/1.5 * SCALE, height_meters/1.5 * SCALE);
    setBrush(Qt::blue);
    setPos(centerX_meters * SCALE, -centerY_meters * SCALE);
}

b2Body* IOItem::getBody() const {
    return body;
}

QVariant IOItem::itemChange(GraphicsItemChange change, const QVariant& value) {
    if (change == QGraphicsItem::ItemPositionHasChanged && body) {
        QPointF pos = value.toPointF();
        body->SetTransform(
            b2Vec2(pos.x() / SCALE, -pos.y() / SCALE),
            body->GetAngle()
            );
    }
    return QGraphicsRectItem::itemChange(change, value);
}

void IOItem::updateGate() {
    if (body) {
        b2Vec2 bodyPos = body->GetPosition();
        setPos(bodyPos.x * SCALE, -bodyPos.y * SCALE);
        setRotation(-body->GetAngle() * 180.0f / b2_pi);
    }
}

void IOItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::blue);

    // Draw the rectangle with rounded corners
    QRectF rect = boundingRect();
    qreal cornerRadius = rect.width(); // Adjust corner radius here
    painter->drawRoundedRect(rect, cornerRadius, cornerRadius);
}

int IOItem::getID() const {
    return id;
}

