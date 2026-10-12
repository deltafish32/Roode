/**
 * @file  vl53l1_i2ccoms.h
 * @brief Contains i2c implementation of the platform
 */
 
#ifndef _VL53L1X_I2CCOMS_H_
#define _VL53L1X_I2CCOMS_H_

#include "vl53l1_types.h"
#include "esphome/components/i2c/i2c_bus.h"

/** @brief Sets the ESPHome I2C bus used for all transfers.\n
 * Must be called before any other function.
 */
void i2c_set_bus(esphome::i2c::I2CBus *bus);

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief i2c_write_multi() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_write_multi(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint8_t      *pdata,
        uint32_t      count);
/** @brief i2c_read_multi() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_read_multi(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint8_t      *pdata,
        uint32_t      count);
/** @brief i2c_write_byte() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_write_byte(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint8_t       data);
/** @brief i2c_write_word() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_write_word(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint16_t      data);
/** @brief i2c_write_Dword() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_write_Dword(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint32_t      data);
/** @brief i2c_read_byte() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_read_byte(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint8_t      *pdata);
/** @brief i2c_read_word() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_read_word(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint16_t     *pdata);
/** @brief i2c_read_Dword() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_read_Dword(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint32_t     *pdata);

#ifdef __cplusplus
}
#endif

#endif
