#include "m5cores3_bmi270.h"
#include "esphome/core/log.h"

namespace esphome {
    namespace m5cores3_bmi270 {

        static const char *TAG = "m5cores3_bmi270";

        void M5CoreS3BMI270::setup() {
            ESP_LOGCONFIG(TAG, "Setting up M5CoreS3 BMI270...");

            if (!M5.Imu.begin()) {
                ESP_LOGE(TAG, "Failed to initialize BMI270!");
                this->mark_failed();
                return;
            }

            ESP_LOGCONFIG(TAG, "BMI270 initialized successfully");
        }

        void M5CoreS3BMI270::loop() {
            this->update_sensors_();
        }

        void M5CoreS3BMI270::update_sensors_() {
            float ax, ay, az, gx, gy, gz;
            M5.Imu.getAccel(&ax, &ay, &az);
            M5.Imu.getGyro(&gx, &gy, &gz);

            if (this->accel_x_sensor_ != nullptr)
                this->accel_x_sensor_->publish_state(ax);
            if (this->accel_y_sensor_ != nullptr)
                this->accel_y_sensor_->publish_state(ay);
            if (this->accel_z_sensor_ != nullptr)
                this->accel_z_sensor_->publish_state(az);

            if (this->gyro_x_sensor_ != nullptr)
                this->gyro_x_sensor_->publish_state(gx);
            if (this->gyro_y_sensor_ != nullptr)
                this->gyro_y_sensor_->publish_state(gy);
            if (this->gyro_z_sensor_ != nullptr)
                this->gyro_z_sensor_->publish_state(gz);
        }

        void M5CoreS3BMI270::dump_config() {
            ESP_LOGCONFIG(TAG, "M5CoreS3 BMI270:");
            LOG_SENSOR("  ", "Acceleration X", this->accel_x_sensor_);
            LOG_SENSOR("  ", "Acceleration Y", this->accel_y_sensor_);
            LOG_SENSOR("  ", "Acceleration Z", this->accel_z_sensor_);
            LOG_SENSOR("  ", "Gyroscope X", this->gyro_x_sensor_);
            LOG_SENSOR("  ", "Gyroscope Y", this->gyro_y_sensor_);
            LOG_SENSOR("  ", "Gyroscope Z", this->gyro_z_sensor_);
        }

    }  // namespace m5cores3_bmi270
}  // namespace esphome