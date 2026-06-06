/*
 * siggen.h
 *
 *  Created on: 20 May 2026
 *      Author: Arvydas
 */

#ifndef INC_SIGGEN_H_
#define INC_SIGGEN_H_

#include "drivers.h"

typedef enum
{
	INC_1 = 1,
	INC_10 = 10,
	INC_100 = 100,
	INC_1000 = 1000

} SigGen_Inc_t;


typedef enum
{
	MODE_INC = 0,
    MODE_WAVE,
    MODE_FREQ

} SigGen_Mode_t;

typedef struct
{
    SigGen_Inc_t inc;
    SigGen_Mode_t mode;
    AD9833_Wave_t wave;
    int freq_val;


} SigGen_t;

void SigGen_NextInc(SigGen_t *gen);
void SigGen_NextWave(SigGen_t *gen);
void SigGen_NextFreq(SigGen_t *gen);
void SigGen_NextMode(SigGen_t *gen);

void SigGen_Update(SigGen_t *gen);
void LCD_Update(SigGen_t *gen);

#endif /* INC_SIGGEN_H_ */
