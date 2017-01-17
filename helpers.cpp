#include "helpers.h"

#include <QtMath>


void MadgwickAHRS::Update(float gx, float gy, float gz, float ax, float ay, float az, float beta, float samplePeriod)
{
    float q1 = orientation.scalar();
    float q2 = orientation.x();
    float q3 = orientation.y();
    float q4 = orientation.z();

    float norm;

    float s1, s2, s3, s4;
    float qDot1, qDot2, qDot3, qDot4;

    // Auxiliary variables to avoid repeated arithmetic
    float _2q1 = 2.0 * q1;
    float _2q2 = 2.0 * q2;
    float _2q3 = 2.0 * q3;
    float _2q4 = 2.0 * q4;
    float _4q1 = 4.0 * q1;
    float _4q2 = 4.0 * q2;
    float _4q3 = 4.0 * q3;
    float _8q2 = 8.0 * q2;
    float _8q3 = 8.0 * q3;
    float q1q1 = q1 * q1;
    float q2q2 = q2 * q2;
    float q3q3 = q3 * q3;
    float q4q4 = q4 * q4;

    // Normalise accelerometer measurement
    norm = (float) sqrt(ax * ax + ay * ay + az * az);
    if (norm == 0.0)
        return; // handle NaN
    norm = 1 / norm;        // use reciprocal for division
    ax *= norm;
    ay *= norm;
    az *= norm;

    // Gradient decent algorithm corrective step
    s1 = _4q1 * q3q3 + _2q3 * ax + _4q1 * q2q2 - _2q2 * ay;
    s2 = _4q2 * q4q4 - _2q4 * ax + 4.0 * q1q1 * q2 - _2q1 * ay - _4q2 + _8q2 * q2q2 + _8q2 * q3q3 + _4q2 * az;
    s3 = 4.0 * q1q1 * q3 + _2q1 * ax + _4q3 * q4q4 - _2q4 * ay - _4q3 + _8q3 * q2q2 + _8q3 * q3q3 + _4q3 * az;
    s4 = 4.0 * q2q2 * q4 - _2q2 * ax + 4.0 * q3q3 * q4 - _2q3 * ay;
    norm = 1.0 / sqrt(s1 * s1 + s2 * s2 + s3 * s3 + s4 * s4);    // normalise step magnitude
    s1 *= norm;
    s2 *= norm;
    s3 *= norm;
    s4 *= norm;

    // Compute rate of change of quaternion
    qDot1 = 0.5f * (-q2 * gx - q3 * gy - q4 * gz) - beta * s1;
    qDot2 = 0.5f * (q1 * gx + q3 * gz - q4 * gy) - beta * s2;
    qDot3 = 0.5f * (q1 * gy - q2 * gz + q4 * gx) - beta * s3;
    qDot4 = 0.5f * (q1 * gz + q2 * gy - q3 * gx) - beta * s4;

    // Integrate to yield quaternion
    q1 += qDot1 * samplePeriod;
    q2 += qDot2 * samplePeriod;
    q3 += qDot3 * samplePeriod;
    q4 += qDot4 * samplePeriod;
    norm = 1.0 / sqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);    // normalise quaternion
    orientation.setScalar(q1 * norm);
    orientation.setX(q2 * norm);
    orientation.setY(q3 * norm);
    orientation.setZ(q4 * norm);
}

void BMI055Integrator::init(AScale AccelerometerScale, GScale GyroscopeScale)
{
    accRes = getAccRes(AccelerometerScale);
    gyroRes = getGyroRes(GyroscopeScale);
}

void BMI055Integrator::Recenter()
{
    mutex.lock();
    zero = QQuaternion(1.0, 0.0, 0.0, 0.0) * fusion.orientation.inverted();
    mutex.unlock();
}
void BMI055Integrator::Recalibrate()
{
    mutex.lock();
    isCalibrating = true;
    accOffset = QVector3D(0.0,0.0,0.0);
    gyroOffset = QVector3D(0.0,0.0,0.0);
    mutex.unlock();
}

float BMI055Integrator::getAccRes(AScale Scale)
{
    switch (Scale)
    {
    case AFS_2G:
        return 2.0f / 2048.0f;
    case AFS_4G:
        return 4.0f / 2048.0f;
    case AFS_8G:
        return 8.0f / 2048.0f;
    case AFS_16G:
        return 16.0f / 2048.0f;
    default:
        return 0;
    }
}

float BMI055Integrator::getGyroRes(GScale Scale)
{
    switch (Scale)
    {
    // Possible gyro scales (and their register bit settings) are:
    // 125 DPS (100), 250 DPS (011), 500 DPS (010), 1000 DPS (001), and 2000 DPS (000).
    case GFS_125DPS:
        return (float)(0.00381f * (M_PI / 180)); //return 124.87 / (32768.0 * 4); // per data sheet, not exactly 125!?
    case GFS_250DPS:
        return (float)(0.007622f * (M_PI / 180)); //1.0 / 262.4; //return 249.75 / 32768.0;
    case GFS_500DPS:
        return (float)(0.01524f * (M_PI / 180));//1.0 / 262.4; //return 499.5 / 32768.0;
    case GFS_1000DPS:
        return (float)(0.03048f * (M_PI / 180)); //1.0 / 262.4; //return 999.0 / 32768.0;
    case GFS_2000DPS:
        return (float)(0.06097f * (M_PI / 180));//1.0 / 262.4; //return 1998.0 / 32768.0;
    default:
        return 0;
    }
}

QQuaternion BMI055Integrator::Integrate(QVector3D linearAcceleration, QVector3D angularAcceleration, uint timestamp)
{
    mutex.unlock();
    // calculate offset
    if (samplesLeft > 0)
    {
        samplesLeft--;
        accOffset += linearAcceleration;
        gyroOffset += angularAcceleration;
        return QQuaternion(1.0, 0.0, 0.0, 0.0);
    }
    // offset calculated
    else if(samplesLeft == 0)
    {
        samplesLeft--;
        accOffset /= 2000;
        gyroOffset /= 2000;

        gravityVector = accOffset;
        gravityVector.normalize();

        accOffset -= gravityVector;

        prevTimestamp = timestamp;
        return QQuaternion(1.0, 0.0, 0.0, 0.0);
    }
    else if (samplesLeft > -1500)
    {
        samplesLeft--;

        linearAcceleration = linearAcceleration - accOffset;
        linearAcceleration.normalize();
        angularAcceleration -= gyroOffset;

        float interval = 0;

        if (prevTimestamp > timestamp)
            interval = (timestamp + (0xFFFFFF - prevTimestamp)) / 1000000.0f;
        else
            interval = (timestamp - prevTimestamp) / 1000000.0f;

        fusion.Update(angularAcceleration.x(), angularAcceleration.y(), angularAcceleration.z(), linearAcceleration.x(), linearAcceleration.y(), linearAcceleration.z(), 1.5f, interval);

        prevTimestamp = timestamp;
        return QQuaternion(1.0, 0.0, 0.0, 0.0);
    }
    else if (samplesLeft > -2000)
    {
        samplesLeft--;

        linearAcceleration = linearAcceleration - accOffset;
        linearAcceleration.normalize();
        angularAcceleration -= gyroOffset;

        float interval = 0;

        if (prevTimestamp > timestamp)
            interval = (timestamp + (0xFFFFFF - prevTimestamp)) / 1000000.0f;
        else
            interval = (timestamp - prevTimestamp) / 1000000.0f;

        fusion.Update(angularAcceleration.x(), angularAcceleration.y(), angularAcceleration.z(), linearAcceleration.x(), linearAcceleration.y(), linearAcceleration.z(), 0.05f, interval);

        prevTimestamp = timestamp;
        return QQuaternion(1.0, 0.0, 0.0, 0.0);
    }
    else if (samplesLeft == -2000)
    {
        samplesLeft--;

        linearAcceleration = linearAcceleration - accOffset;
        linearAcceleration.normalize();
        angularAcceleration -= gyroOffset;

        float interval = 0;

        if (prevTimestamp > timestamp)
            interval = (timestamp + (0xFFFFFF - prevTimestamp)) / 1000000.0f;
        else
            interval = (timestamp - prevTimestamp) / 1000000.0f;

        fusion.Update(angularAcceleration.x(), angularAcceleration.y(), angularAcceleration.z(), linearAcceleration.x(), linearAcceleration.y(), linearAcceleration.z(), 0.035f, interval);

        prevTimestamp = timestamp;

        zero = QQuaternion(1.0, 0.0, 0.0, 0.0) * fusion.orientation.inverted();
        isCalibrating = false;

        return QQuaternion(1.0, 0.0, 0.0, 0.0);
    }
    else
    {
        linearAcceleration = linearAcceleration - accOffset;
        linearAcceleration.normalize();
        angularAcceleration -= gyroOffset;

        float interval = 0;

        if (prevTimestamp > timestamp)
            interval = (timestamp + (0xFFFFFF - prevTimestamp)) / 1000000.0f;
        else
            interval = (timestamp - prevTimestamp) / 1000000.0f;

        fusion.Update(angularAcceleration.x(), angularAcceleration.y(), angularAcceleration.y(), linearAcceleration.x(), linearAcceleration.y(), linearAcceleration.z(), 0.035f, interval);

        prevTimestamp = timestamp;

//        if (recenter)
//        {
//            zero = Quaternion.Identity * Quaternion.Inverse(fusion.Quaternion);
//            recenter = false;
//        }

        return zero * fusion.orientation.inverted();
    }
    mutex.unlock();
}
