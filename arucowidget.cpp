#include "arucowidget.h"
#include "ui_arucowidget.h"

ArucoWidget::ArucoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArucoWidget)
{
    ui->setupUi(this);
}

ArucoWidget::~ArucoWidget()
{
    delete ui;
}

void ArucoWidget::detectMarkers(cv::Mat *img)
{

}
