#include "arucowidget.h"
#include "ui_arucowidget.h"

ArucoWidget::ArucoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArucoWidget)
{
    ui->setupUi(this);

    _detection_enabled = false;
    _using_calibration = false;
    connect(ui->enableDetectionBox,SIGNAL(toggled(bool)),SLOT(setDetectionEnabled(bool)));
    connect(ui->useCalibrationBox,SIGNAL(toggled(bool)),SLOT(setUsingCalibration(bool)));
    connect(ui->markerSizeBox,SIGNAL(textChanged(QString)),SLOT(updateMarkerSizeFromUI()));
}

ArucoWidget::~ArucoWidget()
{
    delete ui;
}

void ArucoWidget::detectMarkers(cv::Mat *img)
{
    if(_detection_enabled){
        if(!_using_calibration) {
            _marker_detector.detect(*img,_markers);
            //ui->label->setText(QString("Number of markers detected: ").append(QString::number(_markers.size())));
            ui->statusLabel->setText("Detecting markers without calibration");
        }
        else {
            _marker_detector.detect(*img,_markers);
            ui->statusLabel->setText("Detecting markers with calibration");
        }
        if(_markers.size()>0) {
            emit markersDetected(_markers);
        }
    }
    else {
        ui->statusLabel->setText("Detection disabled");
    }
}

void ArucoWidget::disableDetection()
{
    _detection_enabled = false;
}
void ArucoWidget::enableDetection()
{
    _detection_enabled = true;
}
void ArucoWidget::setDetectionEnabled(bool detection_enabled)
{
    _detection_enabled = detection_enabled;
}
void ArucoWidget::setUsingCalibration(bool using_calibration)
{
    _using_calibration = using_calibration;
}
void ArucoWidget::updateMarkerSizeFromUI()
{
    _marker_size = ui->markerSizeBox->text().toFloat();
}
