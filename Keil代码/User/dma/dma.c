//	dma.c
#include "dma.h"
#include "adc.h"

// DMA句柄
DMA_HandleTypeDef hdma_adc2;

// 配置DMA
void MY_DMA_Config(void)
{
    // 使能DMA1时钟
    __HAL_RCC_DMA1_CLK_ENABLE();
    
    // 配置DMA1 Stream2
    hdma_adc2.Instance = DMA1_Stream2;  // 使用DMA1 Stream2
    hdma_adc2.Init.Request = DMA_REQUEST_ADC2; // ADC2请求
    hdma_adc2.Init.Direction = DMA_PERIPH_TO_MEMORY; // 外设到内存
    hdma_adc2.Init.PeriphInc = DMA_PINC_DISABLE; // 外设地址不递增
    hdma_adc2.Init.MemInc = DMA_MINC_ENABLE; // 内存地址递增
    hdma_adc2.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD; // 外设数据对齐：16位
    hdma_adc2.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD; // 内存数据对齐：16位
    hdma_adc2.Init.Mode = DMA_CIRCULAR; // 循环模式
    hdma_adc2.Init.Priority = DMA_PRIORITY_MEDIUM; // 中等优先级
    hdma_adc2.Init.FIFOMode = DMA_FIFOMODE_DISABLE; // 禁用FIFO模式
    hdma_adc2.Init.MemBurst = DMA_MBURST_SINGLE; // 单次内存突发
    hdma_adc2.Init.PeriphBurst = DMA_PBURST_SINGLE; // 单次外设突发
    HAL_DMA_Init(&hdma_adc2);  // 初始化DMA

    // 将DMA与ADC2连接
    __HAL_LINKDMA(&hadc2, DMA_Handle, hdma_adc2);
    
    // 启动ADC DMA
    HAL_ADC_Start_DMA(&hadc2, (uint32_t *)adc_buffer, 4);
}
