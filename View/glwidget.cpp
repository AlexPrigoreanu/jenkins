#include <QtWidgets>
#include <QtOpenGL>
#include <QDebug>
#include <math.h>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <GL/glut.h>
#include "../View/glwidget.h"
#include "../View/vcamera.h"
#include <iostream>
#include <QHash>
#include "../Model/SceneObject.h"
#include <QString>
#include "../Model/Scene.h"
#include <time.h>


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "glaux.lib")
#pragma comment( lib, "winmm.lib" )


#define BUFSIZE 512
GLuint selectBuf[BUFSIZE];

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif



GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    xCursore= 0;
    yCursore= 0;
    zCursore= 0;

    frame=0;
    timebase=0;

    drawGrid = true;
    drawLines= false;
    YAxis= false;

    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
    setFocusPolicy (Qt::ClickFocus);
    grabKeyboard();

    objCamera = new CCamera();


    const char* path="C:/assimp-master/test/models/3DS/k.3ds";
    SceneImporter* aa = new AssimpAdapter();
    aiScenaa = const_cast<aiScene*>(aiImportFile(path,aiProcessPreset_TargetRealtime_MaxQuality));
    //    if (scenaa) {
    //        get_bounding_box(&scene_min,&scene_max);
    //        scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
    //        scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
    //        scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
    //    }
    Scene * nuovo=aa->importFile(path);
    scenaa=nuovo;

}



void GLWidget::recursive_render (const struct aiScene *scene, const struct aiNode* nd)
{
    unsigned int i;
    unsigned int n = 0, t;
    aiMatrix4x4 m = nd->mTransformation;
    // update transform
    aiTransposeMatrix4(&m);
    glPushMatrix();
    glMultMatrixf((float*)&m);
    // draw all meshes assigned to this node
    for (; n < nd->mNumMeshes; ++n) {
        const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
        //apply_material(scene->mMaterials[mesh->mMaterialIndex]);
        if(mesh->mNormals == NULL) {
            glDisable(GL_LIGHTING);
        } else {
            glEnable(GL_LIGHTING);
        }
        for (t = 0; t < mesh->mNumFaces; ++t) {
            const struct aiFace* face = &mesh->mFaces[t];
            GLenum face_mode;
            switch(face->mNumIndices) {
            case 1: face_mode = GL_POINTS; break;
            case 2: face_mode = GL_LINES; break;
            case 3: face_mode = GL_TRIANGLES; break;
            default: face_mode = GL_POLYGON; break;
            }
            glBegin(face_mode);
            for(i = 0; i < face->mNumIndices; i++) {
                int index = face->mIndices[i];
                if(mesh->mColors[0] != NULL){
                    glColor4fv((GLfloat*)&mesh->mColors[0][index]);
                }
                if(mesh->mNormals != NULL)
                    glNormal3fv(&mesh->mNormals[index].x);
                glVertex3fv(&mesh->mVertices[index].x);
            }
            glEnd();
        }
    }
    // draw all children
    for (n = 0; n < nd->mNumChildren; ++n) {
        recursive_render(scene, nd->mChildren[n]);
    }
    glPopMatrix();
}





GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(700, 700);
}


void GLWidget::setXRotation(int angle)
{
    if (xCursore<=angle) {objCamera->Move_Camera( CAMERASPEED);}
    else objCamera->Move_Camera( -CAMERASPEED);
    xCursore=angle;
    updateGL();
}


void GLWidget::setYRotation(int angle)
{
    if (yCursore<=angle) {objCamera->Strafe_Camera( CAMERASPEED,YAxis);}
    else objCamera->Strafe_Camera( -CAMERASPEED,YAxis);
    yCursore=angle;
    updateGL();
}


void GLWidget::setZRotation(int angle)
{

    double fangle=angle;

    if (zCursore<0) zCursore=-zCursore;
    if (angle<0) angle=-angle;

    if (zCursore<angle) {
        objCamera->mPos.y  = (objCamera->mPos.y  + (fangle/10000));
        objCamera->mView.y  = (objCamera->mView.y  + (fangle/10000));
    }
    else {
        objCamera->mPos.y  = (objCamera->mPos.y  - (fangle/10000));
        objCamera->mView.y  = (objCamera->mView.y  - (fangle/10000));
    }
    zCursore=angle;
    updateGL();
}


void GLWidget::initializeGL()
{
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    /*glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0,0,0, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);*/
    glClearColor(0.55f,0.55f,0.55f,0.5f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);  ///ANTIALIASING,FORTE DECREMENTO PRESTAZIONALE
    glEnable(GL_MULTISAMPLE);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glDepthFunc(GL_LEQUAL);										// Type Of Depth Testing
    glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending (disable alpha testing)
    glEnable(GL_BLEND);											// Enable Blending       (disable alpha testing)
    //	glAlphaFunc(GL_GREATER,0.1f);								// Set Alpha Testing     (disable blending)
    //	glEnable(GL_ALPHA_TEST);									// Enable Alpha Testing  (disable blending)
    glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
    glEnable(GL_CULL_FACE);										// Remove Back Face
    //    glEnable(GL_LIGHTING);
    //    glEnable(GL_LIGHT0);

    GLfloat lightpos[] = {.5, 1., 1., 0.};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    objCamera->Position_Camera(300,300, 300,	0, 0, 0,   0, 1, 0);
    fov = 45.0f;


}

void GLWidget::ourRender(Scene *sc){
    this->t1= clock();
    std::cout << "tempo 0" << "\t";
    QHash<QString, SceneObject*>& hash=sc->getObj();
    this->t2=clock();
    double diff= (double)(t2-t1);
    std::cout << "tempo trascorso get qhash "<< diff/(double)CLOCKS_PER_SEC << "\n";
    int counter =0;

//    this->t1=clock();
//    std::cout << "tempo 0" << "\t";
    aiMatrix4x4 m;
    for (QHash<QString,SceneObject*>::ConstIterator i = hash.begin();i!=hash.end();++i) {

        aiTransposeMatrix4(&m);
        glPushMatrix();
        Mesh* p = dynamic_cast<Mesh*>(i.value());
        glMultMatrixf((float*) &m);

        if(p){

            QList<Face>& faccie=p->getFaces();
            int numerofacce=faccie.count();
//            this->t1= clock();
//            std::cout << "tempo 0" << "\t";
            for (int t = 0; t < numerofacce; ++t) {
                Face& f = faccie[t];
                GLenum face_mode;
                QList<Vector3D>& lista2 = f.getVerticesArray();
                Vector3D* lista=f.arrayVertici;
                //if (counter ==0) std::cout << lista[0].pos[0]<< "\t";

                switch(f.getVerticesArray().count()) {
                case 1:
                    face_mode = GL_POINTS;
                    glBegin(face_mode);
                    glVertex3fv((GLfloat*)lista[0].pos);
                    break;
                case 2:
                    face_mode = GL_LINES;
                    glBegin(face_mode);
                    glVertex3fv((GLfloat*)lista[0].pos);
                    glVertex3fv((GLfloat*)lista[1].pos);
                    break;
                case 3:
                    face_mode = GL_TRIANGLES;
                    glBegin(face_mode);
                    glVertex3fv(&lista[0].pos[0]);
                    glVertex3fv(&lista[1].pos[0]);
                    glVertex3fv(&lista[2].pos[0]);
                    break;
                default: face_mode = GL_POLYGON; break;
                }
                glEnd();
            }
//            this->t2=clock();
//            double diff= (double)(t2-t1);
//            std::cout << "tempo trascorso ciclo facce "<< diff/(double)CLOCKS_PER_SEC << "\n";
        }
        glPopMatrix();
        //molt+=13;
        counter++;
    }
//    this->t2=clock();
//    diff= (double)(t2-t1);
//    std::cout << "tempo trascorso ciclo facce "<< diff/(double)CLOCKS_PER_SEC << "\n";
    glPopMatrix();
}



void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    ///////////////////////////////////////////////////////////////////////////////MINICAMERA

    glViewport (0, h_screen-200, 200, 200); //2

    gluLookAt(objCamera->mPos.x,  objCamera->mPos.y+25,  objCamera->mPos.z,
              objCamera->mPos.x-(float)2*fov/40, 0, objCamera->mPos.z-(float)2*fov/40,
              1,0,1); //MINICAMERA MOBILE

    /*gluLookAt(10,  20,  10,
                  10, 0, 10,
                  1,0,1);*/   //MINICAMERA FISSA (ONLY FOV POSSIBILE)

    if (drawLines) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    if (drawGrid) draw_grid();
    drawAxis();

    glTranslatef(5,2,3);
    glColor3ub(255,255,0);
    glutSolidTorus(0.5, 1.2, 11, 11);
    glTranslatef(-5,-2,-3);
    glTranslatef(objCamera->mPos.x,objCamera->mPos.y,objCamera->mPos.z);
    glColor3ub(208,32,144);
    glutSolidSphere(0.4, 22, 22);
    glTranslatef(-objCamera->mPos.x,-objCamera->mPos.y,-objCamera->mPos.z);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    ///////////////////////////////////////////////////////////////////////////////END_MINICAMERA*/
    glClear( GL_DEPTH_BUFFER_BIT);
    ///////////////////////////////////////////////////////////////////////////////HUD 2D

    glViewport (w_screen-130, h_screen-200, 200, 200); //2
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 200, 200, 0.0, -1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_DEPTH_BUFFER_BIT);
    drawHud();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //////////////////////////////////////////////////////////////////////////////////END_HUD 2D
    //////////////////////////////////////////////////////////////////////////////////MAINCAMERA

    glViewport (0, 0, w_screen, h_screen);

    if (YAxis){
        gluLookAt(objCamera->mPos.x,  objCamera->mPos.y,  objCamera->mPos.z,
                  0, objCamera->mView.y, 0,
                  objCamera->mUp.x,   objCamera->mUp.y,   objCamera->mUp.z);        //camera intorno all'asse delle y
    }else{
        gluLookAt(objCamera->mPos.x,  objCamera->mPos.y,  objCamera->mPos.z,
                  objCamera->mView.x, objCamera->mView.y, objCamera->mView.z,
                  objCamera->mUp.x,   objCamera->mUp.y,   objCamera->mUp.z);            //camera totalemnete libera
    }
    //DISEGNA QUALSIASI PRIMITIVA SOLO DOPO IL GLULOOKAT (se si usa MINIMONITOR DEVO renderizzare 2 volte la scena (costo da valutare))
    //gluLookAt affects the modelview matrix, so the scene objects.

    if (drawLines) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    draw_grid();
    drawAxis();
    ourRender(this->scenaa);
    //recursive_render(aiScenaa,aiScenaa->mRootNode);

    ///////////////////////////////////////////////////////////////////////////////END_MAINCAMERA
}


void GLWidget::resizeGL(int width, int height)
{
    if (height==0)										// Prevent A Divide By Zero By
    {
        height=1;										// Making Height Equal One
    }

    w_screen=width;
    h_screen=height;
    ratio=width/height;                                 //ricordamelo per lo slider (change_fov)

    glViewport(0,0,width,height);						// Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fov,ratio,0.1f,1000.0f);                //http://www.lighthouse3d.com/tutorials/view-frustum-culling/

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    if (event->buttons() & GLUT_RIGHT_BUTTON){

        qDebug() << "tasto di selezione attivato";
        Selection(event->x(),event->y());
        qDebug() << "Coordinata X: " << event->x() <<" coordinata Y: "<< event->y() ;
        stopSelection();
        updateGL();

    }
}



void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = event->x() - lastPos.x();
    float dy = event->y() - lastPos.y();
    float angle_y = (float)( event->x() - lastPos.x() ) / 100;
    float angle_z = (float)( event->y() - lastPos.y() ) / 100;

    if (dx<0) dx=-dx;
    if (dy<0) dy=-dy;

    if (event->buttons() & Qt::LeftButton) {

        if (dx>dy){
            if (event->x()>lastPos.x()){
                if (YAxis) objCamera->Strafe_Camera(-0.013f,YAxis);
                else objCamera->Rotate_View(-0.013f);
            } else {
                if (YAxis) objCamera->Strafe_Camera(0.013f,YAxis);
                else objCamera->Rotate_View(0.013f);}
        }
        if (dx<dy){
            objCamera->mView.y += angle_z *2;
            objCamera->Rotate_View(-angle_y);
        }
    }

    if (event->buttons() & Qt::RightButton) {

    }
    updateGL();
    lastPos = event->pos();
}


void GLWidget::draw_grid()
{
    if(drawGrid) glColor4f(0,0,0,0.4f);
    else glColor4f(0,0,0,0.1f);
    for(float i = -25; i <= 25; i += 2){
        glBegin(GL_LINES);
        glVertex3f(-25, 0, i);
        glVertex3f(25, 0, i);
        glVertex3f(i, 0,-25);
        glVertex3f(i, 0, 25);
        glEnd();
    }
    if(drawGrid){
        for(float i = -25; i <= 25; i += 2){
            if (i!=0){
                glBegin(GL_LINES);
                glColor4f(0,0,0,0.1f);
                glVertex3f(i, 0, 0);
                glVertex3f(i, 25, 0);
                glVertex3f(0, 0,i);
                glVertex3f(0, 25, i);
                glEnd();
            }
            if (i>0){
                glBegin(GL_LINES);
                glVertex3f(-25, i, 0);
                glVertex3f(25, i, 0);
                glVertex3f(0, i,-25);
                glVertex3f(0, i, 25);
                glEnd();
            }
        }
    }
}

void GLWidget::drawAxis(){
    glLineWidth( 2 );
    glBegin(GL_LINES);                          // assi RGB
    glColor3f (1,0,0);          //x ROSSO
    glVertex3f (0,0,0);
    glVertex3f (55,0,0);

    glColor3f (0,1,0);          //y VERDE
    glVertex3f (0,0,0);
    glVertex3f (0,55,0);

    glColor3f (0,0,5);          //z BLU
    glVertex3f (0,0,0);
    glVertex3f (0,0,55);
    glEnd();
    glLineWidth( 0.5f );
    glBegin(GL_TRIANGLES);
    glColor3ub(66,66,66);
    glVertex3f( 0.0f, 0.12f, 0.0f);
    glVertex3f(0,0, 0.12f);
    glVertex3f( 0.12f,0, 0.12f);
    glVertex3f( 0.0f, 0.12f, 0.0f);
    glVertex3f( 0.12f,0, 0.12f);
    glVertex3f( 0.12f,0, 0);
    glVertex3f( 0.0f, 0.12f, 0.0f);
    glVertex3f( 0.12f,0, 0);
    glVertex3f(0,0, 0);
    glVertex3f( 0.0f, 0.12f, 0.0f);
    glVertex3f(0,0,0);
    glVertex3f(0,0, 0.12f);
    glEnd();
}

void GLWidget::wheelEvent(QWheelEvent *event){
    if (event->delta()<0){
        if (fov<120) fov+=5;
        change_fov(fov);
        fovChanged(fov);
    }
    else{
        if (fov> 5) fov-=5;
        change_fov(fov);
        fovChanged(fov);
    }
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_W) {
        objCamera->Move_Camera( CAMERASPEED);
    }
    else if(event->key() == Qt::Key_Down||event->key() == Qt::Key_S) {
        objCamera->Move_Camera(-CAMERASPEED);
    }
    else if(event->key() == Qt::Key_Left||event->key() == Qt::Key_A) {
        objCamera->Strafe_Camera(-CAMERASPEED,YAxis);
    }
    else if(event->key() == Qt::Key_Right||event->key() == Qt::Key_D) {
        objCamera->Strafe_Camera(CAMERASPEED,YAxis);
    }
    else if(event->key() == Qt::Key_Q) {
        objCamera->mPos.y  = (objCamera->mPos.y  + 0.05f);
        objCamera->mView.y  = (objCamera->mView.y  + 0.05f);
    }
    else if(event->key() == Qt::Key_E) {
        objCamera->mPos.y  = (objCamera->mPos.y  - 0.05f);
        objCamera->mView.y  = (objCamera->mView.y  - 0.05f);
    }
    else if(event->key() == Qt::Key_F) {
        if (fov<120) fov+=5;
        change_fov(fov);
        fovChanged(fov);
    }
    else if(event->key() == Qt::Key_G) {
        if (fov> 5) fov-=5;
        change_fov(fov);
        fovChanged(fov);
    }
    else if(event->key() == Qt::Key_Space) {
        objCamera->Position_Camera(20, 20, 20,	0, 0, 0,   0, 1, 0);
    }
    else if(event->key() == Qt::Key_F1) {
        objCamera->Position_Camera(0, 65, 0,	0, 0, 0,   1, 0, 0);
    }
    else {}
    updateGL();
}


void GLWidget::change_fov(int val){
    fov=val;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov,ratio,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    updateGL();
}

void GLWidget::set_Grid(int val){
    if (val)drawGrid= true;
    else drawGrid = false;
    updateGL();
}

void GLWidget::set_Lines(int val){
    if (val!=0) drawLines= true;
    else drawLines = false;
    updateGL();
}


void GLWidget::drawSphere(double r, int lats, int longs) {
    int i, j;r++;
    for(i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        glColor3ub(255,162,0);
        for(j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
}



void GLWidget::Selection(int x,int y)											// This Is Where Selection Is Done
{
    qDebug() << "dentro al metodo di selezione ";
    GLint viewport[4];

    glSelectBuffer(BUFSIZE,selectBuf);
    glRenderMode(GL_SELECT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glGetIntegerv(GL_VIEWPORT,viewport);
    gluPickMatrix(x,viewport[3]-y,5,5,viewport);
    gluPerspective(fov,ratio,0.1,1000);
    glMatrixMode(GL_MODELVIEW);

    glInitNames();
    ////
    //glTranslatef(-5.0f,-1.0f,-2.0f);
    //drawSphere(1,5,5);
    //glTranslatef(2.0f,0,2.0f);
    //drawSphere(1,5,5);

    glutSolidTorus(1, 2, 55, 55);
    ////
}

void GLWidget::stopSelection() {

    int hits;

    // restoring the original projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glFlush();

    // returning to normal rendering mode
    hits = glRenderMode(GL_RENDER);

    // if there are hits process them
    if (hits != 0)
        qDebug() << "You have a Hit" << hits << " hits";
    //processHits(hits,selectBuf);
}



void GLWidget::set_YAxis(int val){
    if (val)YAxis= true;
    else YAxis= false;
    updateGL();
}

void GLWidget::drawText(char *string,float x,float y)
{
    char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
    }
}




void GLWidget::drawHud(){
    float fps,time;

    frame++;
    time=glutGet(GLUT_ELAPSED_TIME);
    QString str;
    if (time - timebase > 10) {
        fps = frame*1000.0/(time-timebase);
        timebase = time;
        frame = 0;
        str.append(QString("Fps : "));
        str.append(QString("%1").arg(fps));
    }

    QByteArray bafps = str.toLocal8Bit();
    char *strfps = bafps.data();

    drawText(strfps,22,22);

    QString strPos1;
    QString strPos2;
    QString strPos3;

    strPos1.append(QString("Camera -> "));
    strPos1.append(QString("%1").arg(objCamera->mPos.x));
    strPos1.append(QString(" x "));
    strPos2.append(QString("%1").arg(objCamera->mPos.y));
    strPos2.append(QString(" y "));
    strPos3.append(QString("%1").arg(objCamera->mPos.z));
    strPos3.append(QString(" z "));

    QByteArray baPos1 = strPos1.toLocal8Bit();
    char *strPosiz1 = baPos1.data();
    QByteArray baPos2 = strPos2.toLocal8Bit();
    char *strPosiz2 = baPos2.data();
    QByteArray baPos3 = strPos3.toLocal8Bit();
    char *strPosiz3 = baPos3.data();

    glColor3ub(255,255,255);
    glTranslatef(0,12,0);
    drawText(strPosiz1,22,22);
    glTranslatef(47,12,0);
    drawText(strPosiz2,22,22);
    glTranslatef(0,12,0);
    drawText(strPosiz3,22,22);

    QString strView_1;
    QString strView_2;
    QString strView_3;

    strView_1.append(QString("View    ->  "));
    strView_1.append(QString("%1").arg(objCamera->mView.x));
    strView_1.append(QString(" x "));
    strView_2.append(QString("%1").arg(objCamera->mView.y));
    strView_2.append(QString(" y "));
    strView_3.append(QString("%1").arg(objCamera->mView.z));
    strView_3.append(QString(" z "));

    QByteArray baView1 = strView_1.toLocal8Bit();
    char * strView1 = baView1.data();
    QByteArray baView2 = strView_2.toLocal8Bit();
    char * strView2 = baView2.data();
    QByteArray baView3 = strView_3.toLocal8Bit();
    char * strView3 = baView3.data();

    QString strFov;
    strFov.append(QString("FOV    ->   "));
    strFov.append(QString("%1").arg(fov));
    QByteArray baFov= strFov.toLocal8Bit();
    char * str_Fov = baFov.data();

    glColor3ub(255,255,255);
    glTranslatef(-47,12,0);
    drawText( strView1,22,22);
    glTranslatef(47,12,0);
    drawText( strView2,22,22);
    glTranslatef(0,12,0);
    drawText( strView3,22,22);
    glTranslatef(-47,12,0);
    drawText( str_Fov,22,22);
}


