#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include "mainwindow.h"

class OGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OGLWidget(QWidget *parent = nullptr);

    struct incoming_objects{
        QVector2D *kp = new QVector2D;
        QVector2D *l = new QVector2D;
        QVector3D *P = new QVector3D;
        QVector3D *m = new QVector3D;
        QVector2D *q = new QVector2D;
        QVector3D *u = new QVector3D;
        QVector3D *r = new QVector3D;
    };

    struct objects_counts{
        size_t kp = 0;
        size_t l = 0;
        size_t P = 0;
        size_t m = 0;
        size_t q = 0;
        size_t u = 0;
        size_t r = 0;
    };

    incoming_objects i_obj;
    objects_counts c_obj;
    QString filename = "/home/denis/c++/file.txt";
    void addPoint(float x, float y);
    void addLine(int p1, int p2);
    void flushFile();
    bool setAddLine = false;
    int red = -1;

signals:
protected:
    void initializeGL() override; // Метод для инициализирования opengl
    void resizeGL(int w, int h) override; // Метод вызываемый после каждого изменения размера окна
    void paintGL() override; // Метод для вывода изображения на экран
    int loadFile(QString filename, incoming_objects *i_obj, objects_counts *c_obj);

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
    QVector3D global_0;

};

#endif // OGLWIDGET_H
