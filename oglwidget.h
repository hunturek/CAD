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
    QString filename = "/Users/hunturek/Documents/test/qt tests/file.txt";
    void addPoint(float x, float y, float z);
    void addLine(int p1, int p2);
    void flushFile();
    bool setAddLine = false;
    int red = -1;

signals:
protected:
    void initializeGL() override; // Метод для инициализирования opengl
    void resizeGL(int w, int h) override; // Метод вызываемый после каждого изменения размера окна
    void paintGL() override; // Метод для вывода изображения на экран
    int loadFile(QString filename, QVector3D *points, QVector2D *kernels, int *p_counter, int *k_counter);

    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent *event) override;
    bool behindP(int *r);
private:
    QPointF mPosition;
    float scale = 2.0;
    float x_left = -scale;
    float x_right = scale;
    float y_left = -scale;
    float y_right = scale;

};

#endif // OGLWIDGET_H
