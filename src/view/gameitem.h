#ifndef GAMEITEM_H
#define GAMEITEM_H

#include "Box2D/Dynamics/b2Body.h"
#include <QGraphicsRectItem>

class GameItem : public virtual QGraphicsRectItem  {
    public:
        virtual b2Body* getBody() const = 0;

        virtual int getID() const = 0;

};

#endif // GAMEITEM_H
