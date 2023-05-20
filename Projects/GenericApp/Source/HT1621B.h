#include <ioCC2530.h>
#include <string.h>
#define uint unsigned int
#define uchar unsigned char
#define _Nop()  DelayUS(5);
#define BIAS 0x52 //0b1000 0101 0010 1/3duty 4com
#define SYSDIS 0X00 //0b1000 0000 0000 ����ϵͳ������LCDƫѹ������
#define SYSEN 0X02 //0b1000 0000 0010 ��ϵͳ����
#define LCDOFF 0X04 //0b100 0000 0100 0��LCDƫѹ
#define LCDON 0X06 //0b1000 0000 0110 ��LCDƫѹ
#define XTAL 0x28 //0b1000 0010 1000 �ⲿ��ʱ��
#define RC256 0X30 //0b1000 0011 0000 �ڲ�ʱ��
#define TONEON 0X12 //0b1000 0001 0010 ���������
#define TONEOFF 0X10 //0b1000 0001 0000 �ر��������
#define WDTDIS 0X0A //0b1000 0000 1010 ��ֹ���Ź�

//HT1621����λ��Һ��ģ��ӿڶ��壬�������ѵ���Ҫ���ģ�
#define HT1621_DAT P1_5 //HT1621��������

//#define HT1621_CS P1_7 //HT1621ʹ������ �ɰ�
//#define HT1621_WR P1_6 //HT1621ʱ������ �ɰ�
#define HT1621_CS P1_3 //HT1621ʹ������
#define HT1621_WR P1_4 //HT1621ʱ������
//uchar  Ht1621Tab[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//uchar  table1[]={0x0e,0x06,0x0c,0x0e,0x06,0x0a,0x0a,0x0e,0x0e,0x0e};
//uchar  table2[]={0x0b,0x00,0x07,0x05,0x0c,0x0d,0x0f,0x00,0x0f,0x0d};

//��������
void DelayMS(uint iMs);
void Ht1621_Init(void);
void Ht1621Wr_Data(uchar Data,uchar cnt);
void Ht1621WrCmd(uchar Cmd);
void Ht1621WrOneData(uchar Addr,uchar Data);
void Ht1621WrAllData(uchar Addr,uchar *p,uchar cnt);


void DelayUS(uchar);
//delay us
void DelayUS(uchar us) //5,7,9
{
 while(--us);
}

//delay ms
void DelayMS(uint iMs)
{
 uint i,j;
 for(i=0;i<iMs;i++)
 for(j=0;j<65;j++) DelayUS(1);
}

/******************************************************
д���ݺ���,cntΪ��������λ��,���ݴ���Ϊ��λ��ǰ
*******************************************************/
void Ht1621Wr_Data(uchar Data,uchar cnt)
{
 uchar i;
 for (i=0;i<cnt;i++)
      {
       HT1621_WR=0;
       _Nop();
       HT1621_DAT=((Data&0x80)>>7);
       _Nop();
       HT1621_WR=1;
       _Nop();
      Data<<=1;
     }

}

/********************************************************
�������ƣ�void Ht1621WrCmd(uchar Cmd)
��������: HT1621����д�뺯��
ȫ�ֱ�������
����˵����CmdΪд����������
����˵������


˵ ����д�������ʶλ100
********************************************************/
void Ht1621WrCmd(uchar Cmd)
{
 HT1621_CS=0;
 _Nop();
 Ht1621Wr_Data(0x80,4); //д�������־100
 Ht1621Wr_Data(Cmd,8); //д����������
 HT1621_CS=1;
 _Nop();
}
/********************************************************
�������ƣ�void Ht1621WrOneData(uchar Addr,uchar Data)
��������: HT1621��ָ����ַд�����ݺ���
ȫ�ֱ�������
����˵����AddrΪд���ʼ��ַ��DataΪд������
����˵������
˵ ������ΪHT1621������λ4λ������ʵ��д������Ϊ�����ĺ�4λ
********************************************************/
void Ht1621WrOneData(uchar Addr,uchar Data)
{
 HT1621_CS=0;
 Ht1621Wr_Data(0xa0,3); //д�����ݱ�־101
 Ht1621Wr_Data(Addr<<2,6); //д���ַ����
 Ht1621Wr_Data(Data<<4,4); //д������
 HT1621_CS=1;
 _Nop();
}
/********************************************************
HT1621���Գ���2008-2-13, 22:41:43
�������ƣ�void Ht1621WrAllData(uchar Addr,uchar *p,uchar cnt)
��������: HT1621����д�뷽ʽ����
ȫ�ֱ�������
����˵����AddrΪд���ʼ��ַ��*pΪ����д������ָ�룬
                  cntΪд����������
����˵������
˵ ����HT1621������λ4λ���˴�ÿ������Ϊ8λ��д������
           ������8λ����
********************************************************/
void Ht1621WrAllData(uchar Addr,uchar *p,uchar cnt)
{
 uchar i;
 HT1621_CS=0;
 Ht1621Wr_Data(0xa0,3); //д�����ݱ�־101
 Ht1621Wr_Data(Addr<<2,6); //д���ַ����
 for (i=0;i<cnt;i++)
      {
        Ht1621Wr_Data(*p,8); //д������
        p++;
       }
 HT1621_CS=1;
 _Nop();
}
/********************************************************
�������ƣ�void Ht1621_Init(void)
��������: HT1621��ʼ��
ȫ�ֱ�������
����˵������
����˵������
�� ����1.0
˵ ������ʼ����Һ���������ֶξ���ʾ
********************************************************/
void Ht1621_Init(void)
{
 HT1621_CS=1;
 HT1621_WR=1;
 HT1621_DAT=1;
 DelayMS(20); //��ʱʹLCD������ѹ�ȶ�
 Ht1621WrCmd(BIAS);
 Ht1621WrCmd(RC256); //ʹ���ڲ�����
 Ht1621WrCmd(SYSDIS);
 Ht1621WrCmd(WDTDIS);
 Ht1621WrCmd(SYSEN);
 Ht1621WrCmd(LCDON);
}
/*
void main(void)
{	
uchar i,j,t;
   P1DIR |= 0XF0;   
   P2DIR |= 0X01; 
 Ht1621_Init(); //�ϵ��ʼ��LCD
 DelayMS(500); //��ʱһ��ʱ��
 while(1){
Ht1621WrAllData(0,Ht1621Tab,18);//���1621�Ĵ������ݣ������� //SEG0��SEG17 COM0-3=0X00 0000 ȫ��
			Ht1621WrOneData(1,table1[9]);//SEG1 COM0-3=table1[9]=0X0E 1110 ����9
                        Ht1621WrOneData(2,table2[9]);//SEG2 COM0-3=table2[9]=0X0D 1101 ����9
                         DelayMS(5000);
                        Ht1621WrOneData(3,table1[8]);//SEG3 COM0-3=table1[8]=0X0E 1110 ����8
			Ht1621WrOneData(4,table2[8]);//SEG4 COM0-3=table2[8]=0X0F 1111 ����8
                         DelayMS(5000);
                        Ht1621WrOneData(5,table1[7]);
			Ht1621WrOneData(6,table2[7]);
 DelayMS(5000);
			Ht1621WrOneData(7,table1[6]);
			Ht1621WrOneData(8,table2[6]);
 DelayMS(5000);
			Ht1621WrOneData(9,table1[5]);
			Ht1621WrOneData(10,table2[5]);
 DelayMS(5000);
			Ht1621WrOneData(11,table1[4]);
			Ht1621WrOneData(12,table2[4]);
 DelayMS(5000);
			Ht1621WrOneData(13,table1[3]);
			Ht1621WrOneData(14,table2[3]);
 DelayMS(5000);
			Ht1621WrOneData(15,table1[2]);
			Ht1621WrOneData(16,table2[2]);
            DelayMS(5000);
			 Ht1621WrAllData(0,Ht1621Tab,18);//���1621�Ĵ������ݣ������� //SEG0��SEG17 COM0-3=0X00 0000 ȫ��
               for (i=0;i<18;i++) //18���ֶ� SEG0��SEG17 
                    {
                     t=0x01;
                     for (j=0;j<4;j++)//4��һ�� COM0-3
                          {
                           Ht1621WrOneData(i,t); //SEG0 COM0-3. SEG1 COM0-3. SEG2 COM0-3. SEG3 COM0-3. .......
                           t<<=1;
                           t++;
                           DelayMS(5000);
                          }
                     }
               }
}
*/