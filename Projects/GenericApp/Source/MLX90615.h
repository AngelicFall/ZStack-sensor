#include <ioCC2530.h>
#include <string.h>                                 //ͷ�ļ�����������
#include "stdio.h"
#define uint unsigned int
#define uchar unsigned char
#define  _nop_() asm("NOP")
//MLX90615
//�궨��I/O�˿ں�SMBus�źŵķ���
//----------------------------------------------------------------------------------------------------------------------------------------//
#define _SDA_OUTPUT   P1DIR |= 0X10;            //����SDAΪ��©���
#define _SDA_INPUT  P1DIR&= (~0X10); 	  //����SDAΪ��������
#define _SCL_IO  P1DIR |= 0X08;  	//����SDAΪ��©���
#define SDA  P1_4                                                                //ָ��SDA�߸�P14
#define SCL  P1_3                                                                //ָ��SCL�߸�P13

//----------------------------------------------------------------------------------------------------------------------------------------//

void Delay_mlx90615(unsigned int N);
void start_bit(void);
void stop_bit(void);
void send_bit(unsigned char bit_out);
unsigned char receive_bit(void);
unsigned char slave_ack(void);
void TX_byte(unsigned char TX_buffer);
unsigned char RX_byte(unsigned char ack_nack);
unsigned char PEC_cal(unsigned char pec[],int n);
void EEPROM_WRITE(unsigned char slave_addW,unsigned char cmdW,unsigned char DataL,unsigned char DataH);
unsigned long int MEM_READ(unsigned char slave_addR, unsigned char cmdR);
void CALTEMP(unsigned long int TEMP,unsigned char *Datan);
void dec2hex(float e,unsigned int *c);

void Delay_mlx90615(unsigned int N)
{ 
    unsigned int i;
    for(i=0;i<N;i++)
	{ 
    _nop_();}  
}
//----------------------------------------------------------------------------------------------------------------------------------------//

//������: start_bit
//����: ��SMBus�����ϲ�����ʼ״̬
//ע��: �ο�"ϵͳ��������˵����-�汾2.0"
//----------------------------------------------------------------------------------------------------------------------------------------//
void start_bit(void)
{
   _SDA_OUTPUT;		                    //����SDAΪ���
   SDA=1;				       //����SDA��Ϊ�ߵ�ƽ
   _nop_();_nop_();				  
   SCL=1;				       //����SCL��Ϊ�ߵ�ƽ
   Delay_mlx90615(5);				       //����ֹ����ʼ״̬֮��������߿���ʱ��(Tbuf=4.7us��Сֵ)
   SDA=0;				       //����SDA��Ϊ�͵�ƽ
   Delay_mlx90615(5);				      
   //���ظ�����ʼ״̬��ı���ʱ�䣬�ڸ�ʱ��󣬲�����һ��ʱ���ź�
  					       //Thd:sta=4us��Сֵ
   SCL=0;				       //����SCL��Ϊ�͵�ƽ
   _nop_();_nop_();

}
//----------------------------------------------------------------------------------------------------------------------------------------//
//������: stop_bit
//����: ��SMBus�����ϲ�����ֹ״̬
//ע��: �ο�"ϵͳ��������˵����-�汾2.0"
//----------------------------------------------------------------------------------------------------------------------------------------//
void stop_bit(void)
{
  _SDA_OUTPUT;				 //����SDAΪ���
  SCL=0;			     		 //����SCL��Ϊ�͵�ƽ
  Delay_mlx90615(5);
  SDA=0;					 //����SDA��Ϊ�͵�ƽ
  Delay_mlx90615(5);
  SCL=1;				             //����SCL��Ϊ�ߵ�ƽ
  Delay_mlx90615(5);				             //��ֹ״̬����ʱ��(Tsu:sto=4.0us��Сֵ)
  SDA=1;				             //����SDA��Ϊ�ߵ�ƽ 
}
//----------------------------------------------------------------------------------------------------------------------------------------//
//������: send_bit
//����:��SMBus�����Ϸ���һλ����
//----------------------------------------------------------------------------------------------------------------------------------------//
void send_bit(unsigned char bit_out)
{
   
  _SDA_OUTPUT;			   //����SDAΪ��©������������ϴ�������

  if(bit_out==0)				   //�˶��ֽڵ�λ
            					   //���bit_out=1������SDA��Ϊ�ߵ�ƽ
             SDA=0;
  else							  
             SDA=1;				   //���bit_out=0������SDA��Ϊ�͵�ƽ

  _nop_();				   //
  _nop_();				   //Tsu:dat=250ns ��Сֵ
  _nop_();				   //
  SCL=1;				   //����SCL��Ϊ�ߵ�ƽ
  Delay_mlx90615(4);				  //ʱ������ߵ�ƽ����(10.6us)
  SCL=0;				  //����SCL��Ϊ�͵�ƽ
  Delay_mlx90615(4);                                                  //ʱ������͵�ƽ����  
}
//----------------------------------------------------------------------------------------------------------------------------------------//
//������: receive_bit
//���ܣ���SMBus�����Ͻ���һλ����
//----------------------------------------------------------------------------------------------------------------------------------------//
unsigned char receive_bit(void)
{
  unsigned char bit_in;
  _SDA_INPUT;				                //����SDAΪ��������
  SCL=1;					   //����SCL��Ϊ�ߵ�ƽ
  Delay_mlx90615(2);
  if(SDA==1)					   //�������϶�ȡһλ������bit_in
       bit_in=1;
  else
       bit_in=0;
  Delay_mlx90615(2);
  SCL=0;					   //����SCL��Ϊ�͵�ƽ
  Delay_mlx90615(4);
  return bit_in;                                                           //����bit_inֵ
}
//----------------------------------------------------------------------------------------------------------------------------------------//
//������: slave_ack
//����: ���ܿ�����MLX90615�ж�ȡȷ��λ
//����ֵ:  unsigned char ack
// 1 - ACK
// 0 - NACK
//----------------------------------------------------------------------------------------------------------------------------------------//
unsigned char slave_ack(void)
{
   unsigned char ack;
   ack=0;
   _SDA_INPUT;				    //����SDAΪ��������
   SCL=1;					    //����SCL��Ϊ�ߵ�ƽ
   Delay_mlx90615(2);    
   if(SDA==1)					    //�������϶�ȡһλ������ack
         ack=0;
   else
         ack=1; 
   Delay_mlx90615(2);   
   SCL=0;					    //����SCL��Ϊ�͵�ƽ
   Delay_mlx90615(4);   
   return ack;
}
//----------------------------------------------------------------------------------------------------------------------------------------//
//����һ���ֽ�
//������: TX_byte
//����: ��SMBus�����Ϸ���һ���ֽ�
//����: unsigned char TX_buffer (��Ҫ�������Ϸ��͵��ֽ�)
//ע��: �ȷ����ֽڵĸ�λ

//----------------------------------------------------------------------------------------------------------------------------------------//
void TX_byte(unsigned char TX_buffer)
{
   unsigned char Bit_counter;
   unsigned char bit_out;
     
   for(Bit_counter=8;Bit_counter;Bit_counter--)
   {
       if(TX_buffer&0x80)
		     bit_out=1;	               //���TX_buffer�ĵ�ǰλ��1,����bit_outΪ1
		else
		     bit_out=0;	         	  //��������bit_outΪ0
     send_bit(bit_out);			  //����SMBus�����ϵĵ�ǰλ   
     TX_buffer<<=1;		               //�˶���һλ		  
	}			            	                      
}
//----------------------------------------------------------------------------------------------------------------------------------------//
//����һ���ֽ�
//������: RX_byte
//����: ��SMBus�����Ͻ���һ���ֽ�
//����: unsigned char ack_nack (ȷ��λ)
//0 - ������������ ACK
//1 - ������������ NACK
//����ֵ:  unsigned char RX_buffer (���߽��յ��ֽ�)
//ע��: �Ƚ����ֽڵĸ�λ
//----------------------------------------------------------------------------------------------------------------------------------------//
unsigned char RX_byte(unsigned char ack_nack)
{
    unsigned char RX_buffer;
    unsigned char Bit_counter;
    for(Bit_counter=8;Bit_counter;Bit_counter--)
    {
		if(receive_bit()==1)	                //��SDA�߶�ȡһλ
		   {
			RX_buffer<<=1;		   //���λΪ"1"����"1"��RX_buffer 
			RX_buffer|=0x01;
		   }
		else				   //���λΪ"0"����"0"��RX_buffer
		   {
			RX_buffer<<=1;
			RX_buffer&=0xfe;
		   }		
      } 
	 send_bit(ack_nack);			   //����ȷ��λ
	 return RX_buffer;
}

//����PEC����У����
//������: PEC_cal
//����: ���ݽ��յ��ֽڼ���PEC��
//����: unsigned char pec[], int n
//����ֵ: pec[0] - ���ֽڰ�����������crc��ֵ
//----------------------------------------------------------------------------------------------------------------------------------------//
unsigned char PEC_cal(unsigned char pec[],int n)
{
     unsigned char crc[6];
     unsigned char Bitposition=47;
     unsigned char shift;
     unsigned char i;
     unsigned char j;
     unsigned char temp;
  do{
          crc[5]=0;           			        //���� CRC��ֵ 0x000000000107
          crc[4]=0;
          crc[3]=0;
          crc[2]=0;
          crc[1]=0x01;
          crc[0]=0x07;
          Bitposition=47;     		                     //����Bitposition�����ֵΪ47
          shift=0;
          //�ڴ��͵��ֽ����ҳ���һ��"1"

          i=5;                			        //������߱�־λ (�����ֽڱ�־)
          j=0;                			        //�ֽ�λ��־�������λ��ʼ
          while((pec[i]&(0x80>>j))==0 && (i>0))	  
	  {
             Bitposition--;
             if(j<7)
	   {
                    j++;
                 }
             else
	      {
                   j=0x00;
                   i--;
                   }
           }//while�����������ҳ�Bitposition��Ϊ"1"�����λλ��
          shift=Bitposition-8;                                   //�õ�CRC��ֵ��Ҫ����/���Ƶ���ֵ"shift"
	                                                              //��CRC��������"shift"λ
          while(shift)
	     {
              for(i=5;i<0xFF;i--)
		 {  
                    if((crc[i-1]&0x80) && (i>0))          //�˶��ֽڵ����λ����һλ�Ƿ�Ϊ"1"
		     {   			       //�� - ��ǰ�ֽ� + 1
                          temp=1;		       //�� - ��ǰ�ֽ� + 0
                     }				       //ʵ���ֽ�֮���ƶ�"1"
                    else
	             {
                          temp=0;
                     }
                     crc[i]<<=1;
                     crc[i]+=temp;
                  } 

                  shift--;
              } 
           //pec��crc֮�����������
           for(i=0;i<=5;i++)
		   {
                   pec[i]^=crc[i];
		   }  
      }while(Bitposition>8); 
	return pec[0];                                    //���ؼ������õ�crc��ֵ
} 
//----------------------------------------------------------------------------------------------------------------------------------------//
//��MLX90615 RAM/EEPROM ��ȡ������
//������: MEM_READ
//����: �����ܿص�ַ������ʱ��MLX90615��ȡ����
//����: unsigned char slave_addR (�ܿص�ַ)
//         unsigned char cmdR (����)
//����ֵ: unsigned long int Data
//----------------------------------------------------------------------------------------------------------------------------------------//
unsigned long int MEM_READ(unsigned char slave_addR, unsigned char cmdR)
{	
	 unsigned char DataL;		                           //
	 unsigned char DataH;				 //��MLX90615��ȡ�����ݰ�
	 unsigned char PEC;				 //
	 unsigned long int Data;			              //��MLX90615���صļĴ�����ֵ
	 unsigned char Pecreg;				 //�洢��������PEC�ֽ�
              unsigned char arr[6];				 //�洢�ѷ����ֽڵĻ�����
	 unsigned char ack_nack;
	 unsigned char SLA;										
	 SLA=(slave_addR<<1);
   begin:		             
	 start_bit();                 			               //������ʼλ
	 TX_byte(SLA);					  //�����ܿ�������ַ��д����
	 if(slave_ack()==0)
	 {
	     stop_bit();
	     goto begin;
              }						  //��������
              TX_byte(cmdR);
	 if(slave_ack()==0)
	 {
	     stop_bit();
	     goto begin;
              }					
	 start_bit(); 	                                                      //�����ظ���ʼλ				
	 TX_byte(SLA+1);                                                   //�����ܿ�������ַ��������
	 if(slave_ack()==0)
	 {
	     stop_bit();
	     goto begin;
	 }
	 DataL=RX_byte(0);				  //
							  //��ȡ�����ֽ�����
	 DataH=RX_byte(0);				  //
	 PEC=RX_byte(ack_nack);		               //��ȡMLX90615��PEC��
	 if(ack_nack==1)				  //������������ack ���� nack
              //ȡ����pec���㣬���PEC�ǲ���ȷ�ģ�����nack�����ص�goto begin
	 {
	     stop_bit();
	     goto begin;
	 }						
	 stop_bit();                                                               //������ֹλ
	 arr[5]=(SLA);
              arr[4]=cmdR;
              arr[3]=(SLA+1);               
              arr[2]=DataL;
              arr[1]=DataH;
              arr[0]=0;                  										 
	 Pecreg=PEC_cal(arr,6);  			  //���ü��� CRC �ĺ���
	 if(PEC==Pecreg)
	    {
		  ack_nack=0;
	    }
	  else
	    {
		 ack_nack=1;
	    }
	  Data=(( unsigned int)DataH<<8)+DataL;
	  return Data;

}
//----------------------------------------------------------------------------------------------------------------------------------------//	
//MLX90615 EEPROM��д������
//������: EEPROM_WRITE
//����: ��������д��������ݵ������ܿ�������ַ��MLX90615
//����: unsigned char slave_addW (�ܿ�������ַ)
//unsigned char cmdW (����)
//unsigned char DataL 
//unsigned char DataH
//----------------------------------------------------------------------------------------------------------------------------------------//	
void EEPROM_WRITE(unsigned char slave_addW,unsigned char cmdW,unsigned char DataL,unsigned char DataH)
{
     unsigned char Pecreg;			             //�洢��������PEC�ֽ�
     unsigned char SLA;
     unsigned char arr[6];					//�洢��Ҫ�����ֽڵĻ�����
     SLA=(slave_addW<<1);
     arr[5]=0;
     arr[4]=SLA;
     arr[3]=cmdW;
     arr[2]=DataL;
     arr[1]=DataH;
     arr[0]=0;
     Pecreg=PEC_cal(arr,6);

   begin:
     start_bit();						 //������ʼλ
     TX_byte(SLA);					 //�����ܿص�ַ��д����
     if(slave_ack()==0)								  
     {
         stop_bit();
         goto begin;
     }
     TX_byte(cmdW);					  //��������
     if(slave_ack()==0)
     {
         stop_bit();
         goto begin;
     }
     TX_byte(DataL);					 //�������ݵ�λ�ֽ�
     if(slave_ack()==0)
     {
         stop_bit();
         goto begin;
     }
     TX_byte(DataH);					 //�������ݸ�λ�ֽ�
     if(slave_ack()==0)
     {
         stop_bit();
         goto begin;
     }
     TX_byte(Pecreg);					 //����PEC��
     if(slave_ack()==0)
     {
         stop_bit();
         goto begin;
     }
     stop_bit();	            				              //������ֹλ
     Delay_mlx90615(200);						 //�Ⱥ�5ms
    
}
//----------------------------------------------------------------------------------------------------------------------------------------//
//������: CALTEMP
//����: �����¶�
//����: unsigned long int TEMP (��MLX90615�ж���������)
//����ֵ:     unsigned int mah 
//                 mah������mah[5]���׵�ַ
//ע��: ��ʮ�����ƴ���ת��Ϊ�¶����ݵĹ�ʽΪT=(Data)*0.02-273.15
//----------------------------------------------------------------------------------------------------------------------------------------//
void CALTEMP(unsigned long int TEMP,unsigned char *mah)
{
      unsigned long int T;
      unsigned int a,b;
      T=TEMP*2;
      if(T>=27315)
            {
               T=T-27315;
               a=T/100;  //��������
               b=T-a*100;//С������
            }
          else
               {
                  T=27315-T;
                  a=T/100;  //��������
                  b=T-a*100;//С������
                }
	    mah[0]=a;//��������
            mah[1]=b;//С������
}

/*
void main(void)
{    unsigned char     slaveaddress;	 			  
     unsigned long int    DATA;  
     unsigned char tempbat[5];
     
     _SCL_IO;                                            //���ú궨��-����SCLΪ��©ʽI/O��
     _SDA_OUTPUT;                                //���ú궨��-����SDAΪ��©ʽ���
     SCL=0;				//
     Delay_mlx90615(30000);		 //SMBus����ʱ�䣬��PWMģʽת��ΪSMBusģʽ(21ms - 39ms)
     SCL=1;				//	
     initUARTtest();
     while(1)
     {
          slaveaddress=MEM_READ(0x00,0x10);
         //��ȡ����MLX90615 EEPROM "00h"��ַ�е�SMBus��ַ
         DATA=MEM_READ(slaveaddress,0x27);
         //����������ַ��MLX90615���ڴ�07h�ж�ȡ�����¶�
          CALTEMP(DATA,tempbat);	
         //�������õ�ʮ�������¶ȸ�ʽ����ʵ���¶�
          UartTX_Send_String(tempbat,5);	        
          for(int p=0;p<100;p++)
          Delay_mlx90615(30000);		 
     }
 }
*/