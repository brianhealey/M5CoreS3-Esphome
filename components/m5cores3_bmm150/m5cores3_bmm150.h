#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include <M5Unified.h>

namespace esphome {
    namespace m5cores3_bmm150 {

        class M5CoreS3BMM150 : public Component {
        public:
            void setup() override;
            void dump_config() override;
            float get_setup_priority() const override { return setup_priority::DATA; }
            void loop() override;

            void set_mag_x_sensor(sensor::Sensor *mag_x) { mag_x_sensor_ = mag_x; }
            void set_mag_y_sensor(sensor::Sensor *mag_y) { mag_y_sensor_ = mag_y; }
            void set_mag_z_sensor(sensor::Sensor *mag_z) { mag_z_sensor_ = mag_z; }
            void set_heading_sensor(sensor::Sensor *heading) { heading_sensor_ = heading; }

        protected:
            void update_sensors_();

            sensor::Sensor *mag_x_sensor_{nullptr};
            sensor::Sensor *mag_y_sensor_{nullptr};
            sensor::Sensor *mag_z_sensor_{nullptr};
            sensor::Sensor *heading_sensor_{nullptr};

            bool mag_initialized_{false};
        };

    }  // namespace m5cores3_bmm150
}  // namespace esphome