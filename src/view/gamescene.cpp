#include "gamescene.h"
#include <QPainter>
#include <QPen>
#include <QMap>
#include "gameobjects.h"

GameScene::GameScene(QObject* parent) : QGraphicsScene(parent) {
    setBackgroundBrush(Qt::white);
}


void GameScene::addGateItem(LogicGateItem* gate) {
    if (!gate)
        return;

    // Convert grid coordinates to scene position (top-left of the cell)
    QPointF scenePos = gridToScenePos(QPoint(gate->x, gate->y));
    gate->setPos(scenePos);

    // Add it to the scene
    addItem(gate);
}

void GameScene::setGridSize(int gSize, int cSize) {
    gridSize = gSize;
    cellSize = cSize;
    setSceneRect(0, 0, gridSize * cellSize, gridSize * cellSize);
    update();
}

QPointF GameScene::gridToScenePos(QPoint gridPos) const {
    return QPointF(gridPos.x() * cellSize, gridPos.y() * cellSize);
}

void GameScene::drawBackground(QPainter* painter, const QRectF& rect) {
    QPen pen(Qt::lightGray);
    pen.setWidth(1);
    painter->setPen(pen);

    for (int x = 0; x <= gridSize; ++x) {
        painter->drawLine(x * cellSize, 0, x * cellSize, gridSize * cellSize);
    }

    for (int y = 0; y <= gridSize; ++y) {
        painter->drawLine(0, y * cellSize, gridSize * cellSize, y * cellSize);
    }
}

void GameScene::resizeToFit(QSizeF viewSize) {
    if (gridSize == 0)
        return;

    const int padding = 10;
    int availableWidth = viewSize.width() - padding;
    int availableHeight = viewSize.height() - padding;
    cellSize = std::min(availableWidth / gridSize, availableHeight / gridSize);
    setSceneRect(0, 0, gridSize * cellSize, gridSize * cellSize);

    for (auto* item : items()) {
        if (LogicGateItem* gate = qgraphicsitem_cast<LogicGateItem*>(item)) {
            gate->updateImage(gate->getType(), cellSize);

            QPointF topLeftPos = gridToScenePos(QPoint(gate->x, gate->y));
            QPointF centerPos = topLeftPos + QPointF(cellSize / 2.0, cellSize / 2.0);

            gate->setTransformOriginPoint(gate->boundingRect().center());

            QRectF bounds = gate->boundingRect();
            qreal scaleFactor = qMin(cellSize / bounds.width(), cellSize / bounds.height());
            gate->setScale(scaleFactor);
            gate->setRotation(90);

            QPointF gateSceneCenter = gate->mapToScene(gate->transformOriginPoint());
            QPointF offset = centerPos - gateSceneCenter;
            gate->moveBy(offset.x(), offset.y());
        }
    }

    update();
}
