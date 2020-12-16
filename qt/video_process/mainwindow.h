#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstring>
#include <iostream>
#include <iterator>
#include <locale>
#include <iomanip>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/legacy/constants_c.h>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/video/tracking.hpp>
#include <type_traits>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat image;
};

#endif // MAINWINDOW_H

