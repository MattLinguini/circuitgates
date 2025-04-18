#ifndef LOGICGATEITEM_H
#define LOGICGATEITEM_H

#include "Box2D/Dynamics/b2Body.h"
#include "gateslotitem.h"

class LogicGateItem : public QGraphicsRectItem
{
public:
    LogicGateItem(b2World* world, float centerX, float centerY, float width, float height, float padding, float cellSize, QGraphicsItem* parent = nullptr);

    b2Body* getBody() const;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    b2Body* body = nullptr;
    b2World* world = nullptr;

    GateSlotItem* findClosestSlot();
    bool isWithinSnapRange(GateSlotItem* slot);
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

    float snapDistancePixels = 40.0f;
    float padding;
    float cellSize;
};

#endif // LOGICGATEITEM_H
