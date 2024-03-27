#include "oglwidget.h"

int OGLWidget::outFile(QString filename, outcoming_objects o_obj){
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream writeS(&file);
    for(size_t i = 0; i < (size_t)i_obj.l.size(); i++){
        writeS << "l" << i << "\n";
        writeS << "\tN " << o_obj.N[i].x() << " " << o_obj.N[i].y() << "\n";
        writeS << "\tQ " << o_obj.Q[i].x() << " " << o_obj.Q[i].y() << "\n";
        writeS << "\tM " << o_obj.M[i].x() << " " << o_obj.M[i].w() << "(" << o_obj.M[i].z() << ") " << o_obj.M[i].y() << "\n";
        writeS << "\tV " << o_obj.V[i].x() << " " << o_obj.V[i].y() << "\n";
        writeS << "\tU " << o_obj.U[i].x() << " " << o_obj.U[i].y() << "\n";
        writeS << "\tSigma " << o_obj.Sig[i].x() << " " << o_obj.Sig[i].y() << "\n";
    }
    file.close();
    return 0;
}

void OGLWidget::fill_o(outcoming_objects *o_obj){
    o_obj->N[0].setX(12.3);
    o_obj->N[0].setY(11.3);
    o_obj->Q[0].setX(10.32);
    o_obj->Q[0].setY(9.31);
    o_obj->V[0].setX(1.32);
    o_obj->V[0].setY(7.31);
    o_obj->U[0].setX(121.32);
    o_obj->U[0].setY(145.321);
    o_obj->Sig[0].setX(120.32);
    o_obj->Sig[0].setY(91.1);
    o_obj->M[0].setX(0.32);
    o_obj->M[0].setY(2.31);
    o_obj->M[0].setZ(50.32);
    o_obj->M[0].setW(80);
}

bool OGLWidget::behindP(int *r){
    QVector2D click;
    click.setX(x_left + mPosition.x()/460 * abs(x_left - x_right));
    click.setY(y_right - mPosition.y()/380 * abs(y_left - y_right));
    for(size_t i = 0; i < (size_t)i_obj.kp.size(); i++){
        if(click.distanceToPoint(i_obj.kp[i]) <= 0.02 * scale){
            *r = i;
            return true;
        }
    }
    return false;
}

float OGLWidget::modelSize(){
    QVector2D min = {i_obj.kp[0].x(), i_obj.kp[0].y()};
    QVector2D max = {i_obj.kp[0].x(), i_obj.kp[0].y()};
    for(size_t i = 0; i < (size_t)i_obj.kp.size(); i++){
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


void OGLWidget::flushFile(){
    i_obj.clear();
    repaint();
}

void OGLWidget::addPoint(float x, float y){
    i_obj.kp.append({x, y}); //{координата Х, координата У}
}

void OGLWidget::addLine(int p1, int p2){
    i_obj.l.append({(float)p1, (float)p2}); //{номер точки 1, номер точки 2}
}

void OGLWidget::addP(int pNum, float value, int axis){
    i_obj.P.append({(float)pNum, value, (float)axis}); //{номер точки, значение, ось действия}
}

void OGLWidget::addQ(int kNum, float value1, float value2, int axis){
    i_obj.q.append({(float)kNum, value1, value2, (float)axis}); //{номер стержня, значение слева, значение справа, ось действия}
}

void OGLWidget::addM(int pNum, float value, int axis){
    i_obj.m.append({(float)pNum, value, (float)axis}); //{номер точки, значение, ось действия}
}

void OGLWidget::addR(int pNum, float value, int axis){
    i_obj.r.append({(float)pNum, value, (float)axis}); //{номер точки, значение, ось действия}
}

void OGLWidget::addU(int pNum, float value, int axis){
    i_obj.u.append({(float)pNum, value, (float)axis}); //{номер точки, значение, ось действия}
}
