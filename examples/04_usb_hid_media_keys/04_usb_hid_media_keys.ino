// Target MCU: ESP32-S2/S3 or Arduino Leonardo / Micro (Native USB Supported)
#include <Wire.h>
#include <VL53L1X.h>
#include <USBHIDControl.h> // Generic HID / Keyboard Library for native USB boards
#include "VL53L1X_GestureEngine.h"

VL53L1X sensor;
VL53L1X_GestureEngine gestureEngine(300, 400);

void setup() {
  Wire.begin();
  Wire.setClock(400000);

  sensor.setTimeout(500);
  if (!sensor.init()) {
    while (1);
  }

  sensor.setDistanceMode(VL53L1X::Short);
  sensor.setMeasurementTimingBudget(20000);
  sensor.startContinuous(20);

  // USBHID.begin();
}

void loop() {
  sensor.setROISize(8, 16);
  sensor.setROICenter(175);
  int distLeft = sensor.read();

  sensor.setROICenter(239);
  int distRight = sensor.read();

  GestureType gesture = gestureEngine.processDualZone(distLeft, distRight);

  if (gesture == GESTURE_SWIPE_RIGHT) {
    // Send Media Next Track Command
    // ConsumerControl.press(MEDIA_NEXT);
    // ConsumerControl.release();
  } else if (gesture == GESTURE_SWIPE_LEFT) {
    // Send Media Previous Track Command
    // ConsumerControl.press(MEDIA_PREVIOUS);
    // ConsumerControl.release();
  } else if (gesture == GESTURE_HOLD) {
    // Send Play/Pause Command
    // ConsumerControl.press(MEDIA_PLAY_PAUSE);
    // ConsumerControl.release();
  }

  delay(10);
}
