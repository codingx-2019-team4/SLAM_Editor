#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Door : public QObject, public QGraphicsPixmapItem
{
public:
    Door(qreal, qreal);
    ~Door();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
};

#endif // DOOR_H
