import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, binary_sensor
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_VOLTAGE,
    DEVICE_CLASS_BATTERY,
    DEVICE_CLASS_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    UNIT_VOLT,
    UNIT_PERCENT,
    UNIT_CELSIUS,
)

DEPENDENCIES = ["board_m5cores3"]
AUTO_LOAD = ["sensor", "binary_sensor"]

m5cores3_pmu_ns = cg.esphome_ns.namespace("m5cores3_pmu")
M5CoreS3PMU = m5cores3_pmu_ns.class_("M5CoreS3PMU", cg.Component)

# Configuration options
CONF_BATTERY_VOLTAGE = "battery_voltage"
CONF_BATTERY_LEVEL = "battery_level"
CONF_TEMPERATURE = "temperature"
CONF_USB_VOLTAGE = "usb_voltage"
CONF_CHARGING = "charging"
CONF_BATTERY_PRESENT = "battery_present"
CONF_USB_PRESENT = "usb_present"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(M5CoreS3PMU),
    cv.Optional(CONF_BATTERY_VOLTAGE): sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=3,
        device_class=DEVICE_CLASS_VOLTAGE,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_BATTERY_LEVEL): sensor.sensor_schema(
        unit_of_measurement=UNIT_PERCENT,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_BATTERY,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_USB_VOLTAGE): sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=3,
        device_class=DEVICE_CLASS_VOLTAGE,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_CHARGING): binary_sensor.binary_sensor_schema(),
    cv.Optional(CONF_BATTERY_PRESENT): binary_sensor.binary_sensor_schema(),
    cv.Optional(CONF_USB_PRESENT): binary_sensor.binary_sensor_schema(),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    if CONF_BATTERY_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_BATTERY_VOLTAGE])
        cg.add(var.set_battery_voltage_sensor(sens))

    if CONF_BATTERY_LEVEL in config:
        sens = await sensor.new_sensor(config[CONF_BATTERY_LEVEL])
        cg.add(var.set_battery_level_sensor(sens))

    if CONF_TEMPERATURE in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE])
        cg.add(var.set_temp_sensor(sens))

    if CONF_USB_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_USB_VOLTAGE])
        cg.add(var.set_usb_voltage_sensor(sens))

    if CONF_CHARGING in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_CHARGING])
        cg.add(var.set_charging_binary_sensor(sens))

    if CONF_BATTERY_PRESENT in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_BATTERY_PRESENT])
        cg.add(var.set_battery_present_binary_sensor(sens))

    if CONF_USB_PRESENT in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_USB_PRESENT])
        cg.add(var.set_usb_present_binary_sensor(sens))