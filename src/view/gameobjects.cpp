#include "gameobjects.h"

LogicGateItem::LogicGateItem(int x, int y, GateType gateType, QGraphicsItem* parent) : QGraphicsPixmapItem(parent), gateType(gateType), x(x), y(y) {
    setType(gateType);
}

LogicGateItem::GateType LogicGateItem::getType() const {
    return gateType;
}

void LogicGateItem::setType(GateType gateType) {
    updateImage(gateType, 64);
}

void LogicGateItem::updateImage(GateType gateType, int size) {
    QString imagePath;

    switch (gateType) {
        case AND: imagePath = ":/gates/resources/and_gate.png"; break;
        case OR: imagePath = ":/gates/resources/or_gate.png"; break;
        case NOT: imagePath = ":/gates/resources/not_gate.png"; break;
        case XOR: imagePath = ":/gates/resources/xor_gate.png"; break;
    }

    QPixmap raw(imagePath);

    QTransform rotate;
    rotate.rotate(90);

    QPixmap rotated = raw.transformed(rotate, Qt::SmoothTransformation);
    setPixmap(rotated);
    QPixmap scaled = rotated.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaled);
}
