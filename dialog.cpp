#include "debugtools.h"
#include "dialog.h"
#include "lemonade.h"
#include "painter.h"
#include "ui_dialog.h"
#include <QBitmap>
#include <QThread>

#include <chrono>
#include <csignal>
#include <ctime>
#include <thread>

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <future>
#include <math.h>


#include <QGraphicsItem>
#include <QPointF>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimeLine>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemAnimation>

#define PI Physics_engine::PI
#define drawLineInGroup(...) this->movementCurves->addToGroup(this->painter->drawLine(__VA_ARGS__))

class Preset{
public:
    Preset(std::vector<int> s, int fd, int fn){
        this->prebuilt_surface=s;
        animFrame_duration=fd;
        animFrames=fn;
    }
    std::vector<int> prebuilt_surface;
};

void Dialog::debug_items_count(int testPoint, std::string _label="ANIM"){
    std::cout<<std::endl<<"DEBUG: ("<<_label<<") "<<testPoint<<" scene items amount: "<<this->canvas->items().size()<<std::endl;
}

void Dialog::run_preset(int n){
    Preset p = this->presets[n];
    this->resetData();

    environmentHandler->metasurface_genuine=generate_surface(p.prebuilt_surface);
    environmentHandler->interactive_surface=&(environmentHandler->metasurface_genuine.polygon[environmentHandler->metasurface_genuine.polygon.size()-1]);

    //std::cout<<"surface="<<environmentHandler->metasurface_genuine<<std::endl;
    this->updateFrame();
    this->painter->drawElectron(&(environmentHandler->electron_genuine));
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    this->environmentHandler=new Physics_engine();

    auto QSize_out = [&](QSize QS){
        return "("+
            std::to_string(QS.width())+"x;"+
            std::to_string(QS.height())+"y)";
    };

    QSize DISPLAY_SIZE(DISPLAY_WIDTH,       DISPLAY_HEIGTH);    std::cout<<"\"DISPLAY_SIZE\": "     <<QSize_out(DISPLAY_SIZE)   <<std::endl;
    QSize BUTTON_SIZE(BUTTON_WIDTH,         BUTTON_HEIGTH);     std::cout<<"\"BUTTON_SIZE\": "      <<QSize_out(BUTTON_SIZE)    <<std::endl;
    QSize SMOL_LABEL_SIZE(SMOL_LABEL_WIDTH, SMOL_LABEL_HEIGTH); std::cout<<"\"SMOL_LABEL_SIZE\": "  <<QSize_out(SMOL_LABEL_SIZE)<<std::endl;
    QSize BIG_LABEL_SIZE(BIG_LABEL_WIDTH,   BIG_LABEL_HEIGTH);  std::cout<<"\"BIG_LABEL_SIZE\": "   <<QSize_out(BIG_LABEL_SIZE) <<std::endl;

    this->canvas = new QGraphicsScene(-DISPLAY_WIDTH/2,-DISPLAY_HEIGTH/2,DISPLAY_WIDTH,DISPLAY_HEIGTH);
    this->canvas->setBackgroundBrush(QBrush(DISPLAY_BACKGROUND_COLOR));

    this->ui->setupUi(this);

    this->resize(
        DISPLAY_WIDTH,
        DISPLAY_HEIGTH +3*SPACER_HEIGTH +BUTTON_HEIGTH +3*SMOL_LABEL_HEIGTH);
//        DISPLAY_HEIGTH+BUTTON_HEIGTH+3*SMOL_LABEL_HEIGTH+2*SPACER_HEIGTH);
//      DISPLAY_HEIGTH+BUTTON_HEIGTH+2*SMOL_LABEL_HEIGTH+SPACER_HEIGTH

    this->ui->display ->move(0,0);
    this->ui->display ->resize(DISPLAY_SIZE);
    this->ui->display ->setScene(canvas);
    this->ui->display ->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->display ->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    this->ui->test0 ->setText("Diagonal surface\n(UpRight to DownCenter)");
    this->ui->test1 ->setText("Vertical surface\n(Right)");
    this->ui->test2 ->setText("Run simulation");


    this->ui->presets_label ->resize(BIG_LABEL_SIZE);
    this->ui->test0         ->resize(BUTTON_SIZE);
    this->ui->test1         ->resize(BUTTON_SIZE);
    this->ui->test2         ->resize(BUTTON_SIZE);

    //int l=(DISPLAY_WIDTH-BIG_LABEL_WIDTH-2*BUTTON_WIDTH)/4;
    this->ui->presets_label ->move(SPACER_WIDTH, DISPLAY_HEIGTH+SPACER_HEIGTH);
    this->ui->test0         ->move(2*SPACER_WIDTH +BIG_LABEL_WIDTH,                  DISPLAY_HEIGTH +SPACER_HEIGTH);
    this->ui->test1         ->move(3*SPACER_WIDTH +BIG_LABEL_WIDTH +  BUTTON_WIDTH,  DISPLAY_HEIGTH +SPACER_HEIGTH);
    this->ui->test2         ->move(4*SPACER_WIDTH +BIG_LABEL_WIDTH +2*BUTTON_WIDTH,  DISPLAY_HEIGTH +SPACER_HEIGTH);
    //this->ui->test2->move(SPACER_WIDTH*3+BIG_LABEL_WIDTH+BUTTON_WIDTH, DISPLAY_HEIGTH+SPACER_HEIGTH*2+BUTTON_HEIGTH);




    this->ui->label0   ->resize(BIG_LABEL_WIDTH, SMOL_LABEL_HEIGTH);
    this->ui->label1   ->resize(SMOL_LABEL_SIZE);
    this->ui->label2   ->resize(SMOL_LABEL_SIZE);
    this->ui->label0_2 ->resize(BIG_LABEL_WIDTH, SMOL_LABEL_HEIGTH);
    this->ui->label1_2 ->resize(SMOL_LABEL_SIZE);
    this->ui->label2_2 ->resize(SMOL_LABEL_SIZE);
    this->ui->label1_3 ->resize(SMOL_LABEL_SIZE);
    this->ui->label2_3 ->resize(SMOL_LABEL_SIZE);
    this->ui->label3   ->resize(BIG_LABEL_WIDTH, SMOL_LABEL_HEIGTH);

    this->ui->label0   ->move(SPACER_WIDTH, 2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH);
    this->ui->label1   ->move(SPACER_WIDTH, 2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH +  SMOL_LABEL_HEIGTH);
    this->ui->label2   ->move(SPACER_WIDTH, 2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH +2*SMOL_LABEL_HEIGTH);
    this->ui->label0_2 ->move(3*SPACER_WIDTH +BIG_LABEL_WIDTH, 2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH);
    this->ui->label1_2 ->move(3*SPACER_WIDTH +BIG_LABEL_WIDTH, 2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH +  SMOL_LABEL_HEIGTH);
    this->ui->label2_2 ->move(3*SPACER_WIDTH +BIG_LABEL_WIDTH, 2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH +2*SMOL_LABEL_HEIGTH);
    this->ui->label1_3 ->move(2*SPACER_WIDTH +  SMOL_LABEL_WIDTH +2*BIG_LABEL_WIDTH, 1+2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH +  SMOL_LABEL_HEIGTH);
    this->ui->label2_3 ->move(2*SPACER_WIDTH +  SMOL_LABEL_WIDTH +2*BIG_LABEL_WIDTH, 1+2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH +2*SMOL_LABEL_HEIGTH);
    this->ui->label3   ->move(2*SPACER_WIDTH +3*SMOL_LABEL_WIDTH +2*BIG_LABEL_WIDTH,   2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH);

    this->ui->label0   ->setText("Movement vector data:");
    this->ui->label1   ->setText("X");
    this->ui->label2   ->setText("Y");
    this->ui->label0_2 ->setText("Environment data:");
    this->ui->label1_2 ->setText("m=");
    this->ui->label2_2 ->setText("q=");
    this->ui->label1_3 ->setText("*10^");
    this->ui->label2_3 ->setText("*10^");
    this->ui->label3   ->setText("Scale: 1px = 1m");

    this->ui->spinBox0   ->resize(SMOL_LABEL_SIZE);
    this->ui->spinBox1   ->resize(SMOL_LABEL_SIZE);
    this->ui->spinBox0_2 ->resize(BIG_LABEL_WIDTH, SMOL_LABEL_HEIGTH);
    this->ui->spinBox1_2 ->resize(BIG_LABEL_WIDTH, SMOL_LABEL_HEIGTH);
    this->ui->spinBox0_3 ->resize(SMOL_LABEL_SIZE);
    this->ui->spinBox1_3 ->resize(SMOL_LABEL_SIZE);

    this->ui->spinBox0   ->move(SMOL_LABEL_WIDTH, 1+2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH +  SMOL_LABEL_HEIGTH);
    this->ui->spinBox1   ->move(SMOL_LABEL_WIDTH, 1+2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH +2*SMOL_LABEL_HEIGTH);
    this->ui->spinBox0_2 ->move(2*SPACER_WIDTH +  SMOL_LABEL_WIDTH +  BIG_LABEL_WIDTH, 1+2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH +  SMOL_LABEL_HEIGTH);
    this->ui->spinBox1_2 ->move(2*SPACER_WIDTH +  SMOL_LABEL_WIDTH +  BIG_LABEL_WIDTH, 1+2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH +2*SMOL_LABEL_HEIGTH);
    this->ui->spinBox0_3 ->move(1*SPACER_WIDTH +2*SMOL_LABEL_WIDTH +2*BIG_LABEL_WIDTH, 1+2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH +  SMOL_LABEL_HEIGTH);
    this->ui->spinBox1_3 ->move(1*SPACER_WIDTH +2*SMOL_LABEL_WIDTH +2*BIG_LABEL_WIDTH, 1+2*SPACER_HEIGTH +DISPLAY_HEIGTH +BUTTON_HEIGTH +2*SMOL_LABEL_HEIGTH);

    this->ui->spinBox0   ->setMinimum(-DISPLAY_WIDTH/2);
    this->ui->spinBox1   ->setMinimum(0);
    this->ui->spinBox0_2 ->setMinimum(-1000000000);
    this->ui->spinBox1_2 ->setMinimum(-1000000000);
    this->ui->spinBox0_3 ->setMinimum(-100);
    this->ui->spinBox1_3 ->setMinimum(-100);

    this->ui->spinBox0   ->setMaximum(DISPLAY_WIDTH/2);
    this->ui->spinBox1   ->setMaximum(DISPLAY_WIDTH/2);
    this->ui->spinBox0_2 ->setMaximum(1000000000);
    this->ui->spinBox1_2 ->setMaximum(1000000000);
    this->ui->spinBox0_3 ->setMaximum(100);
    this->ui->spinBox1_3 ->setMaximum(100);

    this->ui->spinBox0   ->setValue(v0_x);
    this->ui->spinBox1   ->setValue(v0_y);
    this->ui->spinBox0_2 ->setValue(p_m_mantissa);
    this->ui->spinBox1_2 ->setValue(p_q_mantissa);
    this->ui->spinBox0_3 ->setValue(p_m_exponent);
    this->ui->spinBox1_3 ->setValue(p_q_exponent);


    this->presets=std::vector<Preset>{
        Preset(
            std::vector<int>{
                DISPLAY_WIDTH/2,    -DISPLAY_HEIGTH/2,
                DISPLAY_WIDTH/2,    -DISPLAY_HEIGTH/2,
                DISPLAY_WIDTH/2,    DISPLAY_HEIGTH/2,
                DISPLAY_WIDTH/5,    DISPLAY_HEIGTH/2,
            },
            100,
            60),
        Preset(
            std::vector<int>{
                DISPLAY_WIDTH/4,    -DISPLAY_HEIGTH/2,
                DISPLAY_WIDTH/2,    -DISPLAY_HEIGTH/2,
                DISPLAY_WIDTH/2,    DISPLAY_HEIGTH/2,
                DISPLAY_WIDTH/5,    DISPLAY_HEIGTH/2,
            },
            30,
            120)
    };
    this->on_test0_clicked();
}

Dialog::~Dialog(){
    delete ui;
}

Polygon Dialog::generate_surface(std::vector<int> a){
    Polygon poly;
    for (int i=0; i<a.size()-3; i+=2)
        poly.polygon.push_back(Line(a.at(i), a.at(i+1), a.at(i+2), a.at(i+3)));
    poly.polygon.push_back(Line(a.at(a.size()-2), a.at(a.size()-1), a.at(0), a.at(1)));
    //std::cout<<"surface: "<<poly;
    return poly;
}

void Dialog::simulate(){
    this->updateFrame();

    this->environmentHandler->find_base_of_perpendicular(*(this->environmentHandler->interactive_surface));
    //std::cout<<"base of perpendicular: "<<this->environmentHandler->base_of_perpendicular<<std::endl;
    Line perpendicular = Line(this->environmentHandler->electron_genuine,
                              this->environmentHandler->base_of_perpendicular);

    //(electron)-(surface) perp.
    this->painter->drawLine(perpendicular, QColor("#3F3FFB"));
    //(surface)-(virtual electron) perp.
    this->painter->drawLine(perpendicular.movedCopy(perpendicular), QColor("#FB3F3F"));

    this->painter->drawArrow(Line(p_x, p_y, p_x+2*v0_x, p_y-2*v0_y), QColor("#3F3FFB"));
    this->environmentHandler->calculate_acceleration();

    this->environmentHandler->angle_V0_absolute=
            atan(v0_y/v0_x);
    if(v0_y*v0_x<0)
        this->environmentHandler->angle_V0_absolute+=PI;

    this->environmentHandler->angle_surface_absolute=
            atan(this->environmentHandler->interactive_surface->dy()/
                 this->environmentHandler->interactive_surface->dx());

    double
        *_ang_VS=&(this->environmentHandler->angle_V0_relative),
        *_ang_surf=&(this->environmentHandler->angle_surface_absolute),
        *_a=&(this->environmentHandler->acceleration);

    this->environmentHandler->angle_V0_relative=
            this->environmentHandler->angle_V0_absolute-
            *_ang_surf;

    double
        _h=perpendicular.length(),
        _v0_rel=this->environmentHandler->movementVectorStart_length(),
        _v0_rel_x=_v0_rel*cos(*_ang_VS),
        _v0_rel_y=_v0_rel*sin(*_ang_VS);

    Point*
        _proj=&(this->environmentHandler->base_of_perpendicular);

    //std::cout<<"angle relative: "<<std::setprecision(25)<<*_ang_VS<<"rad   ("<<Physics_engine::angle(*_ang_VS)<<" degree)"<<std::endl<<std::setprecision(5);
    //std::cout<<"angle of surface: "<<std::setprecision(25)<<*_ang_surf<<"rad   ("<<Physics_engine::angle(*_ang_surf)<<" degree)"<<std::endl<<std::setprecision(5);

        double _t=(_v0_rel_y + sqrt(_v0_rel_y*_v0_rel_y + 2*(*_a)*_h)) / (*_a);
        auto dx_in_emulated = [&](double tc){
            return _v0_rel_x*tc;
        };

        auto dy_in_emulated = [&](double tc){
            return _v0_rel_y*tc - *_a*tc*tc/2;
        };
/*
        Point final_point=
            *(Point(
                dx_in_emulated(_t),
                0)
                    .rotateAround00(*_ang_surf)
                        .move(_proj->x, _proj->y));
*/
        //std::cout<<"\"start point\": "<<*_proj<<std::endl;

        //std::cout<<"dx1: "<<dx_in_emulated1<<std::endl;//_h+(_v0*sin(*_ang_VS))
        //std::cout<<"dx: "<<dx_in_emulated(_t)<<std::endl;
        //std::cout<<"t: "<<_t<<std::endl;
        //std::cout<<"h1: "<<_h<<std::endl;
        //std::cout<<"y final (): "<<_h-dy_in_emulated(_t)<<std::endl;

        //initialise animations
        this->environmentHandler->virt_genuine=
            this->environmentHandler->electron_genuine
                .rotate(
                    _proj,
                    PI);
        this->painter->setupAnimations(&(this->environmentHandler->electron_genuine),
                                       &(this->environmentHandler->virt_genuine));
        this->debug_items_count(1);



        double t_step=_t/200,
               t_curr=t_step,
               temp_x,
               temp_y;
        QPointF el_point_prev(p_x,p_y),
                el_point_curr;
        Point virt_point_prev=
                    Point(p_x,p_y).rotate(
                        _proj,
                        PI),
              virt_point_curr;
        //std::cout<<virt_point_prev.x()<<","<<virt_point_prev.y()<<";  ";
        this->movementCurves=this->canvas->createItemGroup(QList<QGraphicsItem*>{});
        for (double i=0.0; i<200.0;
                    ++i,
                    temp_x=dx_in_emulated(t_curr),
                    temp_y=dy_in_emulated(t_curr)){
            //std::cout<<virt_point_prev.x()<<","<<virt_point_prev.y()<<";  ";

            el_point_curr=Point(
                temp_x,
                -temp_y)
                    .rotate(
                        &(this->environmentHandler->electron_genuine),
                        *_ang_surf)
                    .toQPointF();
            //std::cout<<"i: "<<i<<"; x="<<temp_x<<"; y="<<temp_y<<"\n";
            //std::cout<<"el: "<<el_point_curr.x()<<","<<el_point_curr.y()<<"\n";

            //same, but inverted acceleration vector
            virt_point_curr=Point(
                temp_x,
                temp_y)
                    .rotate(
                        &(this->environmentHandler->electron_genuine),
                        *_ang_surf);
            //std::cout<<"virt: "<<virt_point_curr.x()<<","<<virt_point_curr.y()<<"\n\n";



            this->painter->animation_genuine->setPosAt(i/200.0, el_point_curr);
            this->painter->animation_virt   ->setPosAt(i/200.0, virt_point_curr.toQPointF());

            //adding movement curves, 'drawLineInGroup' is a macro
            if (i>1.5){
                // на первом шаге координаты достигают безумных значений, мб из-за t~0
                // temp_y = 1504801260586751059699981857518333261862691243264191369395498873627780433271966903946219951225276342426587754706998501866992797491999548350698206121417028290491087349258125312.00000
                // поэтому значение при и=0 нужно удалить
                // оно все еще существует при и=1 в виде прошлой точки
                drawLineInGroup(el_point_prev, el_point_curr, QColor("#3F3FFB"));
                Line c=Line(virt_point_prev, virt_point_curr).movedCopy(perpendicular.extendedCopy(2));
                //std::cout<<c<<"\n";
                drawLineInGroup(c, QColor("#FB3F3F"));
            }
            el_point_prev=el_point_curr;
            virt_point_prev=virt_point_curr;

            t_curr+=t_step;
        }
        this->painter->animation_timer->start();
}

void Dialog::updateFrame(){
    this->canvas->clear();
    this->painter->drawSurface(&(environmentHandler->metasurface_genuine));
    //this->painter->drawLine(Line(p_x, p_y, p_x+2*v0_x, p_y-2*v0_y));
    //this->painter->drawLine();
}

void Dialog::resetData(){
    this->resetData(animFrame_duration, animFrames);
}

void Dialog::resetData(int _frame_duration, int _frames){
    if(this->painter) this->painter->stop_timer();
    environmentHandler->electron_genuine=Point(p_x,p_y);
    environmentHandler->metasurface_genuine=Polygon();
    this->canvas->clear();
    this->painter = new Painter(this->canvas,_frame_duration*_frames,_frames);
}

void Dialog::on_test0_clicked(){
    this->run_preset(0);
}
void Dialog::on_test1_clicked(){
    this->run_preset(1);
}

void Dialog::on_test2_clicked(){
    /*this->ui->test0->setEnabled(false);
    this->ui->test1->setEnabled(false);
    this->ui->test2->setEnabled(false);*/
    simulate();
    //this->debug_items_count(0);
    /*this->ui->test0->setEnabled(true);
    this->ui->test1->setEnabled(true);
    this->ui->test2->setEnabled(true);*/
//    std::cout<<std::endl<<"scene items amount before: "<<this->canvas->items().size()<<std::endl;
//    this->resetData(0,0);
//    std::cout<<"scene items amount after: "<<this->canvas->items().size()<<std::endl;
}

void Dialog::on_spinBox0_valueChanged(int arg1){
    v0_x=arg1;
    this->ui->label1->setText((v0_x==69)?"nice":"X");
}

void Dialog::on_spinBox1_valueChanged(int arg1){
    v0_y=arg1;
    this->ui->label2->setText((v0_y==69)?"nice":"Y");
}

void Dialog::on_spinBox0_2_valueChanged(int arg1){
    p_m_mantissa=arg1;
}

void Dialog::on_spinBox1_2_valueChanged(int arg1){
    p_q_mantissa=arg1;
}

void Dialog::on_spinBox0_3_valueChanged(int arg1){
    p_m_exponent=arg1;
}

void Dialog::on_spinBox1_3_valueChanged(int arg1){
    p_q_exponent=arg1;
}

