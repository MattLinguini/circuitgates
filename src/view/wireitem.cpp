#include "wireitem.h"
#include "qpen.h"
#include <cmath>

static constexpr float SCALE = 30.0f;

WireItem::WireItem(b2World* world, GameItem* startSlot, GameItem* endSlot, int segmentCount) : world(world), startSlot(startSlot), endSlot(endSlot) {
    // Calculate the starting and ending positions of the wire based on the slot positions.
    QPointF startPos = startSlot->pos();
    QPointF endPos = endSlot->pos();
    b2Vec2 start(startPos.x() / SCALE, -startPos.y() / SCALE);
    b2Vec2 end(endPos.x() / SCALE, -endPos.y() / SCALE);
    b2Vec2 direction = end - start;
    direction.Normalize();
    float totalLength = QLineF(startPos, endPos).length() / SCALE;
    float segmentLength = totalLength / segmentCount;
    float segmentWidth = 0.1f;
    float segmentHeight = segmentLength;

    // Create each rope segment with the calculations above.
    for (int i = 0; i < segmentCount; ++i) {
        // Setup invisible Box2D static body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        float distanceAlong = segmentLength * i;
        b2Vec2 offset(direction.x * distanceAlong, direction.y * distanceAlong);
        bodyDef.position = start + offset;
        b2Body* segment = world->CreateBody(&bodyDef);

        // Attach a rectangle to the body
        b2PolygonShape shape;
        shape.SetAsBox(segmentWidth / 2, segmentHeight / 2);

        // Set the physics properties of the rectangle.
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 1.0f;
        fixDef.friction = 0.2f;
        segment->CreateFixture(&fixDef);

        // Add that segment to the vector.
        segments.append(segment);

        // Connect the segment to the previous box2d body.
        if (i > 0) {
            b2DistanceJointDef jointDef;
            jointDef.Initialize(segments[i-1], segment, segments[i-1]->GetWorldCenter(), segment->GetWorldCenter());
            jointDef.collideConnected = false;
            jointDef.length = segmentLength;
            jointDef.frequencyHz = 4.0f;
            jointDef.dampingRatio = 0.7f;
            joints.append(world->CreateJoint(&jointDef));
        }
    }

    // Attach the first segment in the vector to the startingSlot.
    b2DistanceJointDef firstAnchor;
    firstAnchor.Initialize(startSlot->getBody(), segments[0], startSlot->getBody()->GetWorldCenter(), segments[0]->GetWorldCenter());
    firstAnchor.collideConnected = false;
    firstAnchor.length = 0.0f;
    world->CreateJoint(&firstAnchor);

    // Attach the last segment in the vector to the endingSlot.
    b2DistanceJointDef lastAnchor;
    lastAnchor.Initialize(endSlot->getBody(), segments.last(), endSlot->getBody()->GetWorldCenter(), segments.last()->GetWorldCenter());
    lastAnchor.collideConnected = false;
    lastAnchor.length = 0.0f;
    world->CreateJoint(&lastAnchor);

    // Create the QT Visual.S
    setPen(QPen(Qt::black, 2));
    setZValue(-1);
}


void WireItem::updateWirePath() {
    if (segments.isEmpty()) return;

    QPainterPath path;

    // Update the first segment first and move the path to that position.
    b2Vec2 firstPos = segments[0]->GetPosition();
    path.moveTo(firstPos.x * SCALE, -firstPos.y * SCALE);

    // Once the first has been done, update the rest.
    for (int i = 1; i < segments.size(); ++i) {
        b2Vec2 pos = segments[i]->GetPosition();
        path.lineTo(pos.x * SCALE, -pos.y * SCALE);
    }

    setPath(path);
}

void WireItem::createWires() {
    QPointF startPos = startSlot->pos();
    QPointF endPos = endSlot->pos();
    b2Vec2 start(startPos.x() / SCALE, -startPos.y() / SCALE);
    b2Vec2 end(endPos.x() / SCALE, -endPos.y() / SCALE);
    b2Vec2 direction = end - start;
    direction.Normalize();
    float totalLength = QLineF(startPos, endPos).length() / SCALE;
    float segmentLength = totalLength / segmentCount;
    float segmentWidth = 0.1f;
    float segmentHeight = segmentLength;

    // Create each rope segment with the calculations above.
    for (int i = 0; i < segmentCount; ++i) {
        // Setup invisible Box2D static body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        float distanceAlong = segmentLength * i;
        b2Vec2 offset(direction.x * distanceAlong, direction.y * distanceAlong);
        bodyDef.position = start + offset;
        b2Body* segment = world->CreateBody(&bodyDef);

        // Attach a rectangle to the body
        b2PolygonShape shape;
        shape.SetAsBox(segmentWidth / 2, segmentHeight / 2);

        // Set the physics properties of the rectangle.
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 1.0f;
        fixDef.friction = 0.2f;
        segment->CreateFixture(&fixDef);

        // Add that segment to the vector.
        segments.append(segment);

        // Connect the segment to the previous box2d body.
        if (i > 0) {
            b2DistanceJointDef jointDef;
            jointDef.Initialize(segments[i-1], segment, segments[i-1]->GetWorldCenter(), segment->GetWorldCenter());
            jointDef.collideConnected = false;
            jointDef.length = segmentLength;
            jointDef.frequencyHz = 4.0f;
            jointDef.dampingRatio = 0.7f;
            joints.append(world->CreateJoint(&jointDef));
        }
    }

    // Attach the first segment in the vector to the startingSlot.
    b2DistanceJointDef firstAnchor;
    firstAnchor.Initialize(startSlot->getBody(), segments[0], startSlot->getBody()->GetWorldCenter(), segments[0]->GetWorldCenter());
    firstAnchor.collideConnected = false;
    firstAnchor.length = 0.0f;
    world->CreateJoint(&firstAnchor);

    // Attach the last segment in the vector to the endingSlot.
    b2DistanceJointDef lastAnchor;
    lastAnchor.Initialize(endSlot->getBody(), segments.last(), endSlot->getBody()->GetWorldCenter(), segments.last()->GetWorldCenter());
    lastAnchor.collideConnected = false;
    lastAnchor.length = 0.0f;
    world->CreateJoint(&lastAnchor);

    // Create the QT Visual.S
    setPen(QPen(Qt::black, 2));
    setZValue(-1);
}
