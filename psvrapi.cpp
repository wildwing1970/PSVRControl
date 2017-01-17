#include "psvrapi.h"

namespace PSVRApi
{
    /// -----------------------------------------------------------------------
    /// \brief PSVRContext::PSVRContext
    ///
    PSVRContext::PSVRContext ()
    {
        psvrControl = new PSVRControl();
        psvrSensor  = new PSVRSensor();
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRContext::~PSVRContext
    ///
    PSVRContext::~PSVRContext ()
    {
        psvrControl->exit();
//        psvrControl->Close(HID_CONTROL);
        delete psvrControl;

        psvrSensor->exit();
        psvrSensor->Close(HID_SENSOR);
        delete psvrSensor;
    }

    /// -----------------------------------------------------------------------
    /// \brief Sensor::Sensor
    /// \param sensor
    ///
    PSVRSensor::PSVRSensor ()
    {
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRSensor::PSVRSensor
    ///
    PSVRSensor::~PSVRSensor ()
    {
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRSensor::run
    ///        Thread implementation for sensor
    ///
    void PSVRSensor::run ()
    {
        struct PSVRSensorFrame   frame;

        int     bytesRead = 0;
        bool    connected = false;

        usleep(2000);

        // read reply
        while(isRunning())
        {
            // connect to usb, emit connect signal
            if(!connected)
            {
                if(Open(7, HID_SENSOR))
                {
                    emit connect(true);
                    connected = true;
                }
            }

            // read from device
            if(usbHdl != NULL)
                bytesRead += usb_bulk_read(usbHdl, PSVR_EP_SENSOR, (char *)&frame, sizeof(PSVRSensorFrame), 0);

            // we got some error from usb, eg. device is disconnected from usb
            if (bytesRead < 0)
            {
                // close connection
                if(connected)
                {
                    Close(HID_CONTROL);
                    connected = false;
                    emit connect(false);
                }
                usleep(20);
                continue;
            }

            PSVRSensorData data;
            ProcessFrame(frame, data);

        }
    }

    void PSVRSensor::ProcessFrame(PSVRApi::PSVRSensorFrame rawFrame, PSVRApi::PSVRSensorData rawData)
    {
        // buttons
        rawData.volumeUpPressed   = rawFrame.buttons & 0x02;
        rawData.volumeDownPressed = rawFrame.buttons & 0x04;
        rawData.mutePressed       = rawFrame.buttons & 0x08;

        // volume
        rawData.volume = rawFrame.volume;

        // status
        rawData.isWorn             = rawFrame.status & 0x01;
        rawData.isDisplayActive    = rawFrame.status & 0x02;
        rawData.isMicMuted         = rawFrame.status & 0x08;
        rawData.earphonesConnected = rawFrame.status & 0x10;

        rawData.timeStamp_A        = rawFrame.timeStampA1 | (rawFrame.timeStampA2 << 8) | (rawFrame.timeStampA3 << 16) | (rawFrame.timeStampA3 << 24);

        rawData.rawGyroYaw_A       = rawFrame.rawGyroYaw_AL   | (rawFrame.rawGyroYaw_AL << 8);
        rawData.rawGyroPitch_A     = rawFrame.rawGyroPitch_AL | (rawFrame.rawGyroPitch_AL << 8);
        rawData.rawGyroRoll_A      = rawFrame.rawGyroRoll_AL  | (rawFrame.rawGyroRoll_AL << 8);

        rawData.rawMotionX_A       = (rawFrame.rawMotionX_AL | (rawFrame.rawMotionX_AH << 8)) >> 4;
        rawData.rawMotionY_A       = (rawFrame.rawMotionY_AL | (rawFrame.rawMotionY_AH << 8)) >> 4;
        rawData.rawMotionZ_A       = (rawFrame.rawMotionZ_AL | (rawFrame.rawMotionZ_AH << 8)) >> 4;

        rawData.timeStamp_B        = rawFrame.timeStamp_B1 | (rawFrame.timeStamp_B2 << 8) | (rawFrame.timeStamp_B3 << 16) | (rawFrame.timeStamp_B4 << 24);

        rawData.rawGyroYaw_B       = rawFrame.rawGyroYaw_BL   | (rawFrame.rawGyroYaw_BL << 8);
        rawData.rawGyroPitch_B     = rawFrame.rawGyroPitch_BL | (rawFrame.rawGyroPitch_BL << 8);
        rawData.rawGyroRoll_B      = rawFrame.rawGyroRoll_BL  | (rawFrame.rawGyroRoll_BL << 8);

        rawData.rawMotionX_B       = (rawFrame.rawMotionX_BL | (rawFrame.rawMotionX_BH << 8)) >> 4;
        rawData.rawMotionY_B       = (rawFrame.rawMotionY_BL | (rawFrame.rawMotionY_BH << 8)) >> 4;
        rawData.rawMotionZ_B       = (rawFrame.rawMotionZ_BL | (rawFrame.rawMotionZ_BH << 8)) >> 4;

        rawData.calStatus          = rawFrame.calStatus;
        rawData.ready              = rawFrame.ready;
        rawData.voltageValue       = rawFrame.voltageValue;
        rawData.voltageReference   = rawFrame.voltageReference;
        rawData.frameSequence      = rawFrame.frameSequence;
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::PSVRControl
    ///
    PSVRControl::PSVRControl ()
    {
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::~PSVRControl
    ///
    PSVRControl::~PSVRControl ()
    {
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::run
    ///        Thread implementation for control
    ///
    void PSVRControl::emitUnsolicitedReport(PSVRFrame frame)
    {
        emit unsolicitedReport(frame.data[0], frame.data[1], QByteArray(frame.data[2], 58));
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::run
    ///    
    void PSVRControl::run ()
    {
        PSVRFrame    frame;

        int     bytesRead = 0;
        bool    connected = false;

        while(isRunning())
        {
            // connect to usb, emit connect signal
            if(!connected)
            {
                if(Open(8, HID_CONTROL))
                {
                    //
                    ReadInfo();
                    HeadSetPower(true);
                    EnableCinematic();
                    emit connect(true);
                    connected = true;
                }
            }

            if(usbHdl != NULL)
                bytesRead += usb_bulk_read(usbHdl, 132, (char *)&frame, sizeof(PSVRFrame), 0);

            // we got some error from usb, eg. device is disconnected from usb
            if (bytesRead < 0)
            {
                // close connection
                if(connected)
                {
                    Close(HID_CONTROL);
                    connected = false;
                    emit connect(false);
                }
                usleep(20);
                continue;
            }

            processFrame(frame);
            bytesRead = 0;
        }
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::processFrame
    /// \param frame
    ///
    void PSVRControl::processFrame(PSVRFrame frame)
    {
        switch(frame.id)
        {
        case PSVR_INFO_REPORT :
            emitInfoReport(frame);
            break;
        case PSVR_STATUS_REPORT :
            emitStatusReport(frame);
            break;
        case PSVR_UNSOLICITED_REPORT :
            emitUnsolicitedReport(frame);
            break;
        default:
            break;
        }
    }
    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::HeadSetPower
    /// \param OnOff
    /// \return
    ///
    bool PSVRControl::HeadSetPower (bool OnOff)
    {
        PSVRFrame sendCmd = {0x17, 0x00, 0xAA, 4, (byte)OnOff};
        return SendCommand(&sendCmd);
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::EnableVR
    /// \param WithTracking
    /// \return
    ///
    bool PSVRControl::EnableVR (bool WithTracking)
    {
        // generate packet for shutdown
        PSVRFrame sendCmd;

        // clear memory
        memset(&sendCmd, 0x00, sizeof(sendCmd));

        if(WithTracking)
        {
            // without tracking
            sendCmd.id     = 0x11;
            sendCmd.start  = 0xAA;
            sendCmd.length = 8;

            // payload
            sendCmd.data[1] = 0xFF;
            sendCmd.data[2] = 0xFF;
            sendCmd.data[3] = 0xFF;

        }
        else
        {
            // without tracking
            sendCmd.id     = 0x23;
            sendCmd.start  = 0xAA;
            sendCmd.length = sizeof(int);

            // payload
            sendCmd.data[0] = 1; // VRWithoutTracking = 1 / Cinematic = 0
        }

        // send shutdown command and receive reply
        return SendCommand(&sendCmd);
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::EnableCinematic
    /// \return
    ///
    bool PSVRControl::EnableCinematic()
    {
        // generate packet for shutdown
        PSVRFrame sendCmd = {0x23, 0x00, 0xAA, 4, 0}; // VR = 1 / Cinematic = 0
        return SendCommand(&sendCmd);
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::SetCinematic
    /// \param distance
    /// \param size
    /// \param brightness
    /// \param micVolume
    /// \return
    ///
    bool PSVRControl::SetCinematic(byte distance, byte size, byte brightness, byte micVolume)
    {
        PSVRFrame Cmd = {0x21, 0x00, 0xAA, 16, 0xC0, distance, size, 0x14, 0, 0, 0, 0, 0, 0, brightness, micVolume, 0, 0, 0, 0 };
        return SendCommand(&Cmd);
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::Recenter
    /// \return
    ///
    bool PSVRControl::Recenter ()
    {
        return true;
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::Shutdown
    /// \return
    ///
    bool PSVRControl::Shutdown ()
    {
        // shutdown command
        PSVRFrame Cmd = {0x13, 0x00, 0xAA, 4, 1};
        return SendCommand(&Cmd);
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::ReadInfo
    /// \return
    ///
    bool PSVRControl::ReadInfo ()
    {
        // read info command
        PSVRFrame Cmd = {0x81, 0x00, 0xAA, 8, 0x80};
        return SendCommand(&Cmd);
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::emitInfoReport
    /// \param frame
    ///
    void PSVRControl::emitInfoReport(PSVRFrame frame)
    {
        QString firmware;
        QString serial;
        firmware = QString(frame.data[7] + 0x30) + "." + QString(frame.data[8] + 0x30);
        serial   = QByteArray((char *)&frame.data[12], 16);
        emit infoReport(firmware, serial);
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRControl::emitStatusReport
    /// \param frame
    ///
    void PSVRControl::emitStatusReport(PSVRFrame frame)
    {
        PSVRStatus  *status = new PSVRStatus;
        status->isHeadsetOn       = frame.data[0] & (1 << 0);
        status->isHeadsetWorn     = frame.data[0] & (1 << 1);
        status->isCinematic       = frame.data[0] & (1 << 2);
        status->areHeadphonesUsed = frame.data[0] & (1 << 4);
        status->isMuted           = frame.data[0] & (1 << 5);
        status->isCECUsed         = frame.data[0] & (1 << 7);
        status->volume            = frame.data[1] | (frame.data[2] << 8) | (frame.data[3] << 16) | (frame.data[4] << 24);
        emit statusReport((void *)status);
    }


    /// -----------------------------------------------------------------------
    /// \brief PSVRCommon::Open
    /// \param productNumber
    /// \return
    ///
    bool PSVRCommon::Open(int productNumber, PSVR_USB_INTERFACE usbInterface)
    {
        usb_init();
        usb_find_busses();
        usb_find_devices();

        usbHdl = NULL;

        struct usb_bus *bus;
        struct usb_device *dev;

        // search for PSVR
        for (bus = usb_get_busses(); bus; bus = bus->next)
        {
            for (dev = bus->devices; dev; dev = dev->next)
            {
                if (dev->descriptor.idVendor == PSVR_VID && dev->descriptor.idProduct == PSVR_PID)
                {
                    if(dev->descriptor.iProduct == productNumber)
                    {
                        // open PSVR Control Interface
                        usbHdl = usb_open(dev);
                        if(usbHdl && !usb_claim_interface(usbHdl, usbInterface))
                            continue;
                    }
                }
            }
        }

        if(usbHdl != NULL)
        {
            // reset endpoint
            usb_resetep(usbHdl,  PSVR_EP_CMD_READ);
            return TRUE;
        }
        else
            return FALSE;
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRCommon::Close
    /// \param usbInterface
    ///
    void PSVRCommon::Close(PSVR_USB_INTERFACE usbInterface)
    {
        usb_release_interface(usbHdl, usbInterface);
        usb_close(usbHdl);
        usbHdl = NULL;
    }

    /// -----------------------------------------------------------------------
    /// \brief PSVRCommon::SendCommand
    /// \param Command
    /// \return
    ///
    bool PSVRCommon::SendCommand(PSVRFrame *sendCmd)
    {

        int bytesSent;

        // send command
        if((bytesSent = usb_bulk_write(usbHdl, PSVR_EP_CMD_WRITE, (char *)sendCmd, 64, 20)) != sizeof(PSVRFrame))
            return false;

        return true;
    }
}
