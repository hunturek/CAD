#include "oglwidget.h"
#include "ui_mainwindow.h"

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{
    loadFile(filename, &i_obj, &c_obj);
    repaint();
    setMouseTracking(false);
    global_0.setX(230);
    global_0.setY(190);
}

void OGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
}

void OGLWidget::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
}

void OGLWidget::paintGL(){
    loadFile(filename, &i_obj, &c_obj);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glDisable(GL_BLEND);
    glMatrixMode(GL_PROJECTION);
    glOrtho(x_left, x_right, y_left, y_right, -10, 10);
    glColor3f(1.0f, 1.0f, 1.0f);
    for(size_t i = 0; i < c_obj.l; i++){
        glBegin(GL_LINE_LOOP);
        glVertex2f(i_obj.kp[(int)i_obj.l[i].x()].x(), i_obj.kp[(int)i_obj.l[i].x()].y());
        glVertex2f(i_obj.kp[(int)i_obj.l[i].y()].x(), i_obj.kp[(int)i_obj.l[i].y()].y());
        glEnd();
    }
    glPointSize(5);
    for(size_t i = 0; i < c_obj.kp; i++){
        if((int)i == red)
            glColor3f(1.0f, 0.0f, 0.0f);
        else
            glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POINTS);
        glVertex2f(i_obj.kp[i].x(), i_obj.kp[i].y());
        glEnd();
    }
}

int OGLWidget::loadFile(QString filename, incoming_objects *i_obj, objects_counts *c_obj){
    QFile file(filename);
    c_obj->P=0;
    c_obj->kp=0;
    c_obj->l=0;
    c_obj->q=0;
    c_obj->r=0;
    c_obj->u=0;
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd())
    {
        QString str = file.readLine();
        QStringList lst = str.split(" ");
        if(lst.at(0) == "kp"){
            i_obj->kp[c_obj->kp].setX(lst.at(1).toFloat());
            i_obj->kp[c_obj->kp].setY(lst.at(2).toFloat());
            c_obj->kp++;
        }
        if(lst.at(0) == "l"){
            i_obj->l[c_obj->l].setX(lst.at(1).toInt());
            i_obj->l[c_obj->l].setY(lst.at(2).toInt());
            c_obj->l++;
        }
        if(lst.at(0) == "P"){
            i_obj->P[c_obj->P].setX(lst.at(1).toFloat());
            i_obj->P[c_obj->P].setY(lst.at(2).toFloat());
            i_obj->P[c_obj->P].setZ(lst.at(3).toFloat());
            c_obj->P++;
        }
        if(lst.at(0) == "m"){
            i_obj->m[c_obj->m].setX(lst.at(1).toFloat());
            i_obj->m[c_obj->m].setY(lst.at(2).toFloat());
            i_obj->m[c_obj->m].setZ(lst.at(3).toFloat());
            c_obj->m++;
        }
        if(lst.at(0) == "q"){
            i_obj->q[c_obj->q].setX(lst.at(1).toFloat());
            i_obj->q[c_obj->q].setY(lst.at(2).toFloat());
            c_obj->q++;
        }
        if(lst.at(0) == "u"){
            i_obj->u[c_obj->u].setX(lst.at(1).toFloat());
            i_obj->u[c_obj->u].setY(lst.at(2).toFloat());
            i_obj->u[c_obj->u].setZ(lst.at(3).toFloat());
            c_obj->u++;
        }
        if(lst.at(0) == "r"){
            i_obj->r[c_obj->r].setX(lst.at(1).toFloat());
            i_obj->r[c_obj->r].setY(lst.at(2).toFloat());
            i_obj->r[c_obj->r].setZ(lst.at(3).toFloat());
            c_obj->r++;
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

void OGLWidget::addPoint(float x, float y){
    QString s1 = "\nkp ";
    s1.append(QString::number(x));
    s1.append(" ");
    s1.append(QString::number(y));
    QFile file(filename);
    QTextStream writeStream(&file);
    file.open(QIODevice::Append);
    writeStream << s1;
    file.close();
}

void OGLWidget::addLine(int p1, int p2){
    QString s1 = "\nl ";
    s1.append(QString::number(p1));
    s1.append(" ");
    s1.append(QString::number(p2));
    QFile file(filename);
    QTextStream writeStream(&file);
    file.open(QIODevice::Append | QIODevice::Text);
    writeStream << s1;
    file.close();
}

void OGLWidget::mousePressEvent(QMouseEvent *apEvent){
    mPosition = apEvent->position();
    if(setAddLine){
        int p2 = -1;
        if(red != -1 && behindP(&p2)){
            addLine(red,p2);
            red = -1;
            repaint();
        } else if(behindP(&red)){
            repaint();
        }
    }
}

void OGLWidget::mouseMoveEvent(QMouseEvent *apEvent){
    if(!setAddLine){
        QPointF startPos = mPosition;
        float tmp = 0;
        mPosition = apEvent->position();
        if(startPos.x() != 0 && startPos.y() != 0){
            tmp = (startPos.x() - mPosition.x()) / 250;
            x_left = x_left - tmp;
            x_right = x_left + scale * 2;
            global_0.setX(global_0.x() + tmp*230);
            tmp = (startPos.y() - mPosition.y()) / 250;
            y_left = y_left + tmp;
            y_right = y_left + scale * 2;
            global_0.setY(global_0.y() - tmp*190);
            repaint();
        }
    }
}

void OGLWidget::wheelEvent(QWheelEvent *event){
    QPointF angle = event->angleDelta();
    scale += angle.y()/2000;
    x_left = x_left-angle.y()/2000;
    x_right = x_right+angle.y()/2000;
    y_left = y_left-angle.y()/2000;
    y_right = y_right+angle.y()/2000;
    repaint();
}

bool OGLWidget::behindP(int *r){
    float x = (mPosition.x()-global_0.x())/global_0.x()*scale;
    float y = (mPosition.y()-global_0.y())/global_0.y()*scale*(-1);
    for(size_t i = 0; i < c_obj.kp; i++){
        if(x > i_obj.kp[i].x()-0.02 && x < i_obj.kp[i].x()+0.02
                && y > i_obj.kp[i].y()-0.02 && y < i_obj.kp[i].y()+0.02){
            *r = i;
            return true;
        }
    }
    return false;
}
