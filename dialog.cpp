#include "debugtools.h"
#include "lemonade.h"
#include "dialog.h"
#include "ui_dialog.h"
#include <QBitmap>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    QSize DISPLAY_SIZE(DISPLAY_WIDTH, DISPLAY_HEIGTH);
    DebugTools Debugger;

    ui->setupUi(this);
    this->resize(DISPLAY_WIDTH, DISPLAY_HEIGTH+this->ui->buttonBox->height());
    this->ui->label->resize(DISPLAY_SIZE);
    //this->ui->buttonBox->move((DISPLAY_SIZE.width()-this->ui->buttonBox->width())/2,DISPLAY_SIZE.height());
    this->ui->buttonBox->setDisabled(true);
    this->ui->buttonBox->hide();
    this->ui->test1->move((DISPLAY_WIDTH-this->ui->test1->width())/2,DISPLAY_HEIGTH);

    QPixmap pic(DISPLAY_SIZE);
    pic.fill(QColor(216,228,233));
    this->ui->label->setPixmap(pic);

}

Dialog::~Dialog(){
    delete ui;
}

void Dialog::generate_surface(int* xy_s, int length){
    std::cout<<std::endl;
    DebugTools().intMsg(length);

    for (int i=0; i<length-3; i+=2){
        //for(int j:{i,i+1,i+2,i+3}){std::cout<<"c["<<j<<"]"<<xy_s[j]<<std::endl;}
        metasurface.push_back(Line(xy_s[i], xy_s[i+1],xy_s[i+2], xy_s[i+3]));
    }
    metasurface.push_back(Line(xy_s[length-1], xy_s[length-2],xy_s[0], xy_s[1]));
}
/*
DebugTools().intMsg(sizeof(xy_s));
DebugTools().intMsg(sizeof(xy_s[0]));
std::cout<<&xy_s<<std::endl;
std::cout<<&xy_s[1]<<std::endl;
std::cout<<*&xy_s[1]<<std::endl;
DebugTools().intMsg(*(xy_s+1));

int length=end(xy_s)-begin(xy_s);*/

/*
string
    exec_dir;

double
    p_x, p_y,
    v_x, v_y,
    p_m_mantissa, p_q_mantissa,
    d1, l,
    p_V0_x, p_V0_y,
    k, //exponent defined directly in formula (idk why i didn't put THIS var there...)
    d2, time_prev, time_current;
int
    p_m_exponent, p_q_exponent, resulting_exponent;
*/

void Dialog::simulate(){

}

void Dialog::verticalFlatSurfaceMR(){
    int a[]={DISPLAY_WIDTH/2,0,
             DISPLAY_WIDTH,0,
             DISPLAY_WIDTH,DISPLAY_HEIGTH,
             DISPLAY_WIDTH/2,DISPLAY_HEIGTH};
    generate_surface(a, sizeof(a)/sizeof(int));
    for(Line l:metasurface){
        std::cout<<l<<std::endl;
    }
    simulate();
}

//QPixmap pic(QString::fromStdString(exec_dir+"/other/icon.png"));
//Debugger.strMsgInline("Image full path");
//Debugger.strMsg(exec_dir+"/other/icon.png");

void Dialog::on_test1_clicked(){
    verticalFlatSurfaceMR();
}

