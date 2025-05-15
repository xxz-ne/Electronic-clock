#ifndef __SMG_H__
#define __SMG_H__
#include "stdint.h"

#define spi_handle hspi1
#define smg_num 6
#define z0 0xC0
#define z1 0xF9
#define z2 0xA4
#define z3 0xB0 
#define z4 0x99
#define z5 0x92
#define z6 0x82
#define z7 0xF8
#define z8 0x80
#define z9 0x90
#define zz 0xFF

static uint8_t NUM_USE[11]={z0,z1,z2,z3,z4,z5,z6,z7,z8,z9,zz};

void Setnum(uint32_t * pcount_time, uint16_t *time, uint8_t select, _Bool INC1, _Bool DEC1);
void smg_Display(uint8_t* pdata);
void setdata(uint16_t *time, uint8_t select, uint8_t* pdata);

void test_clock(uint16_t *time, uint8_t* pdata);
#endif
