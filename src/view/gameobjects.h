#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPathItem>

class LogicGateItem : public QGraphicsPixmapItem {
    public:
        enum GateType { AND, OR, NOT, XOR };

        LogicGateItem(int x, int y, GateType gateType, QGraphicsItem* parent = nullptr);
        void updateImage(GateType gateType, int size);
        GateType getType() const;

        int x;
        int y;
    private:
        void setType(GateType gateType);
        void setPowered(bool powered);

        GateType gateType;
};

class WireItem : public QGraphicsPathItem {
    public:
        WireItem();

    private:
};

class InputOutputItem {
    public:
        InputOutputItem();

    private:
        int x;
        int y;
};

#endif // GAMEOBJECTS_H
