#include "m5cores3_pmu.h"
#include "esphome/core/log.h"
#include <M5Unified.h>

namespace esphome {
namespace m5cores3_pmu {

static const char *TAG = "m5cores3_pmu";

void M5CoreS3PMU::setup() {
  // Initialize AXP2101
  if (!M5.Power.Axp2101.begin()) {
    ESP_LOGE(TAG, "Failed to initialize AXP2101!");
    this->mark_failed();
    return;
  }

  // Enable ADC for battery voltage and current
  M5.Power.Axp2101.setAdcState(true);

  // Initial sensor update
  this->update_sensors_();

  ESP_LOGD(TAG, "AXP2101 initialized successfully");
}

void M5CoreS3PMU::loop() {
  this->update_sensors_();
}

void M5CoreS3PMU::update_sensors_() {
  if (this->battery_voltage_sensor_ != nullptr) {
    float battery_voltage = M5.Power.Axp2101.getBatteryVoltage();
    this->battery_voltage_sensor_->publish_state(battery_voltage);
  }

  if (this->battery_level_sensor_ != nullptr) {
    float battery_level = M5.Power.getBatteryLevel();
    this->battery_level_sensor_->publish_state(battery_level);
  }

  if (this->temp_sensor_ != nullptr) {
    float temp = M5.Power.Axp2101.getInternalTemperature();
    this->temp_sensor_->publish_state(temp);
  }

  if (this->usb_voltage_sensor_ != nullptr) {
    float usb_voltage = M5.Power.Axp2101.getVBUSVoltage();
    this->usb_voltage_sensor_->publish_state(usb_voltage);
  }

  if (this->charging_sensor_ != nullptr) {
    bool is_charging = M5.Power.Axp2101.isCharging();
    this->charging_sensor_->publish_state(is_charging);
  }

  if (this->battery_present_sensor_ != nullptr) {
    bool battery_present = M5.Power.Axp2101.getBatState();
    this->battery_present_sensor_->publish_state(battery_present);
  }

  if (this->usb_present_sensor_ != nullptr) {
    bool usb_present = M5.Power.Axp2101.isVBUS();
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
  ESP_LOGCONFIG(TAG, "  Battery Present: %s", YESNO(M5.Power.Axp2101.getBatState()));
  ESP_LOGCONFIG(TAG, "  Battery Level: %.1f%%", M5.Power.getBatteryLevel());
  ESP_LOGCONFIG(TAG, "  USB Present: %s", YESNO(M5.Power.Axp2101.isVBUS()));
  ESP_LOGCONFIG(TAG, "  Charging: %s", YESNO(M5.Power.Axp2101.isCharging()));
}

}  // namespace m5cores3_pmu
}  // namespace esphome