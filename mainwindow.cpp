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
        ui->openGLWidget->redP = -1;
        ui->openGLWidget->repaint();
    }
}


void MainWindow::on_pushButton_flush_clicked()
{
    ui->openGLWidget->flushFile();
    ui->openGLWidget->repaint();
}

void MainWindow::on_pushButton_res_clicked(){
    ui->openGLWidget->fill_o(&ui->openGLWidget->o_obj);
    ui->openGLWidget->o_filename = QFileDialog::getOpenFileName(this,QString::fromUtf8("Open file"),QDir::currentPath(), "All files (*.*)");
    ui->openGLWidget->outFile(ui->openGLWidget->o_filename, ui->openGLWidget->o_obj);
}

void MainWindow::on_pushButton_addLine_coords_clicked()
{
    ui->openGLWidget->addLine(ui->spinBox_line_p1->value(), ui->spinBox_line_p2->value());
    ui->openGLWidget->repaint();
}

void MainWindow::on_pushButton_loadFile_clicked()
{
    ui->openGLWidget->i_filename = QFileDialog::getOpenFileName(this,QString::fromUtf8("Open file"),QDir::currentPath(), "All files (*.*)");
    if(ui->openGLWidget->i_filename != ""){
        ui->label_openFile->setText("FILE OPEN");
        ui->label_openFile->setStyleSheet("QLabel { color : green; }");
        ui->openGLWidget->repaint();
    } else {
        ui->label_openFile->setText("NO FILE");
        ui->label_openFile->setStyleSheet("QLabel { color : red; }");
    }
}

void MainWindow::on_pushButton_addP_clicked()
{
    ui->openGLWidget->addP(ui->spinBox_point_numberP->value(), ui->doubleSpinBox_valueP->value(), ui->comboBox_axisP->currentIndex()+1);
    ui->openGLWidget->repaint();
}

void MainWindow::on_pushButton_kpNums_clicked()
{
    if(ui->pushButton_kpNums->isChecked())
        ui->openGLWidget->kpNumsShow = 1;
    else
        ui->openGLWidget->kpNumsShow = 0;
    ui->openGLWidget->repaint();
}

void MainWindow::on_pushButton_lNums_clicked()
{
    if(ui->pushButton_lNums->isChecked())
        ui->openGLWidget->lNumsShow = 1;
    else
        ui->openGLWidget->lNumsShow = 0;
    ui->openGLWidget->repaint();
}

void MainWindow::on_pushButton_add_q_clicked()
{
    ui->openGLWidget->addQ(ui->spinBox_kernel_numberQ->value(), ui->doubleSpinBox_value_q->value(), ui->doubleSpinBox_value2_q->value(), ui->comboBox_axis_q->currentIndex()+1);
    ui->openGLWidget->repaint();
}
