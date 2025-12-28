
#include "MPU6050.h"

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

MPU6050 mpu;

volatile bool mpuInterrupt = false; // indicates whether MPU interrupt pin has gone high

void dmpDataReady() {
    mpuInterrupt = true;
}

// internal state (mirrors important parts of the original sketch)
static bool dmpReady = false;
static uint8_t mpuIntStatus;
static uint8_t devStatus;
static uint16_t packetSize;
static uint16_t fifoCount;
static uint8_t fifoBuffer[64];

// containers for orientation
static Quaternion q;
static VectorFloat gravity;
static float ypr_internal[3];

MPU6050Driver::MPU6050Driver() {
}

void MPU6050Driver::begin() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
    TWBR = 24; // 400kHz I2C (optional)
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
    #endif

    mpu.initialize();
    devStatus = mpu.dmpInitialize();

    // Set the same offsets used in the original sketch
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788);

    if (devStatus == 0) {
        mpu.setDMPEnabled(true);
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();
        dmpReady = true;
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        dmpReady = false;
    }
}

bool MPU6050Driver::ready() {
    return dmpReady;
}

void MPU6050Driver::getYPR(float out[3]) {
    if (!dmpReady) {
        out[0] = out[1] = out[2] = 0.0f;
        return;
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        mpu.resetFIFO();
        out[0] = out[1] = out[2] = 0.0f;
        return;
    }

    // wait for DMP data ready interrupt or until enough bytes available
    if (mpuIntStatus & 0x02) {
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        fifoCount -= packetSize;

        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr_internal, &q, &gravity);

        // convert to degrees
        out[0] = ypr_internal[0] * 180.0f / M_PI;
        out[1] = ypr_internal[1] * 180.0f / M_PI;
        out[2] = ypr_internal[2] * 180.0f / M_PI;
        return;
    }

    // if no new packet, return last known values
    out[0] = ypr_internal[0] * 180.0f / M_PI;
    out[1] = ypr_internal[1] * 180.0f / M_PI;
    out[2] = ypr_internal[2] * 180.0f / M_PI;
}
