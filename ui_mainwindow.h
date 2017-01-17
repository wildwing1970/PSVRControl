/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *gbxFunctions;
    QPushButton *pbtHeadsetOn;
    QPushButton *pbtHeadsetOff;
    QPushButton *pbtEnableVRTracking;
    QPushButton *pbtEnableVR;
    QPushButton *pbtCinematic;
    QPushButton *pbtRecenter;
    QPushButton *pbtShutdown;
    QGroupBox *gbxStatus;
    QLabel *lblSerial;
    QLabel *lblFirmware;
    QCheckBox *cbHeadsetOn;
    QCheckBox *cbHeadsetWorn;
    QCheckBox *cbCinematic;
    QCheckBox *cbHeadphones;
    QCheckBox *cbMute;
    QSlider *hslVolume;
    QLabel *lblVolume;
    QGroupBox *gbxCinematic;
    QSlider *vslSize;
    QSlider *vslDistance;
    QSlider *vslBrightness;
    QLabel *lblSize;
    QLabel *lblDistance;
    QLabel *lblBrightness;
    QGroupBox *gbxLeds;
    QLabel *lblBrightness_2;
    QSlider *vslLedA;
    QSlider *vslLedB;
    QSlider *vslLedC;
    QSlider *vslLedD;
    QSlider *vslLedE;
    QSlider *vslLedF;
    QSlider *vslLedG;
    QSlider *vslLedH;
    QSlider *vslLedH_2;
    QPushButton *pbtApply;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(710, 285);
        QIcon icon;
        icon.addFile(QStringLiteral("res/psvr.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gbxFunctions = new QGroupBox(centralWidget);
        gbxFunctions->setObjectName(QStringLiteral("gbxFunctions"));
        gbxFunctions->setGeometry(QRect(20, 10, 111, 231));
        pbtHeadsetOn = new QPushButton(gbxFunctions);
        pbtHeadsetOn->setObjectName(QStringLiteral("pbtHeadsetOn"));
        pbtHeadsetOn->setGeometry(QRect(10, 20, 91, 23));
        pbtHeadsetOff = new QPushButton(gbxFunctions);
        pbtHeadsetOff->setObjectName(QStringLiteral("pbtHeadsetOff"));
        pbtHeadsetOff->setGeometry(QRect(10, 50, 91, 23));
        pbtEnableVRTracking = new QPushButton(gbxFunctions);
        pbtEnableVRTracking->setObjectName(QStringLiteral("pbtEnableVRTracking"));
        pbtEnableVRTracking->setGeometry(QRect(10, 80, 91, 23));
        pbtEnableVR = new QPushButton(gbxFunctions);
        pbtEnableVR->setObjectName(QStringLiteral("pbtEnableVR"));
        pbtEnableVR->setGeometry(QRect(10, 110, 91, 23));
        pbtCinematic = new QPushButton(gbxFunctions);
        pbtCinematic->setObjectName(QStringLiteral("pbtCinematic"));
        pbtCinematic->setGeometry(QRect(10, 140, 91, 23));
        pbtRecenter = new QPushButton(gbxFunctions);
        pbtRecenter->setObjectName(QStringLiteral("pbtRecenter"));
        pbtRecenter->setGeometry(QRect(10, 170, 91, 23));
        pbtShutdown = new QPushButton(gbxFunctions);
        pbtShutdown->setObjectName(QStringLiteral("pbtShutdown"));
        pbtShutdown->setGeometry(QRect(10, 200, 91, 23));
        gbxStatus = new QGroupBox(centralWidget);
        gbxStatus->setObjectName(QStringLiteral("gbxStatus"));
        gbxStatus->setGeometry(QRect(140, 10, 161, 231));
        lblSerial = new QLabel(gbxStatus);
        lblSerial->setObjectName(QStringLiteral("lblSerial"));
        lblSerial->setGeometry(QRect(10, 20, 141, 16));
        lblFirmware = new QLabel(gbxStatus);
        lblFirmware->setObjectName(QStringLiteral("lblFirmware"));
        lblFirmware->setGeometry(QRect(10, 40, 141, 16));
        cbHeadsetOn = new QCheckBox(gbxStatus);
        cbHeadsetOn->setObjectName(QStringLiteral("cbHeadsetOn"));
        cbHeadsetOn->setGeometry(QRect(10, 70, 141, 17));
        cbHeadsetWorn = new QCheckBox(gbxStatus);
        cbHeadsetWorn->setObjectName(QStringLiteral("cbHeadsetWorn"));
        cbHeadsetWorn->setGeometry(QRect(10, 90, 141, 17));
        cbCinematic = new QCheckBox(gbxStatus);
        cbCinematic->setObjectName(QStringLiteral("cbCinematic"));
        cbCinematic->setGeometry(QRect(10, 110, 141, 17));
        cbHeadphones = new QCheckBox(gbxStatus);
        cbHeadphones->setObjectName(QStringLiteral("cbHeadphones"));
        cbHeadphones->setGeometry(QRect(10, 130, 141, 17));
        cbMute = new QCheckBox(gbxStatus);
        cbMute->setObjectName(QStringLiteral("cbMute"));
        cbMute->setGeometry(QRect(10, 150, 141, 17));
        hslVolume = new QSlider(gbxStatus);
        hslVolume->setObjectName(QStringLiteral("hslVolume"));
        hslVolume->setGeometry(QRect(10, 200, 141, 22));
        hslVolume->setMaximum(50);
        hslVolume->setOrientation(Qt::Horizontal);
        lblVolume = new QLabel(gbxStatus);
        lblVolume->setObjectName(QStringLiteral("lblVolume"));
        lblVolume->setGeometry(QRect(10, 180, 141, 16));
        gbxCinematic = new QGroupBox(centralWidget);
        gbxCinematic->setObjectName(QStringLiteral("gbxCinematic"));
        gbxCinematic->setGeometry(QRect(310, 10, 101, 201));
        vslSize = new QSlider(gbxCinematic);
        vslSize->setObjectName(QStringLiteral("vslSize"));
        vslSize->setGeometry(QRect(10, 49, 22, 141));
        vslSize->setMinimum(26);
        vslSize->setMaximum(80);
        vslSize->setValue(80);
        vslSize->setOrientation(Qt::Vertical);
        vslDistance = new QSlider(gbxCinematic);
        vslDistance->setObjectName(QStringLiteral("vslDistance"));
        vslDistance->setGeometry(QRect(40, 49, 22, 141));
        vslDistance->setMinimum(20);
        vslDistance->setMaximum(50);
        vslDistance->setValue(50);
        vslDistance->setOrientation(Qt::Vertical);
        vslBrightness = new QSlider(gbxCinematic);
        vslBrightness->setObjectName(QStringLiteral("vslBrightness"));
        vslBrightness->setGeometry(QRect(70, 49, 22, 141));
        vslBrightness->setMaximum(32);
        vslBrightness->setValue(32);
        vslBrightness->setOrientation(Qt::Vertical);
        lblSize = new QLabel(gbxCinematic);
        lblSize->setObjectName(QStringLiteral("lblSize"));
        lblSize->setGeometry(QRect(10, 20, 21, 21));
        lblSize->setPixmap(QPixmap(QString::fromUtf8(":/res/icoSize.png")));
        lblSize->setScaledContents(true);
        lblDistance = new QLabel(gbxCinematic);
        lblDistance->setObjectName(QStringLiteral("lblDistance"));
        lblDistance->setGeometry(QRect(40, 20, 21, 21));
        lblDistance->setPixmap(QPixmap(QString::fromUtf8(":/res/icoDistance.png")));
        lblDistance->setScaledContents(true);
        lblBrightness = new QLabel(gbxCinematic);
        lblBrightness->setObjectName(QStringLiteral("lblBrightness"));
        lblBrightness->setGeometry(QRect(70, 20, 21, 21));
        lblBrightness->setPixmap(QPixmap(QString::fromUtf8(":/res/icoBrigtness.png")));
        lblBrightness->setScaledContents(true);
        gbxLeds = new QGroupBox(centralWidget);
        gbxLeds->setObjectName(QStringLiteral("gbxLeds"));
        gbxLeds->setGeometry(QRect(420, 10, 281, 231));
        lblBrightness_2 = new QLabel(gbxLeds);
        lblBrightness_2->setObjectName(QStringLiteral("lblBrightness_2"));
        lblBrightness_2->setGeometry(QRect(10, 20, 261, 101));
        lblBrightness_2->setPixmap(QPixmap(QString::fromUtf8(":/res/LEDIdentification.png")));
        lblBrightness_2->setScaledContents(true);
        vslLedA = new QSlider(gbxLeds);
        vslLedA->setObjectName(QStringLiteral("vslLedA"));
        vslLedA->setGeometry(QRect(10, 130, 22, 91));
        vslLedA->setMinimum(0);
        vslLedA->setMaximum(100);
        vslLedA->setValue(100);
        vslLedA->setOrientation(Qt::Vertical);
        vslLedA->setInvertedAppearance(false);
        vslLedA->setInvertedControls(false);
        vslLedA->setTickPosition(QSlider::NoTicks);
        vslLedA->setTickInterval(0);
        vslLedB = new QSlider(gbxLeds);
        vslLedB->setObjectName(QStringLiteral("vslLedB"));
        vslLedB->setGeometry(QRect(40, 130, 22, 91));
        vslLedB->setMinimum(20);
        vslLedB->setMaximum(100);
        vslLedB->setValue(100);
        vslLedB->setOrientation(Qt::Vertical);
        vslLedB->setInvertedAppearance(false);
        vslLedB->setInvertedControls(false);
        vslLedB->setTickPosition(QSlider::NoTicks);
        vslLedB->setTickInterval(0);
        vslLedC = new QSlider(gbxLeds);
        vslLedC->setObjectName(QStringLiteral("vslLedC"));
        vslLedC->setGeometry(QRect(70, 130, 22, 91));
        vslLedC->setMaximum(100);
        vslLedC->setValue(100);
        vslLedC->setOrientation(Qt::Vertical);
        vslLedC->setInvertedAppearance(false);
        vslLedC->setInvertedControls(false);
        vslLedC->setTickPosition(QSlider::NoTicks);
        vslLedD = new QSlider(gbxLeds);
        vslLedD->setObjectName(QStringLiteral("vslLedD"));
        vslLedD->setGeometry(QRect(100, 130, 22, 91));
        vslLedD->setMaximum(100);
        vslLedD->setValue(100);
        vslLedD->setOrientation(Qt::Vertical);
        vslLedD->setInvertedAppearance(false);
        vslLedD->setInvertedControls(false);
        vslLedD->setTickPosition(QSlider::NoTicks);
        vslLedE = new QSlider(gbxLeds);
        vslLedE->setObjectName(QStringLiteral("vslLedE"));
        vslLedE->setGeometry(QRect(130, 130, 22, 91));
        vslLedE->setMaximum(100);
        vslLedE->setValue(100);
        vslLedE->setOrientation(Qt::Vertical);
        vslLedE->setInvertedAppearance(false);
        vslLedE->setInvertedControls(false);
        vslLedE->setTickPosition(QSlider::NoTicks);
        vslLedF = new QSlider(gbxLeds);
        vslLedF->setObjectName(QStringLiteral("vslLedF"));
        vslLedF->setGeometry(QRect(160, 130, 22, 91));
        vslLedF->setMaximum(100);
        vslLedF->setValue(100);
        vslLedF->setOrientation(Qt::Vertical);
        vslLedF->setInvertedAppearance(false);
        vslLedF->setInvertedControls(false);
        vslLedF->setTickPosition(QSlider::NoTicks);
        vslLedG = new QSlider(gbxLeds);
        vslLedG->setObjectName(QStringLiteral("vslLedG"));
        vslLedG->setGeometry(QRect(190, 130, 22, 91));
        vslLedG->setMaximum(100);
        vslLedG->setValue(100);
        vslLedG->setOrientation(Qt::Vertical);
        vslLedG->setInvertedAppearance(false);
        vslLedG->setInvertedControls(false);
        vslLedG->setTickPosition(QSlider::NoTicks);
        vslLedH = new QSlider(gbxLeds);
        vslLedH->setObjectName(QStringLiteral("vslLedH"));
        vslLedH->setGeometry(QRect(220, 130, 22, 91));
        vslLedH->setMaximum(100);
        vslLedH->setValue(100);
        vslLedH->setOrientation(Qt::Vertical);
        vslLedH->setInvertedAppearance(false);
        vslLedH->setInvertedControls(false);
        vslLedH->setTickPosition(QSlider::NoTicks);
        vslLedH_2 = new QSlider(gbxLeds);
        vslLedH_2->setObjectName(QStringLiteral("vslLedH_2"));
        vslLedH_2->setGeometry(QRect(250, 130, 22, 91));
        vslLedH_2->setMaximum(100);
        vslLedH_2->setValue(100);
        vslLedH_2->setOrientation(Qt::Vertical);
        vslLedH_2->setInvertedAppearance(false);
        vslLedH_2->setInvertedControls(false);
        vslLedH_2->setTickPosition(QSlider::NoTicks);
        pbtApply = new QPushButton(centralWidget);
        pbtApply->setObjectName(QStringLiteral("pbtApply"));
        pbtApply->setGeometry(QRect(320, 220, 81, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 710, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PSVRControl", 0));
        gbxFunctions->setTitle(QApplication::translate("MainWindow", "Functions", 0));
        pbtHeadsetOn->setText(QApplication::translate("MainWindow", "Headset On", 0));
        pbtHeadsetOff->setText(QApplication::translate("MainWindow", "Headset Off", 0));
        pbtEnableVRTracking->setText(QApplication::translate("MainWindow", "VR with Tracking", 0));
        pbtEnableVR->setText(QApplication::translate("MainWindow", "VR", 0));
        pbtCinematic->setText(QApplication::translate("MainWindow", "Cinematic", 0));
        pbtRecenter->setText(QApplication::translate("MainWindow", "Recenter", 0));
        pbtShutdown->setText(QApplication::translate("MainWindow", "Shutdown", 0));
        gbxStatus->setTitle(QApplication::translate("MainWindow", "Status", 0));
        lblSerial->setText(QApplication::translate("MainWindow", "Device Serial : unknown", 0));
        lblFirmware->setText(QApplication::translate("MainWindow", "Firmware Version : unknown", 0));
        cbHeadsetOn->setText(QApplication::translate("MainWindow", "Headset On", 0));
        cbHeadsetWorn->setText(QApplication::translate("MainWindow", "Headset Worn", 0));
        cbCinematic->setText(QApplication::translate("MainWindow", "Cinematic ", 0));
        cbHeadphones->setText(QApplication::translate("MainWindow", "Headphones", 0));
        cbMute->setText(QApplication::translate("MainWindow", "Mute Mic", 0));
        lblVolume->setText(QApplication::translate("MainWindow", "Volume", 0));
        gbxCinematic->setTitle(QApplication::translate("MainWindow", "Cinematic", 0));
        lblSize->setText(QString());
        lblDistance->setText(QString());
        lblBrightness->setText(QString());
        gbxLeds->setTitle(QApplication::translate("MainWindow", "LED's", 0));
        lblBrightness_2->setText(QString());
#ifndef QT_NO_TOOLTIP
        vslLedA->setToolTip(QApplication::translate("MainWindow", "LED A", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        vslLedA->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        vslLedB->setToolTip(QApplication::translate("MainWindow", "LED B", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        vslLedB->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        vslLedC->setToolTip(QApplication::translate("MainWindow", "LED C", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        vslLedC->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        vslLedD->setToolTip(QApplication::translate("MainWindow", "LED D", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        vslLedD->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        vslLedE->setToolTip(QApplication::translate("MainWindow", "LED E", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        vslLedE->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        vslLedF->setToolTip(QApplication::translate("MainWindow", "LED F", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        vslLedF->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        vslLedG->setToolTip(QApplication::translate("MainWindow", "LED G", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        vslLedG->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        vslLedH->setToolTip(QApplication::translate("MainWindow", "LED H", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        vslLedH->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        vslLedH_2->setToolTip(QApplication::translate("MainWindow", "LED I", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        vslLedH_2->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pbtApply->setText(QApplication::translate("MainWindow", "Apply", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
