# __init__.py
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_ACCELERATION,
    DEVICE_CLASS_GYROSCOPE,
    STATE_CLASS_MEASUREMENT,
    UNIT_METERS_PER_SECOND_SQUARED,
    UNIT_DEGREES_PER_SECOND,
)

DEPENDENCIES = ["board_m5cores3"]
AUTO_LOAD = ["sensor"]

m5cores3_bmi270_ns = cg.esphome_ns.namespace("m5cores3_bmi270")
M5CoreS3BMI270 = m5cores3_bmi270_ns.class_("M5CoreS3BMI270", cg.Component)

# Configuration options
CONF_ACCEL_X = "accel_x"
CONF_ACCEL_Y = "accel_y"
CONF_ACCEL_Z = "accel_z"
CONF_GYRO_X = "gyro_x"
CONF_GYRO_Y = "gyro_y"
CONF_GYRO_Z = "gyro_z"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(M5CoreS3BMI270),
    cv.Optional(CONF_ACCEL_X): sensor.sensor_schema(
        unit_of_measurement=UNIT_METERS_PER_SECOND_SQUARED,
        accuracy_decimals=3,
        device_class=DEVICE_CLASS_ACCELERATION,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_ACCEL_Y): sensor.sensor_schema(
        unit_of_measurement=UNIT_METERS_PER_SECOND_SQUARED,
        accuracy_decimals=3,
        device_class=DEVICE_CLASS_ACCELERATION,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_ACCEL_Z): sensor.sensor_schema(
        unit_of_measurement=UNIT_METERS_PER_SECOND_SQUARED,
        accuracy_decimals=3,
        device_class=DEVICE_CLASS_ACCELERATION,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_GYRO_X): sensor.sensor_schema(
        unit_of_measurement=UNIT_DEGREES_PER_SECOND,
        accuracy_decimals=3,
        device_class=DEVICE_CLASS_GYROSCOPE,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_GYRO_Y): sensor.sensor_schema(
        unit_of_measurement=UNIT_DEGREES_PER_SECOND,
        accuracy_decimals=3,
        device_class=DEVICE_CLASS_GYROSCOPE,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_GYRO_Z): sensor.sensor_schema(
        unit_of_measurement=UNIT_DEGREES_PER_SECOND,
        accuracy_decimals=3,
        device_class=DEVICE_CLASS_GYROSCOPE,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    if CONF_ACCEL_X in config:
        sens = await sensor.new_sensor(config[CONF_ACCEL_X])
        cg.add(var.set_accel_x_sensor(sens))

    if CONF_ACCEL_Y in config:
        sens = await sensor.new_sensor(config[CONF_ACCEL_Y])
        cg.add(var.set_accel_y_sensor(sens))

    if CONF_ACCEL_Z in config:
        sens = await sensor.new_sensor(config[CONF_ACCEL_Z])
        cg.add(var.set_accel_z_sensor(sens))

    if CONF_GYRO_X in config:
        sens = await sensor.new_sensor(config[CONF_GYRO_X])
        cg.add(var.set_gyro_x_sensor(sens))

    if CONF_GYRO_Y in config:
        sens = await sensor.new_sensor(config[CONF_GYRO_Y])
        cg.add(var.set_gyro_y_sensor(sens))

    if CONF_GYRO_Z in config:
        sens = await sensor.new_sensor(config[CONF_GYRO_Z])
        cg.add(var.set_gyro_z_sensor(sens))