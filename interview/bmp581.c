#include "bmp581.h"
#include "gpio.h"

// Global instance of BMP581 registers
static BMP581_registers_t bmp581_regs;

// =============================
// Low-level bus access
// =============================

// Write to registers (I2C or SPI)
static HAL_StatusTypeDef bus_write(BMP581_Handle_t *dev, uint8_t reg, const uint8_t *data, uint16_t len) {
    if (dev->if_type == BMP581_IF_I2C) {
        return HAL_I2C_Mem_Write(dev->hi2c, BMP581_I2C_ADDRESS, reg,
                                 I2C_MEMADD_SIZE_8BIT, (uint8_t*)data, len, I2C_TIMEOUT);
    } else { // SPI
        uint8_t tx[len+1];
        tx[0] = reg & 0x7F; // bit7=0 for write
        memcpy(&tx[1], data, len);

        HAL_GPIO_WritePin(BMP581_SPI_CS_PORT, BMP581_SPI_CS_PIN, GPIO_PIN_RESET);
        HAL_StatusTypeDef status = HAL_SPI_Transmit(dev->hspi, tx, len+1, HAL_MAX_DELAY);
        HAL_GPIO_WritePin(BMP581_SPI_CS_PORT, BMP581_SPI_CS_PIN, GPIO_PIN_SET);
        return status;
    }
}

// Read from registers (I2C or SPI)
static HAL_StatusTypeDef bus_read(BMP581_Handle_t *dev, uint8_t reg, uint8_t *data, uint16_t len) {
    if (dev->if_type == BMP581_IF_I2C) {
        return HAL_I2C_Mem_Read(dev->hi2c, BMP581_I2C_ADDRESS, reg,
                                I2C_MEMADD_SIZE_8BIT, data, len, I2C_TIMEOUT);
    } else { // SPI
        uint8_t tx[1];
        tx[0] = reg | 0x80; // bit7=1 for read

        HAL_GPIO_WritePin(BMP581_SPI_CS_PORT, BMP581_SPI_CS_PIN, GPIO_PIN_RESET);
        HAL_StatusTypeDef status = HAL_SPI_Transmit(dev->hspi, tx, 1, HAL_MAX_DELAY);
        if (status == HAL_OK) {
            status = HAL_SPI_Receive(dev->hspi, data, len, HAL_MAX_DELAY);
        }
        HAL_GPIO_WritePin(BMP581_SPI_CS_PORT, BMP581_SPI_CS_PIN, GPIO_PIN_SET);
        return status;
    }
}

// Helper function: convert 3 bytes → 24-bit signed integer
static inline int32_t get_24bit(const uint8_t *d) {
    return (int32_t)((d[2] << 16) | (d[1] << 8) | d[0]);
}

// =============================
// High-level API
// =============================

HAL_StatusTypeDef BMP581_Init(BMP581_Handle_t *dev) {
    // Reset
    uint8_t cmd = BMP581_CMD_RESET;
    if (bus_write(dev, BMP581_REG_CMD, &cmd, 1) != HAL_OK) return HAL_ERROR;
    HAL_Delay(5);

    // Chip ID
    uint8_t chip_id = 0;
    if (bus_read(dev, BMP581_REG_CHIP_ID, &chip_id, 1) != HAL_OK) return HAL_ERROR;
    if (chip_id != BMP581_CHIP_ID_PRIM) return HAL_ERROR;

    // Basic configuration (example)
    bmp581_regs.OSR_CONFIG.Val.BitField.osr_t = BMP581_OSR_128X;
    bmp581_regs.OSR_CONFIG.Val.BitField.osr_p = BMP581_OSR_128X;
    bmp581_regs.OSR_CONFIG.Val.BitField.press_en = 1;
    if (bus_write(dev, BMP581_REG_OSR_CONFIG, &bmp581_regs.OSR_CONFIG.Value, 1) != HAL_OK) return HAL_ERROR;

    bmp581_regs.ODR_CONFIG.Val.BitField.odr = BMP581_ODR_5_HZ;
    bmp581_regs.ODR_CONFIG.Val.BitField.pwr_mode = BMP581_PWRMODE_NORMAL;
    if (bus_write(dev, BMP581_REG_ODR_CONFIG, &bmp581_regs.ODR_CONFIG.Value, 1) != HAL_OK) return HAL_ERROR;

    return HAL_OK;
}

// Example: read temperature and pressure
HAL_StatusTypeDef BMP581_Get_TempPressData(BMP581_Handle_t *dev, BMP581_sensor_data_t *data) {
    uint8_t buf[6];
    if (bus_read(dev, BMP581_REG_TEMP_DATA_XLSB, buf, 6) != HAL_OK) return HAL_ERROR;

    int32_t raw_t = get_24bit(&buf[0]);
    int32_t raw_p = get_24bit(&buf[3]);

    data->temperature = (float)raw_t / TEMP_COEFF;
    data->pressure    = (float)raw_p / PRESS_COEFF;
    return HAL_OK;
}
