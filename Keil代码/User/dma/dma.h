#ifndef __DMA_H
#define __DMA_H

#include "stm32h7xx_hal.h"

// DMA���
extern DMA_HandleTypeDef hdma_adc2;

// ��������
void MY_DMA_Config(void);  // ����DMA

extern void Error_Handler(void);

#endif /* __DMA_H */
