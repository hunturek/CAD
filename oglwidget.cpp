#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{
    loadFile(filename, points, kernels, &p_counter, &k_counter);

}

void OGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
}

void OGLWidget::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
}

void OGLWidget::paintGL(){
    loadFile(filename, points, kernels, &p_counter, &k_counter);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glDisable(GL_BLEND);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1, 1, -1, 1, -10, 10);
    glColor3f(1.0f, 1.0f, 1.0f);
    for(int i = 0; i < k_counter; i++){
        glBegin(GL_LINE_LOOP);
        glVertex3f(points[(int)kernels[i].x()].x(), points[(int)kernels[i].x()].y(), points[(int)kernels[i].x()].z());
        glVertex3f(points[(int)kernels[i].y()].x(), points[(int)kernels[i].y()].y(), points[(int)kernels[i].y()].z());
        glEnd();
    }
    glPointSize(5);
    for(int i = 0; i < p_counter; i++){
        glBegin(GL_POINTS);
        glVertex3f(points[i].x(), points[i].y(), points[i].z());
        glEnd();
    }
}

int OGLWidget::loadFile(QString filename, QVector3D *points, QVector2D *kernels, int *p_counter, int *k_counter){
    QFile file(filename);
    *p_counter = 0;
    *k_counter = 0;
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd())
    {
        QString str = file.readLine();
        QStringList lst = str.split(" ");
        if(lst.at(0) == "p"){
            points[*p_counter].setX(lst.at(1).toFloat());
            points[*p_counter].setY(lst.at(2).toFloat());
            points[*p_counter].setZ(lst.at(3).chopped(1).toFloat());
            *p_counter = *p_counter + 1;
        }
        if(lst.at(0) == "k"){
            kernels[*k_counter].setX(lst.at(1).toInt());
            kernels[*k_counter].setY(lst.at(2).chopped(1).toInt());
            *k_counter = *k_counter + 1;
        }
    }
    file.close();
    return 0;
}

void OGLWidget::flushFile(){
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    file.close();
}

void OGLWidget::addPoint(float x, float y, float z){
    QString s1 = "\np ";
    s1.append(QString::number(x));
    s1.append(" ");
    s1.append(QString::number(y));
    s1.append(" ");
    s1.append(QString::number(z));
    QFile file(filename);
    QTextStream writeStream(&file);
    file.open(QIODevice::Append);
    writeStream << s1;
    file.close();
}

void OGLWidget::addLine(int p1, int p2){
    QString s1 = "\nk ";
    s1.append(QString::number(p1));
    s1.append(" ");
    s1.append(QString::number(p2));
    QFile file(filename);
    QTextStream writeStream(&file);
    file.open(QIODevice::Append | QIODevice::Text);
    writeStream << s1;
    file.close();
}

