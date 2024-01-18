#include "oglwidget.h"

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
            i_obj->kp[c_obj->kp].setX(lst.at(1).toFloat()); //координата X
            i_obj->kp[c_obj->kp].setY(lst.at(2).toFloat()); //координата Y
            c_obj->kp++;
        }
        if(lst.at(0) == "l"){
            i_obj->l[c_obj->l].setX(lst.at(1).toInt()); //номер первой точки
            i_obj->l[c_obj->l].setY(lst.at(2).toInt()); //номер второй точки
            c_obj->l++;
        }
        if(lst.at(0) == "P"){
            i_obj->P[c_obj->P].setX(lst.at(1).toFloat()); //номер точки
            i_obj->P[c_obj->P].setY(lst.at(2).toFloat()); //значение
            i_obj->P[c_obj->P].setZ(lst.at(3).toFloat()); //ось (1-x 2-y 3-z)
            c_obj->P++;
        }
        if(lst.at(0) == "m"){
            i_obj->m[c_obj->m].setX(lst.at(1).toFloat()); //номер точки
            i_obj->m[c_obj->m].setY(lst.at(2).toFloat()); //значение
            i_obj->m[c_obj->m].setZ(lst.at(3).toFloat()); //ось
            c_obj->m++;
        }
        if(lst.at(0) == "q"){
            i_obj->q[c_obj->q].setZ(lst.at(1).toFloat()); //номер стержня
            i_obj->q[c_obj->q].setX(lst.at(2).toFloat()); //значение справа
            i_obj->q[c_obj->q].setY(lst.at(3).toFloat()); //значение слева
            i_obj->q[c_obj->q].setW(lst.at(4).toFloat()); //ось
            c_obj->q++;
        }
        if(lst.at(0) == "u"){
            i_obj->u[c_obj->u].setX(lst.at(1).toFloat()); //номер точки
            i_obj->u[c_obj->u].setY(lst.at(2).toFloat()); //значение
            i_obj->u[c_obj->u].setZ(lst.at(3).toFloat()); //ось
            c_obj->u++;
        }
        if(lst.at(0) == "r"){
            i_obj->r[c_obj->r].setX(lst.at(1).toFloat()); //номер точки
            i_obj->r[c_obj->r].setY(lst.at(2).toFloat()); //значение
            i_obj->r[c_obj->r].setZ(lst.at(3).toFloat()); //ось
            c_obj->r++;
        }
    }
    file.close();
    return 0;
}

int OGLWidget::outFile(QString filename, outcoming_objects o_obj){
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream writeS(&file);
    for(size_t i = 0; i < c_obj.l; i++){
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
    for(size_t i = 0; i < c_obj.kp; i++){
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


void OGLWidget::flushFile(){
    QFile file(i_filename);
    file.open(QIODevice::WriteOnly);
    file.close();
}

void OGLWidget::addPoint(float x, float y){
    QString s1 = "\nkp ";
    s1.append(QString::number(x));
    s1.append(" ");
    s1.append(QString::number(y));
    QFile file(i_filename);
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
    QFile file(i_filename);
    QTextStream writeStream(&file);
    file.open(QIODevice::Append | QIODevice::Text);
    writeStream << s1;
    file.close();
}

void OGLWidget::addP(int pNum, float value, int axis){
    QString s1 = "\nP ";
    s1.append(QString::number(pNum));
    s1.append(" ");
    s1.append(QString::number(value));
    s1.append(" ");
    s1.append(QString::number(axis));
    s1.append(" ");
    QFile file(i_filename);
    QTextStream writeStream(&file);
    file.open(QIODevice::Append | QIODevice::Text);
    writeStream << s1;
    file.close();
}

void OGLWidget::addQ(int kNum, float value1, float value2, int axis){
    QString s1 = "\nq ";
    s1.append(QString::number(kNum));
    s1.append(" ");
    s1.append(QString::number(value1));
    s1.append(" ");
    s1.append(QString::number(value2));
    s1.append(" ");
    s1.append(QString::number(axis));
    s1.append(" ");
    QFile file(i_filename);
    QTextStream writeStream(&file);
    file.open(QIODevice::Append | QIODevice::Text);
    writeStream << s1;
    file.close();
}
