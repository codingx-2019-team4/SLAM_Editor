#include "door.h"

Door::Door(qreal x, qreal y)
{
    this->setPos(x, y);
    this->setPixmap(QPixmap("../resources/door.png").scaled(20, 20));
}

Door::~Door(){
    this->setVisible(false);
}

void Door::mousePressEvent(QGraphicsSceneMouseEvent *event){
    delete this;
}
