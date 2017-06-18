#ifndef SERIAL_H

#define SERIAL_H

#include "common.h"

void serial_init(uint32_t baud);
void serial_shut(void);
void serial_byte_tx(uint8_t byte);
int serial_byte_available(void);
uint8_t serial_byte_rx(void);
void serial_tx(char* str);
void serial_rx(char *str, int max_len);
void get_hex_string(int num , char *hex_string, int string_size);

#endif
