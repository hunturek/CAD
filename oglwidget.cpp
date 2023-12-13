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
    glPointSize(5);
    DrawL();
    DrawKp();
    glColor3f(1.0f, 0, 0);
    DrawP();
    DrawQ();
    DrawNum(12345.67890, 0.05,-0.4,-0.4);
}

void OGLWidget::DrawL(){
    for(size_t i = 0; i < c_obj.l; i++){
        glBegin(GL_LINE_LOOP);
        glVertex2f(i_obj.kp[(int)i_obj.l[i].x()].x(), i_obj.kp[(int)i_obj.l[i].x()].y());
        glVertex2f(i_obj.kp[(int)i_obj.l[i].y()].x(), i_obj.kp[(int)i_obj.l[i].y()].y());
        glEnd();
    }
}

void OGLWidget::DrawKp(){
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

void OGLWidget::DrawP(){
    for(size_t i = 0; i < c_obj.P; i++){
            if(i_obj.P[i].x())
                DrawArrowX((int)i_obj.P[i].w(), orientation(i_obj.P[i].x()), modelSize()*0.3);
            if(i_obj.P[i].y())
                DrawArrowY((int)i_obj.P[i].w(), orientation(i_obj.P[i].y()), modelSize()*0.3);
            if(i_obj.P[i].z())
                DrawArrowZ((int)i_obj.P[i].w(), orientation(i_obj.P[i].z()), modelSize()*0.3);
    }
}

void OGLWidget::DrawQ(){
    for(size_t i = 0; i < c_obj.q; i++){
        if(i_obj.q[i].w() == 1)
            DrawTrapX(i_obj.q[i].z(), orientation(i_obj.q[i].x()), orientation(i_obj.q[i].y()), modelSize()*0.3);
        if(i_obj.q[i].w() == 2)
            DrawTrapY(i_obj.q[i].z(), orientation(i_obj.q[i].x()), orientation(i_obj.q[i].y()), modelSize()*0.3);
        if(i_obj.q[i].w() == 3)
            DrawTrapZ(i_obj.q[i].z(), orientation(i_obj.q[i].x()), orientation(i_obj.q[i].y()), modelSize()*0.3);
    }
}

void OGLWidget::DrawArrowX(size_t n, float x, float size){
    glBegin(GL_LINE_LOOP);
    glVertex2f(i_obj.kp[n].x(), i_obj.kp[n].y());
    glVertex2f(i_obj.kp[n].x()+size*x, i_obj.kp[n].y());
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(i_obj.kp[n].x(), i_obj.kp[n].y());
    glVertex2f(i_obj.kp[n].x()+size/3*x, i_obj.kp[n].y()+size/6);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(i_obj.kp[n].x(), i_obj.kp[n].y());
    glVertex2f(i_obj.kp[n].x()+size/3*x, i_obj.kp[n].y()-size/6);
    glEnd();
}

void OGLWidget::DrawArrowY(size_t n, float y, float size){
    glBegin(GL_LINE_LOOP);
    glVertex2f(i_obj.kp[n].x(), i_obj.kp[n].y());
    glVertex2f(i_obj.kp[n].x(), i_obj.kp[n].y()+size*y);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(i_obj.kp[n].x(), i_obj.kp[n].y());
    glVertex2f(i_obj.kp[n].x()+size/6, i_obj.kp[n].y()+size/3*y);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(i_obj.kp[n].x(), i_obj.kp[n].y());
    glVertex2f(i_obj.kp[n].x()-size/6, i_obj.kp[n].y()+size/3*y);
    glEnd();
}

void OGLWidget::DrawArrowZ(size_t n, float z, float size){
    glBegin(GL_LINE_LOOP);
    glVertex2f(i_obj.kp[n].x(), i_obj.kp[n].y());
    glVertex3f(i_obj.kp[n].x(), i_obj.kp[n].y(), size*z);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(i_obj.kp[n].x(), i_obj.kp[n].y());
    glVertex3f(i_obj.kp[n].x()+size/6, i_obj.kp[n].y(), size/3*z);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(i_obj.kp[n].x(), i_obj.kp[n].y());
    glVertex3f(i_obj.kp[n].x()-size/6, i_obj.kp[n].y(), size/3*z);
    glEnd();
}

void OGLWidget::DrawTrapX(size_t n, float x1, float x2, float size){
    DrawArrowX(i_obj.l[n].x(), x1, size);
    DrawArrowX(i_obj.l[n].y(), x2, size);
    glBegin(GL_LINE_LOOP);
    glVertex2f(i_obj.kp[(int)i_obj.l[n].x()].x()+size*x1, i_obj.kp[(int)i_obj.l[n].x()].y());
    glVertex2f(i_obj.kp[(int)i_obj.l[n].y()].x()+size*x2, i_obj.kp[(int)i_obj.l[n].y()].y());
    glEnd();
}

void OGLWidget::DrawTrapY(size_t n, float y1, float y2, float size){
    DrawArrowY(i_obj.l[n].x(), y1, size);
    DrawArrowY(i_obj.l[n].y(), y2, size);
    glBegin(GL_LINE_LOOP);
    glVertex2f(i_obj.kp[(int)i_obj.l[n].x()].x(), i_obj.kp[(int)i_obj.l[n].x()].y()+size*y1);
    glVertex2f(i_obj.kp[(int)i_obj.l[n].y()].x(), i_obj.kp[(int)i_obj.l[n].y()].y()+size*y2);
    glEnd();
}

void OGLWidget::DrawTrapZ(size_t n, float z1, float z2, float size){
    DrawArrowZ(i_obj.l[n].x(), z1, size);
    DrawArrowZ(i_obj.l[n].y(), z2, size);
    glBegin(GL_LINE_LOOP);
    glVertex3f(i_obj.kp[(int)i_obj.l[n].x()].x(), i_obj.kp[(int)i_obj.l[n].x()].y(), size*z1);
    glVertex3f(i_obj.kp[(int)i_obj.l[n].y()].x(), i_obj.kp[(int)i_obj.l[n].y()].y(), size*z2);
    glEnd();
}

void OGLWidget::Draw0(float size, float x, float y){
    glBegin(GL_LINE_LOOP);
    glVertex2f(x,y);
    glVertex2f(x+size,y);
    glVertex2f(x+size,y-2*size);
    glVertex2f(x,y-2*size);
    glEnd();
}

void OGLWidget::Draw1(float size, float x, float y){
    glBegin(GL_LINE_STRIP);
    glVertex2f(x,y-size);
    glVertex2f(x+size,y);
    glVertex2f(x+size,y-2*size);
    glEnd();
}

void OGLWidget::Draw2(float size, float x, float y){
    glBegin(GL_LINE_STRIP);
    glVertex2f(x,y);
    glVertex2f(x+size,y);
    glVertex2f(x+size,y-size);
    glVertex2f(x,y-size);
    glVertex2f(x,y-2*size);
    glVertex2f(x+size,y-2*size);
    glEnd();
}

void OGLWidget::Draw3(float size, float x, float y){
    glBegin(GL_LINE_STRIP);
    glVertex2f(x,y);
    glVertex2f(x+size,y);
    glVertex2f(x+size,y-size);
    glVertex2f(x,y-size);
    glVertex2f(x+size,y-size);
    glVertex2f(x+size,y-2*size);
    glVertex2f(x,y-2*size);
    glEnd();
}

void OGLWidget::Draw4(float size, float x, float y){
    glBegin(GL_LINE_STRIP);
    glVertex2f(x,y);
    glVertex2f(x,y-size);
    glVertex2f(x+size,y-size);
    glVertex2f(x+size,y);
    glVertex2f(x+size,y-2*size);
    glEnd();
}

void OGLWidget::Draw5(float size, float x, float y){
    glBegin(GL_LINE_STRIP);
    glVertex2f(x+size,y);
    glVertex2f(x,y);
    glVertex2f(x,y-size);
    glVertex2f(x+size,y-size);
    glVertex2f(x+size,y-2*size);
    glVertex2f(x,y-2*size);
    glEnd();
}

void OGLWidget::Draw6(float size, float x, float y){
    glBegin(GL_LINE_STRIP);
    glVertex2f(x+size,y);
    glVertex2f(x,y);
    glVertex2f(x,y-2*size);
    glVertex2f(x+size,y-2*size);
    glVertex2f(x+size,y-size);
    glVertex2f(x,y-size);
    glEnd();
}

void OGLWidget::Draw7(float size, float x, float y){
    glBegin(GL_LINE_STRIP);
    glVertex2f(x,y);
    glVertex2f(x+size,y);
    glVertex2f(x+size,y-2*size);
    glEnd();
}

void OGLWidget::Draw8(float size, float x, float y){
    Draw0(size,x,y);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x+size,y-size);
    glVertex2f(x,y-size);
    glEnd();
}

void OGLWidget::Draw9(float size, float x, float y){
    glBegin(GL_LINE_STRIP);
    glVertex2f(x,y-2*size);
    glVertex2f(x+size,y-2*size);
    glVertex2f(x+size,y);
    glVertex2f(x,y);
    glVertex2f(x,y-size);
    glVertex2f(x+size,y-size);
    glEnd();
}

void OGLWidget::DrawDot(float size, float x, float y){
    glBegin(GL_POLYGON);
    glVertex2f(x+2*size/5, y-2*size);
    glVertex2f(x+3*size/5, y-2*size);
    glVertex2f(x+3*size/5, y-2*size+size/5);
    glVertex2f(x+2*size/5, y-2*size+size/5);
    glEnd();
}

void OGLWidget::DrawNum(float num, float size, float x, float y){
    QString str = QString::number(num);
    for(int i = 0; i < str.length(); i++){
        switch(str.at(i).unicode()){
            case '0':
                Draw0(size, x, y);
            break;
            case '1':
                Draw1(size, x, y);
            break;
            case '2':
                Draw2(size, x, y);
            break;
            case '3':
                Draw3(size, x, y);
            break;
            case '4':
                Draw4(size, x, y);
            break;
            case '5':
                Draw5(size, x, y);
            break;
            case '6':
                Draw6(size, x, y);
            break;
            case '7':
                Draw7(size, x, y);
            break;
            case '8':
                Draw8(size, x, y);
            break;
            case '9':
                Draw9(size, x, y);
            break;
            case '.':
                DrawDot(size, x, y);
            break;
        }
        x += size + size/3;
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
            i_obj->P[c_obj->P].setX(lst.at(2).toFloat());
            i_obj->P[c_obj->P].setY(lst.at(3).toFloat());
            i_obj->P[c_obj->P].setZ(lst.at(4).toFloat());
            i_obj->P[c_obj->P].setW(lst.at(1).toFloat());
            c_obj->P++;
        }
        if(lst.at(0) == "m"){
            i_obj->m[c_obj->m].setX(lst.at(2).toFloat());
            i_obj->m[c_obj->m].setY(lst.at(3).toFloat());
            i_obj->m[c_obj->m].setZ(lst.at(4).toFloat());
            i_obj->m[c_obj->m].setW(lst.at(1).toFloat());
            c_obj->m++;
        }
        if(lst.at(0) == "q"){
            i_obj->q[c_obj->q].setX(lst.at(2).toFloat());
            i_obj->q[c_obj->q].setY(lst.at(3).toFloat());
            i_obj->q[c_obj->q].setZ(lst.at(1).toFloat());
            i_obj->q[c_obj->q].setW(lst.at(4).toFloat());
            c_obj->q++;
        }
        if(lst.at(0) == "u"){
            i_obj->u[c_obj->u].setX(lst.at(2).toFloat());
            i_obj->u[c_obj->u].setY(lst.at(3).toFloat());
            i_obj->u[c_obj->u].setZ(lst.at(4).toFloat());
            i_obj->u[c_obj->u].setW(lst.at(1).toFloat());
            c_obj->u++;
        }
        if(lst.at(0) == "r"){
            i_obj->r[c_obj->r].setX(lst.at(2).toFloat());
            i_obj->r[c_obj->r].setY(lst.at(3).toFloat());
            i_obj->r[c_obj->r].setZ(lst.at(4).toFloat());
            i_obj->r[c_obj->r].setW(lst.at(1).toFloat());
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
            if(p2 != red)
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
            global_0.setX(global_0.x() + tmp * 250);
            tmp = (startPos.y() - mPosition.y()) / 250;
            y_left = y_left + tmp;
            y_right = y_left + scale * 2;
            global_0.setY(global_0.y() - tmp * 250);
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
    float x_r = abs(x_left - x_right);
    float y_r = abs(y_left - y_right);
    float x = x_left + mPosition.x()/460 * x_r;
    float y = y_right - mPosition.y()/380 * y_r;
    for(size_t i = 0; i < c_obj.kp; i++){
        if(x > i_obj.kp[i].x()-0.02*scale && x < i_obj.kp[i].x()+0.02*scale
                && y > i_obj.kp[i].y()-0.02*scale && y < i_obj.kp[i].y()+0.02*scale){
            *r = i;
            return true;
        }
    }
    return false;
}

float OGLWidget::modelSize(){
    QVector2D min = {i_obj.kp[0].x(), i_obj.kp[0].y()};
    QVector2D max = {i_obj.kp[0].x(), i_obj.kp[0].y()};
    for(size_t i = 0; i < c_obj.kp; i++){
        if (i_obj.kp[i].x() < min.x())
            min.setX(i_obj.kp[i].x());
        if (i_obj.kp[i].x() > max.x())
            max.setX(i_obj.kp[i].x());
        if (i_obj.kp[i].y() < min.y())
            min.setY(i_obj.kp[i].y());
        if (i_obj.kp[i].y() > max.y())
            max.setY(i_obj.kp[i].y());
    }
    return min.distanceToPoint(max);
}

int OGLWidget::orientation(float x){
    int f = 0;
    if(x > 0)
        f = 1;
    if(x < 0)
        f = -1;
    return f;
}
