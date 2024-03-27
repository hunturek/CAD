#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector3D>
#include <QFile>
#include <QFileDialog>
#include <QtWidgets/QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QMouseEvent>
#include <QWheelEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void command_line(QString command, bool write_mode);
    int open_file(QString filename);


private slots:
    void on_pushButton_addPoint_clicked();

    void on_pushButton_addLine_clicked();

    void on_pushButton_flush_clicked();

    void on_pushButton_res_clicked();

    void on_pushButton_addLine_coords_clicked();

    void on_pushButton_loadFile_clicked();

    void on_pushButton_addP_clicked();

    void on_pushButton_kpNums_clicked();

    void on_pushButton_lNums_clicked();

    void on_pushButton_add_q_clicked();

    void on_pushButton_add_m_clicked();

    void on_pushButton_add_r_clicked();

    void on_pushButton_add_u_clicked();

    void on_lineEdit_commandLine_editingFinished();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
