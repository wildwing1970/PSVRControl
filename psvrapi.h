#ifndef PSVRAPI_H
#define PSVRAPI_H

#include <QThread>
#include <libusb/include/lusb0_usb.h>

///
/// \brief The PSVRApi namespace
///
namespace                      PSVRApi
{
    ///
    /// \brief PSVR_VID
    ///
    static int const           PSVR_VID(0x054C);
    ///
    /// \brief PSVR_PID
    ///
    static int const           PSVR_PID(0x09AF);
    ///
    /// \brief PSVR_EP_COMMAND
    ///
    static int const           PSVR_EP_CMD_WRITE(0x04);
    ///
    /// \brief PSVR_EP_SENSOR
    ///
    static int const           PSVR_EP_CMD_READ(PSVR_EP_CMD_WRITE | 0x80);
    ///
    /// \brief PSVR_EP_SENSOR
    ///
    static int const           PSVR_EP_SENSOR(0x03 | 0x80);
    ///
    /// \brief PSVR_INFO_REPORT
    ///
    static int const           PSVR_INFO_REPORT(0x80);
    ///
    /// \brief PSVR_STATUS_REPORT
    ///
    static int const           PSVR_STATUS_REPORT(0xF0);
    ///
    /// \brief PSVR_UNSOL_REPORT
    ///
    static int const           PSVR_UNSOLICITED_REPORT(0xA0);

    /// ----------------------------------
    /// \brief The PSVR_USB_INTERFACE enum
    ///
    typedef enum
    {
        AUDIO_3D               = 0,
        AUDIO_CONTROL          = 1,
        AUDIO_MIC              = 2,
        AUDIO_CHAT             = 3,
        HID_SENSOR             = 4,
        HID_CONTROL            = 5,
        VS_H264                = 6,
        VS_BULK_IN             = 7,
        HID_CONTROL2           = 8
    } PSVR_USB_INTERFACE;
	/// -----------------------------
	/// \brief The PSVRFrame struct
	///
#pragma pack(1)
	struct PSVRFrame
	{
		byte                   id;
		byte                   status;
		byte                   start;
		byte                   length;
		byte                   data [60];
	};

	struct PSVRSensorFrame
	{
		byte                  buttons;

		byte                  u_b01;

		byte                  volume;

		byte                  u_b03;
		byte                  u_b04;
		byte                  u_b05;
		byte                  u_b06;
		byte                  u_b07;

		byte                  status;

		byte                  u_b09;
		byte                  u_b10;
		byte                  u_b11;
		byte                  u_b12;
		byte                  u_b13;
		byte                  u_b14;
		byte                  u_b15;

		byte                  timeStampA1;
		byte                  timeStampA2;
		byte                  timeStampA3;
		byte                  timeStampA4;

		byte                  rawGyroYaw_AL;
		byte                  rawGyroYaw_AH;

		byte                  rawGyroPitch_AL;
		byte                  rawGyroPitch_AH;

		byte                  rawGyroRoll_AL;
		byte                  rawGyroRoll_AH;

		byte                  rawMotionX_AL;
		byte                  rawMotionX_AH;

		byte                  rawMotionY_AL;
		byte                  rawMotionY_AH;

		byte                  rawMotionZ_AL;
		byte                  rawMotionZ_AH;        // 32 bytes

		byte                  timeStamp_B1;
		byte                  timeStamp_B2;
		byte                  timeStamp_B3;
		byte                  timeStamp_B4;

		byte                  rawGyroYaw_BL;
		byte                  rawGyroYaw_BH;

		byte                  rawGyroPitch_BL;
		byte                  rawGyroPitch_BH;

		byte                  rawGyroRoll_BL;
		byte                  rawGyroRoll_BH;

		byte                  rawMotionX_BL;
		byte                  rawMotionX_BH;

		byte                  rawMotionY_BL;
		byte                  rawMotionY_BH;

		byte                  rawMotionZ_BL;
		byte                  rawMotionZ_BH;

		byte                  calStatus;
		byte                  ready;

		byte                  u_b51;
		byte                  u_b52;
		byte                  u_b53;

		byte                  voltageValue;
		byte                  voltageReference;

		byte                  irSensorL;
		byte                  irSensorH;

		byte                  u_b58;
		byte                  u_b59;
		byte                  u_b60;
		byte                  u_b61;
		byte                  u_b62;

		byte                  frameSequence;
	};
#pragma pack()
	///
	/// \brief The PSVRSensorData struct
	///
	struct PSVRSensorData
	{
		bool                      volumeUpPressed;
		bool                      volumeDownPressed;
		bool                      mutePressed;

		byte                      volume;

		bool                      isWorn;
		bool                      isDisplayActive;
		bool                      isMicMuted;
		bool                      earphonesConnected;

		int                       timeStamp_A;

		int                       rawGyroYaw_A;
		int                       rawGyroPitch_A;
		int                       rawGyroRoll_A;

		int                       rawMotionX_A;
		int                       rawMotionY_A;
		int                       rawMotionZ_A;

		int                       timeStamp_B;

		int                       rawGyroYaw_B;
		int                       rawGyroPitch_B;
		int                       rawGyroRoll_B;

		int                       rawMotionX_B;
		int                       rawMotionY_B;
		int                       rawMotionZ_B;

		byte                      calStatus;
		byte                      ready;

		byte                      voltageValue;
		byte                      voltageReference;

		short                     irSensor;

		byte                      frameSequence;

	};

	///
	/// \brief The PSVRStatus struct
	///
	struct                     PSVRStatus
	{
	public:
		bool                   isHeadsetOn;
		bool                   isHeadsetWorn;
		bool                   isCinematic;
		bool                   areHeadphonesUsed;
		bool                   isMuted;
		bool                   isCECUsed;
		int                    volume;
	};

    class                      PSVRControl;    // forward declaration
    class                      PSVRSensor;     // forward declaration
    /// ----------------------------
    /// \brief The Context class
    ///
    class PSVRContext : public QObject
    {
        Q_OBJECT

    public:
        PSVRContext            ();
        ~PSVRContext           ();

        PSVRSensor             *psvrSensor;
        PSVRControl            *psvrControl;

        QString                serialNumber;
        unsigned char          minorVersion;
        unsigned char          majorVersion;
    };

    class PSVRCommon
    {
    public:
        bool Open              (int productNumber, PSVR_USB_INTERFACE usbInterface);
        void Close             (PSVR_USB_INTERFACE usbInterface);
    protected:
        bool SendCommand       (PSVRFrame *sendCmd);
        usb_dev_handle         *usbHdl = NULL;
    };

    /// ---------------------------
    /// \brief The Sensor class
    ///
    class PSVRSensor : public  QThread, public PSVRCommon
    {
        Q_OBJECT

    public:
        PSVRSensor             ();
        ~PSVRSensor            ();
        void run               ();
    private:
        void ProcessFrame      (PSVRApi::PSVRSensorFrame rawFrame, PSVRApi::PSVRSensorData rawData);
    signals:
        void connect           (bool isConnected);
    };

    /// ------------------------
    /// \brief The Control class
    ///
    class PSVRControl : public QThread, public PSVRCommon
    {
        Q_OBJECT        
    public :
        PSVRControl            ();
        ~PSVRControl           ();
        void run               ();
        bool HeadSetPower      (bool OnOff);
        bool EnableVR          (bool WithTracking);
        bool EnableCinematic   ();
        bool SetCinematic      (byte distance, byte size, byte brightness, byte micVolume);
        bool Recenter          ();
        bool Shutdown          ();
        bool ReadInfo          ();
    private:
        void emitInfoReport    (PSVRFrame frame);
        void emitStatusReport  (PSVRFrame frame);
        void emitUnsolicitedReport (PSVRFrame frame);
        void processFrame      (PSVRFrame frame);

    signals:
        void connect           (bool isConnected);
        void infoReport        (QString firmware, QString serial);
        void statusReport      (void *status);
        void unsolicitedReport (byte reportId, byte result, QByteArray message);
    };
}

#endif // PSVRAPI_H


