#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QImage>
#include "control.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_2->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,
            tr("open Image"),".",
            tr("Image Files(*.png *.jpg *jpeg *.bmp)"));
    image = cv::imread(fileName.toStdString().data());
    if (image.data)
        ui->pushButton_2->setEnabled(true);
    QImage img = QImage((const unsigned char *)(image.data),
            image.cols, image.rows, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::on_pushButton_2_clicked()
{
    cv::flip(image, image, 1);
    cv::cvtColor(image, image , CV_BGR2RGB);
    QImage img = QImage((const unsigned char *)(image.data),
            image.cols, image.rows, QImage::Format_RGB888);
    ui->label_2->setPixmap(QPixmap::fromImage(img));
    ui->label_2->resize(ui->label_2->pixmap()->size());
}

void MainWindow::on_pushButton_3_clicked()
{
    cv::Mat output;
    cv::Mat frame;
    Guictrl::get_instance()->vp_set_input();
    Guictrl::get_instance()->vp_set_delay();
    Guictrl::get_instance()->vp_set_processor();
    // while (1) {
        Guictrl::get_instance()->vp_get_frame(output, frame);
        // cv::imshow("djfi", frame);
        QImage img = QImage((const unsigned char *)(frame.data),
                frame.cols, frame.rows, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap::fromImage(img));
        ui->label->resize(ui->label->pixmap()->size());
    // }
}

void MainWindow::on_pushButton_4_clicked()
{

   Guictrl::get_instance()->vp_stop();
}

void MainWindow::on_pushButton_8_clicked()
{

}
