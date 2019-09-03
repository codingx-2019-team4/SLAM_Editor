#include "sensor.h"

Sensor::Sensor(qreal x, qreal y)
{
    this->setPos(x, y);
    this->setPixmap(QPixmap("../res/sensor.png").scaled(20, 20));

}

Sensor::~Sensor(){
    this->setVisible(false);
}

void Sensor::mousePressEvent(QGraphicsSceneMouseEvent *event){
    delete this;
}
