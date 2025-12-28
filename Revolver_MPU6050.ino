// Refactored main: uses MPU6050Driver and RevolverController classes
#include "Arduino.h"
#include "MPU6050.h"
#include "Revolver.h"

MPU6050Driver mpu;
RevolverController revolver;

void setup() {
  Serial.begin(115200);
  while (!Serial) ;

  mpu.begin();
  revolver.begin();

  if (!mpu.ready()) {
    Serial.println("Warning: MPU DMP not ready. Check wiring and libraries.");
  } else {
    Serial.println("MPU DMP ready.");
  }
}

void loop() {
  if (!mpu.ready()) {
    delay(100);
    return;
  }

  float ypr[3];
  mpu.getYPR(ypr);

  // print yaw pitch roll and button states
  Serial.print(ypr[0], 2);
  Serial.print(" ");
  Serial.print(ypr[1], 2);
  Serial.print(" ");
  Serial.print(ypr[2], 2);
  Serial.print(" ");
  Serial.print(digitalRead(BUTTON_PIN_1));
  Serial.print(" ");
  Serial.println(digitalRead(BUTTON_PIN_2));

  // signal activity with LED
  revolver.signalActivity();

  // small delay to let serial drain
  delay(10);
}