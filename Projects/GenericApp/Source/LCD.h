/*******************************************************************************
 * �ļ����ƣ�LCD.h
 * ��    �ܣ����������
 *           
 * Ӳ�����ӣ��������CC2530��Ӳ�����ӹ�ϵ���£�
 *             
 *
 *               SPILED-data ��������             P1.6
 *               SPILED-CLK ��λ�Ĵ���ʱ������   P1.5
 *               GPH      �洢�Ĵ���ʱ������   P1.3
 * ��    �ߣ�w
 * ��    ˾��������̫�Ƽ����޹�˾
 ******************************************************************************/


#ifndef LCD_H
#define LCD_H 
/* ������Ŷ��� */
/*===================================================*/

#if(SENSOR_TYPE ==0X6E)
#define      SPILEDdata        P1_7
#define      SPILEDCLK         P1_5=P1_6
#define      GPH               P1_3=P2_0
#else 
#define      SPILEDdata        P1_6
#define      SPILEDCLK         P1_5
#define      GPH               P1_3
#define      DS1               P1_2
#define      DS2               P1_1
#endif 
/*===================================================*/
/* ������������ƽ���� */
/*===================================================*/
#define      H_SPILEDdata()       SPILEDdata = 1
#define      L_SPILEDdata()       SPILEDdata = 0
#define      H_SPILEDCLK()       SPILEDCLK = 1 
#define      L_SPILEDCLK()       SPILEDCLK = 0
#define      H_GPH()             GPH = 1
#define      L_GPH()             GPH = 0

/*===================================================*/

#define      NOP()              asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
extern void LCD_SPILEDSendData(unsigned char  Data);
extern void LCD_SPILEDSendDatal(unsigned char Data);
extern void LCD_SPILEDOUT(void);
extern void SendData(unsigned char Data);
extern void SendDataS(unsigned char * Data,unsigned char len);
#endif
 