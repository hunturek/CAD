#include "oglwidget.h"
#include "ui_mainwindow.h"

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{
    if(i_filename != "")
        loadFile(i_filename, &i_obj, &c_obj);
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
    if(i_filename != "")
        loadFile(i_filename, &i_obj, &c_obj);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glDisable(GL_BLEND);
    glMatrixMode(GL_PROJECTION);
    glOrtho(x_left, x_right, y_left, y_right, -10, 10);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(5);
    DrawL();
    DrawKp();
    glColor3f(0, 1.0f, 0);
    if(kpNumsShow)
        DrawKpNum();
    glColor3f(0, 0, 1.0f);
    if(lNumsShow)
        DrawLNum();
    glColor3f(1.0f, 0, 0);
    DrawP();
    DrawQ();
    DrawM();
}

void OGLWidget::DrawL(){
    for(size_t i = 0; i < c_obj.l; i++){
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(i_obj.kp[(int)i_obj.l[i].x()].x(), i_obj.kp[(int)i_obj.l[i].x()].y());
        glVertex2f(i_obj.kp[(int)i_obj.l[i].y()].x(), i_obj.kp[(int)i_obj.l[i].y()].y());
        glEnd();
    }
}

void OGLWidget::DrawKp(){
    for(size_t i = 0; i < c_obj.kp; i++){
        if((int)i == redP)
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
            if(i_obj.P[i].z() == 1)
                DrawArrowX((int)i_obj.P[i].x(), orientation(i_obj.P[i].y()), scale*0.2);
            if(i_obj.P[i].z() == 2)
                DrawArrowY((int)i_obj.P[i].x(), orientation(i_obj.P[i].y()), scale*0.2);
            if(i_obj.P[i].z() == 3)
                DrawArrowZ((int)i_obj.P[i].x(), orientation(i_obj.P[i].y()), scale*0.2);
    }
}

void OGLWidget::DrawQ(){
    for(size_t i = 0; i < c_obj.q; i++){
        if(i_obj.q[i].w() == 1)
            DrawTrapX(i_obj.q[i].z(), orientation(i_obj.q[i].x()), orientation(i_obj.q[i].y()), scale*0.2);
        if(i_obj.q[i].w() == 2)
            DrawTrapY(i_obj.q[i].z(), orientation(i_obj.q[i].x()), orientation(i_obj.q[i].y()), scale*0.2);
        if(i_obj.q[i].w() == 3)
            DrawTrapZ(i_obj.q[i].z(), orientation(i_obj.q[i].x()), orientation(i_obj.q[i].y()), scale*0.2);
    }
}

void OGLWidget::DrawM(){
    for(size_t i = 0; i < c_obj.m; i++){
        if(i_obj.m[i].z() == 1)
            DrawArcArrowX(i_obj.kp[(int)i_obj.m[i].x()].x(), i_obj.kp[(int)i_obj.m[i].x()].y(), scale*0.2, orientation(i_obj.m[i].y()));
    }
}

void OGLWidget::DrawArcArrowX(float x, float y, float size, float orientation){
    glBegin(GL_LINE_STRIP);
    glVertex2f(x,y);
    glVertex2f(x+(size/2*orientation), y+size/2);
    glVertex2f(x, y+size);
    glVertex2f(x-(size/2*orientation), y+size/2);
    glVertex2f(x-(size/4*orientation), y+size/2);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(x-(size/2*orientation), y+size/2);
    glVertex2f(x-(size/2*orientation), y+size/4*3);
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
    QString str = QString::number(num,'g',10);
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

void OGLWidget::DrawKpNum(){
    float size = scale/40;
    for(size_t i = 0; i < c_obj.kp; i++){
        DrawNum(i, size, i_obj.kp[i].x()+size, i_obj.kp[i].y()-size);
    }
}

void OGLWidget::DrawLNum(){
    float size = scale/40;
    float x, y;
    for(size_t i = 0; i < c_obj.l; i++){
         x = (i_obj.kp[(int)i_obj.l[i].x()].x() + i_obj.kp[(int)i_obj.l[i].y()].x()) / 2;
         y = (i_obj.kp[(int)i_obj.l[i].x()].y() + i_obj.kp[(int)i_obj.l[i].y()].y()) / 2;
         if(i_obj.kp[(int)i_obj.l[i].x()].x() != i_obj.kp[(int)i_obj.l[i].y()].x())
             y -= size;
         if(i_obj.kp[(int)i_obj.l[i].x()].y() != i_obj.kp[(int)i_obj.l[i].y()].y())
             x += size;
         DrawNum(i, size, x, y);
    }
}

void OGLWidget::mousePressEvent(QMouseEvent *apEvent){
    mPosition = apEvent->position();
    if(setAddLine){
        int p2 = -1;
        if(redP != -1 && behindP(&p2)){
            if(p2 != redP)
                addLine(redP,p2);
            redP = -1;
            repaint();
        } else if(behindP(&redP)){
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
