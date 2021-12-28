#include "lcd_command.h"

#include "mcp23017.h"
#include "twi_master.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

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
static inline void scan_matrix(char key_matrix[4][4]) {
    uint8_t payload;

    for (int i = 0; i < 4; i++) {
        mcp23017_write(MCP23S08_ADDR, GPIOA, (0b10000000 >> i));
        mcp23017_read(MCP23S08_ADDR, GPIOA, &payload);
        mcp23017_write(MCP23S08_ADDR, GPIOB, payload);
        for (int j = 0; j < 4; j++) {
            key_matrix[i][j] = (payload >> j) & 0b00000001;
        }
    }
    mcp23017_write(MCP23S08_ADDR, GPIOA, 0b00000000);
}

char key_matrix_char[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'},
};

void build_key_string(char key_matrix[4][4], char *buffer) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (key_matrix[i][j] == 1) {
                *buffer = key_matrix_char[i][j];
                buffer++;
            }
        }
    }
}

int main(void)
{
    char key_matrix[4][4] = {
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
    };
    LCD_Init();
    LCD_String  ("Wazaaaa");
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

    mcp23017_write(MCP23S08_ADDR, IODIRA, 0b00001111);
    mcp23017_write(MCP23S08_ADDR, IODIRB, 0b00000000);
    char buffer[17];
    while (1) {
        memset(buffer, ' ', 16);
        buffer[16]= '\0';
        /*uint8_t data;*/
        /*
        mcp23017_write(MCP23S08_ADDR, GPIOA, 0b10000000);
        mcp23017_read(MCP23S08_ADDR, GPIOA, &data);
        mcp23017_write(MCP23S08_ADDR, GPIOB, data);
        PORTB ^= _BV(PB1);
        printBits(&data);
        _delay_ms(200);
        mcp23017_write(MCP23S08_ADDR, GPIOA, 0b01000000);
        mcp23017_read(MCP23S08_ADDR, GPIOA, &data);
        mcp23017_write(MCP23S08_ADDR, GPIOB, data);
        PORTB ^= _BV(PB1);
        printBits(&data);
        _delay_ms(200);
        */
        scan_matrix(key_matrix);
        build_key_string(key_matrix, (char *)buffer);
        PORTB ^= _BV(PB1);
        /*LCD_Command (0x01);*/
        LCD_String(buffer);
        LCD_Command(0xC0);
        _delay_ms(200);
    }
}
