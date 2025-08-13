//	ͷ�ļ�����
#include "usart.h"
#include "delay.h"
#include "string.h"
#include "stdio.h"
#include "main.h"

//-----------------------------------------------------------------

u8 USART_RX_BUF[USART_REC_LEN]; 	// ���ջ���,���USART_REC_LEN���ֽ�.
u16 USART_RX_STA=0;       				// ����״̬��ǣ�bit15��������ɱ�־  bit14�����յ�0x0d   bit13~0�����յ�����Ч�ֽ���Ŀ��
u8 aRxBuffer[RXBUFFERSIZE];				// HAL��ʹ�õĴ��ڽ��ջ���
UART_HandleTypeDef UART_Handler;  // UART���

//	����1��ʼ��
//void uart_init(u32 bound)
//{	
//	//UART ��ʼ������
//	UART_Handler.Instance=USARTx;					    			// USART1
//	UART_Handler.Init.BaudRate=bound;				    		// ������
//	UART_Handler.Init.WordLength=UART_WORDLENGTH_8B;// �ֳ�Ϊ8λ���ݸ�ʽ
//	UART_Handler.Init.StopBits=UART_STOPBITS_1;	    // һ��ֹͣλ
//	UART_Handler.Init.Parity=UART_PARITY_NONE;		  // ����żУ��λ
//	UART_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;// ��Ӳ������
//	UART_Handler.Init.Mode=UART_MODE_TX_RX;		    	// �շ�ģʽ
//	HAL_UART_Init(&UART_Handler);					    			// HAL_UART_Init()��ʹ��UART1
//	
//	// �ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
//	HAL_UART_Receive_IT(&UART_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE);
//}


//	UART�ײ��ʼ����ʱ��ʹ�ܣ��������ã��ж�����
// void HAL_UART_MspInit(UART_HandleTypeDef *huart)

//	���жϻص�����
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//    if (huart->Instance == USART1) // �������Ĵ���ʵ���޸�
//    {
//        switch (currentMode)
//        {
//            case MODE_K3:
//                if (aRxBuffer[0] == '1') 
//                 {
//									OLED_Clear();
//									OLED_ShowCHinese(28,0 ,12);         //��ʾ��ʶ��ģʽ��
//									OLED_ShowCHinese(46,0 ,13);
//									OLED_ShowCHinese(64,0 ,14);
//									OLED_ShowCHinese(82,0 ,15); 
//									OLED_ShowCHinese(28,3 ,0);          //��ʾ���򿪵ƹ⡱
//									OLED_ShowCHinese(46,3 ,1);
//									OLED_ShowCHinese(64,3 ,2);
//									OLED_ShowCHinese(82,3 ,3);
//                  messageDisplayFlag = 1;
//                  messageStartTime = HAL_GetTick(); // ��¼��ʼʱ��
//                 }
//								else if (aRxBuffer[0] == '2')
//								 {
//									OLED_Clear();
//									OLED_ShowCHinese(28,0 ,12);         //��ʾ��ʶ��ģʽ��
//									OLED_ShowCHinese(46,0 ,13);
//									OLED_ShowCHinese(64,0 ,14);
//									OLED_ShowCHinese(82,0 ,15); 
//									OLED_ShowCHinese(28,3 ,4);          //��ʾ���رյƹ⡱
//									OLED_ShowCHinese(46,3 ,5);
//									OLED_ShowCHinese(64,3 ,2);
//									OLED_ShowCHinese(82,3 ,3);
//									messageDisplayFlag = 1;
//                  messageStartTime = HAL_GetTick(); // ��¼��ʼʱ��
//								 }
//								else if (aRxBuffer[0] == '3')
//								 {
//									OLED_Clear();
//									OLED_ShowCHinese(28,0 ,12);         //��ʾ��ʶ��ģʽ��
//									OLED_ShowCHinese(46,0 ,13);
//									OLED_ShowCHinese(64,0 ,14);
//									OLED_ShowCHinese(82,0 ,15); 
//									OLED_ShowCHinese(28,3 ,0);          //��ʾ���򿪿յ���
//									OLED_ShowCHinese(46,3 ,1);
//									OLED_ShowCHinese(64,3 ,6);
//									OLED_ShowCHinese(82,3 ,7);								
//									messageDisplayFlag = 1;
//                  messageStartTime = HAL_GetTick(); // ��¼��ʼʱ��
//								 }
//								else if (aRxBuffer[0] == '4')
//								 {
//									OLED_Clear();
//									OLED_ShowCHinese(28,0 ,12);         //��ʾ��ʶ��ģʽ��
//									OLED_ShowCHinese(46,0 ,13);
//									OLED_ShowCHinese(64,0 ,14);
//									OLED_ShowCHinese(82,0 ,15); 
//									OLED_ShowCHinese(28,3 ,4);          //��ʾ���رտյ���
//									OLED_ShowCHinese(46,3 ,5);
//									OLED_ShowCHinese(64,3 ,6);
//									OLED_ShowCHinese(82,3 ,7);								
//                  messageDisplayFlag = 1;
//                  messageStartTime = HAL_GetTick(); // ��¼��ʼʱ��
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
//        // �������� UART �����ж�
//				HAL_UART_Receive_IT(&huart1, aRxBuffer, 1);
//    }
//}


//	����1�жϷ������
//void USART1_IRQHandler(void)                	

//	���غ���
void USART_Send_Back(uint8_t* data, uint16_t length)
{
    HAL_UART_Transmit(&UART_Handler, data, length, HAL_MAX_DELAY);
}



//	�������´���,֧��printf���� 
#if 1
#pragma import(__use_no_semihosting)             
//	��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;  

//	����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 


//	�ض���fputc���� 
int	fputc(int ch, FILE *f)
{ 	
	while((USART1->ISR&0X40)==0);// ѭ������,ֱ���������   
	USART1->TDR = (u8) ch;      
	return ch;
}

// �ض���fgetc���� 
int fgetc(FILE *file)
{
  int ch;
  while((USART1->ISR&0X40)==0) ;
  ch = USART1->RDR;
  return ch;
}  

#endif

// End Of File
