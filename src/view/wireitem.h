// * Checked by ?

/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        24 April, 2025
 * Description: ?
 */

#ifndef WIREITEM_H
#define WIREITEM_H

#include <QGraphicsItem>
#include <Box2D/Box2D.h>
#include <QVector>
#include "gameitem.h"

/// @class WireItem
/// @brief A QGraphicsPathItem that integrates Box2D physics and displays a wire path from GameItem to GameItem.
class WireItem : public QGraphicsPathItem {
    public:
        /// @brief Creates a wire from one GameItem to another.
        /// @param world Reference to the box2d world.
        /// @param startSlot GameItem that the wire will start from.
        /// @param endSlot GameItem that the wire will end from.
        WireItem(b2World* world, GameItem* startSlot, GameItem* endSlot, int segmentCount);

        /// @brief Updates the visual of the wirepath.
        void updateWirePath();

        /// @brief Toggles the powered state of the wire.
        /// @param state True if powered on, false otherwise.
        void togglePower(bool state);

    private:
        // Physics
        b2World* world;
        QVector<b2Body*> segments;
        QVector<b2Joint*> joints;
        int segmentCount;

        // GameItems
        GameItem* startSlot;
        GameItem* endSlot;
};

#endif // WIREITEM_H
