/************************************************************
* �궨��			

************************************************************/
#include "IIC.h"
/************************************************************

* ������ʼ��												
************************************************************/
void mDelay(unsigned j);
void Start(void);
void Stop(void);
void Ack(void);
void NoAck(void);
void Send(unsigned char Data);
unsigned char Read(void);
/************************************************************
* ��������:��ʱk ms����										
* ��ڲ���:k(1-128)											
* ���ڲ���:��	
* ��    ��:												
**********************************************************/
//��ʱ����
void mDelay(unsigned j)
{
	unsigned int i;
	for(;j>0;j--)
	{	for(i=0;i<500;i++)
		{;}
    }
}
//������ʼ����
void Start(void)
{IIC_DATAOUT;
	SDA=1;
	SCL=1;
	NOPS;
	SDA=0;
	NOPS;
}
//����ֹͣ����
void Stop(void)
{IIC_DATAOUT;
	SDA=0;
	SCL=1;
	NOPS;
	SDA=1;
	NOPS;	
}
//Ӧ��λ
void Ack(void)
{IIC_DATAOUT;
	SDA=0;
	NOPS;
	SCL=1;
	NOPS;
	SCL=0;
}
//��Ӧ��
void NoAck(void)
{IIC_DATAOUT;
	SDA=1;
	NOPS;
	SCL=1;
	NOPS;
	SCL=0;	
}
//���������ӳ���DataΪҪ���͵�����a
void Send(unsigned char Data)
{	 unsigned char BitCounter=8;//λ������
	 unsigned char temp;//�м��������
        IIC_DATAOUT;
	do{ 
	 temp=Data;
	 SCL=0;
	 NOPS;
	 if((temp&0x0080)==0x0080)//������λ��1
	    SDA=1;
	 else
		SDA=0;
	 SCL=1;
	 temp=Data<<1;//����
	 Data=temp;
	 BitCounter--;
	 }while(BitCounter);
	 SCL=0;
         NOPS;
         SDA=1;
          NOPS;
}
//��һ���ֽڵ����ݣ������ظ��ֽڵ�ֵ
unsigned char Read(void)
{   unsigned char temp=0;
    unsigned char temp1=0;
    unsigned BitCounter=8;
   IIC_DATAOUT;
	SDA=1;
        IIC_DATAIN ;
	do{	SCL=0;
		NOPS;
		SCL=1;
		NOPS;
		if(SDA)
		temp=temp|0x01;
		else
		temp=temp&0xfe;
		if(BitCounter-1)
		{	temp1=temp<<1;
			temp=temp1;
		}
		BitCounter--;
	  }while(BitCounter);
         IIC_DATAOUT;
	return(temp);	
}
//***************************************************

void Single_Write_(unsigned char REG_Address,unsigned char REG_data)
{
    Start();                  //��ʼ�ź�
#if(SENSOR_TYPE =='F')
    Send(AddWr);  //�����豸��ַ+д�ź�
    Ack();
#endif
    Send(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf 
    Ack();
   Send(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf
   Ack();
   Stop();                   //����ֹͣ�ź�
   NOPS;
}

//********���ֽڶ�ȡ�ڲ��Ĵ���*************************
unsigned char Single_Read_(unsigned char REG_Address)
{  unsigned char REG_data;
    Start();                          //��ʼ�ź�
#if(SENSOR_TYPE =='F')
    Send(AddWr);          //�����豸��ַ+д�ź�
    Ack();
#endif
    Send(REG_Address);                   //���ʹ洢��Ԫ��ַ����0��ʼ	
    Ack();
#if(SENSOR_TYPE =='F')
   Start();                          //��ʼ�ź�
   Send(AddRd);         //�����豸��ַ+���ź�
   Ack();
#endif
    REG_data=Read();              //�����Ĵ�������
    SCL=0;
	 NoAck();  
	Stop();                           //ֹͣ�ź�
         NOPS;
           NOPS;
    return REG_data; 
}

//��IIC��д����
void WrToROM(unsigned char Data[],unsigned char Address,unsigned char Num)
{   unsigned char i;
    unsigned char *Pdata;
    Pdata=Data;
	for(i=0;i<Num;i++)
	{	Start();
		Send(AddWr);
		Ack();
		Send(Address+i);
		Ack();
		Send(*(Pdata+i));
		Ack();
		Stop();
		mDelay(20);
	}
}
//	������
void RdFromROM(unsigned char Data[],unsigned char Address,unsigned char Num)
{
	unsigned char i;
	unsigned char *Pdata;
	Pdata=Data;
	for(i=0;i<Num;i++)
	{
		Start();
		Send(AddWr);
		Ack();
		Send(Address+i);
		Ack();
		Start();
		Send(AddRd);
		Ack();
		*(Pdata+i)=Read();
		SCL=0;
        NoAck();
		Stop();
	}
}
