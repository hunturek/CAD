#ifndef WIDGET_H
#define WIDGET_H
#define GL_SILENCE_DEPRECATION

#include <QtWidgets/QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QOpenGLFunctions>
#include <fstream>
#include <string>
extern "C" {
#include "backend/back.h"
}

class widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit widget(QWidget *parent = nullptr);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void openFile(char *filename, int fileStatus);

    res syst = {0};
    int flag;


    std::ofstream file;
    char *filename = "/Users/hunturek/Documents/test/qt tests/dip/file.obj";
    void add_point(double x, double y, double z);
    void add_line(int p_num1, int p_num2);
signals:

};

#endif // WIDGET_H
