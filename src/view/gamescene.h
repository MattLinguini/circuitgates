#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QSize>

class GameScene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit GameScene(QObject* parent = nullptr);

    void setGridSize(int gSize, int cSize = 64);
    QPointF gridToScenePos(QPoint gridPos) const;

    void resizeToFit(QSizeF viewSize);

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override;

private:
    int gridSize;
    int cellSize = 64;
};

#endif // GAMESCENE_H
