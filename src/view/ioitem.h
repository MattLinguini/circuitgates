#ifndef IOITEM_H
#define IOITEM_H

#include "Box2D/Dynamics/b2Body.h"
#include "gameitem.h"
#include <QGraphicsItem>
#include <QGraphicsSceneEvent>
#include <QVariant>

class WireItem;

class CircuitGameView;

/// @class IOItem
/// @brief A GameItem that either gives or recieves power from or to a gate.
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

        /// @brief Returns the ID of the IO item.
        int getID() const override;

        /// @brief Toggles the power of itself and any wires connected to it.
        /// @param state True if powered on, false otherwise.
        void togglePower(bool state) override;

        /// @brief Lets the Gate know a wire is connected to it.
        /// @param wire Pointer to a WireItem.
        void addWire(WireItem* wire) override;

        /// @brief Sets a reference to the view that the item is contained in.
        /// @param view View to be set.
        void setView(CircuitGameView* view);

    private:
        /// @brief Called when the LogicGateItem changes position. Updates the box2d's position.
        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

        /// @brief Overriden paint method to add styling to the QT object.
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

        /// @brief Override for mouse click toggling.
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

        // Physics
        b2Body* body;
        b2World* world;
        QList<WireItem*> connectedWires;

        // Layout constants
        float snapDistancePixels;
        float padding;
        float cellSize;

        int id;
        bool state;

        CircuitGameView* view = nullptr;
};

#endif // IOITEM_H
