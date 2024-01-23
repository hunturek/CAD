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
        QVector3D *l = new QVector3D;
        QVector3D *P = new QVector3D;
        QVector3D *m = new QVector3D;
        QVector4D *q = new QVector4D;
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

    struct outcoming_objects{
        QVector2D *Q = new QVector2D; //значение слева, значение справа
        QVector4D *M = new QVector4D; //значение слева, значение справа, удаленность от левой, значение в середине
        QVector2D *N = new QVector2D; //значение слева, значение справа
        QVector2D *V = new QVector2D; //значение слева, значение справа
        QVector2D *U = new QVector2D; //значение слева, значение справа
        QVector2D *Sig = new QVector2D; //значение слева, значение справа
    };

    incoming_objects i_obj;
    objects_counts c_obj;
    outcoming_objects o_obj;
    QString i_filename = "";
    QString o_filename = "";
    void addPoint(float x, float y);
    void addLine(int p1, int p2);
    void addP(int pNum, float value, int axis);
    void addQ(int kNum, float value1, float value2, int axis);
    void addM(int pNum, float value, int axis);
    void flushFile();
    int loadFile(QString filename, incoming_objects *i_obj, objects_counts *c_obj);
    int outFile(QString filename, outcoming_objects o_obj);
    void fill_o(outcoming_objects *o_obj);
    bool setAddLine = false;
    int redP = -1;
    int kpNumsShow = 0;
    int lNumsShow = 0;

    float pRatio = 0.3;
    float yModulus = 2e11;

signals:
protected:
    void initializeGL() override; // Метод для инициализирования opengl
    void resizeGL(int w, int h) override; // Метод вызываемый после каждого изменения размера окна
    void paintGL() override; // Метод для вывода изображения на экран

    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent *event) override;
    bool behindP(int *r);

    // SUDA DAVAY

private:
    QPointF mPosition;
    float scale = 2.0;
    float x_left = -scale;
    float x_right = scale;
    float y_left = -scale;
    float y_right = scale;
    QVector3D global_0;

    void DrawL();
    void DrawKp();
    void DrawP();
    void DrawQ();
    void DrawM();
    void DrawTrapX(size_t n, float x1, float x2, float size);
    void DrawTrapY(size_t n, float y1, float y2, float size);
    void DrawTrapZ(size_t n, float z1, float z2, float size);
    void DrawArrowX(size_t n, float x, float size);
    void DrawArrowY(size_t n, float y, float size);
    void DrawArrowZ(size_t n, float z, float size);
    void DrawArcArrowX(float x, float y, float size, float orientation);
    void DrawNum(float num, float size, float x, float y);
    void Draw0(float size, float x, float y);
    void Draw1(float size, float x, float y);
    void Draw2(float size, float x, float y);
    void Draw3(float size, float x, float y);
    void Draw4(float size, float x, float y);
    void Draw5(float size, float x, float y);
    void Draw6(float size, float x, float y);
    void Draw7(float size, float x, float y);
    void Draw8(float size, float x, float y);
    void Draw9(float size, float x, float y);
    void DrawDot(float size, float x, float y);
    void DrawKpNum();
    void DrawLNum();

    float modelSize();
    int orientation(float x);
};

#endif // OGLWIDGET_H
