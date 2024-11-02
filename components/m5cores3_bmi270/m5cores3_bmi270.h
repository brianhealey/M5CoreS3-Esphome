#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include <M5Unified.h>

namespace esphome {
    namespace m5cores3_bmi270 {

        class M5CoreS3BMI270 : public Component {
        public:
            void setup() override;
            void dump_config() override;
            float get_setup_priority() const override { return setup_priority::DATA; }
            void loop() override;

            void set_accel_x_sensor(sensor::Sensor *accel_x) { accel_x_sensor_ = accel_x; }
            void set_accel_y_sensor(sensor::Sensor *accel_y) { accel_y_sensor_ = accel_y; }
            void set_accel_z_sensor(sensor::Sensor *accel_z) { accel_z_sensor_ = accel_z; }
            void set_gyro_x_sensor(sensor::Sensor *gyro_x) { gyro_x_sensor_ = gyro_x; }
            void set_gyro_y_sensor(sensor::Sensor *gyro_y) { gyro_y_sensor_ = gyro_y; }
            void set_gyro_z_sensor(sensor::Sensor *gyro_z) { gyro_z_sensor_ = gyro_z; }

        protected:
            void update_sensors_();

            sensor::Sensor *accel_x_sensor_{nullptr};
            sensor::Sensor *accel_y_sensor_{nullptr};
            sensor::Sensor *accel_z_sensor_{nullptr};
            sensor::Sensor *gyro_x_sensor_{nullptr};
            sensor::Sensor *gyro_y_sensor_{nullptr};
            sensor::Sensor *gyro_z_sensor_{nullptr};
        };

    }  // namespace m5cores3_bmi270
}  // namespace esphome