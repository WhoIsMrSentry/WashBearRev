// Simple MPU6050 driver implemented using the I2Cdev / MPU6050 MotionApps DMP
#ifndef MPU6050_WRAPPER_H
#define MPU6050_WRAPPER_H

#include <Arduino.h>

class MPU6050Driver {
public:
    MPU6050Driver();
    // Initialize the sensor and DMP. Call in `setup()`.
    void begin();
    // Return true if DMP/sensor is ready
    bool ready();
    // Fill out array with Yaw, Pitch, Roll (degrees)
    // This function blocks briefly while reading FIFO and returns latest values.
    void getYPR(float out[3]);
};

#endif // MPU6050_WRAPPER_H
