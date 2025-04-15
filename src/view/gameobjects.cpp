#include "gameobjects.h"

LogicGateItem::LogicGateItem(int x, int y, GateType gateType, QGraphicsSvgItem* parent) : QGraphicsSvgItem(parent), gateType(gateType), x(x), y(y) {
    setType(gateType);
}

LogicGateItem::GateType LogicGateItem::getType() const {
    return gateType;
}

void LogicGateItem::setType(GateType gateType) {
    updateImage(gateType, 64);
}

void LogicGateItem::updateImage(GateType gateType, int size) {
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
