#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "psvrapi.h"


namespace Ui {
    class MainWindow;
    }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbtHeadsetOn_clicked        ();
    void on_pbtHeadsetOff_clicked       ();
    void on_pbtEnableVRTracking_clicked ();
    void on_pbtEnableVR_clicked         ();
    void on_pbtCinematic_clicked        ();
    void on_pbtRecenter_clicked         ();
    void on_pbtShutdown_clicked         ();
    void on_pbtApply_clicked            ();

private:
    Ui::MainWindow                      *ui;
    PSVRApi::PSVRContext                *psvr;
private slots:
    void setInfo                        (QString firmware, QString serial);
    void setStatus                      (void *status);
    void onConnect                      (bool isConnected);
};

#endif // MAINWINDOW_H
