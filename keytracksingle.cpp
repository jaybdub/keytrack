#include "keytracksingle.h"
#include "ui_keytracksingle.h"
#include "camerawidget.h"
#include "arucowidget.h"
#include "serialwidget.h"
#include <aruco/aruco.h>
#include <opencv2/opencv.hpp>

KeytrackSingle::KeytrackSingle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KeytrackSingle)
{
    ui->setupUi(this);


    CameraWidget* camera_widget = new CameraWidget(ui->cameraWidgetTab);
    camera_widget->show();

    ArucoWidget* aruco_widget = new ArucoWidget(ui->arucoWidgetTab);
    aruco_widget->show();

    SerialWidget* serial_widget = new SerialWidget(ui->serialWidgetTab);
    serial_widget->show();

    connect(camera_widget,SIGNAL(frameGrabbed(cv::Mat*)),aruco_widget,SLOT(detectMarkers(cv::Mat*)));
    connect(aruco_widget,SIGNAL(markersDetected(vector<aruco::Marker>)),serial_widget,SLOT(sendArucoMarkers(vector<aruco::Marker>)));
    //connect(camera_widget,SIGNAL(frameGrabbed(cv::Mat*)),aruco_widget,SLOT(detectMarkers(cv::Mat*)));
}

KeytrackSingle::~KeytrackSingle()
{
    delete ui;
}
