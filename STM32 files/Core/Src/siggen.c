/*
 * siggen.c
 *
 *  Created on: 20 May 2026
 *      Author: Arvydas
 */


#include "siggen.h"
#include "drivers.h"

static uint8_t strInc1[] =    "Inc 1   ";
static uint8_t strInc10[] =   "Inc 10  ";
static uint8_t strInc100[] =  "Inc 100 ";
static uint8_t strInc1000[] = "Inc 1000";


static uint8_t strWaveSIN[] = "SIN";
static uint8_t strWaveTRI[] = "TRI";
static uint8_t strWaveSQR[] = "SQR";


static uint8_t strFreq[] =    "Freq(Hz):";
static uint8_t strFreqVal[5];

static uint8_t strPosInd[] =   ">";

void SigGen_NextFreq(SigGen_t *gen){

	gen->freq_val = gen->freq_val + gen->inc;
	if(gen->freq_val > 99000) gen->freq_val = 10;

}

void SigGen_NextWave(SigGen_t *gen){
	switch (gen->wave)
	{
	    case AD9833_WAVE_SIN:
	    	gen->wave = AD9833_WAVE_TRI;
	        break;

	    case AD9833_WAVE_TRI:
	    	gen->wave = AD9833_WAVE_SQR;
	        break;

	    case AD9833_WAVE_SQR:
	    default:
	    	gen->wave = AD9833_WAVE_SIN;
	    	break;
	}
}

void SigGen_NextMode(SigGen_t *gen){
	switch (gen->mode)
	{
	    case MODE_INC:
	    	gen->mode = MODE_WAVE;
	        break;

	    case MODE_WAVE:
	    	gen->mode = MODE_FREQ;
	        break;

	    case MODE_FREQ:
	    default:
	    	gen->mode = MODE_INC;
	    	break;
	}
}

void SigGen_NextInc(SigGen_t *gen){

	switch (gen->inc)
	{
    	case INC_1:
    	default:
    		gen->inc = INC_10;
    		break;

	    case INC_10:
	    	gen->inc = INC_100;
	        break;

	    case INC_100:
	    	gen->inc = INC_1000;
	        break;

	    case INC_1000:
	    	gen->inc = INC_1;
	        break;
	}
}

void SigGen_Update(SigGen_t *gen)
{

    AD9833_SetWaveform(gen->wave);
    AD9833_SetFrequency(gen->freq_val);
}

void LCD_Update(SigGen_t *gen)
{
  LCDClear();
  LCDSetCursor(1, 0);

  switch (gen->inc){
  	  case INC_1:
  	  default:
  		  LCDPrintStr(strInc1, 8);
	      break;

  	  case INC_10:
  		  LCDPrintStr(strInc10, 8);
	      break;

  	  case INC_100:
  		  LCDPrintStr(strInc100, 8);
	      break;

  	  case INC_1000:
  		  LCDPrintStr(strInc1000, 8);
	      break;
	}

  LCDSetCursor(13, 0);

  switch (gen->wave){
  	  case AD9833_WAVE_TRI:
  		  LCDPrintStr(strWaveTRI, 3);
	      break;

  	  case AD9833_WAVE_SQR:
  		  LCDPrintStr(strWaveSQR, 3);
	      break;

	  case AD9833_WAVE_SIN:
	  default:
		  LCDPrintStr(strWaveSIN, 3);
	      break;
  }



  LCDSetCursor(1, 1);
  LCDPrintStr(strFreq, 8);

  LCDSetCursor(11, 1);

  strFreqVal[0] = (gen->freq_val / 10000) % 10 + '0';
  strFreqVal[1] = (gen->freq_val / 1000) % 10 + '0';
  strFreqVal[2] = (gen->freq_val / 100) % 10 + '0';
  strFreqVal[3] = (gen->freq_val / 10) % 10 + '0';
  strFreqVal[4] = gen->freq_val % 10 + '0';

  LCDPrintStr(strFreqVal, 5);



  switch (gen->mode){
  	  case MODE_INC:
  	  default:
  		  LCDSetCursor(0, 0);
	      break;

	  case MODE_WAVE:
		  LCDSetCursor(12, 0);
	      break;

	  case MODE_FREQ:
		  LCDSetCursor(0, 1);
		  break;
	}
	LCDPrintStr(strPosInd, 1);

}
