#ifndef DIALOG_H
#define DIALOG_H
//dialog.h
#include <QColor>
#include <QDialog>
#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimeLine>

#include "painter.h"
#include "physics_engine.h"
#include <vector>

namespace Ui {
class Dialog;
}

class Preset;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
private slots:
    void on_test1_clicked();
    void on_test0_clicked();
    void on_test2_clicked();

    void on_spinBox0_valueChanged(int arg1);

    void on_spinBox1_valueChanged(int arg1);

    void on_spinBox0_2_valueChanged(int arg1);

    void on_spinBox1_2_valueChanged(int arg1);

    void on_spinBox0_3_valueChanged(int arg1);

    void on_spinBox1_3_valueChanged(int arg1);

private:
    const int DISPLAY_WIDTH=1000,
              DISPLAY_HEIGTH=600;
    const int BUTTON_WIDTH=200,
              BUTTON_HEIGTH=50;
    const int SMOL_LABEL_WIDTH=60,
              SMOL_LABEL_HEIGTH=30;
    const int BIG_LABEL_WIDTH=160,
              BIG_LABEL_HEIGTH=50;
    const int SPACER_WIDTH=20,
              SPACER_HEIGTH=20;

    const QColor DISPLAY_BACKGROUND_COLOR=QColor("#B9CEFF");

    Painter *painter = nullptr;
    QGraphicsScene *canvas = nullptr;
    Physics_engine *environmentHandler = nullptr;
    QGraphicsItemGroup *movementCurves = nullptr;
    std::vector<int> surface_holder;

    std::vector<Preset> presets;
    void run_preset(int);

    Ui::Dialog *ui;
    void resetData();
    void resetData(int,int);
    void resetData(Preset *P);

    Polygon generate_surface(std::vector<int>);
    void drawVector(Line);

    //void init_animation(Point*);

    bool isRunning;
    void simulate();
    void updateFrame();


    void debug_items_count(int, std::string _label);
};

#endif // DIALOG_H
