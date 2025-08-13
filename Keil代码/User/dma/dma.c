//	dma.c
#include "dma.h"
#include "adc.h"

// DMA���
DMA_HandleTypeDef hdma_adc2;

// ����DMA
void MY_DMA_Config(void)
{
    // ʹ��DMA1ʱ��
    __HAL_RCC_DMA1_CLK_ENABLE();
    
    // ����DMA1 Stream2
    hdma_adc2.Instance = DMA1_Stream2;  // ʹ��DMA1 Stream2
    hdma_adc2.Init.Request = DMA_REQUEST_ADC2; // ADC2����
    hdma_adc2.Init.Direction = DMA_PERIPH_TO_MEMORY; // ���赽�ڴ�
    hdma_adc2.Init.PeriphInc = DMA_PINC_DISABLE; // �����ַ������
    hdma_adc2.Init.MemInc = DMA_MINC_ENABLE; // �ڴ��ַ����
    hdma_adc2.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD; // �������ݶ��룺16λ
    hdma_adc2.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD; // �ڴ����ݶ��룺16λ
    hdma_adc2.Init.Mode = DMA_CIRCULAR; // ѭ��ģʽ
    hdma_adc2.Init.Priority = DMA_PRIORITY_MEDIUM; // �е����ȼ�
    hdma_adc2.Init.FIFOMode = DMA_FIFOMODE_DISABLE; // ����FIFOģʽ
    hdma_adc2.Init.MemBurst = DMA_MBURST_SINGLE; // �����ڴ�ͻ��
    hdma_adc2.Init.PeriphBurst = DMA_PBURST_SINGLE; // ��������ͻ��
    HAL_DMA_Init(&hdma_adc2);  // ��ʼ��DMA

    // ��DMA��ADC2����
    __HAL_LINKDMA(&hadc2, DMA_Handle, hdma_adc2);
    
    // ����ADC DMA
    HAL_ADC_Start_DMA(&hadc2, (uint32_t *)adc_buffer, 4);
}
