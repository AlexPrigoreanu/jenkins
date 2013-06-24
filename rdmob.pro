#-------------------------------------------------
#
# Project created by QtCreator 2013-04-23T15:28:46
#
#-------------------------------------------------

VPATH += ../shared
INCLUDEPATH += ../shared

QT       += core gui\
            opengl widgets\

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rdmob
TEMPLATE = app


SOURCES  += main.cpp\
            Controller\Translate.cpp\
            Controller\Transform.cpp\
            Controller\SelectObject.cpp\
            Controller\Scale.cpp\
            Controller\Rotate.cpp\
            Controller\Restrict.cpp\
            Controller\Remove.cpp\
            Controller\EditMaterial.cpp\
            Controller\EditLight.cpp\
            Controller\Controller.cpp\
            Controller\CommandScene.cpp\
            Controller\AddLight.cpp\
            View\vcamera.cpp\
            View\glwidget.cpp\
            View\mainwindow.cpp\
            View\window.cpp\
Model\AssimpAdapter.cpp\
Model\Camera.cpp\
Model\CJSONExp.cpp\
Model\CJSONImporter.cpp\
Model\Colour.cpp\
Model\Constraint.cpp\
Model\Face.cpp\
Model\Importer.cpp\
Model\JSONExp.cpp\
Model\JSONImporter.cpp\
Model\Light.cpp\
Model\Material.cpp\
Model\Matrix4x4.cpp\
Model\Mesh.cpp\
Model\RJSONExporter.cpp\
Model\RJSONImporter.cpp\
Model\Scene.cpp\
Model\SceneExporter.cpp\
Model\SceneImporter.cpp\
Model\SceneObject.cpp\
Model\Setting.cpp\
Model\Texture.cpp\
Model\Vector3D.cpp\
Model\XMLExp.cpp\
Model\XMLImporter.cpp\

HEADERS  += Controller\Translate.h\
            Controller\Transform.h\
            Controller\SelectObject.h\
            Controller\Scale.h\
            Controller\Rotate.h\
            Controller\Restrict.h\
            Controller\Remove.h\
            Controller\EditMaterial.h\
            Controller\EditLight.h\
            Controller\Controller.h\
            Controller\CommandScene.h\
            Controller\AddLight.h\
            View\vcamera.h\
            View\glwidget.h\
            View\mainwindow.h\
            View\window.h\
Model\AssimpAdapter.h\
Model\Camera.h\
Model\CJSONExp.h\
Model\CJSONImporter.h\
Model\Colour.h\
Model\Constraint.h\
Model\Face.h\
Model\Importer.h\
Model\JSONExp.h\
Model\JSONImporter.h\
Model\Light.h\
Model\Material.h\
Model\Matrix4x4.h\
Model\Mesh.h\
Model\RJSONExporter.h\
Model\RJSONImporter.h\
Model\Scene.h\
Model\SceneExporter.h\
Model\SceneImporter.h\
Model\SceneObject.h\
Model\Setting.h\
Model\Texture.h\
Model\Vector3D.h\
Model\XMLExp.h\
Model\XMLImporter.h\

LIBS +=C:\assimpD\code\assimpD.lib

CONFIG +=console

target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl
INSTALLS += target
