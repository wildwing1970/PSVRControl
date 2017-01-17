#include "mainwindow.h"
#include "ui_mainwindow.h"

/// ---------------------------------------------------------------------------
/// \brief MainWindow::MainWindow
///


MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    psvr = new PSVRApi::PSVRContext();
    PSVRApi::PSVRControl *psvrControl = psvr->psvrControl;
    PSVRApi::PSVRSensor *psvrSensor = psvr->psvrSensor;

    // connect info report signal to setInfo
    if(!connect(psvrControl, SIGNAL(infoReport(QString,QString))  , this, SLOT(setInfo(QString,QString))))
        return;
    // connect status report signal to setStatus
    if(!connect(psvrControl, SIGNAL(statusReport(void *)), this, SLOT(setStatus(void *))))
        return;

    if(!connect(psvrControl, SIGNAL(connect(bool)), this, SLOT(onConnect(bool))))
        return;

    psvrControl->start();
    psvrSensor->start();

}

/// ---------------------------------------------------------------------------
/// \brief MainWindow::~MainWindow
///
MainWindow::~MainWindow()
{
    delete ui;
}

/// ---------------------------------------------------------------------------
/// \brief MainWindow::on_pbtHeadsetOn_clicked
///
void MainWindow::on_pbtHeadsetOn_clicked()
{
    psvr->psvrControl->HeadSetPower(true);
}

/// ---------------------------------------------------------------------------
/// \brief MainWindow::on_pbtHeadsetOff_clicked
///
void MainWindow::on_pbtHeadsetOff_clicked()
{
    psvr->psvrControl->HeadSetPower(false);
}

/// ---------------------------------------------------------------------------
/// \brief MainWindow::on_pbtEnableVRTracking_clicked
///
/// This funcion enables the VR mode and the Tracking on the PSVR
///
void MainWindow::on_pbtEnableVRTracking_clicked()
{
    psvr->psvrControl->EnableVR(true);
}

/// ---------------------------------------------------------------------------
/// \brief MainWindow::on_pbtEnableVR_clicked
///
void MainWindow::on_pbtEnableVR_clicked()
{
    psvr->psvrControl->EnableVR(false);
}

/// ---------------------------------------------------------------------------
/// \brief MainWindow::on_pbtCinematic_clicked
///
void MainWindow::on_pbtCinematic_clicked()
{
    psvr->psvrControl->EnableCinematic();
}

/// ---------------------------------------------------------------------------
/// \brief MainWindow::on_pbtRecenter_clicked
///
void MainWindow::on_pbtRecenter_clicked()
{
    psvr->psvrControl->Recenter();
}

/// ---------------------------------------------------------------------------
/// \brief MainWindow::on_pbtShutdown_clicked
///
void MainWindow::on_pbtShutdown_clicked()
{
    psvr->psvrControl->Shutdown();
}
/// ---------------------------------------------------------------------------
/// \brief MainWindow::on_pbtApply_clicked
///
void MainWindow::on_pbtApply_clicked()
{
    psvr->psvrControl->SetCinematic(ui->vslDistance->value(), ui->vslSize->value(), ui->vslBrightness->value(), ui->hslVolume->value());
}

/// ---------------------------------------------------------------------------
/// \brief MainWindow::SetInfo
/// \param firmware
/// \param serial
///
void MainWindow::setInfo(QString firmware, QString serial)
{
    ui->lblFirmware->setText(QString("Firmware : ") + firmware);
    ui->lblSerial->setText(QString("Serial : ") + serial);
    return;
}

void MainWindow::setStatus(void *status) // in connect mit QObject * versuchen
{
    PSVRApi::PSVRStatus *stat = (PSVRApi::PSVRStatus *)status;

    ui->cbHeadsetOn->setChecked(stat->isHeadsetOn);
    ui->cbHeadsetWorn->setChecked(stat->isHeadsetWorn);
    ui->cbCinematic->setChecked(stat->isCinematic);
    ui->cbHeadphones->setChecked(stat->areHeadphonesUsed);
    ui->cbMute->setChecked(stat->isMuted);
    ui->hslVolume->setValue(stat->volume);
    delete stat;
    return;
}

void MainWindow::onConnect(bool isConnected)
{
    ui->gbxFunctions->setEnabled(isConnected);
    ui->gbxStatus->setEnabled(isConnected);
    ui->gbxCinematic->setEnabled(isConnected);
    ui->gbxLeds->setEnabled(isConnected);
    ui->pbtApply->setEnabled(isConnected);

    if(!isConnected)
    {
        ui->lblFirmware->setText("Firmware : unknown");
        ui->lblSerial->setText("Serial : unknown");
    }
}

