#ifndef DIALOG_H
#define DIALOG_H
//dialog.h
#include <QColor>
#include <QDialog>
#include <QLabel>
#include <QGraphicsScene>

#include "painter.h"
#include "physics_engine.h"
#include <vector>

namespace Ui {
class Dialog;
}

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

private:
    const int DISPLAY_WIDTH=1000,
              DISPLAY_HEIGTH=600;
    const int BUTTON_WIDTH=200,
              BUTTON_HEIGTH=50;
    const int LABEL0_WIDTH=200,
              LABEL_WIDTH=30,
              LABEL_HEIGTH=30;

    const QColor DISPLAY_BACKGROUND_COLOR=QColor("#b9ceff");

    Painter *painter;
    QGraphicsScene *canvas;

    Ui::Dialog *ui;

    void resetData();

    Polygon generate_surface(std::vector<int>);
    void drawVector(Line);

    bool isRunning;
    void simulate(int);
    void updateFrame();
};

#endif // DIALOG_H
