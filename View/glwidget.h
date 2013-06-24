#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <time.h>
#include "../View/mainwindow.h"
#include "../View/window.h"
#include "../View/glwidget.h"
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <cmath>
#include <QGLWidget>
#include <QMessageBox>
#include "../View/vcamera.h"
#include <QDialog>
#include "../Model/Scene.h"
#include "../Model/AssimpAdapter.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>


class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mouse(int,int,int,int);    
    CCamera* objCamera;
    float frame;     //fps
    float timebase;  //fps
    clock_t t1;
    clock_t t2;
    float zoomFactor;
    Scene* scenaa;
    aiScene* aiScenaa;
    char* file;
    void ourRender(Scene*);
    void recursive_render(const struct aiScene *scene, const struct aiNode* nd);


public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void draw_grid();
    void change_fov(int val);
    void set_Grid(int val);
    void set_Lines(int val);
    void set_YAxis(int val);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void fovChanged(int val);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void drawAxis();
    void Selection(int x, int y);
    void stopSelection();
    void drawSphere(double r, int lats, int longs);
    void drawText(char * string, float x, float y);
    void drawHud();

private:

    int xRot;
    int yRot;
    int zRot;
    float fov;
    float ratio;
    float w_screen;
    float h_screen;
    int xCursore;
    int yCursore;
    int zCursore;
    bool drawGrid;
    bool drawLines;
    bool YAxis;
    QPoint lastPos;
    QColor qtGreen;
    QColor qtPurple;
    float angle;
    QDialog *a ;

};


#endif
