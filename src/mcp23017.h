#ifndef MCP23017_H
# define MCP23017_H
#include <stdint.h>
#include "twi_master.h"

// addr 0|1|0|0|A2|A1|A0|
// all addr pin need to be pulled up

/*MCP23017 opcode*/
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

inline void mcp23017_write(uint8_t addr, uint8_t opcode, uint8_t data) {
    uint8_t payload[2];
    payload[0] = opcode;
    payload[1] = data;
    tw_master_transmit(addr, payload, 2, false);
}

inline void mcp23017_read(uint8_t addr, uint8_t opcode, uint8_t *data) {
    tw_master_transmit(addr, &opcode, 1, false);
    tw_master_receive(addr, data, 1);
}

#endif /* MCP23017_H */
