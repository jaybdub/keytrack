//View to control camera parameters
//Signal generated when frame is grabbed
//Slot to grab frame

#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <QTimer>

namespace Ui {
class CameraWidget;
}

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWidget(QWidget *parent = 0);
    ~CameraWidget();
    QImage cvMatToQImage( const cv::Mat &inMat );
    void setCaptureDevice(int capture_device);
    void setImageWidth(int image_width);
    void setImageHeight(int image_height);
    void setFrameIntervalMs(int frame_interval_ms);
public slots:
    void grabFrame();
    void showFrame();
    void connectCamera();
    void reconnectCamera();
    void disconnectCamera();
signals:
    void frameGrabbed(cv::Mat *img);
private slots:
    void updateSettingsFromUI();
private:
    //Image
    cv::Mat _img;
    QImage _qimg;
    cv::VideoCapture _cap;
    int _image_height;
    int _image_width;
    int _capture_device;
    int _frame_interval_ms;
    //
    Ui::CameraWidget *ui;
};

#endif // CAMERAWIDGET_H
