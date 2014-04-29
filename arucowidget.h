//ArucoWidget contains GUI controls for configuring the ArucoAlgorithm
//a slot for connecting to a signal with a CV::Mat camera image as a parameter
//and a signal generated which includes a list of markers detected in the image

#ifndef ARUCOWIDGET_H
#define ARUCOWIDGET_H

#include <QWidget>
#include <aruco/aruco.h>
#include <opencv2/opencv.hpp>

namespace Ui {
class ArucoWidget;
}

class ArucoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArucoWidget(QWidget *parent = 0);
    ~ArucoWidget();
public slots:
    void detectMarkers(cv::Mat* img);
signals:
    //void markersDetected();
private:
    aruco::MarkerDetector _marker_detector;
    QList<aruco::Marker> _markers;
    //_using_calibration is true if a calibration file is being used when detecting markers, false otherwise.
    bool _using_calibration;
    //Marker size is the actual size of one side of the square marker in meters
    float _marker_size;
    //Min and max marker size are parameters used for limiting the apparent sizes of markers detectable
    float _min_marker_size;
    float _max_marker_size;
    //Image width and height used for resizing calibration file
    int _image_width;
    int _image_height;
    Ui::ArucoWidget *ui;
};

#endif // ARUCOWIDGET_H
