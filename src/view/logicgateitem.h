// * Checked by ?

/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        24 April, 2025
 * Description: ?
 */

#ifndef LOGICGATEITEM_H
#define LOGICGATEITEM_H

#include "Box2D/Dynamics/b2Body.h"
#include "gateslotitem.h"
#include "QPainter"

class CircuitGameView;

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
        LogicGateItem(LogicGate::GateType gateType, b2World* world, float centerX, float centerY, float width, float height, float padding, float cellSize, QGraphicsItem* parent = nullptr);

        /// @brief Updates the LogicGateItem's position and rotation to match the box2d body.
        void updateGate();

        /// @brief Returns the body of the specific LogicGate.
        b2Body* getBody() const override;

        /// @brief Returns the view reference of the specific LogicGate.
        CircuitGameView* getView() const;

        /// @brief Sets a reference to the view that the item is contained in.
        /// @param viewObj View to be set.
        void setView(CircuitGameView* viewObj);

        /// @brief Returns the id of the specific LogicGate.
        int getID() const override;

        /// @brief Lets the Gate know a wire is connected to it.
        /// @param wire Pointer to a WireItem.
        void addWire(WireItem* wire) override;

        /// @brief Toggles the power of itself and any wires connected to it.
        /// @param state True if powered on, false otherwise.
        void togglePower(bool state) override;

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

        /// @brief Draws the gate icon.
        void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;

        // Physics
        b2Body* body;
        b2World* world;
        b2Vec2 originalPosition;

        // Constrants
        float snapDistancePixels;
        float padding;
        float cellSize;

        // Identifiers
        int id;
        GateSlotItem* snappedSlot = nullptr;
        LogicGate::GateType gateType;

        CircuitGameView* view = nullptr;
        QPixmap icon;

};

#endif // LOGICGATEITEM_H
