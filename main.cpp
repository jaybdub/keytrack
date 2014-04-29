#include "keytracksingle.h"
#include "keytrackserial.h"
#include "camerawidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KeytrackSingle window;
    /*KeytrackSerial serial_widget1;
    KeytrackSerial serial_widget2;
    window.show();
    serial_widget1.show();
    serial_widget2.show();*/
    CameraWidget cam;
    cam.setCaptureDevice(0);
    cam.setImageWidth(640);
    cam.setImageHeight(480);
    cam.connectCamera();
    cam.show();
    return a.exec();
}
