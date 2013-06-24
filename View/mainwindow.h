#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include "window.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Window* window;
private:
    QMenuBar * menuBar;
    QPushButton * push;

};

#endif // MAINWINDOW_H
