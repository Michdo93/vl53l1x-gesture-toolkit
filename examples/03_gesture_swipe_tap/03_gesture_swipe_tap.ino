#include <Wire.h>
#include <VL53L1X.h>
#include "VL53L1X_GestureEngine.h"

VL53L1X sensor;
VL53L1X_GestureEngine gestureEngine(300, 400); // 300mm threshold, 400ms timeout

const uint8_t ROI_LEFT_CENTER = 175;
const uint8_t ROI_RIGHT_CENTER = 239;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("[ERROR] Failed to detect VL53L1X sensor!");
    while (1);
  }

  sensor.setDistanceMode(VL53L1X::Short);
  sensor.setMeasurementTimingBudget(20000);
  sensor.startContinuous(20);

  Serial.println("[READY] Gesture Recognition Running (Swipe Left/Right, Hold)...");
}

void loop() {
  sensor.setROISize(8, 16);
  sensor.setROICenter(ROI_LEFT_CENTER);
  int distLeft = sensor.read();

  sensor.setROICenter(ROI_RIGHT_CENTER);
  int distRight = sensor.read();

  GestureType gesture = gestureEngine.processDualZone(distLeft, distRight);

  switch (gesture) {
    case GESTURE_SWIPE_RIGHT:
      Serial.println(">>> [EVENT] SWIPE RIGHT Detected!");
      break;
    case GESTURE_SWIPE_LEFT:
      Serial.println("<<< [EVENT] SWIPE LEFT Detected!");
      break;
    case GESTURE_HOLD:
      Serial.println("[EVENT] HOLD Gesture Detected!");
      break;
    default:
      break;
  }

  delay(10);
}
