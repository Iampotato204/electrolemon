#include "debugtools.h"
#include "dialog.h"
#include "lemonade.h"
#include "painter.h"
#include "ui_dialog.h"
#include <QBitmap>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    QSize DISPLAY_SIZE(DISPLAY_WIDTH, DISPLAY_HEIGTH);
    QSize BUTTON_SIZE(BUTTON_WIDTH, BUTTON_HEIGTH);

    this->canvas = new QGraphicsScene(-DISPLAY_WIDTH/2,-DISPLAY_WIDTH/2,DISPLAY_WIDTH,DISPLAY_HEIGTH);
    //this->canvas->setSceneRect(-DISPLAY_WIDTH/2,-DISPLAY_WIDTH/2,DISPLAY_WIDTH,DISPLAY_HEIGTH);
    this->canvas->setBackgroundBrush(QBrush(DISPLAY_BACKGROUND_COLOR));

    this->ui->setupUi(this);
    this->ui->label->setVisible(false);
    this->resize(DISPLAY_WIDTH, DISPLAY_HEIGTH+BUTTON_HEIGTH);
    this->ui->display->move(0,0);
    this->ui->display->resize(DISPLAY_SIZE);
    this->ui->display->setScene(canvas);
    this->ui->display->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->display->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->buttonBox->setDisabled(true);
    this->ui->buttonBox->hide();
    this->ui->test0->resize(BUTTON_SIZE);
    this->ui->test1->resize(BUTTON_SIZE);
    this->ui->test0->move(DISPLAY_WIDTH/3-BUTTON_WIDTH/2, DISPLAY_HEIGTH);
    this->ui->test1->move(DISPLAY_WIDTH*2/3-BUTTON_WIDTH/2, DISPLAY_HEIGTH);

    /*QPixmap pic(DISPLAY_SIZE);
    pic.fill(QColor(216,228,233));
    this->ui->label->setPixmap(pic);

    QPixmap pic(QString::fromStdString(exec_dir+"/other/icon.png"));
    Debugger.strMsgInline("Image full path");
    Debugger.strMsg(exec_dir+"/other/icon.png");*/

}

Dialog::~Dialog(){
    delete ui;
}

void Dialog::generate_surface(std::vector<int> a[], int amount_of_polygons){
    std::cout<<"Starting generating surface"<<std::endl<<
               "Amount of polygons: "<<amount_of_polygons<<std::endl;

    for (int c=0; c<amount_of_polygons; c++){
        std::cout<<std::endl<<"Creating empty temp poly: "<<std::endl;
        Polygon current_polygon;
        std::cout<<"Yeah, alright, the error is fake"<<std::endl<<std::endl;

        for (int i=0; i<a[c].size()-3; i+=2){
            current_polygon.polygon.push_back(Line(a[c].at(i), a[c].at(i+1), a[c].at(i+2), a[c].at(i+3)));
        }
        //current_polygon.polygon.push_back(Line(a[c].at(a[c].size()-1), a[c].at(a[c].size()-2), a[c].at(0), a[c].at(1)));
        current_polygon.polygon.push_back(Line(a[c].at(a[c].size()-2), a[c].at(a[c].size()-1), a[c].at(0), a[c].at(1)));

        metasurface.push_back(current_polygon);
    }
}

/*
DebugTools().intMsg(sizeof(xy_s));
DebugTools().intMsg(sizeof(xy_s[0]));
std::cout<<&xy_s<<std::endl;
std::cout<<&xy_s[1]<<std::endl;
std::cout<<*&xy_s[1]<<std::endl;
DebugTools().intMsg(*(xy_s+1));

int length=end(xy_s)-begin(xy_s);*/

void Dialog::simulate(){

}

void Dialog::simple_singlePolygonSurface_handler(std::vector<int> a[], int size=1){
    generate_surface(a,size);

    std::cout<<"Generated polygons:"<<std::endl;
    for(Polygon poly:metasurface){
        std::cout<<poly<<std::endl;
        this->painter->drawPoly(poly);
    }

    simulate();
}

void Dialog::resetData(){
    this->canvas->clear();
    this->metasurface.clear();
}

void Dialog::on_test0_clicked(){
    resetData();
    this->painter = new Painter(canvas);

    std::vector<int> a[]={
        {
            -250,100,
            250,100,
            250,250,
            -250,250
        },
        {
            -250,-100,
            250,-100,
            250,-250,
            -250,-250
        }
    };
    simple_singlePolygonSurface_handler(a,2);

    this->painter = new Painter(canvas, QBrush(QColor("#fbfb3f")));
    this->painter->drawCircle(Point(p_x,p_y), 5);

}
void Dialog::on_test1_clicked(){
    resetData();
    this->painter = new Painter(canvas);
    /*std::vector<int> a[]={
        {
            0,                  -DISPLAY_HEIGTH/2,
            DISPLAY_WIDTH/2,    -DISPLAY_HEIGTH/2,
            DISPLAY_WIDTH/2,    DISPLAY_HEIGTH/2,
            0,                  DISPLAY_HEIGTH/2,
        }
    };
    std::vector<int> a[]={
        {
            0,0,
            250,0,
            250,250,
            0,250
        }
    };*/

    std::vector<int> a[]={
        {
            100,-250,
            250,-250,
            250,250,
            100,250
        }
    };
    simple_singlePolygonSurface_handler(a);
}


