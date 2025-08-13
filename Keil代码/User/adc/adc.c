//	adc.c
#include "adc.h"
#include "dma.h"
#include "delay.h"
#include "lcd.h"

// DMA���
extern DMA_HandleTypeDef hdma_adc2;

// ADC���
ADC_HandleTypeDef hadc2;

// �洢ADC��������Ļ�����
uint16_t adc_buffer[4];  // ���ڴ洢ADC2ͨ�����ݵĻ�����

// ADC��ʼ��
void MY_ADC_Init(void)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    // ����ADC2
    hadc2.Instance = ADC2;
    hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;  // ADCʱ���첽����Ƶ1
    hadc2.Init.Resolution = ADC_RESOLUTION_16B;        // 16λ�ֱ���
    hadc2.Init.ScanConvMode = ADC_SCAN_ENABLE;          // ɨ��ģʽ����
    hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;      // ÿ��ת������ж�
    hadc2.Init.LowPowerAutoWait = DISABLE;              // �����õ͹���ģʽ
    hadc2.Init.ContinuousConvMode = DISABLE;             // ��ֹ����ת��ģʽ
    hadc2.Init.NbrOfConversion = 4;                      // 4��ͨ��
    hadc2.Init.DiscontinuousConvMode = DISABLE;          // ���ò�����ģʽ
    hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;    // ʹ���������
    hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;  // ���ⲿ����
    hadc2.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR; // ���������DR�Ĵ���
    hadc2.Init.Overrun = ADC_OVR_DATA_PRESERVED;         // �������ʱ����������
    hadc2.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;     // ������
    hadc2.Init.OversamplingMode = DISABLE;               // �رչ�����

    // ��ʼ��ADC2
    if (HAL_ADC_Init(&hadc2) != HAL_OK)
    {
        Error_Handler();  // ��ʼ��ʧ�ܴ���
    }

    // ����ADC2ͨ��
    sConfig.Channel = ADC_CHANNEL_3;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_16CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }

    sConfig.Channel = ADC_CHANNEL_4;
    sConfig.Rank = ADC_REGULAR_RANK_2;
    if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }

    sConfig.Channel = ADC_CHANNEL_14;
    sConfig.Rank = ADC_REGULAR_RANK_3;
    if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }

    sConfig.Channel = ADC_CHANNEL_15;
    sConfig.Rank = ADC_REGULAR_RANK_4;
    if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }

    // ����DMA
    HAL_ADC_Start_DMA(&hadc2, (uint32_t *)adc_buffer, 4);  // ����4��ͨ��������
}


// ADC�жϻص�����
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    // ����Ƿ�����������ADC������ADC2��
    if (hadc->Instance == ADC2)
    {
        // ��ÿ��ADCת����ɺ����LCD��ʾ
        Update_LCD_Display();
    }
}



// ADC����ת��ƽ��ֵ����
void Get_Adc_Average(uint16_t *average_value, uint8_t times)
{
    uint32_t temp_val = 0;
    for (uint8_t t = 0; t < times; t++)
    {
        HAL_ADC_Start(&hadc2); // ����ADCת��
        HAL_Delay(1);  // �ӳٵȴ�����
        temp_val += adc_buffer[0]; // ��ȡ��һ��ͨ������
    }
    *average_value = temp_val / times; // ����ƽ��ֵ
}
// ADC������ʾ
void Update_LCD_Display(void)
{
	
	  LCD_ShowChinese(90, 110, HZ_NI[8], 30, 0);
    // ��ʾ��һ����˷������
    if (adc_buffer[0] > 0) {
        // �����һ����˷����źţ���ʾ�ź�ǿ��
        LCD_ShowNum(10, 10, adc_buffer[0], 4, 16);  // ����ź�ǿ��
    } else {
        // ���û���źţ���ʾ "NS"
        LCD_ShowString(10, 10, 100, 20, 16, "NS");  // ��� "NS" ��ʾ���ź�
    }

    // ��ʾ�ڶ�����˷������
    if (adc_buffer[1] > 0) {
        // ����ڶ�����˷����źţ���ʾ�ź�ǿ��
        LCD_ShowNum(10, 30, adc_buffer[1], 4, 16);
    } else {
        // ���û���źţ���ʾ "NS"
        LCD_ShowString(10, 30, 100, 20, 16, "NS");
    }

    // ��ʾ��������˷������
    if (adc_buffer[2] > 0) {
        // �����������˷����źţ���ʾ�ź�ǿ��
        LCD_ShowNum(10, 50, adc_buffer[2], 4, 16);
    } else {
        // ���û���źţ���ʾ "NS"
        LCD_ShowString(10, 50, 100, 20, 16, "NS");
    }

    // ��ʾ���ĸ���˷������
    if (adc_buffer[3] > 0) {
        // ������ĸ���˷����źţ���ʾ�ź�ǿ��
        LCD_ShowNum(10, 70, adc_buffer[3], 4, 16);
    } else {
        // ���û���źţ���ʾ "NS"
        LCD_ShowString(10, 70, 100, 20, 16, "NS");
    }
}
