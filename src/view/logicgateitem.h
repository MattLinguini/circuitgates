#ifndef LOGICGATEITEM_H
#define LOGICGATEITEM_H

#include "Box2D/Dynamics/b2Body.h"
#include "gateslotitem.h"

class LogicGateItem : public GameItem {
public:
    /// @brief Constructor to create a gate slot with a static box2d body and Qt Rectangle.
    /// @param world    Reference to the box2D world created in the GameScene
    /// @param centerX  X value (in meters) where the item should be created
    /// @param centerY  Y value (in meters) where the item should be created
    /// @param width    Width (in meters) of the item.
    /// @param height   Height (in meters) of the item.
    /// @param padding  Padding around the grid.
    /// @param cellSize Cellsize of the scene.
    LogicGateItem(b2World* world, float centerX, float centerY, float width, float height, float padding, float cellSize, QGraphicsItem* parent = nullptr);

    /// @brief Returns the body of the specific LogicGate.
    b2Body* getBody() const override;

    /// @brief Updates the LogicGateItem's position and rotation to match the box2d body.
    void updateGate();

private:
    /// @brief Returns the closest GateSlot to the LogicGateItem's position.
    GateSlotItem* findClosestSlot();

    /// @brief Returns whether the GateSlotItem is in range for the LogicGateItem to be snapped in.
    /// @param slot GateSlotItem to be checked.
    bool isWithinSnapRange(GateSlotItem* slot);

    /// @brief Called when the LogicGateItem changes position. Updates the box2d's position.
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

    /// @brief If when the mouse releases the GateSlotItem is close enough, it will snap. If not, it will fall.
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    /// @brief Switches the LogicGate to allow movement instead of being static when clicked.
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    b2Body* body;
    b2World* world;
         float snapDistancePixels;
    float padding;
    float cellSize;
};

#endif // LOGICGATEITEM_H
