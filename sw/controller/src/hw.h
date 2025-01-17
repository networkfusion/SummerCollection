#ifndef HW_H__
#define HW_H__


#include <stdint.h>


#define GPIO_PORT_PIN(p, n)     ((((p) & 0x07) << 4) | ((n) & 0x0F))

typedef enum {
    GPIO_ID_N64_RESET   = GPIO_PORT_PIN(0, 0),
    GPIO_ID_N64_CIC_CLK = GPIO_PORT_PIN(0, 1),
    GPIO_ID_N64_CIC_DQ  = GPIO_PORT_PIN(0, 2),
    GPIO_ID_LED         = GPIO_PORT_PIN(0, 3),
    GPIO_ID_SPI_CS      = GPIO_PORT_PIN(0, 4),
    GPIO_ID_SPI_CLK     = GPIO_PORT_PIN(0, 5),
    GPIO_ID_SPI_MISO    = GPIO_PORT_PIN(0, 6),
    GPIO_ID_SPI_MOSI    = GPIO_PORT_PIN(0, 7),
    GPIO_ID_UART_TX     = GPIO_PORT_PIN(0, 9),
    GPIO_ID_UART_RX     = GPIO_PORT_PIN(0, 10),
    GPIO_ID_FPGA_INT    = GPIO_PORT_PIN(1, 2),
    GPIO_ID_I2C_SCL     = GPIO_PORT_PIN(1, 6),
    GPIO_ID_I2C_SDA     = GPIO_PORT_PIN(1, 7),
    GPIO_ID_RTC_MFP     = GPIO_PORT_PIN(1, 9),
} gpio_id_t;

typedef enum {
    GPIO_IRQ_FALLING    = 0b01,
    GPIO_IRQ_RISING     = 0b10,
} gpio_irq_t;

typedef enum {
    TIM_ID_CIC          = 0,
    TIM_ID_RTC          = 1,
    TIM_ID_SD           = 2,
    TIM_ID_DD           = 3,
    TIM_ID_LED          = 4,
} tim_id_t;

typedef enum {
    SPI_TX,
    SPI_RX,
} spi_direction_t;

typedef uint64_t hw_flash_t;

typedef enum {
    LOADER_FLAGS_UPDATE_MCU = (1 << 0),
    LOADER_FLAGS_UPDATE_FPGA = (1 << 1),
    LOADER_FLAGS_UPDATE_BOOTLOADER = (1 << 2),
} loader_parameters_flags_t;

typedef struct {
    uint32_t magic;
    loader_parameters_flags_t flags;
    uint32_t mcu_address;
    uint32_t fpga_address;
    uint32_t bootloader_address;
} loader_parameters_t;


void hw_gpio_irq_setup (gpio_id_t id, gpio_irq_t irq, void (*callback)(void));
uint32_t hw_gpio_get (gpio_id_t id);
void hw_gpio_set (gpio_id_t id);
void hw_gpio_reset (gpio_id_t id);
void hw_uart_read (uint8_t *data, int length);
void hw_uart_write (uint8_t *data, int length);
void hw_uart_wait_busy (void);
void hw_spi_start (void);
void hw_spi_stop (void);
void hw_spi_trx (uint8_t *data, int length, spi_direction_t direction);
void hw_i2c_read (uint8_t i2c_address, uint8_t address, uint8_t *data, uint8_t length, void (*callback)(void));
void hw_i2c_write (uint8_t i2c_address, uint8_t address, uint8_t *data, uint8_t length, void (*callback)(void));
uint32_t hw_i2c_get_error (void);
void hw_i2c_raw (uint8_t i2c_address, uint8_t *tx_data, uint8_t tx_length, uint8_t *rx_data, uint8_t rx_length);
void hw_i2c_disable_irq (void);
void hw_i2c_enable_irq (void);
void hw_tim_setup (tim_id_t id, uint16_t delay, void (*callback)(void));
void hw_tim_stop (tim_id_t id);
void hw_tim_disable_irq (tim_id_t id);
void hw_tim_enable_irq (tim_id_t id);
void hw_delay_ms (uint32_t ms);
void hw_crc32_reset (void);
uint32_t hw_crc32_calculate (uint8_t *data, uint32_t length);
uint32_t hw_flash_size (void);
void hw_flash_erase (void);
void hw_flash_program (uint32_t offset, hw_flash_t value);
hw_flash_t hw_flash_read (uint32_t offset);
void hw_reset (loader_parameters_t *parameters);
void hw_loader_get_parameters (loader_parameters_t *parameters);
void hw_set_vector_table (uint32_t offset);
void hw_init (void);
void hw_loader_init (void);
void hw_primer_init (void);


#endif
