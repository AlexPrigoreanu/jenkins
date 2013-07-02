/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QApplication>
#include <QDesktopWidget>
#include "View/mainwindow.h"
#include "View/window.h"
#include "View/glwidget.h"
#include <QDebug>
#include <QWidget>
#include <QtGui>
#include <QMainWindow>
#include <assimp/cimport.h>
#include "Model/AssimpAdapter.h"
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <cmath>
#include<iostream>


/*

int main(int argc, char *argv[])
{

    //testing importazione scena
    const std::string nomeF("/usr/share/glchess/pieces/3d");
    AssimpAdapter* aa = new AssimpAdapter();
    aa->importFile(nomeF);
    aiScene* bellascena=aa->GetScene();
    //testing
}
*/
    // ----------------------------------------------------------------------------
    // Simple sample to prove that Assimp is easy to use with OpenGL.
    // It takes a file name as command line parameter, loads it using standard
    // settings and displays it.
    //
    // If you intend to _use_ this code sample in your app, do yourself a favour
    // and replace immediate mode calls with VBOs ...
    //
    // The vc8 solution links against assimp-release-dll_win32 - be sure to
    // have this configuration built.
    // ----------------------------------------------------------------------------

    #include <stdlib.h>
    #include <stdio.h>

    #include <GL/glut.h>
    // assimp include files. These three are usually needed.
    //#include <assimp/cimport.h>
    #include <assimp/cimport.h>
    #include <assimp/scene.h>
    #include <assimp/postprocess.h>
    //#include <assimp-master/include/assimp/cimport.h>

    // the global Assimp scene object
    const struct aiScene* scene = NULL;
    GLuint scene_list = 0;
    aiVector3D scene_min, scene_max, scene_center;

    // current rotation angle
    static float angle = 0.f;

    #define aisgl_min(x,y) (x<y?x:y)
    #define aisgl_max(x,y) (y>x?y:x)

    // ----------------------------------------------------------------------------
    void reshape(int width, int height)
    {   int xVarnew;
        const double aspectRatio = (float) width / height, fieldOfView = 45.0;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fieldOfView, aspectRatio,
            1.0, 1000.0);  /* Znear and Zfar */
        glViewport(0, 0, width, height);
        int xxxxxxxxxx;
    }
    static const char* fileFuori = "C:/assimp-master/test/models/3DS/k.3ds";

    static AssimpAdapter aaFuori;
    static Scene* pFuori=aaFuori.importFile(fileFuori);
    // ----------------------------------------------------------------------------
    void get_bounding_box_for_node (const struct aiNode* nd,
         aiVector3D* min,
         aiVector3D* max,
         aiMatrix4x4* trafo
    ){
         aiMatrix4x4 prev;
        unsigned int n = 0, t;
        int unreally;
        prev = *trafo;
        aiMultiplyMatrix4(trafo,&nd->mTransformation);

        for (; n < nd->mNumMeshes; ++n) {
            const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
            for (t = 0; t < mesh->mNumVertices; ++t) {

                aiVector3D tmp = mesh->mVertices[t];
                aiTransformVecByMatrix4(&tmp,trafo);

                min->x = aisgl_min(min->x,tmp.x);
                min->y = aisgl_min(min->y,tmp.y);
                min->z = aisgl_min(min->z,tmp.z);

                max->x = aisgl_max(max->x,tmp.x);
                max->y = aisgl_max(max->y,tmp.y);
                max->z = aisgl_max(max->z,tmp.z);
            }
        }

        for (n = 0; n < nd->mNumChildren; ++n) {
            get_bounding_box_for_node(nd->mChildren[n],min,max,trafo);
        }
        *trafo = prev;
        int breal=0;
        int creallllll=0;
    }

    // ----------------------------------------------------------------------------
    void get_bounding_box (aiVector3D* min, aiVector3D* max)
    {
        aiMatrix4x4 trafo;
        aiIdentityMatrix4(&trafo);

        min->x = min->y = min->z =  1e10f;
        max->x = max->y = max->z = -1e10f;
        get_bounding_box_for_node(scene->mRootNode,min,max,&trafo);
    }

    // ----------------------------------------------------------------------------
    void color4_to_float4(const aiColor4D *c, float f[4])
    {
        f[0] = c->r;
        f[1] = c->g;
        f[2] = c->b;
        f[3] = c->a;
    }

    // ----------------------------------------------------------------------------
    void set_float4(float f[4], float a, float b, float c, float d)
    {
        f[0] = a;
        f[1] = b;
        f[2] = c;
        f[3] = d;
        int xasd;
    }

    // ----------------------------------------------------------------------------
    void apply_material(const struct aiMaterial *mtl)
    {
        float c[4];

        GLenum fill_mode;
        int ret1, ret2;
        aiColor4D diffuse;
        aiColor4D specular;
        aiColor4D ambient;
        aiColor4D emission;
        float shininess, strength;
        int two_sided;
        int wireframe;
        unsigned int max;

        set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
            color4_to_float4(&diffuse, c);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

        set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
            color4_to_float4(&specular, c);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

        set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
            color4_to_float4(&ambient, c);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

        set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
            color4_to_float4(&emission, c);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

        max = 1;
        ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
        if(ret1 == AI_SUCCESS) {
            max = 1;
            ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
            if(ret2 == AI_SUCCESS)
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
            else
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
        }
        else {
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
            set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
        }

        max = 1;
        if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
            fill_mode = wireframe ? GL_LINE : GL_FILL;
        else
            fill_mode = GL_FILL;
        glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

        max = 1;
        if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
            glDisable(GL_CULL_FACE);
        else
            glEnable(GL_CULL_FACE);
    }





    // ----------------------------------------------------------------------------
//    void recursive_render (const struct aiScene *sc, const struct aiNode* nd)
//    {
//        unsigned int i;
//        unsigned int n = 0, t;
//        aiMatrix4x4 m = nd->mTransformation;
//        // update transform
//        aiTransposeMatrix4(&m);
//        glPushMatrix();
//        glMultMatrixf((float*)&m);
//        // draw all meshes assigned to this node
//        for (; n < nd->mNumMeshes; ++n) {
//            const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
//            apply_material(sc->mMaterials[mesh->mMaterialIndex]);
//            if(mesh->mNormals == NULL) {
//                glDisable(GL_LIGHTING);
//            } else {
//                glEnable(GL_LIGHTING);
//            }
//            for (t = 0; t < mesh->mNumFaces; ++t) {
//                const struct aiFace* face = &mesh->mFaces[t];
//                GLenum face_mode;
//                switch(face->mNumIndices) {
//                    case 1: face_mode = GL_POINTS; break;
//                    case 2: face_mode = GL_LINES; break;
//                    case 3: face_mode = GL_TRIANGLES; break;
//                    default: face_mode = GL_POLYGON; break;
//                }
//                glBegin(face_mode);
//                for(i = 0; i < face->mNumIndices; i++) {
//                    int index = face->mIndices[i];
//                    if(mesh->mColors[0] != NULL){
//                        glColor4fv((GLfloat*)&mesh->mColors[0][index]);
//                    }
//                    if(mesh->mNormals != NULL)
//                        glNormal3fv(&mesh->mNormals[index].x);
//                    glVertex3fv(&mesh->mVertices[index].x);
//                }
//                glEnd();
//            }
//        }
//        // draw all children
//        for (n = 0; n < nd->mNumChildren; ++n) {
//            recursive_render(sc, nd->mChildren[n]);
//        }
//        glPopMatrix();
//    }

    // ----------------------------------------------------------------------------
    void do_motion (void)
    {
        static GLint prev_time = 0;
        static GLint prev_fps_time = 0;
        static int frames = 0;

        int time = glutGet(GLUT_ELAPSED_TIME);
        angle += (time-prev_time)*0.01;
        prev_time = time;

        frames += 1;
        if ((time - prev_fps_time) > 1000) // update every seconds
        {
            int current_fps = frames * 1000 / (time - prev_fps_time);
            printf("%d fps\n", current_fps);
            frames = 0;
            prev_fps_time = time;
        }


        glutPostRedisplay ();
    }








    // ----------------------------------------------------------------------------
    void display(void)
    {
//        float tmp;

//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();
//        gluLookAt(0.f,0.f,3.f,0.f,0.f,-5.f,0.f,1.f,0.f);

//        // rotate it around the y axis
//        glRotatef(angle,0.1,0.1,0.1);

//        // scale the whole asset to fit into our view frustum
//        tmp = scene_max.x-scene_min.x;
//        tmp = aisgl_max(scene_max.y - scene_min.y,tmp);
//        tmp = aisgl_max(scene_max.z - scene_min.z,tmp);
//        tmp = 1.f / tmp;
//        glScalef(tmp, tmp, tmp);

//            // center the model
//        glTranslatef( -scene_center.x, -scene_center.y, -scene_center.z );

//            // if the display list has not been made yet, create a new one and
//            // fill it with scene contents
//        if(scene_list == 0) {
//            scene_list = glGenLists(1);
//            glNewList(scene_list, GL_COMPILE);
//                // now begin at the root node of the imported data and traverse
//                // the scenegraph by multiplying subsequent local transforms
//                // together on GL's matrix stack.
//            recursive_render(scene, scene->mRootNode);
//            //ourRender(pFuori);
//            glEndList();

//        }

//        glCallList(scene_list);

//        glutSwapBuffers();

//        do_motion();
    }

    // ----------------------------------------------------------------------------
    int loadasset (const char* path)
    {
        // we are taking one of the postprocessing presets to avoid
        // spelling out 20+ single postprocessing flags here.
        scene = aiImportFile(path,aiProcessPreset_TargetRealtime_MaxQuality);

        if (scene) {
            get_bounding_box(&scene_min,&scene_max);
            scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
            scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
            scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
            return 0;
        }
        return 1;
    }

    void stampamatrice(aiMatrix4x4);
    void stampa_gerarchia(aiNode* root){
        cout << "Nome nodo corrente: " <<AssimpAdapter::convertAiString(root->mName) <<"\n";
        if (root->mParent != 0) cout << "Nome nodo padre: " <<AssimpAdapter::convertAiString(root->mParent->mName) <<"\n";
        else cout << "Siamo in nodo radice\n";
        aiMatrix4x4t<float> tr=root->mTransformation;
        aiMatrix4x4t<float> m1,m2,m3,m4,m5;
        aiVector3D position, scaling;
        aiQuaternion rotation;
        tr.Decompose(scaling,rotation,position);
        cout << "Position-> x: " << position.x << "\ty: " << position.y << "\tz: " << position.z <<  "\n";
        cout << "Scaling-> x: " << scaling.x << "\ty: " << scaling.y << "\tz: " << scaling.z <<  "\n";
        cout << "Rotation-> w: " << rotation.w << "\tx: " << rotation.x << "\ty: " << rotation.y << "\tz: " << rotation.z << "\n";
        stampamatrice(tr);
        aiMatrix4x4t<float>::Translation(position,m1);
        aiMatrix4x4t<float>::Scaling(scaling,m2);
        if (root->mNumChildren!=0){
            for (int k=0; k<(int)root->mNumChildren; k++){
                stampa_gerarchia(root->mChildren[k]);
            }
        }
//        cout << "matrice da position: \n";
//        stampamatrice(m1);
//        cout << "matrice da scaling: \n";
//        stampamatrice(m2);
//        cout << "\n";

    }
    void stampamatrice(aiMatrix4x4 tr){
        cout << tr.a1 << " " << tr.a2 << " " << tr.a3 << " " << tr.a4 << "\n";
        cout << tr.b1 << " " << tr.b2 << " " << tr.b3 << " " << tr.b4 << "\n";
        cout << tr.c1 << " " << tr.c2 << " " << tr.c3 << " " << tr.c4 << "\n";
        cout << tr.d1 << " " << tr.d2 << " " << tr.d3 << " " << tr.d4 << "\n";

    }
    // ----------------------------------------------------------------------------
    /*int main(int argc, char **argv)
    {
        struct aiLogStream stream;

        glutInitWindowSize(900,600);
        glutInitWindowPosition(100,100);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutInit(&argc, argv);

        glutCreateWindow("Assimp - Very simple OpenGL sample");
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);

        // get a handle to the predefined STDOUT log stream and attach
        // it to the logging system. It remains active for all further
        // calls to aiImportFile(Ex) and aiApplyPostProcessing.
        stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
        aiAttachLogStream(&stream);

        // ... same procedure, but this stream now writes the
        // log messages to assimp_log.txt
        stream = aiGetPredefinedLogStream(aiDefaultLogStream_FILE,"assimp_log.txt");
        aiAttachLogStream(&stream);

        // the model name can be specified on the command line. If none
        // is specified, we try to locate one of the more expressive test
        // models from the repository (/models-nonbsd may be missing in
        // some distributions so we need a fallback from /models!).







//---------------------------               QUA FA IL CARICAMENTO-----------------------//
        const char* file = "C:/Users/Giulio/Downloads/3DS/warrior.3ds";

        if( 0 != loadasset( argc >= 2 ? argv[1] : file)) {
                if( argc != 1 || (0 != loadasset( file) && 0 != loadasset( file))) {
                    return -1;
                }
            }


        //--------------questo è testing sull'importazione----------------//

        AssimpAdapter aa;
        Scene* p=aa.importFile(file);

        //facciamo qualche stampa per debug sulla scena di assimp
        aiString nam;
        ((aa.GetScene())->mMaterials)[0]->Get(AI_MATKEY_NAME,nam);
        std::cout << "----------STAMPE SU AISCENE-------------- \n";
        std::cout << "Numero di Meshes: " << (aa.GetScene())->mNumMeshes << "\n";
        std::cout << "Nome della prima mesh e: " << AssimpAdapter::convertAiString((*((aa.GetScene())->mMeshes))[0].mName) << "\n";
        std::cout << "Numero di Luci: " << (aa.GetScene())->mNumLights << "\n";
        std::cout << "Nome nodo radice: " << AssimpAdapter::convertAiString(((aa.GetScene())->mRootNode)->mName) << "\n";
        std::cout << "Numero di Facce prima Mesh: " << ((aa.GetScene())->mMeshes)[0]->mNumFaces << "\n";
        std::cout << "Numero di Vertici prima Mesh: " << ((aa.GetScene())->mMeshes)[0]->mNumVertices << "\n";
        std::cout << "Nome del primo Materiale: " << AssimpAdapter::convertAiString(nam) << "\n";
        std::cout << "----------STAMPE SU SCENE IMPORTATA-------------- \n";

        QHash<QString,SceneObject*>& hash = p->getObj();
        aiScene* s=aa.GetScene();
        int j=0;
        for (QHash<QString, SceneObject*>::Iterator i=hash.begin();i!=hash.end();i++){
            Mesh* point = dynamic_cast<Mesh*>(i.value());
            if(point){
                std::cout << i.value()->getName().toStdString() << "\n";
                for (int k=0;k<s->mMeshes[j]->mNumFaces;k++){ //ciclo sulle facce
                    for (int m=0; m<s->mMeshes[j]->mFaces[k].mNumIndices;m++){ //ciclo sui vertici per faccia
                        double a=s->mMeshes[j]->mVertices[(s->mMeshes[j]->mFaces[k].mIndices[m])].x;
                        //std::cout << a <<" "<< p->getFaces()[k].getVerticesArray()[m].getX()<< "\n";
                    }
                }
            }
            j++;
    }




        glClearColor(0.1f,0.1f,0.1f,1.f);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);    // Uses default lighting parameters

        glEnable(GL_DEPTH_TEST);

        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
        glEnable(GL_NORMALIZE);

        // XXX docs say all polygons are emitted CCW, but tests show that some aren't.
        if(getenv("MODEL_IS_BROKEN"))
            glFrontFace(GL_CW);

        glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

        glutGet(GLUT_ELAPSED_TIME);
        glutMainLoop();

        // cleanup - calling 'aiReleaseImport' is important, as the library
        // keeps internal resources until the scene is freed again. Not
        // doing so can cause severe resource leaking.
        aiReleaseImport(scene);

        // We added a log stream to the library, it's our job to disable it
        // again. This will definitely release the last resources allocated
        // by Assimp.
        aiDetachAllLogStreams();
        return 0;
    }




















    /*

    QApplication app(argc, argv);
    //QListView* banana= new QListView();
    //banana.show();
    QMainWindow* banana =new QMainWindow();
    banana->show();

    return app.exec();*/



    int main(int argc, char *argv[])
    {
        QApplication app(argc, argv);
        MainWindow w;
        //w.window->glWidget->paintGL();
        w.show();

        qDebug() << "Avvio";

        //Window * a  = new Window();

        //a->show();
        return app.exec();
    }

