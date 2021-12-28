#include "lcd_command.h"

#include "twi_master.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define MCP23S08_ADDR  0b0100000 // address of io expander
// addr 0|1|0|0|A2|A1|A0|
// all addr pin need to be pulled up

/*MCP23S08_ADDR*/
/*
#define IODIR   0x00
#define IPOL    0x01
#define GPINTEN 0x02
#define DEFVAL  0x03
#define INTCON  0x04
#define IOCON   0x05
#define GPPU    0x06
#define INTF    0x07
#define INTCAP  0x08 //(Read-only)
#define GPIO    0x09
#define OLAT    0x0A
*/

/*MCP23017_ADDR*/
/*IOCON.bank = 0*/
#define IODIRA   0x00
#define IODIRB   0x01
#define IPOLA    0x02
#define IPOLB    0x03
#define GPINTENA 0x04
#define GPINTENB 0x05
#define DEFVALA  0x06
#define DEFVALB  0x07
#define INTCONA  0x08
#define INTCONB  0x09
#define IOCONA   0x0A
#define IOCONB   0x0B
#define GPPUA    0x0C
#define GPPUB    0x0D
#define INTFA    0x0E
#define INTFB    0x0F
#define INTCAPA  0x10
#define INTCAPB  0x11
#define GPIOA    0x12
#define GPIOB    0x13
#define OLATA    0x14
#define OLATB    0x15

static inline uint8_t port_b_select(int i) {
    if (i == 0) {
        return _BV(PB1);
    }
    else if (i == 1) {
        return _BV(PB2);
    }
    else if (i == 2) {
        return _BV(PB3);
    }
    else {
        return _BV(PB4);
    }
}


// spi
/*
#define P_SCK PB5
#define P_MISO PB4
#define P_MOSI PB3
#define P_SS PB2

#define DDR_SPI DDRB
#define DD_SCK DDB5
#define DD_MISO DDB4
#define DD_MOSI DDB3
#define DD_SS DDB2

static inline void SPI_MasterInit(void){
    // Set MOSI and SCK output, all others input
    DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
    DDR_SPI &= ~(_BV(P_MISO));
    // Enable SPI, Master, set clock rate fck/16
    //SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
    // Enable SPI, Master, set clock rate fck/2
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
    SPSR = (1<<SPI2X);

    PORTB |= _BV(P_SS) | _BV(P_MISO);
}

static inline void SPI_MasterTransmit(char cData)
{
    // Start transmission
    SPDR = cData;
    // Wait for transmission complete
    while(!(SPSR & (1<<SPIF)));
}

static inline void chip_select(void) {
    PORTB &= ~(_BV(P_SS));
}

static inline void chip_unselect(void) {
    PORTB |= _BV(P_SS);
}

static inline void spi_transmit(uint8_t opcode, uint8_t addr, uint8_t bit) {
    chip_select();
    SPI_MasterTransmit(opcode);
    SPI_MasterTransmit(addr);
    SPI_MasterTransmit(bit);
    chip_unselect();
}

void SPI_tests(void) {
    SPI_MasterInit();
    spi_transmit(MCP23S08_ADDR, IODIR, 0b00000000); // all as output

    while (1) {
        spi_transmit(MCP23S08_ADDR, GPIO, 0b11111111);
        PORTB ^= _BV(PB1);
        //_delay_ms(100);
        spi_transmit(MCP23S08_ADDR, GPIO, 0b00000000);
        PORTB ^= _BV(PB1);
        //_delay_ms(100);
    }
}
*/

static inline void mcp_write(uint8_t addr, uint8_t opcode, uint8_t data) {
    uint8_t payload[2];
    payload[0] = opcode;
    payload[1] = data;
    tw_master_transmit(addr, payload, 2, false);
}

static inline void mcp_read(uint8_t addr, uint8_t opcode, uint8_t *data) {
    tw_master_transmit(addr, &opcode, 1, false);
    tw_master_receive(addr, data, 1);
}

static inline void scan(uint8_t def) {
    (void)def;
    /*uint8_t payload;*/

    /*for (int i = 0; i < 1; i++) {*/
        /*payload = def | (1 << i);*/
        /*mcp_write(MCP23S08_ADDR, IODIRB, payload);*/
        /*mcp_read(MCP23S08_ADDR, IODIRA, &payload);*/
        /*mcp_write(MCP23S08_ADDR, IODIRA, payload << 4);*/
    /*}*/
    /*mcp_write(MCP23S08_ADDR, IODIRB, 0b00000001);*/
}

void printBits(const uint8_t *payload)
{
    char string[9] = {};

    for (int j = 7; j >= 0; j--) {
        string[j] = '0' + ((*payload >> j) & 1);
    }
    string[8] = '\0';
    LCD_String(string);
    LCD_Command(0xC0);
}

/*int timer_init() {*/
    /*(1/(F/1024))*1000*/
/*}*/

int main(void)
{
    LCD_Init();
    LCD_String  ("Emma je t aime");
    /*LCD_String("Hello World");*/
    LCD_Command(0xC0);
    // disable power-reduction just in case
    PRR = 0x00;
    DDRB = _BV(PB1); //only enable pb1 as output for now
    /*
    _delay_ms(100);
    SPI_tests();
    */
    tw_init(TW_FREQ_100K, false);

    mcp_write(MCP23S08_ADDR, IODIRA, 0b00001111);
    mcp_write(MCP23S08_ADDR, IODIRB, 0b00000000);

    while (1) {
        uint8_t data;
        /*
        mcp_read(MCP23S08_ADDR, GPIOA, &data);
        mcp_write(MCP23S08_ADDR, GPIOA, 0b10101111);
        mcp_write(MCP23S08_ADDR, GPIOB, data);
        PORTB ^= _BV(PB1);
        _delay_ms(200);
        mcp_write(MCP23S08_ADDR, GPIOA, 0b00000000);
        mcp_write(MCP23S08_ADDR, GPIOB, 0b00000000);
        */
        mcp_write(MCP23S08_ADDR, GPIOA, 0b10000000);
        mcp_read(MCP23S08_ADDR, GPIOA, &data);
        mcp_write(MCP23S08_ADDR, GPIOB, data);
        printBits(&data);
        _delay_ms(200);
        mcp_write(MCP23S08_ADDR, GPIOA, 0b01000000);
        mcp_read(MCP23S08_ADDR, GPIOA, &data);
        mcp_write(MCP23S08_ADDR, GPIOB, data);
        printBits(&data);
        _delay_ms(200);
        /*PORTB ^= _BV(PB1);*/
        /*_delay_ms(200);*/
        /*mcp_write(MCP23S08_ADDR, IODIRB, 0b00000001);*/
        /*PORTB ^= _BV(PB1);*/
        /*_delay_ms(200);*/
        /*mcp_write(MCP23S08_ADDR, IODIRB, 0b11111111);*/
    }
}
