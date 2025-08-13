// ͷ�ļ�����
#include "system.h"

//-----------------------------------------------------------------

//ϵͳʱ�ӳ�ʼ��

//	����CPU����
void CPU_CACHE_Enable(void)
{
  SCB_EnableICache();	// ʹ��ָ���
  SCB_EnableDCache();	// ʹ�����ݻ���
	SCB->CACR|=1<<2;		// ����D-CacheΪWrite Through����֤���ݵ�һ����
}


//	����MPU
void MPU_Set_Protection(u32 Number,u32 BASEADDR,u32 SIZE,u8 AP,u8 DE,u8 S,u8 C,u8 B)
{
	MPU_Region_InitTypeDef MPU_Initure;
	
	HAL_MPU_Disable(); 											// ���� MPU ֮ǰ�ȹر� MPU,��������Ժ���ʹ�� MPU
	MPU_Initure.Enable=MPU_REGION_ENABLE; 	// ʹ�ܸñ�������
	MPU_Initure.Number=Number; 							// ���ñ�������
	MPU_Initure.BaseAddress=BASEADDR; 			// ���û�ַ
	MPU_Initure.Size=SIZE; 									// ���ñ��������С
	MPU_Initure.SubRegionDisable=0X00; 			// ��ֹ������
	MPU_Initure.TypeExtField=MPU_TEX_LEVEL0;// ����������չ��Ϊ level0
	MPU_Initure.AccessPermission=AP; 				// ���÷���Ȩ��,
	MPU_Initure.DisableExec=DE; 						// �Ƿ�����ָ�����(�����ȡָ��)
	MPU_Initure.IsShareable=S; 							// �Ƿ���
	MPU_Initure.IsCacheable=C; 							// �Ƿ񻺴�
	MPU_Initure.IsBufferable=B; 						// �Ƿ񻺳�
	HAL_MPU_ConfigRegion(&MPU_Initure); 		// ���� MPU
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT); // ���� MPU
}


//	������Ҫ�ı�������AXI SRAM��FMC
void MPU_Memory_Protection(void)
{
	// ����AXI SRAM����512KB�ֽڣ�ȫ���ʣ�����ָ����ʣ���ֹ���������棬������
	MPU_Set_Protection(
		MPU_REGION_NUMBER0,
		0x24000000,						
		MPU_REGION_SIZE_512KB,
		MPU_REGION_FULL_ACCESS,
		MPU_INSTRUCTION_ACCESS_ENABLE,
		MPU_ACCESS_NOT_SHAREABLE,
		MPU_ACCESS_CACHEABLE,
		MPU_ACCESS_BUFFERABLE
	);
	
	// ����FMC����64MB�ֽڣ�ȫ���ʣ�����ָ����ʣ���ֹ������ֹ���棬������
	MPU_Set_Protection(
		MPU_REGION_NUMBER1,
		0x60000000,				
		MPU_REGION_SIZE_64MB,
		MPU_REGION_FULL_ACCESS,
		MPU_INSTRUCTION_ACCESS_ENABLE,
		MPU_ACCESS_NOT_SHAREABLE,
		MPU_ACCESS_NOT_CACHEABLE,
		MPU_ACCESS_BUFFERABLE
	);
}


// End Of File
