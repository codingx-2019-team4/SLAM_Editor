#include "canvasscene.h"

CanvasScene::CanvasScene(int x, int y, int w, int h) : QGraphicsScene(x, y, w, h)
{
    LStart = new QPoint();
    LEnd = new QPoint();
}


// Mouse Press
void CanvasScene::mousePressEvent(QGraphicsSceneMouseEvent *event){

    // Painter - start line
    if(mouseStatus == MS_PAINTER){
        LStart->setX(event->scenePos().x());
        LStart->setY(event->scenePos().y());
    }

    // Eraser ON
    else if(mouseStatus == MS_ERASER) erasing = true;
}

// Mouse Realease
void CanvasScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    // Painter - draw line
    if(mouseStatus == MS_PAINTER){
        LEnd->setX(event->scenePos().x());
        LEnd->setY(event->scenePos().y());
        QGraphicsLineItem* newLine = new QGraphicsLineItem(QLine(*LStart, *LEnd));
        newLine->setPen(QPen(Qt::black, 5));
        this->addItem(newLine);
    }
    // Eraser OFF
    else if(mouseStatus == MS_ERASER) erasing = false;
}

// Mouse Moving
void CanvasScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    // Eraser
    if(mouseStatus == MS_ERASER && erasing == true){
        LEnd->setX(event->scenePos().x());
        LEnd->setY(event->scenePos().y());
        QGraphicsEllipseItem* newEllipse = new QGraphicsEllipseItem((*LEnd).x()-10, (*LEnd).y()-10, 20, 20);
        newEllipse->setPen(QPen(Qt::white));
        newEllipse->setBrush(QBrush(Qt::white, Qt::SolidPattern));
        this->addItem(newEllipse);
    }
}

void CanvasScene::setEraser(){
    mouseStatus = MS_ERASER;
}

void CanvasScene::setMouse(){
    mouseStatus = MS_MOUSE;
}

void CanvasScene::setPainter(){
    mouseStatus = MS_PAINTER;
}

