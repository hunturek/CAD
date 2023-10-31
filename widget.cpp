#include "widget.h"

widget::widget(QWidget *parent)
    : QOpenGLWidget{parent}
{
    std::fstream clear_file(filename, std::ios::out);
    clear_file.close();
    openFile(filename,1);
}

void widget::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
}

void widget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
}

void widget::paintGL() {
  glLoadIdentity();
  glDisable(GL_BLEND);
  glMatrixMode(GL_PROJECTION);
  glOrtho(-1, 1, -1, 1, -10, 10);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < syst.amountFacets; ++i) {
          glBegin(GL_LINE_LOOP);
          for (int j = 0; j < syst.face[i].count; ++j) {
            int n = syst.face[i].f[j];
            glVertex3d(syst.vert.coord[n].x, syst.vert.coord[n].y,
                       syst.vert.coord[n].z);
          }
          glEnd();
        }
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_POINT_SPRITE);
    glPointSize(10);
    for (int i = 0; i < syst.amountFacets; ++i) {
            glBegin(GL_POINTS);
            //  glColor3f(1.0f, 0.0f, 0.0f); //цвет отображения
            for (int j = 0; j < syst.face[i].count; ++j) {
              int n = syst.face[i].f[j];
              glVertex3d(syst.vert.coord[n].x, syst.vert.coord[n].y,
                         syst.vert.coord[n].z);
            }
            glEnd();
          }
}

void widget::add_point(double x, double y, double z){
    std::string s1 = "\nv ";
    s1.append(std::to_string(x));
    s1.append(" ");
    s1.append(std::to_string(y));
    s1.append(" ");
    s1.append(std::to_string(z));
    file.open(filename,std::ios::app);
    file << s1;
    file.close();
    openFile(filename, 1);
    update();
}

void widget::add_line(int p_num1, int p_num2){
    std::string s1 = "\nf ";
    s1.append(std::to_string(p_num1));
    s1.append(" ");
    s1.append(std::to_string(p_num2));
    s1.append(" ");
    s1.append(std::to_string(p_num1));
    file.open(filename,std::ios::app);
    file << s1;
    file.close();
    openFile(filename, 1);
    update();
}

void widget::openFile(char *filename, int fileStatus) {
    if (fileStatus != 0) res_free(&syst);
    flag = obj_counter(filename, &syst);
    flag = matrix_fill(filename, &syst);
    if (syst.vert.amountVert == 0) flag = -1;
    if (flag == 0) {
      center_frames(&syst);
      resize_frames(&syst, 0.5);
      update();
    }
}
