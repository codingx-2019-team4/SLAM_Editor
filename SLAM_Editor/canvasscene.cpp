#include "canvasscene.h"

using namespace std;
using json = nlohmann::json;

CanvasScene::CanvasScene(int x, int y, int w, int h) : QGraphicsScene(x, y, w, h)
{
    // Variables initialization
    this->LStart = new QPoint(NOTDRAWING, NOTDRAWING);
    this->LEnd = new QPoint();
    this->erasing = new bool(false);
    this->mouseStatus = new qreal(MS_MOUSE);
    this->PenThickness = new qreal(3);
    this->EraserThickness = new qreal(6);
    this->lineBuf = new QGraphicsLineItem();
    this->lineBuf->hide();
    this->lines = new std::vector<QGraphicsLineItem*>();
    this->doors_pos = new std::vector<qreal*>();
    this->sensors_pos = new std::vector<qreal*>();

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
        Door *door = new Door(event->scenePos().x() - 10, event->scenePos().y() - 10);
        doors->addToGroup(door);
        qreal* temp = new qreal[2];
        temp[0] = event->scenePos().x() - 992;
        temp[1] = - event->scenePos().y() + 992;
        doors_pos->push_back(temp);
    }

    else if(*mouseStatus == SENSOR){
        Sensor *sensor = new Sensor(event->scenePos().x() - 10, event->scenePos().y() - 10);
        sensors->addToGroup(sensor);
        qreal* temp = new qreal[2];
        temp[0] = event->scenePos().x() - 992;
        temp[1] = - event->scenePos().y() + 992;
        sensors_pos->push_back(temp);
    }
}

// Mouse Realease
void CanvasScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    // Painter - draw line
    if(*mouseStatus == MS_PEN){
        LEnd->setX(event->scenePos().x());
        LEnd->setY(event->scenePos().y());
        QGraphicsLineItem* newLine = new QGraphicsLineItem(QLine(*LStart, *LEnd));
        lines->push_back(newLine);
        newLine->setPen(QPen(Qt::black, *PenThickness));
        this->addItem(newLine);
        LStart->setX(NOTDRAWING);
        LStart->setY(NOTDRAWING);
        lineBuf->hide();
    }
    // Eraser OFF
    else if(*mouseStatus == MS_ERASER) *erasing = false;
}

// Mouse Moving
void CanvasScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    // Pen hint
    if(*mouseStatus == MS_PEN){
        if(LStart->x() != NOTDRAWING){
            delete lineBuf;
            lineBuf = new QGraphicsLineItem(QLine(*LStart, QPoint(event->scenePos().x(), event->scenePos().y())));
            lineBuf->setPen(QPen(Qt::black, *PenThickness));
            lineBuf->show();
            this->addItem(lineBuf);
        }
    }

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

// Undo
void CanvasScene::undo(){
    if(lines->size() == 0) return;
    QGraphicsLineItem *temp = this->lines->at(lines->size() - 1);
    lines->pop_back();
    delete temp;
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

void CanvasScene::exportJson(QString filename){

    // Transfer yaml to json and add doors and sensors
    YAML::Node config;

    string fileName = filename.toStdString();
    config = YAML::LoadFile(fileName + ".yaml");
    //////////////////////////////////////////////////
    string image = config["image"].as<string>();
    double resolution = config["resolution"].as<double>();

    int negate = config["negate"].as<int>();
    double occupied_thresh = config["occupied_thresh"].as<double>();
    double free_thresh = config["free_thresh"].as<double>();

    vector<double> origin;
    origin = config["origin"].as<vector<double>>();

    cout << "image:" << image << endl;
    cout << "resolution:" << resolution << endl;

    cout<<"origin: [";
    for (std::vector<double>::const_iterator i = origin.begin(); i != origin.end(); ++i){
        cout << *i << ' ';
    }
    cout<<"]"<<endl;

    cout << "negate:" << negate  << endl;
    cout << "occupied_thresh:" << occupied_thresh << endl;
    cout << "free_thresh:" << free_thresh << endl;

    json data2save;

    data2save["image"] = image;
    data2save["resolution"] = resolution;
    data2save["origin"] = origin;
    data2save["negate"] = negate;
    data2save["occupied_thresh"] = occupied_thresh;
    data2save["free_thresh"] = free_thresh;
    if(doors_pos->size() > 0)
        for(int i = 0; i < doors_pos->size(); i++)
            data2save["door"] += {(doors_pos->at(i))[0], (doors_pos->at(i))[1], 0.0};
    if(sensors_pos->size() > 0)
        for(int i = 0; i < sensors_pos->size(); i++)
            data2save["sensor"] += {(sensors_pos->at(i))[0], (sensors_pos->at(i))[1], 0.0};

    string savePath = fileName+".json";
    std::ofstream o(savePath);
    o << std::setw(4) << data2save << std::endl;
}
