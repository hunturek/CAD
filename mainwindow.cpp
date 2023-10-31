#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->openGLWidget->openFile("skull.obj",1);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_add_point_clicked()
{
    points[p_counter] = {ui->doubleSpinBox_point_x->value(), ui->doubleSpinBox_point_y->value(), ui->doubleSpinBox_point_z->value(), p_counter};
    ui->openGLWidget->add_point(points[p_counter].x, points[p_counter].y, points[p_counter].z);
    p_counter++;
}


void MainWindow::on_pushButton_add_line_clicked()
{
    int num1 = ui->spinBox_line_1p->value();
    int num2 = ui->spinBox_line_2p->value();
    ui->openGLWidget->add_line(num1, num2);
}

