// * Checked by ?

/*
 * Authors:     Adam Wightman, Alex Johnson, Andrew Kellmer, Matt Bennett
 * Date:        24 April, 2025
 * Description: ?
 */

#ifndef GAMEITEM_H
#define GAMEITEM_H

#include "Box2D/Dynamics/b2Body.h"
#include <QGraphicsRectItem>

class WireItem;

class GameItem : public virtual QGraphicsRectItem  {
    public:
        /// @brief Returns the Box2D body.
        virtual b2Body* getBody() const = 0;

        /// @brief Returns the Gate or IO ID.
        virtual int getID() const = 0;

        /// @brief Adds a wire to the GameItem
        virtual void addWire(WireItem* wire) = 0;

        /// @brief Toggles the power of the GameItem
        virtual void togglePower(bool state) = 0;
};

#endif // GAMEITEM_H
