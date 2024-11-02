#include "esphome/core/log.h"
#include "board_m5cores3.h"

namespace esphome {
namespace board_m5cores3 {

static const char *TAG = "board.m5cores3";

void BoardM5CoreS3::setup() {
    ESP_LOGI(TAG, "Setting up M5Stack Core S3");
    auto cfg = M5.config();
    cfg.clear_display = true;    // Clear display on init
    cfg.output_power = true;     // Enable power control
    cfg.internal_imu = true;    // Don't initialize IMU by default
    cfg.internal_rtc = true;    // Don't initialize RTC by default

    M5.begin(cfg);

    initialized_ = true;
    ESP_LOGI(TAG, "M5Stack Core S3 initialized successfully");
}

void BoardM5CoreS3::loop() {
    if (initialized_) {
        M5.update();  // Handle button updates etc.
    }
}

void BoardM5CoreS3::dump_config() {
    ESP_LOGCONFIG(TAG, "M5Stack Core S3:");
    ESP_LOGCONFIG(TAG, "  Initialization: %s", initialized_ ? "SUCCESS" : "FAILED");
}

}  // namespace board_m5cores3
}  // namespace esphome