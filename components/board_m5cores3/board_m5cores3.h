#pragma once

#include <M5Unified.h>
#include "esphome/core/component.h"

namespace esphome {
namespace board_m5cores3 {

class BoardM5CoreS3 : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::WIFI + 100.0f; }
  bool is_initialized() const { return initialized_; }

protected:
  bool initialized_{false};
};

}  // namespace board_m5cores3
}  // namespace esphome