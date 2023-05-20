
#ifndef _IIC_H
#define _IIC_H

/*******************************************************************************
 * INCLUDES
 */
#include <ioCC2530.h>
#include "GenericApp.h"

/*******************************************************************************
 * CONSTANTS AND MACROS
 */
//�˿����Ӷ���
#define SCL P1_3         //I2C���ߵ�ʱ��
#define SDA P1_4         //I2C���ߵ�����
#define IIC_DATAOUT; P1DIR|=0x18       //�������
#define IIC_DATAIN P1SEL&=~0x10;P1DIR&=~0X10
#if(SENSOR_TYPE =='C')
//��ַ����
#define AddWr 0xa0  /*������ַѡ��д��־*/
#define AddRd 0xa1  /*������ַѡ�񼰶���־*/
#endif
#if(SENSOR_TYPE =='F')
//��ַ����
#define AddWr 0xEE  /*������ַѡ��д��־*/
#define AddRd 0xEF  /*������ַѡ�񼰶���־*/
#endif
//��ַ����
#if !defined( AddWr )
#define AddWr 0xa0  /*������ַѡ��д��־*/
#endif
#if !defined( AddRd )
#define AddRd 0xa1  /*������ַѡ�񼰶���־*/
#endif

//�����ֶ���
#define NOPS  asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
extern void mDelay(unsigned j);
extern void Single_Write_(unsigned char,unsigned char );
extern unsigned char Single_Read_(unsigned char);
extern void WrToROM(unsigned char *,unsigned char ,unsigned char);
extern void RdFromROM(unsigned char *,unsigned char ,unsigned char);


/*****************************************************************************/
#endif

