#ifndef GAMEITEM_H
#define GAMEITEM_H

#include "Box2D/Dynamics/b2Body.h"
#include <QGraphicsRectItem>

class GameItem : public virtual QGraphicsRectItem  {
    public:
        GameItem();

        virtual b2Body* getBody() const = 0;

    private:
        b2Body* body;
};

#endif // GAMEITEM_H
