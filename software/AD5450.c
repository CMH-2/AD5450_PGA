#include "AD5450.h"


void AD5450_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	HAL_GPIO_WritePin(AD5450_SYNC_N_PORT, AD5450_SYNC_N_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD5450_SDIN_PORT, AD5450_SDIN_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD5450_SCLK_PORT, AD5450_SCLK_PIN, GPIO_PIN_RESET);

	GPIO_InitStruct.Pin = AD5450_SYNC_N_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(AD5450_SYNC_N_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = AD5450_SDIN_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(AD5450_SDIN_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = AD5450_SCLK_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(AD5450_SCLK_PORT, &GPIO_InitStruct);
	
}

void AD5450_Write(uint16_t DATA)
{
	AD5450_SCLK_OFF;
	AD5450_SYNC_ON;
	AD5450_SCLK_ON;
	AD5450_SYNC_OFF;
	
	for(int i = 0; i < 16; i++)
	{
		if(DATA&0x8000)
			AD5450_SDIN_ON;
		else
			AD5450_SDIN_OFF;
		AD5450_SCLK_OFF;
		AD5450_SCLK_ON;
		DATA = DATA <<1;
	}
	AD5450_SCLK_OFF;
	AD5450_SYNC_ON;
	AD5450_SCLK_ON;
}

void AD5450_AM(uint8_t DATA)
{
	uint16_t AD_5450;
	AD_5450 = (DATA<<6)|0x003f;
	AD5450_Write(AD_5450);

}

