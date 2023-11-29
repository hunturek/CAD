#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include "mainwindow.h"

class OGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OGLWidget(QWidget *parent = nullptr);

    QVector3D *points = new QVector3D;
    QVector2D *kernels = new QVector2D;
    int p_counter = 0;
    int k_counter = 0;
    QString filename = "/Users/hunturek/Documents/test/qt tests/CAD_0_1/file.txt";
    void addPoint(float x, float y, float z);
    void addLine(int p1, int p2);
    void flushFile();

signals:
protected:
    void initializeGL(); // Метод для инициализирования opengl
    void resizeGL(int w, int h); // Метод вызываемый после каждого изменения размера окна
    void paintGL(); // Метод для вывода изображения на экран
    int loadFile(QString filename, QVector3D *points, QVector2D *kernels, int *p_counter, int *k_counter);
};

#endif // OGLWIDGET_H
