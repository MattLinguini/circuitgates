#pragma once

#include <Box2D/Box2D.h>
#include <QPainter>
class Box2DDebugDraw : public b2Draw {
public:
    explicit Box2DDebugDraw(float scale = 30.0f);

    void setPainter(QPainter* painter);

    void DrawPolygon      (const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    void DrawSolidPolygon (const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    void DrawCircle       (const b2Vec2& center, float radius, const b2Color& color) override;
    void DrawSolidCircle  (const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;
    void DrawSegment      (const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
    void DrawTransform    (const b2Transform& xf) override;

private:
    QPainter* m_painter;
    float     m_scale;

    QPointF worldToScene(const b2Vec2& v) const;
    QColor  toQColor    (const b2Color& c) const;
};
