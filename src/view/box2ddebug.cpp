// box2ddebug.cpp
#include "box2ddebug.h"

Box2DDebugDraw::Box2DDebugDraw(float scale)
    : m_painter(nullptr), m_scale(scale)
{}

void Box2DDebugDraw::setPainter(QPainter* painter) {
    m_painter = painter;
}

QPointF Box2DDebugDraw::worldToScene(const b2Vec2& v) const {
    return QPointF(v.x * m_scale, -v.y * m_scale);
}

QColor Box2DDebugDraw::toQColor(const b2Color& c) const {
    return QColor(int(c.r * 255), int(c.g * 255), int(c.b * 255));
}

void Box2DDebugDraw::DrawPolygon(const b2Vec2* verts, int32 cnt, const b2Color& c) {
    if (!m_painter) return;
    QPolygonF poly;
    poly.reserve(cnt);
    for (int32 i = 0; i < cnt; ++i)
        poly << worldToScene(verts[i]);
    m_painter->setPen(QPen(toQColor(c)));
    m_painter->setBrush(Qt::NoBrush);
    m_painter->drawPolygon(poly);
}

void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2* verts, int32 cnt, const b2Color& c) {
    if (!m_painter) return;
    QPolygonF poly;
    poly.reserve(cnt);
    for (int32 i = 0; i < cnt; ++i)
        poly << worldToScene(verts[i]);
    auto qc = toQColor(c);
    m_painter->setPen(QPen(qc));
    qc.setAlpha(60);
    m_painter->setBrush(qc);
    m_painter->drawPolygon(poly);
}

void Box2DDebugDraw::DrawCircle(const b2Vec2& center, float r, const b2Color& c) {
    if (!m_painter) return;
    QPointF cen = worldToScene(center);
    qreal  rr  = r * m_scale;
    m_painter->setPen(QPen(toQColor(c)));
    m_painter->setBrush(Qt::NoBrush);
    m_painter->drawEllipse(cen, rr, rr);
}

void Box2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float r, const b2Vec2& axis, const b2Color& c) {
    if (!m_painter) return;
    QPointF cen = worldToScene(center);
    qreal  rr  = r * m_scale;
    auto qc = toQColor(c);
    m_painter->setPen(QPen(qc));
    qc.setAlpha(60);
    m_painter->setBrush(qc);
    m_painter->drawEllipse(cen, rr, rr);

    // draw radius/axis line
    b2Vec2 end = center + r * axis;
    m_painter->setBrush(Qt::NoBrush);
    m_painter->drawLine(cen, worldToScene(end));
}

void Box2DDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& c) {
    if (!m_painter) return;
    m_painter->setPen(QPen(toQColor(c)));
    m_painter->setBrush(Qt::NoBrush);
    m_painter->drawLine(worldToScene(p1), worldToScene(p2));
}

void Box2DDebugDraw::DrawTransform(const b2Transform& xf) {
    if (!m_painter) return;
    const float k_axisScale = 0.4f;
    b2Vec2 p  = xf.p;
    // X axis (red)
    b2Vec2 pX = p + k_axisScale * xf.q.GetXAxis();
    m_painter->setPen(QPen(Qt::red));
    m_painter->drawLine(worldToScene(p), worldToScene(pX));
    // Y axis (green)
    b2Vec2 pY = p + k_axisScale * xf.q.GetYAxis();
    m_painter->setPen(QPen(Qt::green));
    m_painter->drawLine(worldToScene(p), worldToScene(pY));
}
