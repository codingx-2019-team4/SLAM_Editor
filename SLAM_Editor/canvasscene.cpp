#include "canvasscene.h"
#include "door.h"
#include "sensor.h"

CanvasScene::CanvasScene(int x, int y, int w, int h) : QGraphicsScene(x, y, w, h)
{
    LStart = new QPoint();
    LEnd = new QPoint();
    this->setBackgroundBrush(QBrush(Qt::transparent));
    doors = this->createItemGroup(this->selectedItems());
    sensors = this->createItemGroup(this->selectedItems());

    doors->show();
    sensors->show();
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

    else if(mouseStatus == DOOR){
        Door *door = new Door(event->scenePos().x() - 25, event->scenePos().y() - 25);
        doors->addToGroup(door);
    }

    else if(mouseStatus == SENSOR){
        Sensor *sensor = new Sensor(event->scenePos().x() - 10, event->scenePos().y() - 10);
        sensors->addToGroup(sensor);
    }
}

// Mouse Realease
void CanvasScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    // Painter - draw line
    if(mouseStatus == MS_PAINTER){
        LEnd->setX(event->scenePos().x());
        LEnd->setY(event->scenePos().y());
        QGraphicsLineItem* newLine = new QGraphicsLineItem(QLine(*LStart, *LEnd));
        newLine->setPen(QPen(Qt::black, PainterThickness));
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
        QGraphicsEllipseItem* newEllipse = new QGraphicsEllipseItem((*LEnd).x()-EraserThickness/2, (*LEnd).y()-EraserThickness/2, EraserThickness, EraserThickness);
        newEllipse->setPen(QPen(Qt::transparent));
        newEllipse->setBrush(QBrush(this->backgroundBrush()));
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

void CanvasScene::setDoor(){
    mouseStatus = DOOR;
}

void CanvasScene::setSensor(){
    mouseStatus = SENSOR;
}

void CanvasScene::setEraserThickness(int thickness){
    this->EraserThickness = thickness;
}

void CanvasScene::setPainterThickness(int thickness){
    this->PainterThickness = thickness;
}

void CanvasScene::setBackground(QString fileName){
    QPixmap pixmap;
    pixmap.load(fileName);
    QBrush brush(QGradient::PadSpread);
    brush.setTexture(pixmap);

    this->setBackgroundBrush(brush);
}

int CanvasScene::getMS(){
    return mouseStatus;
}

void CanvasScene::hideIcons(){
    doors->hide();
    sensors->hide();
}
