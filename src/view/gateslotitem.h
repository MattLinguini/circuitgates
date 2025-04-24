// * Checked by ?

/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        24 April, 2025
 * Description: ?
 */

#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "Box2D/Dynamics/b2Body.h"
#include "gameitem.h"
#include "src/model/logic_gate.h"
#include "src/view/wireitem.h"

class LogicGateItem;

/// @class GameSlotItem
/// @brief A GameItem that handles logic gates snapping into it and changing its type.
class GateSlotItem : public GameItem {
    public:
        /// @brief Constructor to create a gate slot with a static box2d body and Qt Rectangle.
        /// @param world Reference to the box2D world created in the GameScene
        /// @param centerX X value (in meters) where the item should be created
        /// @param centerY Y value (in meters) where the item should be created
        /// @param width Width (in meters) of the item.
        /// @param height Height (in meters) of the item.
        GateSlotItem(b2World* world, float centerX, float centerY, float width, float height, float cellSize, float padding, int id, QGraphicsItem* parent = nullptr);

        /// @brief Returns the specific body for the gate slot.
        b2Body* getBody() const override;

        int getID() const override;

        /// @brief Checks if the slot is occupied by a gate.
        bool isOccupied() const;

        /// @brief Sets the slot to occupied.
        /// @param occ True if the slot has a gate inside of it, false otherwise.
        void setOccupied(bool occ);

        /// @brief Sets the current gate in the slot.
        /// @param gate Gate to be set.
        void setCurrentGate(LogicGateItem* gate);

        /// @brief Gets the current gate in the slot.
        LogicGateItem* getCurrentGate();

        /// @brief Toggles the power of itself and any wires connected to it.
        /// @param state True if powered on, false otherwise.
        void togglePower(bool state) override;

        /// @brief Lets the Gate know a wire is connected to it.
        /// @param wire Pointer to a WireItem.
        void addWire(WireItem* wire) override;
    private:
        /// @brief Called automatically when item properties (like position) change.
        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

        /// @brief Called when the user releases the mouse after dragging
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

        /// @brief Used to draw the gate slot icon.
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

        // Layout constants
        float padding;
        float cellSize;

        // Box2D Physics body
        b2Body* body;
        QList<WireItem*> connectedWires;

        // Flags
        int id = -1;
        bool occupied = false;
        LogicGate::GateType gateType;

        LogicGateItem* currentGate;

        // Icon for the gate slot.
        QPixmap icon;
};

#endif // GAMEOBJECTS_H
