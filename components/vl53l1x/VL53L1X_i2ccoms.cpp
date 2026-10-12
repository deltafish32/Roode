#include "VL53L1X_i2ccoms.h"
#include "vl53l1_error_codes.h"

// ESPHome I2C bus implementation of the platform, replacing the original Arduino Wire one.
// Addresses passed in by the ULD API are 8-bit (e.g. 0x52), the bus expects 7-bit.

#define I2C_REGISTER_SIZE 2
#define I2C_MAX_DATA_SIZE 64

static esphome::i2c::I2CBus *i2c_bus = nullptr;

void i2c_set_bus(esphome::i2c::I2CBus *bus) {
    i2c_bus = bus;
}

int8_t i2c_write_multi(uint8_t deviceAddress, uint16_t registerAddress, uint8_t *pdata, uint32_t count) {
    if (i2c_bus == nullptr || count > I2C_MAX_DATA_SIZE) {
        return VL53L1_ERROR_CONTROL_INTERFACE;
    }
    uint8_t buffer[I2C_REGISTER_SIZE + I2C_MAX_DATA_SIZE];
    buffer[0] = registerAddress >> 8;
    buffer[1] = registerAddress & 0xFF;
    memcpy(buffer + I2C_REGISTER_SIZE, pdata, count);

    auto err = i2c_bus->write_readv((deviceAddress >> 1) & 0x7F, buffer, I2C_REGISTER_SIZE + count, nullptr, 0);
    return err == esphome::i2c::ERROR_OK ? VL53L1_ERROR_NONE : VL53L1_ERROR_CONTROL_INTERFACE;
}

int8_t i2c_read_multi(uint8_t deviceAddress, uint16_t registerAddress, uint8_t *pdata, uint32_t count) {
    if (i2c_bus == nullptr) {
        return VL53L1_ERROR_CONTROL_INTERFACE;
    }
    uint8_t buffer[I2C_REGISTER_SIZE];
    buffer[0] = registerAddress >> 8;
    buffer[1] = registerAddress & 0xFF;

    auto err = i2c_bus->write_readv((deviceAddress >> 1) & 0x7F, buffer, I2C_REGISTER_SIZE, pdata, count);
    return err == esphome::i2c::ERROR_OK ? VL53L1_ERROR_NONE : VL53L1_ERROR_CONTROL_INTERFACE;
}

int8_t i2c_write_byte(uint8_t deviceAddress, uint16_t registerAddress, uint8_t data) {
    return i2c_write_multi(deviceAddress, registerAddress, &data, 1);
}

int8_t i2c_write_word(uint8_t deviceAddress, uint16_t registerAddress, uint16_t data) {
    uint8_t buff[2];
    buff[1] = data & 0xFF;
    buff[0] = data >> 8;
    return i2c_write_multi(deviceAddress, registerAddress, buff, 2);
}

int8_t i2c_write_Dword(uint8_t deviceAddress, uint16_t registerAddress, uint32_t data) {
    uint8_t buff[4];

    buff[3] = data & 0xFF;
    buff[2] = data >> 8;
    buff[1] = data >> 16;
    buff[0] = data >> 24;

    return i2c_write_multi(deviceAddress, registerAddress, buff, 4);
}

int8_t i2c_read_byte(uint8_t deviceAddress, uint16_t registerAddress, uint8_t *data) {
    return i2c_read_multi(deviceAddress, registerAddress, data, 1);
}

int8_t i2c_read_word(uint8_t deviceAddress, uint16_t registerAddress, uint16_t *data) {
    uint8_t buff[2];
    int r = i2c_read_multi(deviceAddress, registerAddress, buff, 2);

    uint16_t tmp;
    tmp = buff[0];
    tmp <<= 8;
    tmp |= buff[1];
    *data = tmp;

    return r;
}

int8_t i2c_read_Dword(uint8_t deviceAddress, uint16_t registerAddress, uint32_t *data) {
    uint8_t buff[4];
    int r = i2c_read_multi(deviceAddress, registerAddress, buff, 4);

    uint32_t tmp;
    tmp = buff[0];
    tmp <<= 8;
    tmp |= buff[1];
    tmp <<= 8;
    tmp |= buff[2];
    tmp <<= 8;
    tmp |= buff[3];

    *data = tmp;

    return r;
}
