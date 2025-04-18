#ifndef WIREITEM_H
#define WIREITEM_H

#include "gateslotitem.h"
#include <QGraphicsItem>
#include <Box2D/Box2D.h>
#include <QVector>

class WireItem : public QGraphicsPathItem {
public:
    /// @brief Creates a wire from one GateSlotItem to another.
    /// @param world Reference to the box2d world.
    /// @param startSlot GateSlot that the wire will start from.
    /// @param endSlot GateSlot that the wire will end from.
    WireItem(b2World* world, GateSlotItem* startSlot, GateSlotItem* endSlot, int segmentCount = 10);

    /// @brief Updates the visual of the wirepath.
    void updateWirePath();

private:
    b2World* world;
    QVector<b2Body*> segments;
    QVector<b2Joint*> joints;
    GateSlotItem* startSlot;
    GateSlotItem* endSlot;
};

#endif // WIREITEM_H
