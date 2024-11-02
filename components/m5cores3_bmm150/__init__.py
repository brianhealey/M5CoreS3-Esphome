# __init__.py
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    STATE_CLASS_MEASUREMENT,
    UNIT_MICROTESLA,
    UNIT_DEGREES,
    ICON_MAGNET,
    ICON_COMPASS,
)

DEPENDENCIES = ["board_m5cores3"]
AUTO_LOAD = ["sensor"]

m5cores3_bmm150_ns = cg.esphome_ns.namespace("m5cores3_bmm150")
M5CoreS3BMM150 = m5cores3_bmm150_ns.class_("M5CoreS3BMM150", cg.Component)

# Configuration options
CONF_MAG_X = "mag_x"
CONF_MAG_Y = "mag_y"
CONF_MAG_Z = "mag_z"
CONF_HEADING = "heading"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(M5CoreS3BMM150),
    cv.Optional(CONF_MAG_X): sensor.sensor_schema(
        unit_of_measurement=UNIT_MICROTESLA,
        accuracy_decimals=2,
        icon=ICON_MAGNET,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_MAG_Y): sensor.sensor_schema(
        unit_of_measurement=UNIT_MICROTESLA,
        accuracy_decimals=2,
        icon=ICON_MAGNET,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_MAG_Z): sensor.sensor_schema(
        unit_of_measurement=UNIT_MICROTESLA,
        accuracy_decimals=2,
        icon=ICON_MAGNET,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_HEADING): sensor.sensor_schema(
        unit_of_measurement=UNIT_DEGREES,
        accuracy_decimals=1,
        icon=ICON_COMPASS,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    if CONF_MAG_X in config:
        sens = await sensor.new_sensor(config[CONF_MAG_X])
        cg.add(var.set_mag_x_sensor(sens))

    if CONF_MAG_Y in config:
        sens = await sensor.new_sensor(config[CONF_MAG_Y])
        cg.add(var.set_mag_y_sensor(sens))

    if CONF_MAG_Z in config:
        sens = await sensor.new_sensor(config[CONF_MAG_Z])
        cg.add(var.set_mag_z_sensor(sens))

    if CONF_HEADING in config:
        sens = await sensor.new_sensor(config[CONF_HEADING])
        cg.add(var.set_heading_sensor(sens))