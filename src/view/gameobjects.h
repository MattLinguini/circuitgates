#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <QtSvg>
#include <QGraphicsSvgItem>
#include <QGraphicsPathItem>

class LogicGateItem : public QGraphicsSvgItem {
    public:
        enum GateType { AND, OR, NOT, XOR };

        LogicGateItem(int x, int y, GateType gateType, QGraphicsSvgItem* parent = nullptr);
        void updateImage(GateType gateType, int size);
        GateType getType() const;

        int x;
        int y;
    private:
        void setType(GateType gateType);
        void setPowered(bool powered);
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

        GateType gateType;
        QColor gateColor;
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
