#ifndef SYS_H__
#define SYS_H__


#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


#define DEBUG_ENABLED


typedef volatile uint8_t            io8_t;
typedef volatile uint32_t           io32_t;


#define RAM_BASE                    (0x00000000UL)
#define RAM                         (*((io32_t *) RAM_BASE))


#define BOOTLOADER_BASE             (0x10000000UL)
#define BOOTLOADER                  (*((io32_t *) BOOTLOADER_BASE))


typedef volatile struct gpio_regs {
    io8_t ODR;
    io8_t IDR;
    io8_t OER;
    io8_t __padding;
} gpio_regs_t;

#define GPIO_BASE                   (0x20000000UL)
#define GPIO                        ((gpio_regs_t *) GPIO_BASE)


typedef volatile struct i2c_regs {
    io32_t SCR;
    io32_t DR;
} i2c_regs_t;

#define I2C_BASE                    (0x30000000UL)
#define I2C                         ((i2c_regs_t *) I2C_BASE)

#define I2C_SCR_START               (1 << 0)
#define I2C_SCR_STOP                (1 << 1)
#define I2C_SCR_MACK                (1 << 2)
#define I2C_SCR_ACK                 (1 << 3)
#define I2C_SCR_BUSY                (1 << 4)


typedef volatile struct usb_regs {
    io32_t SCR;
    io8_t DR;
    io8_t __padding[3];
} usb_regs_t;

#define USB_BASE                    (0x40000000UL)
#define USB                         ((usb_regs_t *) USB_BASE)

#define USB_SCR_RXNE                (1 << 0)
#define USB_SCR_TXE                 (1 << 1)
#define USB_SCR_FLUSH_RX            (1 << 2)
#define USB_SCR_FLUSH_TX            (1 << 3)


typedef volatile struct uart_regs {
    io32_t SCR;
    io8_t DR;
    io8_t __padding[3];
} uart_regs_t;

#define UART_BASE                   (0x50000000UL)
#define UART                        ((uart_regs_t *) UART_BASE)

#define UART_SCR_RXNE               (1 << 0)
#define UART_SCR_TXE                (1 << 1)


typedef volatile struct dma_regs {
    io32_t SCR;
    io32_t MADDR;
    io32_t ID_LEN;
} dma_regs_t;

#define DMA_BASE                    (0x60000000UL)
#define DMA                         ((dma_regs_t *) DMA_BASE)

#define DMA_SCR_START               (1 << 0)
#define DMA_SCR_STOP                (1 << 1)
#define DMA_SCR_DIR                 (1 << 2)
#define DMA_SCR_BUSY                (1 << 3)


typedef volatile struct cfg_regs {
    io32_t SCR;
    io32_t DD_OFFSET;
    io32_t SAVE_OFFSET;
    io8_t CMD;
    io8_t __padding[3];
    io32_t DATA[2];
} cfg_regs_t;

#define CFG_BASE                    (0x70000000UL)
#define CFG                         ((cfg_regs_t *) CFG_BASE)

#define CFG_SCR_SDRAM_SWITCH        (1 << 0)
#define CFG_SCR_SDRAM_WRITABLE      (1 << 1)
#define CFG_SCR_DD_EN               (1 << 2)
#define CFG_SCR_SRAM_EN             (1 << 3)
#define CFG_SCR_SRAM_BANKED         (1 << 4)
#define CFG_SCR_FLASHRAM_EN         (1 << 5)
#define CFG_SCR_CMD_ERROR           (1 << 28)
#define CFG_SCR_USB_WAITING         (1 << 29)
#define CFG_SCR_CPU_BUSY            (1 << 30)
#define CFG_SCR_CPU_READY           (1 << 31)


#define SDRAM_BASE                  (0x80000000UL)
#define SDRAM                       (*((io32_t *) SDRAM_BASE))
#define SDRAM_SIZE                  (64 * 1024 * 1024)


typedef volatile struct flashram_regs {
    io32_t SCR;
    io32_t __padding[31];
    io32_t BUFFER[32];
} flashram_regs_t;

#define FLASHRAM_BASE               (0x90000000UL)
#define FLASHRAM                    ((flashram_regs_t *) FLASHRAM_BASE)

#define FLASHRAM_OPERATION_PENDING  (1 << 0)
#define FLASHRAM_OPERATION_DONE     (1 << 1)
#define FLASHRAM_WRITE_OR_ERASE     (1 << 2)
#define FLASHRAM_SECTOR_OR_ALL      (1 << 3)
#define FLASHRAM_PAGE_BIT           (8)


typedef volatile struct joybus_regs {
    io32_t SCR;
    io32_t DATA[3];
} joybus_regs_t;

#define JOYBUS_BASE                 (0xA0000000UL)
#define JOYBUS                      ((joybus_regs_t *) JOYBUS_BASE)

#define JOYBUS_SCR_RX_READY         (1 << 0)
#define JOYBUS_SCR_RX_STOP_BIT      (1 << 1)
#define JOYBUS_SCR_TX_START         (1 << 2)
#define JOYBUS_SCR_TX_BUSY          (1 << 3)
#define JOYBUS_SCR_RX_RESET         (1 << 6)
#define JOYBUS_SCR_TX_RESET         (1 << 7)
#define JOYBUS_SCR_RX_LENGTH_BIT    (8)
#define JOYBUS_SCR_RX_LENGTH_MASK   (0x7F << JOYBUS_SCR_RX_LENGTH_BIT)
#define JOYBUS_SCR_TX_LENGTH_BIT    (16)


void reset_handler (void);
void app_handler (void);


#endif
