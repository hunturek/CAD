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
    open_file(ui->openGLWidget->i_filename);
}

void MainWindow::on_pushButton_addP_clicked()
{
    if(ui->openGLWidget->i_obj.kp.size() > ui->spinBox_point_numberP->value())
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
    if(ui->openGLWidget->i_obj.l.size() > ui->spinBox_kernel_numberQ->value())
        ui->openGLWidget->addQ(ui->spinBox_kernel_numberQ->value(), ui->doubleSpinBox_value_q->value(), ui->doubleSpinBox_value2_q->value(), ui->comboBox_axis_q->currentIndex()+1);
    ui->openGLWidget->repaint();
}

void MainWindow::on_pushButton_add_m_clicked()
{
    if(ui->openGLWidget->i_obj.kp.size() > ui->spinBox_point_numberm->value())
        ui->openGLWidget->addM(ui->spinBox_point_numberm->value(), ui->doubleSpinBox_value_m->value(), ui->comboBox_axis_m->currentIndex()+1);
    ui->openGLWidget->repaint();
}

void MainWindow::on_pushButton_add_r_clicked()
{
    if(ui->openGLWidget->i_obj.kp.size() > ui->spinBox_point_numberr->value())
        ui->openGLWidget->addR(ui->spinBox_point_numberr->value(), ui->doubleSpinBox_value_r->value(), ui->comboBox_axis_r->currentIndex()+1);
    ui->openGLWidget->repaint();
}

void MainWindow::on_pushButton_add_u_clicked()
{
    if(ui->openGLWidget->i_obj.kp.size() > ui->spinBox_point_numberu->value())
        ui->openGLWidget->addU(ui->spinBox_point_numberu->value(), ui->doubleSpinBox_value_u->value(), ui->comboBox_axis_u->currentIndex()+1);
    ui->openGLWidget->repaint();
}

void MainWindow::on_lineEdit_commandLine_editingFinished()
{
    this->command_line(ui->lineEdit_commandLine->text(), 1);
    ui->lineEdit_commandLine->setText("");
}

void MainWindow::command_line(QString command, bool write_mode){
    if(command == "\n" || command == "")
        return;
    QStringList parse = command.split(" ");
    if(parse[0].toLower() == "load"){
        if(parse[1].toLower() == "file")
            this->on_pushButton_loadFile_clicked();
        else if(open_file(parse[1])){
            ui->openGLWidget->i_filename = parse[1];
            ui->openGLWidget->repaint();
        }
        write_mode = 0;
    } else if(parse[0].toLower() == "flush") {
        ui->openGLWidget->flushFile();
    } else if(parse[0].toLower() == "show") {
        if(parse[1].toLower() == "kpnums")
            ui->openGLWidget->kpNumsShow = !ui->openGLWidget->kpNumsShow;
        if(parse[1].toLower() == "lnums")
            ui->openGLWidget->lNumsShow = !ui->openGLWidget->lNumsShow;
        if(parse[1].toLower() == "p" || parse[1].toLower() == "forces")
            ui->openGLWidget->PShow = !ui->openGLWidget->PShow;
        if(parse[1].toLower() == "q" || parse[1].toLower() == "forces")
            ui->openGLWidget->qShow = !ui->openGLWidget->qShow;
        if(parse[1].toLower() == "m" || parse[1].toLower() == "forces")
            ui->openGLWidget->mShow = !ui->openGLWidget->mShow;
        if(parse[1].toLower() == "r" || parse[1].toLower() == "degrees")
            ui->openGLWidget->rShow = !ui->openGLWidget->rShow;
        if(parse[1].toLower() == "u" || parse[1].toLower() == "degrees")
            ui->openGLWidget->uShow = !ui->openGLWidget->uShow;
        write_mode = 0;
    } else if(parse[0].toLower() == "kp") {
        ui->openGLWidget->addPoint(parse[1].toFloat(), parse[2].toFloat());
    } else if(parse[0].toLower() == "l") {
        ui->openGLWidget->addLine(parse[1].toInt(), parse[2].toInt());
    } else if(parse[0].toLower() == "p") {
        ui->openGLWidget->addP(parse[1].toInt(), parse[2].toFloat(), parse[3].toInt());
    } else if(parse[0].toLower() == "q") {
        ui->openGLWidget->addQ(parse[1].toInt(), parse[2].toFloat(), parse[3].toFloat(), parse[4].toInt());
    } else if(parse[0].toLower() == "m") {
        ui->openGLWidget->addM(parse[1].toInt(), parse[2].toFloat(), parse[3].toInt());
    } else if(parse[0].toLower() == "u") {
        ui->openGLWidget->addU(parse[1].toInt(), parse[2].toFloat(), parse[3].toInt());
    } else if(parse[0].toLower() == "r") {
        ui->openGLWidget->addR(parse[1].toInt(), parse[2].toFloat(), parse[3].toInt());
    }
    if(write_mode){
        QFile file(ui->openGLWidget->i_filename);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << command << "\n";
            file.close();
        }
    }
    ui->openGLWidget->repaint();
}

int MainWindow::open_file(QString filename){
    if(filename != ""){
        ui->label_openFile->setText("FILE OPEN");
        ui->label_openFile->setStyleSheet("QLabel { color : green; }");
        ui->toolBox->setEnabled(true);
        ui->pushButton_kpNums->setEnabled(true);
        ui->pushButton_lNums->setEnabled(true);
        ui->pushButton_res->setEnabled(true);
        ui->pushButton_flush->setEnabled(true);
        ui->openGLWidget->i_filename = filename;
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly)) {
            if (file.size() != 0) {
                while (!file.atEnd()) {
                    QString str = file.readLine();
                    command_line(str, 0);
                }
            }
            file.close();
        }
        ui->openGLWidget->repaint();
        return 1;
    } else {
        ui->label_openFile->setText("NO FILE");
        ui->label_openFile->setStyleSheet("QLabel { color : red; }");
        return 0;
    }
}
