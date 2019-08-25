#ifndef CANVASVIEW_H
#define CANVASVIEW_H

// Mouse status
#define MS_MOUSE 301
#define MS_PAINTER 302
#define MS_ERASER 303

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QPointF>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <canvasScene.h>
#include <QGraphicsLineItem>



class CanvasView : public QGraphicsView
{

public:
    explicit CanvasView(QWidget* parent = 0);
    void setMouse();
    void setEraser();
    void setPainter();
    QPoint getLineStart();
    QPoint getLineEnd();

private:
    CanvasScene* canvasScene;
    QPainter* painter;

    int mouseStatus = MS_MOUSE; // The status of the cursor

    // The coordinates to draw lines
    QPoint* LStart;
    QPoint* LEnd;
    bool erasing = false;



public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *);

};

#endif // CANVASVIEW_H
