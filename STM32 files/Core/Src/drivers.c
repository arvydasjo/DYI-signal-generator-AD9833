#include "drivers.h"
#include "main.h"

#define AD9833_MCLK    25000000UL
#define LCD_ADR        0x3E << 1

static void AD9833_Write16(uint16_t data)
{
    uint8_t buf[2];

    buf[0] = (data >> 8) & 0xFF;
    buf[1] = data & 0xFF;

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

    HAL_SPI_Transmit(&hspi1, buf, 2, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

void AD9833_SetFrequency(uint16_t freq)
{
    uint32_t freqWord;
    uint16_t lsb;
    uint16_t msb;

    freqWord = (uint32_t)(
        ((double)freq * 268435456.0) / AD9833_MCLK
    );

    lsb = 0x4000 | (freqWord & 0x3FFF);
    msb = 0x4000 | ((freqWord >> 14) & 0x3FFF);

    AD9833_Write16(lsb);
    AD9833_Write16(msb);
}

void AD9833_SetWaveform(AD9833_Wave_t wave)
{
    uint16_t ctrl = 0x2000;

    switch (wave)
    {
        case AD9833_WAVE_SIN:
            ctrl = 0x2000;
            break;

        case AD9833_WAVE_TRI:
            ctrl = 0x2002;
            break;

        case AD9833_WAVE_SQR:
            ctrl = 0x2028;
            break;

        default:
            ctrl = 0x2000;
            break;
    }

    AD9833_Write16(ctrl);
}


/* ================= LCD LOW LEVEL ================= */
void LCDSetCursor(uint8_t col, uint8_t row)
{
  uint8_t arr[2];

  col = (row == 0) ? (col | 0x80) : (col | 0xC0);

  arr[0] = 0x00;
  arr[1] = col;

  HAL_I2C_Master_Transmit(&hi2c1, LCD_ADR, arr, 2, HAL_MAX_DELAY);
}

void LCDPrintStr(uint8_t *str, uint8_t len)
{
  uint8_t arr[2];

  arr[0] = 0x40;

  for (uint8_t i = 0; i < len; i++)
  {
    arr[1] = str[i];
    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADR, arr, 2, HAL_MAX_DELAY);
  }
}

void LCDClear(void)
{
  uint8_t arr[2] = {0x00, 0x01};
  HAL_I2C_Master_Transmit(&hi2c1, LCD_ADR, arr, 2, HAL_MAX_DELAY);
  HAL_Delay(2);
}

void LCDInit(void)
{

	    HAL_Delay(50);

	    uint8_t arr[6] = {0x33, 0x32, 0x28, 0x0C, 0x06, 0x01};
	    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADR, arr, 6, HAL_MAX_DELAY);


	    HAL_Delay(5);


//	  uint8_t arr[2] = {0x00, 0x0C};
//	  HAL_I2C_Master_Transmit(&hi2c1, LCD_ADR, arr, 2, HAL_MAX_DELAY);
//
//	  arr[1] = 0x3F;
//	  HAL_I2C_Master_Transmit(&hi2c1, LCD_ADR, arr, 2, HAL_MAX_DELAY);

}


