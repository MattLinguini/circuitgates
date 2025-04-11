#include "gamescene.h"
#include <QPainter>
#include <QPen>

GameScene::GameScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::white);
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
    update();
}
