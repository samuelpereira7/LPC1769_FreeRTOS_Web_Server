/*
 * OLED_display.c
 *
 *  Created on: 15 de abr de 2018
 *      Author: samuelpereira
 */


#include "OLED_display.h"
#include "oled.h"

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_ssp.h"

static void OLED_display_init_ssp(void);

void OLED_display_init_ssp(void)
{
	SSP_CFG_Type SSP_ConfigStruct;
	PINSEL_CFG_Type PinCfg;

	/*
	 * Initialize SPI pin connect
	 * P0.7 - SCK;
	 * P0.8 - MISO
	 * P0.9 - MOSI
	 * P2.2 - SSEL - used as GPIO
	 */
	PinCfg.Funcnum = 2;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 7;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 8;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 9;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Funcnum = 0;
	PinCfg.Portnum = 2;
	PinCfg.Pinnum = 2;
	PINSEL_ConfigPin(&PinCfg);

	SSP_ConfigStructInit(&SSP_ConfigStruct);

	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(LPC_SSP1, &SSP_ConfigStruct);

	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP1, ENABLE);
}

void OLED_display_init (void)
{
	OLED_display_init_ssp();
	oled_init();

	OLED_display_clearScreen();
}

void OLED_display_fillRect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	oled_fillRect(x0, y0, x1, y1, OLED_COLOR_WHITE);
}

void OLED_display_clearScreen(void)
{
	oled_clearScreen(OLED_COLOR_WHITE);
}

void OLED_display_putString(uint8_t x, uint8_t y, uint8_t *pStr)
{
	oled_putString(x, y, pStr, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

