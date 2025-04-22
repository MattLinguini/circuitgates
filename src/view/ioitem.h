#ifndef IOITEM_H
#define IOITEM_H

#include "Box2D/Dynamics/b2Body.h"
#include "gameitem.h"
#include <QGraphicsItem>
#include <QGraphicsSceneEvent>
#include <QVariant>

class IOItem : public GameItem {
    public:
        /// @brief Constructor to create a gate slot with a static box2d body and Qt Rectangle.
        /// @param world    Reference to the box2D world created in the GameScene
        /// @param centerX  X value (in meters) where the item should be created
        /// @param centerY  Y value (in meters) where the item should be created
        /// @param width    Width (in meters) of the item.
        /// @param height   Height (in meters) of the item.
        /// @param padding  Padding around the grid.
        /// @param cellSize Cellsize of the scene.
        IOItem(b2World* world, float centerX, float centerY, float width, float height, float padding, float cellSize, int id, QGraphicsItem* parent = nullptr);

        /// @brief Returns the body of the specific LogicGate.
        b2Body* getBody() const override;

        /// @brief Updates the LogicGateItem's position and rotation to match the box2d body.
        void updateGate();

        int getID() const override;

    private:
        /// @brief Called when the LogicGateItem changes position. Updates the box2d's position.
        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

        b2Body* body;
        b2World* world;
        float snapDistancePixels;
        float padding;
        float cellSize;
        int id = -1;
};

#endif // IOITEM_H
