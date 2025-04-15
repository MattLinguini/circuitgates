#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <QGraphicsSvgItem>
#include <QGraphicsPathItem>
#include <QGraphicsRectItem>

class LogicGateItem : public QGraphicsSvgItem {
    public:
        enum GateType { AND, OR, NOT, XOR };

        LogicGateItem(int x, int y, GateType gateType, QGraphicsSvgItem* parent = nullptr);
        void updateImage(GateType gateType);
        GateType getType() const;
        void setPowered(bool state);

        int x;
        int y;
    private:
        void setType(GateType gateType);
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

        GateType gateType;
        QColor gateColor;
};

class WireItem : public QGraphicsPathItem {
    public:
        WireItem();

    private:
};

class InputOutputItem : public QGraphicsRectItem {
    public:
        enum IOType { INPUT, OUTPUT };
        InputOutputItem(int x, int y, IOType type, QGraphicsRectItem* parent = nullptr);
        void setState(bool on);

        int x;
        int y;
    private:
        IOType ioType;
        QGraphicsTextItem* label;
};

#endif // GAMEOBJECTS_H
