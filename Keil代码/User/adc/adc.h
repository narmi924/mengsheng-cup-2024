#ifndef __ADC_H
#define __ADC_H

#include "stm32h7xx_hal.h"

// DMA���
extern DMA_HandleTypeDef hdma_adc2;

// ADC���
extern ADC_HandleTypeDef hadc2;

// �洢ADC��������Ļ�����
extern uint16_t adc_buffer[4];  // ���ڴ洢ADC2ͨ�����ݵĻ�����

// ��������
void MY_ADC_Init(void);  																					// ADC��ʼ��
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);           // ADC���ת���ص�
void Get_Adc_Average(uint16_t *average_value, uint8_t times);  // ����ADC������ƽ��ֵ
void Update_LCD_Display(void);                                   // ����Update_LCD_Display����
#endif /* __ADC_H */
