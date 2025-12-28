
# WashBearRev

This repository contains an example Arduino project using the MPU6050 sensor (with DMP) and CAD/model files for the Washbear Revolver.

Key files:
- `Revolver_MPU6050.ino` — Example Arduino sketch demonstrating MPU6050 DMP usage.
- `Washbear_Revolver_v2.0/` — CAD files and renders (IPT, STEP, STL, etc.).

Quick start:
1. Open `Revolver_MPU6050.ino` in the Arduino IDE or PlatformIO.
2. Install required libraries: `I2Cdev` and `MPU6050_6Axis_MotionApps20`.
3. Select your board, compile and upload.

Modularization (notes):
- Example skeleton modules were added under `src/`: `MPU6050` and `Revolver`. These are minimal starting points and can be extended for your application.
- I did not modify the original `.ino` file automatically; if you want, I can refactor the `.ino` to use the new classes and test compilation.

Next steps (suggestions):
- I can refactor the sketch into the classes and verify compilation on PlatformIO or give step-by-step instructions for Arduino IDE.
- I can add a `platformio.ini` for easier builds and tests.

If you want me to proceed, tell me whether you prefer `Arduino IDE` or `PlatformIO` for building.

Project purpose
---------------

This project is a small interactive game controller built around a 3D-printed gun (WashBear model) that uses an MPU6050 IMU for orientation (yaw/pitch/roll) and buttons for user input. The intent is to use the physical movement and buttons on the gun to play a simple game (for example: aim by moving the gun, press buttons to fire/reload). The sketch `Revolver_MPU6050.ino` reads MPU data and reports YPR values and button states over serial.

Wiring and pins
---------------

- MPU6050: connect to the I2C bus (SDA, SCL) and power (Vcc, GND).
- Buttons: this project uses two buttons on pins `3` and `4` (configured as `INPUT_PULLUP`).
- LED: on-board LED pin `13` is used to indicate activity.

Suggested pin mapping (based on existing sketch):

- `BUTTON_PIN_1 = 3`
- `BUTTON_PIN_2 = 4`
- `LED_PIN = 13`

How it works
------------

1. The MPU6050 DMP is initialized in `setup()` to provide stable YPR values.
2. The sketch waits for the MPU interrupt, reads FIFO, extracts yaw/pitch/roll, and prints them on serial with button states.
3. The on-board LED blinks when new data is processed.

Files added by maintainer
-------------------------

- `README_MODULARIZATION.md` — a short guide on how to move code into modules.
- `src/MPU6050.{h,cpp}` — skeleton for an MPU6050 driver class.
- `src/Revolver.{h,cpp}` — skeleton for a revolver controller (buttons, LED).

Next recommended actions
------------------------

- If you want a reproducible build: choose `PlatformIO` (recommended) or `Arduino IDE`. I can add a `platformio.ini` and refactor the sketch to use the `src/` classes and then verify compilation.
- If you prefer minimal changes now, I can implement the `MPU6050` class to wrap the existing DMP code and update the `.ino` to call it.

Contact / help
--------------

Tell me which direction you prefer (full refactor + compile, or only documentation + TODOs) and which build environment you use (Arduino IDE or PlatformIO). I will proceed accordingly.
# WashBearRev