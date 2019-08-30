#ifndef CANVASSCENE_H
#define CANVASSCENE_H

// Mouse status
#define MS_MOUSE 301
#define MS_PAINTER 302
#define MS_ERASER 303
#define DOOR 304
#define SENSOR 305


#include <QWidget>
#include <QPoint>
#include <QPointF>
#include <QLine>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemGroup>
#include <QPainter>
#include <QPen>
#include <QWheelEvent>
#include <QDebug>
#include <QGradient>



class CanvasScene : public QGraphicsScene
{
public:
    CanvasScene(int x, int y, int w, int h);
    void setEraser();
    void setMouse();
    void setPainter();
    void setDoor();
    void setSensor();
    void setEraserThickness(int);
    void setPainterThickness(int);
    void setBackground(QString);
    int getMS();
    void hideIcons();

private:

    // The coordinates to draw lines
    QPoint* LStart;
    QPoint* LEnd;
    bool erasing = false;
    int mouseStatus = MS_MOUSE;
    int EraserThickness = 10;
    int PainterThickness = 5;
    QGraphicsItem* backgroundItem;

    QGraphicsItemGroup* doors;
    QGraphicsItemGroup* sensors;





public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);
};

#endif // CANVASSCENE_H
