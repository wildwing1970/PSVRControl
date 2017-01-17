#ifndef HELPERS_H
#define HELPERS_H

#include <QVector3D>
#include <QQuaternion>
#include <QMutex>


class MadgwickAHRS
{
public:
    MadgwickAHRS() : orientation(QQuaternion(1.0, 0.0, 0.0, 0.0)) {}
    MadgwickAHRS(QQuaternion orientationSeed) : orientation(orientationSeed) {}

    QQuaternion orientation;

    void MadgwickAHRS::Update(float gx, float gy, float gz, float ax, float ay, float az, float beta, float samplePeriod);
};

class BMI055Integrator
{
public:
    BMI055Integrator() : samplesLeft(2000), ledOn(true), isCalibrating(true) {}

    enum AScale
    {
        AFS_2G = 0x03,
        AFS_4G = 0x05,
        AFS_8G = 0x08,
        AFS_16G = 0x0C
    };

    enum GScale
    {
        GFS_2000DPS = 0,
        GFS_1000DPS,
        GFS_500DPS,
        GFS_250DPS,
        GFS_125DPS
    };

    void init(AScale AccelerometerScale, GScale GyroscopeScale);

    bool isCalibrating = true;

public slots:
    void Recenter();
    void Recalibrate();

private:
    QMutex mutex;
    float accRes;
    float gyroRes;

    float accResolution;
    float gResResolution;

    bool recenter = false;

    int samplesLeft;
    uint prevTimestamp;

    bool ledOn = true;

    MadgwickAHRS fusion;

    QVector3D gravityVector;
    QVector3D accOffset;
    QVector3D gyroOffset;
    QQuaternion zero;

    float getAccRes(AScale Scale);
    float getGyroRes(GScale Scale);

    QQuaternion Integrate(QVector3D linearAcceleration, QVector3D angularAcceleration, uint timestamp);
};

#endif // HELPERS_H
