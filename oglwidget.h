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
        QVector<QVector2D> kp;
        QVector<QVector2D> l;
        QVector<QVector3D> P;
        QVector<QVector3D> m;
        QVector<QVector4D> q;
        QVector<QVector3D> u;
        QVector<QVector3D> r;

        void clear(){
                    kp.clear();
                    l.clear();
                    P.clear();
                    m.clear();
                    q.clear();
                    u.clear();
                    r.clear();
        }

        ~incoming_objects() {
                this->clear();
            }
    };

    struct outcoming_objects{
        QVector2D *Q = new QVector2D; //значение слева, значение справа
        QVector4D *M = new QVector4D; //значение слева, значение справа, удаленность от левой, значение в середине
        QVector2D *N = new QVector2D; //значение слева, значение справа
        QVector2D *V = new QVector2D; //значение слева, значение справа
        QVector2D *U = new QVector2D; //значение слева, значение справа
        QVector2D *Sig = new QVector2D; //значение слева, значение справа

        ~outcoming_objects() {
                delete Q;
                delete M;
                delete N;
                delete V;
                delete U;
                delete Sig;
            }
    };

    incoming_objects i_obj;
    outcoming_objects o_obj;
    QString i_filename = "";
    QString o_filename = "";
    void addPoint(float x, float y);
    void addLine(int p1, int p2);
    void addP(int pNum, float value, int axis);
    void addQ(int kNum, float value1, float value2, int axis);
    void addM(int pNum, float value, int axis);
    void addR(int pNum, float value, int axis);
    void addU(int pNum, float value, int axis);

    void flushFile();
    int outFile(QString filename, outcoming_objects o_obj);
    void fill_o(outcoming_objects *o_obj);

    bool setAddLine = false;
    int redP = -1;
    int kpNumsShow = 0;
    int lNumsShow = 0;
    int PShow = 1;
    int qShow = 1;
    int mShow = 1;
    int uShow = 1;
    int rShow = 1;

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
    void DrawU();
    void DrawR();
    void DrawTrapX(size_t n, float x1, float x2, float size);
    void DrawTrapY(size_t n, float y1, float y2, float size);
    void DrawTrapZ(size_t n, float z1, float z2, float size);
    void DrawArrowX(size_t n, float x, float size);
    void DrawArrowY(size_t n, float y, float size);
    void DrawArrowZ(size_t n, float z, float size);
    void DrawArcArrow(float x, float y, float size, float orientation);
    void DrawRect(float x, float y, float size);
    void DrawRumb(float x, float y, float size);
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
