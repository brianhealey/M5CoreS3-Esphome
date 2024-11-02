import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

board_m5cores3_ns = cg.esphome_ns.namespace('board_m5cores3')
BoardM5CoreS3 = board_m5cores3_ns.class_('BoardM5CoreS3', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(BoardM5CoreS3)
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)