#ifndef __SHT1X_H__
#define __SHT1X_H__
#include <ioCC2530.h>
#include "math.h"    //Keil library  
#include "stdio.h"

#define uchar unsigned char
#define uint unsigned int
#define DATA P1_2         //����ͨѶ���ݶ˿�
#define SCK P1_1
#define  SHT_DATAOUT  P1DIR|=0x04 ;   //�������
#define SHT_DATAIN  P1DIR&=~0X04;  
typedef union  
{ unsigned int i;      //����������������
  float f; 
} valuen; 

enum {TEMP,HUMI};      //TEMP=0,HUMI=1

//extern uint tempvalue,tempvalue2;
//extern uint flag;
//extern float wenduf,shiduf;
//extern unsigned int wendu,shidu;   
 
#define noACK 0             //�����ж��Ƿ����ͨѶ
#define ACK   1             //�������ݴ���
                            //adr  command  r/w 
#define STATUS_REG_W 0x06   //000   0011    0 
#define STATUS_REG_R 0x07   //000   0011    1 
#define MEASURE_TEMP 0x03   //000   0001    1 
#define MEASURE_HUMI 0x05   //000   0010    1 
#define RESET        0x1e   //000   1111    0 
#define _nop_() asm("NOP"); asm("NOP");  asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");  asm("NOP");
/****************���庯��****************/
void s_transstart(void);               //�������亯��
void s_connectionreset(void);          //���Ӹ�λ����
char s_write_byte(unsigned char value);//DHT90д����
char s_read_byte(unsigned char ack);   //DHT90������
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode);//������ʪ
void calc_dht90(float *p_humidity ,float *p_temperature);//��ʪ�Ȳ���
void delay_n10us(uint n);                     //��ʱ����

#endif
