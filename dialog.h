#ifndef DIALOG_H
#define DIALOG_H

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
    const int DISPLAY_WIDTH=600,
              DISPLAY_HEIGTH=600;
    Painter *painter;
    QGraphicsScene *canvas;

    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    std::vector<Polygon> metasurface;
private slots:
    void on_test1_clicked();

private:
    void simulate();
    void generate_surface(std::vector<int>[], int);
    Ui::Dialog *ui;
    void verticalFlatSurfaceMR();//from middle to right
};

#endif // DIALOG_H
