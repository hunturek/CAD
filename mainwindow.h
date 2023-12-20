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

private slots:
    void on_pushButton_addPoint_clicked();

    void on_pushButton_addLine_clicked();

    void on_pushButton_flush_clicked();

    void on_pushButton_res_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
