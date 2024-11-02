#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace m5cores3_pmu {

class M5CoreS3PMU : public Component {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::IO; }
  void loop() override;
  
  // Sensor setters
  void set_battery_voltage_sensor(sensor::Sensor *batt_voltage) { battery_voltage_sensor_ = batt_voltage; }
  void set_battery_current_sensor(sensor::Sensor *batt_current) { battery_current_sensor_ = batt_current; }
  void set_battery_level_sensor(sensor::Sensor *batt_level) { battery_level_sensor_ = batt_level; }
  void set_temp_sensor(sensor::Sensor *temp) { temp_sensor_ = temp; }
  void set_usb_voltage_sensor(sensor::Sensor *usb_voltage) { usb_voltage_sensor_ = usb_voltage; }
  void set_usb_current_sensor(sensor::Sensor *usb_current) { usb_current_sensor_ = usb_current; }
  
  // Binary sensor setters
  void set_charging_binary_sensor(binary_sensor::BinarySensor *charging) { charging_sensor_ = charging; }
  void set_battery_present_binary_sensor(binary_sensor::BinarySensor *battery_present) { battery_present_sensor_ = battery_present; }
  void set_usb_present_binary_sensor(binary_sensor::BinarySensor *usb_present) { usb_present_sensor_ = usb_present; }

  // Power control methods
  void set_screen_brightness(uint8_t brightness);
  void power_off();
  bool is_battery_exist(); // { return M5.Power.Axp2101.getBatteryExist(); }
  float get_battery_level(); // { return M5.Power.getBatteryLevel(); }
  
 protected:
  // Internal methods
  void update_sensors_();
  
  // Sensor pointers
  sensor::Sensor *battery_voltage_sensor_{nullptr};
  sensor::Sensor *battery_current_sensor_{nullptr};
  sensor::Sensor *battery_level_sensor_{nullptr};
  sensor::Sensor *temp_sensor_{nullptr};
  sensor::Sensor *usb_voltage_sensor_{nullptr};
  sensor::Sensor *usb_current_sensor_{nullptr};
  
  // Binary sensor pointers
  binary_sensor::BinarySensor *charging_sensor_{nullptr};
  binary_sensor::BinarySensor *battery_present_sensor_{nullptr};
  binary_sensor::BinarySensor *usb_present_sensor_{nullptr};
};

}  // namespace m5cores3_pmu
}  // namespace esphome