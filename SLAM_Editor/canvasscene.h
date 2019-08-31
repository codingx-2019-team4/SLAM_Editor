#ifndef CANVASSCENE_H
#define CANVASSCENE_H

// Mouse status
#define MS_MOUSE 301
#define MS_PEN 302
#define MS_ERASER 303
#define DOOR 304
#define SENSOR 305
#define NOTDRAWING -100


#include <QWidget>
#include <QPoint>
#include <QPointF>
#include <QLine>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QWheelEvent>

class CanvasScene : public QGraphicsScene
{
public:

    // Constructor (info of input image)
    CanvasScene(int x, int y, int w, int h);

    // Mouse status
    void setMouse();
    void setPen();
    void setEraser();
    void setDoor();
    void setSensor();

    // Set painters' thickness
    void setEraserThickness(qreal);
    void setPenThickness(qreal);

    // Scene setting
    void setBackground(QString);
    void hideIcons();

private:

    // The coordinates to draw lines
    QPoint* LStart;
    QPoint* LEnd;

    // Buffer Image
    QGraphicsLineItem* lineBuf;

    bool *erasing;
    qreal *mouseStatus;

    // Painters' thickness
    qreal *PenThickness;
    qreal *EraserThickness;

    // Groups of doors & sensors
    QGraphicsItemGroup* doors;
    QGraphicsItemGroup* sensors;

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);
};

#endif // CANVASSCENE_H
