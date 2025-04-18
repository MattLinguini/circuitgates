#include "gateslotitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

static constexpr float SCALE = 30.0f;

GateSlotItem::GateSlotItem(float centerX, float centerY, float width, float height, float cellSize, float padding, QGraphicsItem* parent) : QGraphicsRectItem(parent), padding(padding), cellSize(cellSize) {
    setRect(-width/2 * SCALE, -height/2 * SCALE, width * SCALE, height * SCALE);
    setBrush(Qt::gray);

    setPos(centerX * SCALE, -centerY * SCALE);
}

QVariant GateSlotItem::itemChange(GraphicsItemChange change, const QVariant& value) {
    return QGraphicsRectItem::itemChange(change, value);
}

void GateSlotItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsRectItem::mouseReleaseEvent(event);
}
