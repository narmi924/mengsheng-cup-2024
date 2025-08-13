#ifndef __ADC_H
#define __ADC_H

#include "stm32h7xx_hal.h"

// DMA句柄
extern DMA_HandleTypeDef hdma_adc2;

// ADC句柄
extern ADC_HandleTypeDef hadc2;

// 存储ADC采样结果的缓冲区
extern uint16_t adc_buffer[4];  // 用于存储ADC2通道数据的缓冲区

// 函数声明
void MY_ADC_Init(void);  																					// ADC初始化
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);           // ADC完成转换回调
void Get_Adc_Average(uint16_t *average_value, uint8_t times);  // 计算ADC采样的平均值
void Update_LCD_Display(void);                                   // 声明Update_LCD_Display函数
#endif /* __ADC_H */
