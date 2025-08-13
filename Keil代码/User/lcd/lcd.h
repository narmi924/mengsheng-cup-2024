//-----------------------------------------------------------------
// 程序描述:
// 　	 2.8寸/4.3寸TFT液晶显示屏驱动程序头文件  
// 作　　者: 凌智电子
// 开始日期: 2020-11-11
// 完成日期: 2020-11-11
// 修改日期:  
// 当前版本: V1.0
// 历史版本:
//	 - V1.0：4.3寸/2.8寸 TFT液晶显示  
// 调试工具: 凌智STM32H750核心板、LZE_ST_LINK2
// 说　　明: 
//
//-----------------------------------------------------------------
#ifndef __LCD_H
#define __LCD_H		
#include "system.h"
//-----------------------------------------------------------------
// 变量声明
//-----------------------------------------------------------------
typedef struct	// LCD地址结构体
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_TypeDef;

//LCD重要参数集
typedef struct  
{		 	 
	u16 width;		// LCD 宽度
	u16 height;		// LCD 高度
	u16 id;				// LCD ID
	u16 scan;			// 扫描方向
	u8  dir;			// 显示方向	
	u16	wramcmd;	// 开始写gram指令
	u16 setxcmd;	// 设置x坐标指令
	u16 setycmd;	// 设置y坐标指令 
	
}_lcd_dev; 	  

// LCD参数
extern _lcd_dev lcddev;	// 管理LCD重要参数
// LCD的画笔颜色和背景色	   
extern u32  POINT_COLOR;// 默认红色    
extern u32  BACK_COLOR; // 背景颜色.默认为白色

//-----------------------------------------------------------------
// 宏定义
//-----------------------------------------------------------------
#define LCD_REG_0             0x00
#define LCD_REG_1             0x01
#define LCD_REG_2             0x02
#define LCD_REG_3             0x03
#define LCD_REG_4             0x04
#define LCD_REG_5             0x05
#define LCD_REG_6             0x06
#define LCD_REG_7             0x07
#define LCD_REG_8             0x08
#define LCD_REG_9             0x09
#define LCD_REG_10            0x0A
#define LCD_REG_12            0x0C
#define LCD_REG_13            0x0D
#define LCD_REG_14            0x0E
#define LCD_REG_15            0x0F
#define LCD_REG_16            0x10
#define LCD_REG_17            0x11
#define LCD_REG_18            0x12
#define LCD_REG_19            0x13
#define LCD_REG_20            0x14
#define LCD_REG_21            0x15
#define LCD_REG_22            0x16
#define LCD_REG_23            0x17
#define LCD_REG_24            0x18
#define LCD_REG_25            0x19
#define LCD_REG_26            0x1A
#define LCD_REG_27            0x1B
#define LCD_REG_28            0x1C
#define LCD_REG_29            0x1D
#define LCD_REG_30            0x1E
#define LCD_REG_31            0x1F
#define LCD_REG_32            0x20
#define LCD_REG_33            0x21
#define LCD_REG_34            0x22
#define LCD_REG_36            0x24
#define LCD_REG_37            0x25
#define LCD_REG_40            0x28
#define LCD_REG_41            0x29
#define LCD_REG_43            0x2B
#define LCD_REG_45            0x2D
#define LCD_REG_48            0x30
#define LCD_REG_49            0x31
#define LCD_REG_50            0x32
#define LCD_REG_51            0x33
#define LCD_REG_52            0x34
#define LCD_REG_53            0x35
#define LCD_REG_54            0x36
#define LCD_REG_55            0x37
#define LCD_REG_56            0x38
#define LCD_REG_57            0x39
#define LCD_REG_58            0x3A
#define LCD_REG_59            0x3B
#define LCD_REG_60            0x3C
#define LCD_REG_61            0x3D
#define LCD_REG_62            0x3E
#define LCD_REG_63            0x3F
#define LCD_REG_64            0x40
#define LCD_REG_65            0x41
#define LCD_REG_66            0x42
#define LCD_REG_67            0x43
#define LCD_REG_68            0x44
#define LCD_REG_69            0x45
#define LCD_REG_70            0x46
#define LCD_REG_71            0x47
#define LCD_REG_72            0x48
#define LCD_REG_73            0x49
#define LCD_REG_74            0x4A
#define LCD_REG_75            0x4B
#define LCD_REG_76            0x4C
#define LCD_REG_77            0x4D
#define LCD_REG_78            0x4E
#define LCD_REG_79            0x4F
#define LCD_REG_80            0x50
#define LCD_REG_81            0x51
#define LCD_REG_82            0x52
#define LCD_REG_83            0x53
#define LCD_REG_96            0x60
#define LCD_REG_97            0x61
#define LCD_REG_106           0x6A
#define LCD_REG_118           0x76
#define LCD_REG_128           0x80
#define LCD_REG_129           0x81
#define LCD_REG_130           0x82
#define LCD_REG_131           0x83
#define LCD_REG_132           0x84
#define LCD_REG_133           0x85
#define LCD_REG_134           0x86
#define LCD_REG_135           0x87
#define LCD_REG_136           0x88
#define LCD_REG_137           0x89
#define LCD_REG_139           0x8B
#define LCD_REG_140           0x8C
#define LCD_REG_141           0x8D
#define LCD_REG_143           0x8F
#define LCD_REG_144           0x90
#define LCD_REG_145           0x91
#define LCD_REG_146           0x92
#define LCD_REG_147           0x93
#define LCD_REG_148           0x94
#define LCD_REG_149           0x95
#define LCD_REG_150           0x96
#define LCD_REG_151           0x97
#define LCD_REG_152           0x98
#define LCD_REG_153           0x99
#define LCD_REG_154           0x9A
#define LCD_REG_157           0x9D
#define LCD_REG_192           0xC0
#define LCD_REG_193           0xC1
#define LCD_REG_229           0xE5

// LCD背光	PD13
#define LCD_LED_ON			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_SET)
#define LCD_LED_OFF			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET) 	 
// 使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A16作为数据命令区分线 
// 注意设置时STM32内部会右移一位对其!  			    
#define LCD_BASE        ((u32)(0x60000000 | 0x0001FFFE))
#define LCD_ADDRESS_START		(0X60000000)			//LCD区的首地址
#define LCD             ((LCD_TypeDef *) LCD_BASE)
	 
// 显示方向 
#define DISPLAY_DIR_D          2               // 下
#define DISPLAY_DIR_U          1               // 上
#define DISPLAY_DIR_L          3               // 左
#define DISPLAY_DIR_R          4               // 右

#define LCD_DIR                DISPLAY_DIR_L   // 默认显示方向

// 画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 	 0x001F  
#define BRED             0XF81F
#define GRED 			 			 0XFFE0
#define GBLUE			 			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 		 0XBC40 
#define BRRED 			 		 0XFC07 
#define GRAY  			 		 0X8430
// GUI颜色

#define DARKBLUE      	 0X01CF	
#define LIGHTBLUE      	 0X7D7C	
#define GRAYBLUE       	 0X5458 
// 以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F 
#define LGRAY 			 		 0XC618 

#define LGRAYBLUE        0XA651 
#define LBBLUE           0X2B12 


// ST7789V ID
#define ST7789V_ID       0x8552
// SPFD5408 ID
#define SPFD5408_ID      0x5408
// NT35510 ID
#define NT35510_ID       0x5510

#define LCD_CS_Set 	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET) 
#define LCD_CS_Clr 	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET)

#define LCD_RST_Set	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET) 
#define LCD_RST_Clr	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET)

#define LCD_RS_Set 	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET)
#define LCD_RS_Clr 	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET)

#define LCD_WR_Set 	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_SET)
#define LCD_WR_Clr 	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_RESET)

#define LCD_RD_Set 	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_SET)
#define LCD_RD_Clr 	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_RESET)

//-----------------------------------------------------------------
// 外部函数声明
//-----------------------------------------------------------------
extern void LCD_WR_REG(vu16 regval);
extern void LCD_WR_DATA(vu16 data);
extern u16 LCD_RD_DATA(void);
extern void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue);
extern u16 LCD_ReadReg(u16 LCD_Reg);
extern void LCD_WriteRAM_Prepare(void);
extern void LCD_WriteRAM(u16 RGB_Code);
extern u16 LCD_BGR2RGB(u16 c);
extern void opt_delay(u8 i);
extern u32 LCD_ReadPoint(u16 x,u16 y);
extern void LCD_DisplayOn(void);
extern void LCD_DisplayOff(void);
extern void LCD_Display_Dir(u8 dir);
extern void LCD_SetCursor(u16 Xpos, u16 Ypos);
extern void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);
extern void LCD_Init(void);
extern void LCD_DrawPoint(u16 x,u16 y);
extern void LCD_Fast_DrawPoint(u16 x,u16 y,u32 color);
extern void LCD_Clear(uint16_t Color);
extern void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u32 color);
extern void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);
extern void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
extern void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
extern void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);
extern void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);
extern u32 LCD_Pow(u8 m,u8 n);
extern void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
extern void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);
extern void LCD_ShowChinese(u16 x, u16 y, const unsigned char *data, u8 size, u8 mode);
extern void	LCD_ShowHZString(u16 x, u16 y, const unsigned char *str, u16 color);
extern const unsigned char HZ_NI[][120];
extern void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,char *p);
//-----------------------------------------------------------------
#endif  
//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------  
