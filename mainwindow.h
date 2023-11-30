#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector3D>
#include <QFile>
#include <QtWidgets/QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVector3D *points = new QVector3D;
    QVector2D *kernels = new QVector2D;
    int p_counter = 0;
    int k_counter = 0;


private slots:
    void on_pushButton_addPoint_clicked();

    void on_pushButton_addLine_clicked();

    void on_pushButton_flush_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
