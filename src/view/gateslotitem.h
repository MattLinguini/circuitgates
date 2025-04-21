#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "Box2D/Dynamics/b2Body.h"
#include "gameitem.h"
#include <QGraphicsRectItem>
#include "src/model/logic_gate.h"


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

        LogicGate::GateType gateType;

        int getID() const override;

    private:
        /// @brief Called automatically when item properties (like position) change.
        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

        /// @brief Called when the user releases the mouse after dragging
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

        float padding;
        float cellSize;
        b2Body* body;
        int id = -1;
};

#endif // GAMEOBJECTS_H
