//	adc.c
#include "adc.h"
#include "dma.h"
#include "delay.h"
#include "lcd.h"

// DMA句柄
extern DMA_HandleTypeDef hdma_adc2;

// ADC句柄
ADC_HandleTypeDef hadc2;

// 存储ADC采样结果的缓冲区
uint16_t adc_buffer[4];  // 用于存储ADC2通道数据的缓冲区

// ADC初始化
void MY_ADC_Init(void)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    // 配置ADC2
    hadc2.Instance = ADC2;
    hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;  // ADC时钟异步，分频1
    hadc2.Init.Resolution = ADC_RESOLUTION_16B;        // 16位分辨率
    hadc2.Init.ScanConvMode = ADC_SCAN_ENABLE;          // 扫描模式启用
    hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;      // 每次转换完成中断
    hadc2.Init.LowPowerAutoWait = DISABLE;              // 不启用低功耗模式
    hadc2.Init.ContinuousConvMode = DISABLE;             // 禁止连续转换模式
    hadc2.Init.NbrOfConversion = 4;                      // 4个通道
    hadc2.Init.DiscontinuousConvMode = DISABLE;          // 禁用不连续模式
    hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;    // 使用软件触发
    hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;  // 无外部触发
    hadc2.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR; // 结果保存在DR寄存器
    hadc2.Init.Overrun = ADC_OVR_DATA_PRESERVED;         // 数据溢出时保留新数据
    hadc2.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;     // 无左移
    hadc2.Init.OversamplingMode = DISABLE;               // 关闭过采样

    // 初始化ADC2
    if (HAL_ADC_Init(&hadc2) != HAL_OK)
    {
        Error_Handler();  // 初始化失败处理
    }

    // 配置ADC2通道
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

    // 启动DMA
    HAL_ADC_Start_DMA(&hadc2, (uint32_t *)adc_buffer, 4);  // 传输4个通道的数据
}


// ADC中断回调函数
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    // 检查是否是你期望的ADC（例如ADC2）
    if (hadc->Instance == ADC2)
    {
        // 在每次ADC转换完成后更新LCD显示
        Update_LCD_Display();
    }
}



// ADC数据转换平均值计算
void Get_Adc_Average(uint16_t *average_value, uint8_t times)
{
    uint32_t temp_val = 0;
    for (uint8_t t = 0; t < times; t++)
    {
        HAL_ADC_Start(&hadc2); // 启动ADC转换
        HAL_Delay(1);  // 延迟等待采样
        temp_val += adc_buffer[0]; // 获取第一个通道数据
    }
    *average_value = temp_val / times; // 计算平均值
}
// ADC更新显示
void Update_LCD_Display(void)
{
	
	  LCD_ShowChinese(90, 110, HZ_NI[8], 30, 0);
    // 显示第一个麦克风的数据
    if (adc_buffer[0] > 0) {
        // 如果第一个麦克风有信号，显示信号强度
        LCD_ShowNum(10, 10, adc_buffer[0], 4, 16);  // 输出信号强度
    } else {
        // 如果没有信号，显示 "NS"
        LCD_ShowString(10, 10, 100, 20, 16, "NS");  // 输出 "NS" 表示无信号
    }

    // 显示第二个麦克风的数据
    if (adc_buffer[1] > 0) {
        // 如果第二个麦克风有信号，显示信号强度
        LCD_ShowNum(10, 30, adc_buffer[1], 4, 16);
    } else {
        // 如果没有信号，显示 "NS"
        LCD_ShowString(10, 30, 100, 20, 16, "NS");
    }

    // 显示第三个麦克风的数据
    if (adc_buffer[2] > 0) {
        // 如果第三个麦克风有信号，显示信号强度
        LCD_ShowNum(10, 50, adc_buffer[2], 4, 16);
    } else {
        // 如果没有信号，显示 "NS"
        LCD_ShowString(10, 50, 100, 20, 16, "NS");
    }

    // 显示第四个麦克风的数据
    if (adc_buffer[3] > 0) {
        // 如果第四个麦克风有信号，显示信号强度
        LCD_ShowNum(10, 70, adc_buffer[3], 4, 16);
    } else {
        // 如果没有信号，显示 "NS"
        LCD_ShowString(10, 70, 100, 20, 16, "NS");
    }
}
