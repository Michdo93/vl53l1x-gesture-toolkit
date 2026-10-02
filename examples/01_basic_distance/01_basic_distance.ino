#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

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

  Serial.println("[INFO] VL53L1X Basic Distance Measurement Started.");
}

void loop() {
  int distance = sensor.read();
  
  if (sensor.timeoutOccurred()) {
    Serial.println("[WARN] Sensor read timeout!");
  } else {
    Serial.print("[DATA] Distance: ");
    Serial.print(distance);
    Serial.println(" mm");
  }

  delay(50);
}
