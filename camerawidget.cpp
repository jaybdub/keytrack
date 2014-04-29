#include "camerawidget.h"
#include "ui_camerawidget.h"
#include <QTimer>
CameraWidget::CameraWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraWidget)
{
    ui->setupUi(this);

    //Set up a timer for grabbing images from the camera
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(grabFrame()));
    _frame_interval_ms = 30;
    timer->start(_frame_interval_ms);

    //Show the image when it is received
    connect(this,SIGNAL(frameGrabbed(cv::Mat*)),SLOT(showFrame()));

    //Disconnect when disconnect button pressed
    connect(ui->disconnectButton,SIGNAL(clicked()),SLOT(disconnectCamera()));
    //Connect when the connectButton is clicked
    connect(ui->connectButton,SIGNAL(clicked()),SLOT(connectCamera()));
    //Refresh when updateButton is clicked
    connect(ui->updateButton,SIGNAL(clicked()),SLOT(reconnectCamera()));

    connect(ui->captureDeviceBox,SIGNAL(editingFinished()),SLOT(updateSettingsFromUI()));
    connect(ui->imageHeightBox,SIGNAL(editingFinished()),SLOT(updateSettingsFromUI()));
    connect(ui->imageWidthBox,SIGNAL(editingFinished()),SLOT(updateSettingsFromUI()));
}

CameraWidget::~CameraWidget()
{
    delete ui;
}
void CameraWidget::updateSettingsFromUI() {
    setCaptureDevice(ui->captureDeviceBox->text().toInt());
    setImageHeight(ui->imageHeightBox->text().toInt());
    setImageWidth(ui->imageWidthBox->text().toInt());
}

void CameraWidget::reconnectCamera()
{
    disconnectCamera();
    connectCamera();
}
void CameraWidget::connectCamera()
{
    if(_cap.open(_capture_device))
    {
        _cap.set(CV_CAP_PROP_FRAME_HEIGHT, _image_height);
        _cap.set(CV_CAP_PROP_FRAME_WIDTH, _image_width);
    }
}

void CameraWidget::disconnectCamera()
{
    _cap.release();
}

//Grab a frame from the capture device, store the frame in the _img class variable and
//emit a frameGrabbed signal with the image address as a parameter
void CameraWidget::grabFrame()
{
    if(_cap.isOpened()) {
        _cap >> _img;
        _qimg = cvMatToQImage(_img);
        emit frameGrabbed(&_img);
    }
}
void CameraWidget::showFrame()
{
    ui->image->setPixmap(QPixmap::fromImage(_qimg.scaled(ui->image->size(),Qt::KeepAspectRatio)));
    ui->image->show();
}

void CameraWidget::setFrameIntervalMs(int frame_interval_ms)
{
    _frame_interval_ms = frame_interval_ms;
}
void CameraWidget::setCaptureDevice(int capture_device)
{
    _capture_device = capture_device;
}
void CameraWidget::setImageHeight(int image_height)
{
    _image_height = image_height;
    //if(_cap.isOpened())
    //    _cap.set(CV_CAP_PROP_FRAME_HEIGHT, _image_height);
}
void CameraWidget::setImageWidth(int image_width)
{
    _image_width = image_width;
    //if(_cap.isOpened())
    //    _cap.set(CV_CAP_PROP_FRAME_WIDTH, _image_width);
}

inline QImage CameraWidget::cvMatToQImage( const cv::Mat &inMat )
   {
      switch ( inMat.type() )
      {
         // 8-bit, 4 channel
         case CV_8UC4:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

            return image;
         }

         // 8-bit, 3 channel
         case CV_8UC3:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

            return image.rgbSwapped();
         }

         // 8-bit, 1 channel
         case CV_8UC1:
         {
            static QVector<QRgb>  sColorTable;

            // only create our color table once
            if ( sColorTable.isEmpty() )
            {
               for ( int i = 0; i < 256; ++i )
                  sColorTable.push_back( qRgb( i, i, i ) );
            }

            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

            image.setColorTable( sColorTable );

            return image;
         }

         default:
            //qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
      }

      return QImage();
   }
