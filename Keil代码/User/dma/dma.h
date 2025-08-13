#ifndef __DMA_H
#define __DMA_H

#include "stm32h7xx_hal.h"

// DMA¾ä±ú
extern DMA_HandleTypeDef hdma_adc2;

// º¯ÊıÉùÃ÷
void MY_DMA_Config(void);  // ÅäÖÃDMA

extern void Error_Handler(void);

#endif /* __DMA_H */
