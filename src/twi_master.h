/*
* twi_master.h
*
* Created: 09-Jun-19 11:20:04 AM
*  Author: TEP SOVICHEA
*/


#ifndef TWI_MASTER_H_
#define TWI_MASTER_H_

#include <avr/io.h>
#include <util/twi.h>
#include <stdbool.h>

#define SUCCESS				0

#define TW_SLA_W(ADDR)		((ADDR << 1) | TW_WRITE)
#define TW_SLA_R(ADDR)		((ADDR << 1) | TW_READ)
#define TW_READ_ACK			1
#define TW_READ_NACK		0

#ifndef TW_DIR
#error  TW_DIR: should be defined
#endif
#ifndef TW_PORT
#error  TW_PORT: should be defined
#endif
#ifndef TW_SCL_PIN
#error  TW_SCL_PIN: should be defined
#endif
#ifndef TW_SDA_PIN
#error  TW_SDA_PIN: should be defined
#endif

#ifdef DEBUG_LOG
  #include <stdio.h>
  # define LOG(...)  printf(__VA_ARGS__)
#else
  # define LOG(...)
#endif

typedef uint16_t ret_code_t;

typedef enum {
	TW_FREQ_100K=100000,
	TW_FREQ_250K=250000,
	TW_FREQ_400K=400000,
} twi_freq_mode_t;

void tw_init(twi_freq_mode_t twi_freq, bool pullup_en);
ret_code_t tw_master_transmit(uint8_t slave_addr, uint8_t* p_data, uint8_t len, bool repeat_start);
ret_code_t tw_master_receive(uint8_t slave_addr, uint8_t* p_data, uint8_t len);

#endif /* TWI_MASTER_H_ */
