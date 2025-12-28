
# Modularization Guide

This document describes recommended steps to modularize the code inside `Revolver_MPU6050.ino`.

1) Preparation
- Create an Arduino IDE or PlatformIO project.
- Ensure there is a `src/` folder alongside `Revolver_MPU6050.ino` for additional source files.

2) Proposed modules
- `MPU6050` module: handles sensor initialization, DMP management and reading Yaw/Pitch/Roll (YPR).
- `Revolver` module: handles buttons, LED and application-specific control logic.

3) Migration steps
- Move MPU initialization code from `setup()` into a `begin()` method of the `MPU6050` class.
- Move DMP reading and YPR extraction from `loop()` into methods like `read()` or `getYPR()` in the `MPU6050` class.
- Move hardware pin definitions and button/LED handling into the `Revolver` class.

3.1) Pin mapping and integration details

- The original sketch uses `BUTTON_PIN_1 = 3`, `BUTTON_PIN_2 = 4`, and `LED_PIN = 13`. It's convenient to centralize these in `Revolver.h` as constants so both the `.ino` and other modules reference the same pins.
- The MPU uses I2C (`Wire`). Keep I2C initialization (`Wire.begin()`) in the `MPU6050::begin()` implementation or centralize it in the `.ino` if multiple I2C devices are present.

3.2) Example integration (pseudo)

In your `.ino` main file:

```
// global instances
MPU6050Driver mpu;
RevolverController revolver;

void setup() {
	mpu.begin();
	revolver.begin();
}

void loop() {
	if (mpu.ready()) {
		float ypr[3];
		mpu.getYPR(ypr);
		// use ypr and revolver.buttonPressed() for game logic
	}
	revolver.update();
}
```

4) Build and test
- Place all files in the project folder and build. Use Arduino Library Manager to install missing dependencies.

5) Notes
- The `src/` folder in this repository contains skeleton files to get started; they are templates and need implementation.

6) Implementation TODOs

- `MPU6050`:
	- Implement DMP initialization using `mpu.dmpInitialize()` and set offsets.
	- Install and include `I2Cdev`/`MPU6050_6Axis_MotionApps20` in the project.
	- Provide `ready()` that returns true once DMP is enabled.
	- Provide `getYPR()` that reads FIFO and fills yaw/pitch/roll in degrees.

- `Revolver`:
	- Define button and LED pins in header constants.
	- Implement debounced button reads (or simple `digitalRead()` if debouncing handled elsewhere).
	- Provide `update()` to manage LED blink states and read buttons.


