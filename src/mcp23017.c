#include "mcp23017.h"

void mcp23017_write(uint8_t addr, uint8_t opcode, uint8_t data) {
    uint8_t payload[2];
    payload[0] = opcode;
    payload[1] = data;
    tw_master_transmit(addr, payload, 2, false);
}

void mcp23017_read(uint8_t addr, uint8_t opcode, uint8_t *data) {
    tw_master_transmit(addr, &opcode, 1, false);
    tw_master_receive(addr, data, 1);
}
