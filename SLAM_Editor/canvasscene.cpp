#include "canvasscene.h"
#include "door.h"
#include "sensor.h"

CanvasScene::CanvasScene(int x, int y, int w, int h) : QGraphicsScene(x, y, w, h)
{
    // Variables initialization
    this->LStart = new QPoint();
    this->LEnd = new QPoint();
    this->erasing = new bool(false);
    this->mouseStatus = new qreal(MS_MOUSE);
    this->PenThickness = new qreal(5);
    this->EraserThickness = new qreal(10);

    this->setBackgroundBrush(QBrush(Qt::transparent));

    // Create item groups
    doors = this->createItemGroup(this->selectedItems());
    sensors = this->createItemGroup(this->selectedItems());
}


// Mouse Press
void CanvasScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // Painter - start line
    if(*mouseStatus == MS_PEN){
        LStart->setX(event->scenePos().x());
        LStart->setY(event->scenePos().y());
    }

    // Eraser ON
    else if(*mouseStatus == MS_ERASER) *erasing = true;

    else if(*mouseStatus == DOOR){
        Door *door = new Door(event->scenePos().x() - 25, event->scenePos().y() - 25);
        doors->addToGroup(door);
    }

    else if(*mouseStatus == SENSOR){
        Sensor *sensor = new Sensor(event->scenePos().x() - 10, event->scenePos().y() - 10);
        sensors->addToGroup(sensor);
    }
}

// Mouse Realease
void CanvasScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    // Painter - draw line
    if(*mouseStatus == MS_PEN){
        LEnd->setX(event->scenePos().x());
        LEnd->setY(event->scenePos().y());
        QGraphicsLineItem* newLine = new QGraphicsLineItem(QLine(*LStart, *LEnd));
        newLine->setPen(QPen(Qt::black, *PenThickness));
        this->addItem(newLine);
    }
    // Eraser OFF
    else if(*mouseStatus == MS_ERASER) *erasing = false;
}

// Mouse Moving
void CanvasScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    // Eraser
    if(*mouseStatus == MS_ERASER && *erasing == true){
        LEnd->setX(event->scenePos().x());
        LEnd->setY(event->scenePos().y());
        QGraphicsEllipseItem* newEllipse = new QGraphicsEllipseItem((*LEnd).x()-*EraserThickness/2, (*LEnd).y()-*EraserThickness/2, *EraserThickness, *EraserThickness);
        newEllipse->setPen(QPen(Qt::transparent));
        newEllipse->setBrush(QBrush(this->backgroundBrush()));
        this->addItem(newEllipse);
    }
}


// *** Mouse status ***

// To MOUSE
void CanvasScene::setMouse(){
    *mouseStatus = MS_MOUSE;
}

// To PEN
void CanvasScene::setPen(){
    *mouseStatus = MS_PEN;
}

// To ERASER
void CanvasScene::setEraser(){
    *mouseStatus = MS_ERASER;
}

// To DOOR
void CanvasScene::setDoor(){
    *mouseStatus = DOOR;
}

// To SENSOR
void CanvasScene::setSensor(){
    *mouseStatus = SENSOR;
}


// *** Painters' thickness ***

// Pen
void CanvasScene::setPenThickness(qreal thickness){
    *PenThickness = thickness;
}

// Eraser
void CanvasScene::setEraserThickness(qreal thickness){
    *EraserThickness = thickness;
}


// *** Scene setting ***

// Render input image to background
void CanvasScene::setBackground(QString fileName){
    QPixmap pixmap;
    pixmap.load(fileName);
    QBrush brush(QGradient::PadSpread);
    brush.setTexture(pixmap);

    this->setBackgroundBrush(brush);
}

// Hide the icons
void CanvasScene::hideIcons(){
    doors->hide();
    sensors->hide();
}
