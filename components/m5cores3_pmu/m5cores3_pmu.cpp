#include "m5cores3_pmu.h"
#include "esphome/core/log.h"
#include <M5Unified.h>

namespace esphome {
namespace m5cores3_pmu {

static const char *TAG = "m5cores3_pmu";

bool M5CoreS3PMU::is_battery_exist() { return M5.Power.Axp2101.getBatteryExist(); }
float M5CoreS3PMU::get_battery_level() { return M5.Power.getBatteryLevel(); }

void M5CoreS3PMU::setup() {
  if (!M5.Power.Axp2101.begin()) {
    ESP_LOGE(TAG, "Failed to initialize AXP2101!");
    this->mark_failed();
    return;
  }
  
  // Enable ADC for battery voltage and current
  M5.Power.Axp2101.setADCState(true);
  
  // Initial sensor update
  this->update_sensors_();
  
  ESP_LOGD(TAG, "AXP2101 initialized successfully");
}

void M5CoreS3PMU::loop() {
  // Update sensor values every loop
  this->update_sensors_();
}

void M5CoreS3PMU::update_sensors_() {
  if (this->battery_voltage_sensor_ != nullptr) {
    float battery_voltage = M5.Power.getBatteryVoltage();
    this->battery_voltage_sensor_->publish_state(battery_voltage);
  }
  
  if (this->battery_current_sensor_ != nullptr) {
    float battery_current = M5.Power.Axp2101.getBatteryChargeCurrent() - 
                          M5.Power.Axp2101.getBatteryDischargeCurrent();
    this->battery_current_sensor_->publish_state(battery_current);
  }
  
  if (this->battery_level_sensor_ != nullptr) {
    float battery_level = M5.Power.getBatteryLevel();
    this->battery_level_sensor_->publish_state(battery_level);
  }
  
  if (this->temp_sensor_ != nullptr) {
    float temp = M5.Power.Axp2101.getTemp();
    this->temp_sensor_->publish_state(temp);
  }
  
  if (this->usb_voltage_sensor_ != nullptr) {
    float usb_voltage = M5.Power.Axp2101.getVbusVoltage();
    this->usb_voltage_sensor_->publish_state(usb_voltage);
  }
  
  if (this->usb_current_sensor_ != nullptr) {
    float usb_current = M5.Power.Axp2101.getVbusCurrent();
    this->usb_current_sensor_->publish_state(usb_current);
  }
  
  if (this->charging_sensor_ != nullptr) {
    bool is_charging = M5.Power.Axp2101.isCharging();
    this->charging_sensor_->publish_state(is_charging);
  }
  
  if (this->battery_present_sensor_ != nullptr) {
    bool battery_present = M5.Power.Axp2101.getBatteryExist();
    this->battery_present_sensor_->publish_state(battery_present);
  }
  
  if (this->usb_present_sensor_ != nullptr) {
    bool usb_present = M5.Power.Axp2101.getVbusExist();
    this->usb_present_sensor_->publish_state(usb_present);
  }
}

void M5CoreS3PMU::set_screen_brightness(uint8_t brightness) {
  M5.Display.setBrightness(brightness);
}

void M5CoreS3PMU::power_off() {
  M5.Power.powerOff();
}

void M5CoreS3PMU::dump_config() {
  ESP_LOGCONFIG(TAG, "AXP2101:");
  if (this->is_failed()) {
    ESP_LOGCONFIG(TAG, "  Setup Failed!");
    return;
  }
  ESP_LOGCONFIG(TAG, "  Battery Present: %s", YESNO(this->is_battery_exist()));
  ESP_LOGCONFIG(TAG, "  Battery Level: %.1f%%", this->get_battery_level());
  ESP_LOGCONFIG(TAG, "  USB Present: %s", YESNO(M5.Power.Axp2101.getVbusExist()));
  ESP_LOGCONFIG(TAG, "  Charging: %s", YESNO(M5.Power.Axp2101.isCharging()));
}

}  // namespace m5cores3_pmu
}  // namespace esphome