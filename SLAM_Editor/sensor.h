#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Sensor : public QObject, public QGraphicsPixmapItem
{
public:
    Sensor(qreal, qreal);
    ~Sensor();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
};

#endif // SENSOR_H
