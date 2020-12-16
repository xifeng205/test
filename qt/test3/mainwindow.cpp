#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{

}


void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{

}
