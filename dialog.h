#ifndef DIALOG_H
#define DIALOG_H

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

private:
    const int DISPLAY_WIDTH=600,
              DISPLAY_HEIGTH=600;
    const int BUTTON_WIDTH=50,
              BUTTON_HEIGTH=50;
    const QColor DISPLAY_BACKGROUND_COLOR=QColor("#b9ceff");

    std::vector<Polygon> metasurface;
    Painter *painter;
    QGraphicsScene *canvas;

    void simulate();
    void generate_surface(std::vector<int>[], int);
    Ui::Dialog *ui;

    void simple_singlePolygonSurface_handler(std::vector<int> a[], int);
    void resetData();
};

#endif // DIALOG_H
