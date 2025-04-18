#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "Box2D/Dynamics/b2Body.h"
#include <QGraphicsRectItem>

class GateSlotItem : public QGraphicsRectItem {
    public:
        /// @brief Constructor to create a Gate Slot
        /// @param world Reference to the box2D world created in the GameScene
        /// @param centerX X value (in meters) where the item should be created
        /// @param centerY Y value (in meters) where the item should be created
        /// @param width Width (in meters) of the item.
        /// @param height Height (in meters) of the item.
        GateSlotItem(b2World* world, float centerX, float centerY, float width, float height, float cellSize, float padding, QGraphicsItem* parent = nullptr);

        /// @brief Returns the box2d body of the Gate Slot.
        b2Body* getBody() const;

    private:
        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
        b2Body* body;
        float padding;
        float cellSize;
};

#endif // GAMEOBJECTS_H
