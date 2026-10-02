#ifndef VL53L1X_GESTURE_ENGINE_H
#define VL53L1X_GESTURE_ENGINE_H

#include <Arduino.h>

enum GestureType {
  GESTURE_NONE = 0,
  GESTURE_SWIPE_LEFT,
  GESTURE_SWIPE_RIGHT,
  GESTURE_TAP,
  GESTURE_HOLD
};

class VL53L1X_GestureEngine {
private:
  int thresholdMm;
  unsigned long timeoutMs;
  
  unsigned long leftTriggerTime;
  unsigned long rightTriggerTime;
  unsigned long holdStartTime;
  bool isHolding;

public:
  VL53L1X_GestureEngine(int thresholdMm = 300, unsigned long timeoutMs = 400)
    : thresholdMm(thresholdMm), timeoutMs(timeoutMs),
      leftTriggerTime(0), rightTriggerTime(0), holdStartTime(0), isHolding(false) {}

  GestureType processDualZone(int distLeft, int distRight) {
    unsigned long now = millis();
    GestureType detected = GESTURE_NONE;

    bool activeLeft = (distLeft > 0 && distLeft < thresholdMm);
    bool activeRight = (distRight > 0 && distRight < thresholdMm);

    // Track timestamps for Left zone
    if (activeLeft && leftTriggerTime == 0) {
      leftTriggerTime = now;
    }
    
    // Track timestamps for Right zone
    if (activeRight && rightTriggerTime == 0) {
      rightTriggerTime = now;
    }

    // Process Swipe gestures
    if (leftTriggerTime > 0 && rightTriggerTime > 0) {
      if (rightTriggerTime > leftTriggerTime && (rightTriggerTime - leftTriggerTime) <= timeoutMs) {
        detected = GESTURE_SWIPE_RIGHT;
        reset();
        return detected;
      } else if (leftTriggerTime > rightTriggerTime && (leftTriggerTime - rightTriggerTime) <= timeoutMs) {
        detected = GESTURE_SWIPE_LEFT;
        reset();
        return detected;
      }
    }

    // Process Hold gesture (single zone or combined)
    if (activeLeft || activeRight) {
      if (holdStartTime == 0) {
        holdStartTime = now;
      } else if (!isHolding && (now - holdStartTime >= 1000)) {
        isHolding = true;
        detected = GESTURE_HOLD;
      }
    } else {
      holdStartTime = 0;
      isHolding = false;
    }

    // Reset timed-out triggers
    if (leftTriggerTime > 0 && (now - leftTriggerTime > timeoutMs)) {
      leftTriggerTime = 0;
    }
    if (rightTriggerTime > 0 && (now - rightTriggerTime > timeoutMs)) {
      rightTriggerTime = 0;
    }

    return detected;
  }

  void reset() {
    leftTriggerTime = 0;
    rightTriggerTime = 0;
    holdStartTime = 0;
    isHolding = false;
  }
};

#endif // VL53L1X_GESTURE_ENGINE_H
