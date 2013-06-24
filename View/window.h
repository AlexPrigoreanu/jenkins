
#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QRadioButton>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
class QSlider;
QT_END_NAMESPACE
//! [0]
class GLWidget;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    GLWidget *glWidget;

public slots:
    void resetValue();

protected:
    void keyPressEvent(QKeyEvent *event);


private:
    QSlider *createSlider();

    QRadioButton *chooseCamera_1;
    QRadioButton *chooseCamera_2;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QSlider *fovSlider;
    QCheckBox * checkGrid;
    QCheckBox * checkLines;
    QCheckBox * checkAxis;
};
//! [0]

#endif
