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
    this->canvas = new QGraphicsScene();
    this->canvas->setSceneRect(-DISPLAY_WIDTH/2,-DISPLAY_WIDTH/2,DISPLAY_WIDTH,DISPLAY_HEIGTH);
    this->canvas->setBackgroundBrush(QBrush(QColor("#b9ceff")));

    this->ui->setupUi(this);
    this->ui->label->setVisible(false);
    this->resize(DISPLAY_WIDTH, DISPLAY_HEIGTH+this->ui->buttonBox->height());
    this->ui->display->move(0,0);
    this->ui->display->resize(DISPLAY_SIZE);
    this->ui->display->setScene(canvas);
    this->ui->display->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->display->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->buttonBox->setDisabled(true);
    this->ui->buttonBox->hide();
    this->ui->test1->move((DISPLAY_WIDTH-this->ui->test1->width())/2,DISPLAY_HEIGTH);

    //QPixmap pic(DISPLAY_SIZE);
    //pic.fill(QColor(216,228,233));
    //this->ui->label->setPixmap(pic);

}

Dialog::~Dialog(){
    delete ui;
}

void Dialog::generate_surface(std::vector<int> a[], int amount_of_polygons=1){
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

void Dialog::verticalFlatSurfaceMR(){

    /*std::vector<int> a[]={
        {
            DISPLAY_WIDTH/2,    0,
            DISPLAY_WIDTH,      0,
            DISPLAY_WIDTH,      DISPLAY_HEIGTH,
            DISPLAY_WIDTH/2,    DISPLAY_HEIGTH
        }
    };*/
    std::vector<int> a[]={
        {
            0,0,
            250,0,
            250,250,
            0,250
        }
    };
    generate_surface(a);


    this->painter = new Painter(canvas, metasurface);

    std::cout<<"Generated polygons:"<<std::endl;
    for(Polygon poly:metasurface){
        std::cout<<poly<<std::endl;
        this->painter->drawPoly(poly);
    }
    //this->canvas->addPolygon(metasurface.at(0).to_qpoly());

    simulate();
}

//QPixmap pic(QString::fromStdString(exec_dir+"/other/icon.png"));
//Debugger.strMsgInline("Image full path");
//Debugger.strMsg(exec_dir+"/other/icon.png");

void Dialog::on_test1_clicked(){
    verticalFlatSurfaceMR();
}

