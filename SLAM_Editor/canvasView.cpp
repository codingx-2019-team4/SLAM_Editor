#include "canvasView.h"

CanvasView::CanvasView(QWidget* parent) : QGraphicsView(parent)
{
    canvasScene = new CanvasScene();
    canvasScene->setSceneRect(
                0, 0, this->width() - 2, this->height() - 2);
    this->setScene(canvasScene);
    LStart = new QPoint();
    LEnd = new QPoint();
}

// Mouse Press
void CanvasView::mousePressEvent(QMouseEvent *event){

    // Painter - start line
    if(mouseStatus == MS_PAINTER){
        LStart->setX(mapToScene(event->pos()).x());
        LStart->setY(mapToScene(event->pos()).y());
    }

    // Eraser ON
    else if(mouseStatus == MS_ERASER) erasing = true;
}

// Mouse Realease
void CanvasView::mouseReleaseEvent(QMouseEvent *event){

    // Painter - draw line
    if(mouseStatus == MS_PAINTER){
        LEnd->setX(mapToScene(event->pos()).x());
        LEnd->setY(mapToScene(event->pos()).y());
        QGraphicsLineItem* newLine = new QGraphicsLineItem(QLine(getLineStart(), getLineEnd()));
        newLine->setPen(QPen(Qt::black, 5));
        canvasScene->addItem(newLine);
    }
    // Eraser OFF
    else if(mouseStatus == MS_ERASER) erasing = false;
}

// Mouse Moving
void CanvasView::mouseMoveEvent(QMouseEvent *event){

    // Eraser
    if(mouseStatus == MS_ERASER && erasing == true){
        LEnd->setX(mapToScene(event->pos()).x());
        LEnd->setY(mapToScene(event->pos()).y());
        QGraphicsEllipseItem* newEllipse = new QGraphicsEllipseItem(getLineEnd().x()-10, getLineEnd().y()-10, 20, 20);
        newEllipse->setPen(QPen(Qt::white));
        newEllipse->setBrush(QBrush(Qt::white, Qt::SolidPattern));
        canvasScene->addItem(newEllipse);
    }
}

// Cursor state - Mouse
void CanvasView::setMouse(){
    mouseStatus = MS_MOUSE;
}

// Cursor state - Eraser
void CanvasView::setEraser(){
    mouseStatus = MS_ERASER;
}

// Cursor state - Painter (Line)
void CanvasView::setPainter(){
    mouseStatus = MS_PAINTER;
}

// Get the start point of drawing a line
QPoint CanvasView::getLineStart(){
    return *LStart;
}

// Get the end point of drawing a line
QPoint CanvasView::getLineEnd(){
    return *LEnd;
}
