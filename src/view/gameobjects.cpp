#include "gameobjects.h"
#include <QtSvg>

LogicGateItem::LogicGateItem(int x, int y, GateType gateType, QGraphicsSvgItem* parent) : QGraphicsSvgItem(parent), x(x), y(y), gateType(gateType) {
    setType(gateType);
}

LogicGateItem::GateType LogicGateItem::getType() const {
    return gateType;
}

void LogicGateItem::setType(GateType gateType) {
    updateImage(gateType);
}

void LogicGateItem::updateImage(GateType gateType) {
    QString svgPath;
    switch (gateType) {
        case AND: svgPath = ":/gates/resources/and_gate.svg"; break;
        case OR: svgPath = ":/gates/resources/or_gate.svg"; break;
        case NOT: svgPath = ":/gates/resources/not_gate.svg"; break;
        case XOR: svgPath = ":/gates/resources/xor_gate.svg"; break;
    }
        setSharedRenderer(new QSvgRenderer(svgPath));
}

void LogicGateItem::setPowered(bool state) {
    if (state) {
        gateColor = Qt::green;
    }
    else {
        gateColor = Qt::black;
    }
}

void LogicGateItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QGraphicsSvgItem::paint(painter, option, widget);
    if (gateColor.isValid()) {
        painter->setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter->fillRect(boundingRect(), gateColor);
    }
}

InputOutputItem::InputOutputItem(int x, int y, IOType ioType, QGraphicsRectItem* parent) : QGraphicsRectItem(parent), x(x), y(y), ioType(ioType) {
    setRect(0, 0, 40, 40);  // or cellSize-based
    setBrush(Qt::white);

    label = new QGraphicsTextItem(this);
    label->setDefaultTextColor(Qt::black);
    label->setFont(QFont("Arial", 16, QFont::Bold));
    label->setPos(10, 5);  // approximate centering

    if (ioType == OUTPUT) {
        setState(true);
    } else {
        setState(false);
    }
}

void InputOutputItem::setState(bool state) {
    if (state) {
        label->setPlainText("1");
        setPen(QPen(Qt::green, 4));
    }
    else {
        label->setPlainText("0");
        setPen(QPen(Qt::black, 4));
    }
}
