#ifndef CANVASSCENE_H
#define CANVASSCENE_H

// Mouse status
#define MS_MOUSE 301
#define MS_PAINTER 302
#define MS_ERASER 303

#include <QWidget>
#include <QPoint>
#include <QPointF>
#include <QLine>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPen>
#include <QWheelEvent>



class CanvasScene : public QGraphicsScene
{
public:
    CanvasScene(int x, int y, int w, int h);
    void setEraser();
    void setMouse();
    void setPainter();

private:

    // The coordinates to draw lines
    QPoint* LStart;
    QPoint* LEnd;
    bool erasing = false;
    int mouseStatus = MS_MOUSE;





public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);
};

#endif // CANVASSCENE_H
