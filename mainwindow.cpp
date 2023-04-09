#include "debugtools.h"
#include "dialog.h"
#include "lemonade.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //skip main window
    this->on_pushButton_2_clicked();
    std::exit(1);
}

MainWindow::~MainWindow(){
    delete ui;
}

int qLineEdit2int(QLineEdit *qle){return qle->text().toInt();}
double qLineEdit2double(QLineEdit *qle){return qle->text().toDouble();}

/*! if no data specified in field, defaults are applied*/
void MainWindow::read_input_data(){
    /*p_x=qLineEdit2double(ui->x0_line);
    p_y=qLineEdit2double(ui->y0_line);
    p_m_mantissa=qLineEdit2double(ui->m_mantissa_line);
    p_m_exponent=qLineEdit2int(ui->m_exponent_line);
    p_q_mantissa=qLineEdit2double(ui->q_mantissa_line);
    p_q_exponent=qLineEdit2int(ui->q_exponent_line);
    v_x=qLineEdit2double(ui->xVector_line);
    v_y=qLineEdit2double(ui->yVector_line);*/
}
    // ¯\_( ͡° ͜ʖ ͡°)_/¯
void MainWindow::on_pushButton_clicked(){
    /*this->read_input_data();
    this->on_pushButton_2_clicked();*/
}

void MainWindow::on_pushButton_2_clicked(){
    debug_output_available_data();

    Dialog d(this);
    d.exec();
}
