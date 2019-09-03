#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QPointF>

class CanvasScene : public QGraphicsScene{
    Q_OBJECT
public:
    explicit CanvasScene(QObject *parent = 0);

signals:

public slots:

};

#endif // CANVAS_H
