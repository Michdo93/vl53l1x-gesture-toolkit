#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;

const uint8_t ROI_LEFT_CENTER = 175;
const uint8_t ROI_RIGHT_CENTER = 239;
const uint8_t ROI_SIZE = 8;

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

  Serial.println("[INFO] Dual-Zone ROI Switching Initialized.");
}

void loop() {
  // Read Left Zone
  sensor.setROISize(ROI_SIZE, 16);
  sensor.setROICenter(ROI_LEFT_CENTER);
  int distLeft = sensor.read();

  // Read Right Zone
  sensor.setROICenter(ROI_RIGHT_CENTER);
  int distRight = sensor.read();

  Serial.print("Left ROI: ");
  Serial.print(distLeft);
  Serial.print(" mm | Right ROI: ");
  Serial.print(distRight);
  Serial.println(" mm");

  delay(20);
}
