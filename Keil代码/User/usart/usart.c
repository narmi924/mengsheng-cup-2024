//	头文件包含
#include "usart.h"
#include "delay.h"
#include "string.h"
#include "stdio.h"
#include "main.h"

//-----------------------------------------------------------------

u8 USART_RX_BUF[USART_REC_LEN]; 	// 接收缓冲,最大USART_REC_LEN个字节.
u16 USART_RX_STA=0;       				// 接收状态标记（bit15：接收完成标志  bit14：接收到0x0d   bit13~0：接收到的有效字节数目）
u8 aRxBuffer[RXBUFFERSIZE];				// HAL库使用的串口接收缓冲
UART_HandleTypeDef UART_Handler;  // UART句柄

//	串口1初始化
//void uart_init(u32 bound)
//{	
//	//UART 初始化设置
//	UART_Handler.Instance=USARTx;					    			// USART1
//	UART_Handler.Init.BaudRate=bound;				    		// 波特率
//	UART_Handler.Init.WordLength=UART_WORDLENGTH_8B;// 字长为8位数据格式
//	UART_Handler.Init.StopBits=UART_STOPBITS_1;	    // 一个停止位
//	UART_Handler.Init.Parity=UART_PARITY_NONE;		  // 无奇偶校验位
//	UART_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;// 无硬件流控
//	UART_Handler.Init.Mode=UART_MODE_TX_RX;		    	// 收发模式
//	HAL_UART_Init(&UART_Handler);					    			// HAL_UART_Init()会使能UART1
//	
//	// 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
//	HAL_UART_Receive_IT(&UART_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE);
//}


//	UART底层初始化，时钟使能，引脚配置，中断配置
// void HAL_UART_MspInit(UART_HandleTypeDef *huart)

//	新中断回调函数
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//    if (huart->Instance == USART1) // 根据您的串口实例修改
//    {
//        switch (currentMode)
//        {
//            case MODE_K3:
//                if (aRxBuffer[0] == '1') 
//                 {
//									OLED_Clear();
//									OLED_ShowCHinese(28,0 ,12);         //显示“识别模式”
//									OLED_ShowCHinese(46,0 ,13);
//									OLED_ShowCHinese(64,0 ,14);
//									OLED_ShowCHinese(82,0 ,15); 
//									OLED_ShowCHinese(28,3 ,0);          //显示“打开灯光”
//									OLED_ShowCHinese(46,3 ,1);
//									OLED_ShowCHinese(64,3 ,2);
//									OLED_ShowCHinese(82,3 ,3);
//                  messageDisplayFlag = 1;
//                  messageStartTime = HAL_GetTick(); // 记录开始时间
//                 }
//								else if (aRxBuffer[0] == '2')
//								 {
//									OLED_Clear();
//									OLED_ShowCHinese(28,0 ,12);         //显示“识别模式”
//									OLED_ShowCHinese(46,0 ,13);
//									OLED_ShowCHinese(64,0 ,14);
//									OLED_ShowCHinese(82,0 ,15); 
//									OLED_ShowCHinese(28,3 ,4);          //显示“关闭灯光”
//									OLED_ShowCHinese(46,3 ,5);
//									OLED_ShowCHinese(64,3 ,2);
//									OLED_ShowCHinese(82,3 ,3);
//									messageDisplayFlag = 1;
//                  messageStartTime = HAL_GetTick(); // 记录开始时间
//								 }
//								else if (aRxBuffer[0] == '3')
//								 {
//									OLED_Clear();
//									OLED_ShowCHinese(28,0 ,12);         //显示“识别模式”
//									OLED_ShowCHinese(46,0 ,13);
//									OLED_ShowCHinese(64,0 ,14);
//									OLED_ShowCHinese(82,0 ,15); 
//									OLED_ShowCHinese(28,3 ,0);          //显示“打开空调”
//									OLED_ShowCHinese(46,3 ,1);
//									OLED_ShowCHinese(64,3 ,6);
//									OLED_ShowCHinese(82,3 ,7);								
//									messageDisplayFlag = 1;
//                  messageStartTime = HAL_GetTick(); // 记录开始时间
//								 }
//								else if (aRxBuffer[0] == '4')
//								 {
//									OLED_Clear();
//									OLED_ShowCHinese(28,0 ,12);         //显示“识别模式”
//									OLED_ShowCHinese(46,0 ,13);
//									OLED_ShowCHinese(64,0 ,14);
//									OLED_ShowCHinese(82,0 ,15); 
//									OLED_ShowCHinese(28,3 ,4);          //显示“关闭空调”
//									OLED_ShowCHinese(46,3 ,5);
//									OLED_ShowCHinese(64,3 ,6);
//									OLED_ShowCHinese(82,3 ,7);								
//                  messageDisplayFlag = 1;
//                  messageStartTime = HAL_GetTick(); // 记录开始时间
//								 }
//                break;

//            case MODE_K1:
//                OLED_ShowString(0,0,"UART Interrupt in K3",16);
////                DW();
//                messageDisplayFlag = 1;
//                messageStartTime = HAL_GetTick();
//                break;

//            default:
//                break;
//        }
//        // 重新启动 UART 接收中断
//				HAL_UART_Receive_IT(&huart1, aRxBuffer, 1);
//    }
//}


//	串口1中断服务程序
//void USART1_IRQHandler(void)                	

//	返回函数
void USART_Send_Back(uint8_t* data, uint16_t length)
{
    HAL_UART_Transmit(&UART_Handler, data, length, HAL_MAX_DELAY);
}



//	加入以下代码,支持printf函数 
#if 1
#pragma import(__use_no_semihosting)             
//	标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;  

//	定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 


//	重定义fputc函数 
int	fputc(int ch, FILE *f)
{ 	
	while((USART1->ISR&0X40)==0);// 循环发送,直到发送完毕   
	USART1->TDR = (u8) ch;      
	return ch;
}

// 重定义fgetc函数 
int fgetc(FILE *file)
{
  int ch;
  while((USART1->ISR&0X40)==0) ;
  ch = USART1->RDR;
  return ch;
}  

#endif

// End Of File
