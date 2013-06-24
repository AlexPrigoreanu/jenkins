#include <QtWidgets>

#include "glwidget.h"
#include "window.h"

//! [0]
Window::Window() //finestra di view con relativi tre slider (da togleire)
{
    glWidget  = new GLWidget;
/*
    chooseCamera_1 = new QRadioButton("Prima persona", this);
    chooseCamera_1->setDown(TRUE);
    chooseCamera_2 = new QRadioButton("Centra all'origine", this);
*/
    checkGrid = new QCheckBox("Grid");
    checkGrid->setCheckState(Qt::Checked);

    checkLines = new QCheckBox("Lines");
    checkLines->setCheckState(Qt::Unchecked);

    checkAxis = new QCheckBox("Y Fxd");
    checkAxis->setCheckState(Qt::Unchecked);

    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();

    fovSlider = createSlider();
    fovSlider->setRange(5, 120);
    fovSlider->setSingleStep(5);
    fovSlider->setTickInterval(5);
    fovSlider->setTickPosition(QSlider::TicksRight);

    connect(fovSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(change_fov(int)));
    connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int)));
    connect(glWidget, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));
    connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int)));
    connect(glWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));
    connect(zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));
    connect(glWidget, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));
    connect(glWidget, SIGNAL(fovChanged(int)), fovSlider, SLOT(setValue(int)));
    connect(checkGrid, SIGNAL(stateChanged(int)), glWidget, SLOT(set_Grid(int)));
    connect(checkLines, SIGNAL(stateChanged(int)), glWidget, SLOT(set_Lines(int)));
    connect(checkAxis, SIGNAL(stateChanged(int)), glWidget, SLOT(set_YAxis(int)));
    connect(xSlider, SIGNAL(sliderReleased ()), this, SLOT(resetValue()));
    connect(ySlider, SIGNAL(sliderReleased ()), this, SLOT(resetValue()));
    connect(zSlider, SIGNAL(sliderReleased ()), this, SLOT(resetValue()));



//! [0]

//! [1]

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(glWidget,0,0,2,2);
    mainLayout->addWidget(xSlider,0,2,1,1);
    mainLayout->addWidget(ySlider,0,3,1,1);
    mainLayout->addWidget(zSlider,0,4,1,1);
    mainLayout->addWidget(fovSlider,0,5,1,1);
    mainLayout->addWidget(checkGrid,1,2,1,1);
    mainLayout->addWidget(checkLines,1,3,1,1);
    mainLayout->addWidget(checkAxis,1,4,1,1);
    //mainLayout->addWidget(chooseCamera_2);

/*
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(glWidget);
    mainLayout->addWidget(xSlider);
    mainLayout->addWidget(ySlider);
    mainLayout->addWidget(zSlider);
    mainLayout->addWidget(fovSlider);
    mainLayout->addWidget(checkGrid);*/

    setLayout(mainLayout);

    xSlider->setValue(0);
    ySlider->setValue(0);
    zSlider->setValue(0);
    fovSlider->setValue(45);
    }
//! [1]

//! [2]
QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(-280*16 , 280 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    slider->setTracking(true);
    slider->setSliderDown ( false );
    slider->setFocusPolicy (Qt::ClickFocus);
    return slider;
}
//! [2]

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void Window::resetValue(){

    xSlider->setValue(0);
    ySlider->setValue(0);
    zSlider->setValue(0);

}


