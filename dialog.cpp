#include "debugtools.h"
#include "dialog.h"
#include "lemonade.h"
#include "painter.h"
#include "ui_dialog.h"
#include <QBitmap>

#include <chrono>
#include <ctime>
#include <thread>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    QSize DISPLAY_SIZE(DISPLAY_WIDTH, DISPLAY_HEIGTH);
    QSize BUTTON_SIZE(BUTTON_WIDTH, BUTTON_HEIGTH);
    QSize LABEL_SIZE(LABEL_WIDTH, LABEL_HEIGTH);

    this->canvas = new QGraphicsScene(-DISPLAY_WIDTH/2,-DISPLAY_HEIGTH/2,DISPLAY_WIDTH,DISPLAY_HEIGTH);
    this->canvas->setBackgroundBrush(QBrush(DISPLAY_BACKGROUND_COLOR));

    this->ui->setupUi(this);

    this->resize(DISPLAY_WIDTH, DISPLAY_HEIGTH+BUTTON_HEIGTH+3*LABEL_HEIGTH);

    this->ui->display->move(0,0);
    this->ui->display->resize(DISPLAY_SIZE);
    this->ui->display->setScene(canvas);
    this->ui->display->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->display->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->ui->buttonBox->setDisabled(true);
    this->ui->buttonBox->hide();


    this->ui->test0->resize(BUTTON_SIZE);
    this->ui->test1->resize(BUTTON_SIZE);
    this->ui->test2->resize(BUTTON_SIZE);

    this->ui->test0->move(DISPLAY_WIDTH/4-BUTTON_WIDTH/2, DISPLAY_HEIGTH);
    this->ui->test1->move(DISPLAY_WIDTH/2-BUTTON_WIDTH/2, DISPLAY_HEIGTH);
    this->ui->test2->move(DISPLAY_WIDTH*3/4-BUTTON_WIDTH/2, DISPLAY_HEIGTH);

    this->ui->test0->setText("Diagonal surface\n(UpRight to DownCenter)");
    this->ui->test1->setText("Vertical surface\n(Right)");
    this->ui->test2->setText("Run simulation");

    this->ui->label0->resize(LABEL0_WIDTH, LABEL_HEIGTH);
    this->ui->label1->resize(LABEL_SIZE);
    this->ui->label2->resize(LABEL_SIZE);

    this->ui->label0->move(0, DISPLAY_HEIGTH+BUTTON_HEIGTH);
    this->ui->label1->move(0, DISPLAY_HEIGTH+BUTTON_HEIGTH+LABEL_HEIGTH);
    this->ui->label2->move(0, DISPLAY_HEIGTH+BUTTON_HEIGTH+2*LABEL_HEIGTH);

    this->ui->label0->setText("Movement vector data:");
    this->ui->label1->setText("X");
    this->ui->label2->setText("Y");


    this->ui->spinBox0->move(LABEL_WIDTH, DISPLAY_HEIGTH+BUTTON_HEIGTH+LABEL_HEIGTH);
    this->ui->spinBox1->move(LABEL_WIDTH, DISPLAY_HEIGTH+BUTTON_HEIGTH+2*LABEL_HEIGTH);

    this->ui->spinBox0->setMinimum(-DISPLAY_WIDTH/2);
    this->ui->spinBox1->setMinimum(-DISPLAY_WIDTH/2);
    this->ui->spinBox0->setMaximum(DISPLAY_WIDTH/2);
    this->ui->spinBox1->setMaximum(DISPLAY_WIDTH/2);

    this->ui->spinBox0->setValue(v_x);
    this->ui->spinBox1->setValue(v_y);


    this->on_test0_clicked();

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

Polygon Dialog::generate_surface(std::vector<int> a){
    Polygon poly;
    for (int i=0; i<a.size()-3; i+=2)
        poly.polygon.push_back(Line(a.at(i), a.at(i+1), a.at(i+2), a.at(i+3)));
    poly.polygon.push_back(Line(a.at(a.size()-2), a.at(a.size()-1), a.at(0), a.at(1)));
    return poly;
}

/*
DebugTools().intMsg(sizeof(xy_s));
DebugTools().intMsg(sizeof(xy_s[0]));
std::cout<<&xy_s<<std::endl;
std::cout<<&xy_s[1]<<std::endl;
std::cout<<*&xy_s[1]<<std::endl;
DebugTools().intMsg(*(xy_s+1));

int length=end(xy_s)-begin(xy_s);*/

void Dialog::simulate(int frame_duration){
    std::time_t time = std::time(0);
    std::cout<<std::ctime(&time)<<std::endl;
    while(this->isRunning){
        this_thread::sleep_for(std::chrono::milliseconds(frame_duration));
        Physics_engine.change_particle_position(10,10);
        updateFrame();
    }
}

void Dialog::updateFrame(){
    this->canvas->clear();
    this->painter->drawSurface();
    this->painter->drawLine();
    this->painter->drawElectron();
}

void Dialog::resetData(){
    this->canvas->clear();
    Physics_engine.metasurface_genuine=Polygon();
    this->painter = new Painter(canvas);
}

void Dialog::on_test0_clicked(){
    resetData();
    Physics_engine.metasurface_genuine=generate_surface(std::vector<int>{
        DISPLAY_WIDTH/3,    -DISPLAY_HEIGTH/2,
        DISPLAY_WIDTH/2,    -DISPLAY_HEIGTH/2,
        DISPLAY_WIDTH/2,    DISPLAY_HEIGTH/2,
        DISPLAY_WIDTH/5,    DISPLAY_HEIGTH/2,
    });
    this->painter->drawSurface();
    this->painter->drawElectron();
}
void Dialog::on_test1_clicked(){
    resetData();
    Physics_engine.metasurface_genuine=generate_surface(std::vector<int>{
            DISPLAY_WIDTH/5,    -DISPLAY_HEIGTH/2,
            DISPLAY_WIDTH/2,    -DISPLAY_HEIGTH/2,
            DISPLAY_WIDTH/2,    DISPLAY_HEIGTH/2,
            DISPLAY_WIDTH/5,    DISPLAY_HEIGTH/2,
    });
    this->painter->drawSurface();
    this->painter->drawElectron();
}

void Dialog::on_test2_clicked(){
    this->ui->test0->setEnabled(false);
    this->ui->test1->setEnabled(false);
    this->ui->test2->setEnabled(false);
    simulate(300);
    this->ui->test0->setEnabled(true);
    this->ui->test1->setEnabled(true);
    this->ui->test2->setEnabled(true);
}

