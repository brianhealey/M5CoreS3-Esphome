#include "m5cores3_bmm150.h"
#include "esphome/core/log.h"
#include <math.h>

namespace esphome {
    namespace m5cores3_bmm150 {

        static const char *TAG = "m5cores3_bmm150";

        void M5CoreS3BMM150::setup() {
            ESP_LOGCONFIG(TAG, "Setting up M5CoreS3 BMM150...");

            // The BMM150 is initialized as part of M5.Imu.begin() in the BMI270 component
            // We just need to verify it's working
            if (!M5.Imu.magAvailable()) {
                ESP_LOGE(TAG, "Failed to find BMM150!");
                this->mark_failed();
                return;
            }

            ESP_LOGCONFIG(TAG, "BMM150 initialized successfully");
        }

        void M5CoreS3BMM150::loop() {
            this->update_sensors_();
        }

        void M5CoreS3BMM150::update_sensors_() {
            float mx, my, mz;
            M5.Imu.getMag(&mx, &my, &mz);

            if (this->mag_x_sensor_ != nullptr)
                this->mag_x_sensor_->publish_state(mx);
            if (this->mag_y_sensor_ != nullptr)
                this->mag_y_sensor_->publish_state(my);
            if (this->mag_z_sensor_ != nullptr)
                this->mag_z_sensor_->publish_state(mz);

            // Calculate heading if requested
            if (this->heading_sensor_ != nullptr) {
                float heading = atan2(my, mx) * 180.0 / M_PI;
                // Convert to 0-360 range
                if (heading < 0) {
                    heading += 360.0;
                }
                this->heading_sensor_->publish_state(heading);
            }
        }

        void M5CoreS3BMM150::dump_config() {
            ESP_LOGCONFIG(TAG, "M5CoreS3 BMM150:");
            LOG_SENSOR("  ", "Magnetic Field X", this->mag_x_sensor_);
            LOG_SENSOR("  ", "Magnetic Field Y", this->mag_y_sensor_);
            LOG_SENSOR("  ", "Magnetic Field Z", this->mag_z_sensor_);
            LOG_SENSOR("  ", "Heading", this->heading_sensor_);
        }

    }  // namespace m5cores3_bmm150
}  // namespace esphome