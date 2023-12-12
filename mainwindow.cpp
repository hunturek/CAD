#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui->openGLWidget->i_obj.kp;
    delete ui->openGLWidget->i_obj.l;
    delete ui;
}


void MainWindow::on_pushButton_addPoint_clicked()
{
    ui->openGLWidget->addPoint(ui->doubleSpinBox_pointX->value(), ui->doubleSpinBox_pointY->value());
    ui->openGLWidget->repaint();
}


void MainWindow::on_pushButton_addLine_clicked()
{
    if(ui->pushButton_addLine->isChecked()){
    ui->pushButton_addLine->setChecked(true);
    ui->openGLWidget->setAddLine = true;
    } else {
        ui->pushButton_addLine->setChecked(false);
        ui->openGLWidget->setAddLine = false;
        ui->openGLWidget->red = -1;
        ui->openGLWidget->repaint();
    }
}


void MainWindow::on_pushButton_flush_clicked()
{
    ui->openGLWidget->flushFile();
    ui->openGLWidget->repaint();
}
