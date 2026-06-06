/*
 * drivers.h
 *
 *  Created on: 20 May 2026
 *      Author: Arvydas
 */

#ifndef INC_DRIVERS_H_
#define INC_DRIVERS_H_

#include <stdint.h>

typedef enum
{
    AD9833_WAVE_SIN = 0,
    AD9833_WAVE_TRI,
    AD9833_WAVE_SQR

} AD9833_Wave_t;


void AD9833_SetFrequency(uint16_t freq);
void AD9833_SetWaveform(AD9833_Wave_t wave);

void LCDSetCursor(uint8_t col, uint8_t row);
void LCDPrintStr(uint8_t *str, uint8_t len);
void LCDClear(void);
void LCDInit(void);

#endif /* INC_DRIVERS_H_ */
