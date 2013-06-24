#include "mainwindow.h"
#include <QGridLayout>
#include <QtGui>
#include <QToolBar>
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QSlider>
#include "window.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){

    QIcon icon(":/n.png");

    window=new Window();

    //this->setStyleSheet("background-color: grey");
    setWindowTitle("Prototipo 3.1" );

    QPixmap pixmap(15,15);
    pixmap.fill(QColor("red"));
    QIcon redIcon(pixmap);

    QAction *openAction = new QAction(redIcon, "Open", this);
        openAction->setShortcut(tr("CTRL+O"));
    QAction *saveAction = new QAction(icon, "Save As...", this);
        saveAction->setShortcut(tr("CTRL+S"));
    QAction *quitAction = new QAction(icon, "Exit", this);
        quitAction->setShortcut(tr("CTRL+Q"));
    QAction *undoAction = new QAction(icon, "Undo", this);
        undoAction->setShortcut(tr("CTRL+Z"));
    QAction *redoAction = new QAction(icon, "Redo", this);
        redoAction->setShortcut(tr("CTRL+Y"));
    QAction *settingAction = new QAction(icon, "Settings...", this);
        settingAction->setShortcut(tr("CTRL+S"));

    QAction *aboutAction = new QAction(icon, "About", this);
        aboutAction->setShortcut(tr("CTRL+à"));


    QWidget *centralWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout();

    QMenuBar *menubar = new QMenuBar();
    QMenu* menu1 = new QMenu("File");
    menu1->addAction(openAction);
    menu1->addAction(saveAction);
    menu1->addAction(quitAction);
    QMenu* menu2 = new QMenu("Edit");
    menu2->addAction(undoAction);
    menu2->addAction(redoAction);
    menu2->addAction(settingAction);
    QMenu* menu3 = new QMenu("?");
    menu3->addAction(aboutAction);
    menubar->addMenu(menu1);
    menubar->addMenu(menu2);
    menubar->addMenu(menu3);

    menubar->setMaximumHeight(25);

    layout->addWidget(menubar,0,0,1,5);


    layout->addWidget(window,1,0,3,0);

    QToolBar * toolbar_1 =new QToolBar("1");
    QToolBar * toolbar_2 =new QToolBar("2");

    QGroupBox *groupBox_1 = new QGroupBox(tr("Scene Information"));

        QLabel *label1 = new QLabel(tr("# Meshes:"));
        QLabel *label2 = new QLabel(tr("# Vertices"));
        QLabel *label3 = new QLabel(tr("# Lights"));
        QLabel *label4 = new QLabel(tr("# Cameras"));
        QLabel *label5 = new QLabel(tr(""));
        QVBoxLayout *vbox1 = new QVBoxLayout;
        vbox1->addWidget(label1);
        vbox1->addWidget(label2);
        vbox1->addWidget(label3);
        vbox1->addWidget(label4);
        vbox1->addWidget(label5);

        vbox1->addStretch(1);
        groupBox_1->setLayout(vbox1);

    QGroupBox *groupBox_2 = new QGroupBox(tr("Reshaping"));

        QSlider * x_reshaping = new QSlider (Qt::Horizontal);
        x_reshaping->setFocusPolicy (Qt::ClickFocus);
        QSlider * y_reshaping = new QSlider (Qt::Horizontal);
        QSlider * z_reshaping = new QSlider (Qt::Horizontal);
        QVBoxLayout *vbox2 = new QVBoxLayout;

        vbox2->addWidget(x_reshaping);
        vbox2->addWidget(y_reshaping);
        vbox2->addWidget(z_reshaping);
        vbox2->addStretch(1);
        groupBox_2->setLayout(vbox2);

    QGroupBox *groupBox_3 = new QGroupBox(tr("Translation"));

        QSlider * x_translation = new QSlider (Qt::Horizontal);
        QSlider * y_translation = new QSlider (Qt::Horizontal);
        QSlider * z_translation = new QSlider (Qt::Horizontal);

        QVBoxLayout *vbox3 = new QVBoxLayout;
        vbox3->addWidget(x_translation);
        vbox3->addWidget(y_translation);
        vbox3->addWidget(z_translation);
        vbox3->addStretch(1);
        groupBox_3->setLayout(vbox3);

    QGroupBox *groupBox_4 = new QGroupBox(tr("Rotation"));

        QSlider * x_rotation = new QSlider (Qt::Horizontal);
        QSlider * y_rotation = new QSlider (Qt::Horizontal);
        QSlider * z_rotation = new QSlider (Qt::Horizontal);

        QVBoxLayout *vbox4 = new QVBoxLayout;
        vbox4->addWidget(x_rotation);
        vbox4->addWidget(y_rotation);
        vbox4->addWidget(z_rotation);
        vbox4->addStretch(1);
        groupBox_4->setLayout(vbox4);



    toolbar_1->addWidget(groupBox_1);
    toolbar_1->addWidget(groupBox_2);
    toolbar_1->addWidget(groupBox_3);
    toolbar_1->addWidget(groupBox_4);



    QGroupBox *groupBox_5 = new QGroupBox(tr("Scene Hierarchy"));
    QGroupBox *groupBox_6 = new QGroupBox(tr("History"));
    QGroupBox *groupBox_7 = new QGroupBox(tr("Light"));

        QRadioButton * omniRadio = new QRadioButton(tr("&Omni"));
        QRadioButton * spotRadio = new QRadioButton(tr("&Spot"));
        QPushButton * addButton = new QPushButton("Add");
        QPushButton * removeButton = new QPushButton("Remove");
        QVBoxLayout *vbox_light = new QVBoxLayout;
        vbox_light->addWidget(addButton);
        vbox_light->addWidget(removeButton);
        vbox_light->addWidget(omniRadio);
        vbox_light->addWidget(spotRadio);
        vbox_light->addStretch(1);
        groupBox_7->setLayout(vbox_light);

    QGroupBox *groupBox_8 = new QGroupBox(tr("Material"));

        QPushButton * propertyButton = new QPushButton("Properties");
        QVBoxLayout *vbox_material = new QVBoxLayout;
        vbox_material->addWidget(propertyButton);
        vbox_material->addStretch(1);
        groupBox_8->setLayout(vbox_material);

    toolbar_2->addWidget(groupBox_5);
    toolbar_2->addWidget(groupBox_6);
    toolbar_2->addWidget(groupBox_7);
    toolbar_2->addWidget(groupBox_8);



    toolbar_1->setAllowedAreas ( Qt::LeftToolBarArea | Qt::RightToolBarArea | Qt::BottomToolBarArea );
    toolbar_2->setAllowedAreas ( Qt::LeftToolBarArea | Qt::RightToolBarArea | Qt::BottomToolBarArea );


    //toolbar_1->setFixedSize(150, 600); non si mette piu sotto dal momento che è fixed
    //toolbar_2->setFixedSize(150, 600);
    layout->addWidget(toolbar_1);
    layout->addWidget(toolbar_2); // FIXEDDDDDDDDDDDDD


    //this->addToolBar(Qt::RightToolBarArea, toolbar_2); // FLOATTTTTTTTT

    //layout->addWidget(toolbar_1,1,0);
    //layout->addWidget(toolbar_2,2,0);



    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    resize(1024,600);

   // connect(window->glWidget, SIGNAL(xRotationChanged(int)), x_rotation, SLOT(setValue(int)));

}



MainWindow::~MainWindow()
{

}
