#include "door.h"

Door::Door(qreal x, qreal y)
{
    this->setPos(x, y);
    this->setPixmap(QPixmap("door.png").scaled(50, 50));
}

Door::~Door(){
    this->setVisible(false);
}

void Door::mousePressEvent(QGraphicsSceneMouseEvent *event){
    delete this;
}
