#ifndef __B_LUX_V30_H
#define __B_LUX_V30_H

/*--------------------------ͷ�ļ�����--------------------------------*/
#include <iocc2530.h>

/*-----------------------------�ṹ�嶨��---------------------------------*/

/*-----------------------------�궨��---------------------------------*/
//�������Ͷ���
#define   uint16    unsigned int
#define   uint8     unsigned char
#define   fint32    float
#define   uint32    unsigned long


//#define         B_LUX30_SCL0      (0x01<<2)
//#define         B_LUX30_SDA0      (0x01<<3)

//�˿����Ӷ���
#define SCL P1_3         //I2C���ߵ�ʱ��
#define SDA P1_4         //I2C���ߵ�����
#define IIC_DATAOUT; P1DIR|=0x18       //�������
#define IIC_DATAIN P1SEL&=~0x10;P1DIR&=~0X10



//���Ŷ���
#define B_LUX30_SCL0_O    P1DIR |= 0x08
#define B_LUX30_SCL0_H    P1_3 = 1
#define B_LUX30_SCL0_L    P1_3 = 0

#define B_LUX30_SDA0_O    P1DIR |= 0x10    
#define B_LUX30_SDA0_H    P1_4 = 1
#define B_LUX30_SDA0_L    P1_4 = 0

#define B_LUX30_SDA0_I    P1DIR &= ~0x10
#define B_LUX30_SDA0_DAT  P1_4

#define	B_LUX30_SlaveAddress	  0x94                                          //����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�

/*-----------------------------��������-------------------------------*/
void B_LUX30_delay_nms(uint16 k);
void B_LUX30_Init(void);

void B_LUX30_Multiple_Write(uint8 REG_Address, uint8* vBuf, uint8 vLen);        //���ֽ�д
void B_LUX30_Multiple_read(uint8 REG_Address, uint8* vBuf, uint8 vLen);         //���ֽڶ�
//------------------------------------
void B_LUX30_Delay5us(void);
void B_LUX30_Delay5ms(void);
void B_LUX30_Start(void);                          //��ʼ�ź�
void B_LUX30_Stop(void);                           //ֹͣ�ź�
void B_LUX30_SendACK(uint8 ack);                  //Ӧ��ACK
uint8  B_LUX30_RecvACK(void);                     //��ack
void B_LUX30_SendByte(uint8 dat);                 //IIC�����ֽ�д
uint8 B_LUX30_RecvByte(void);                     //IIC�����ֽڶ�

#endif
