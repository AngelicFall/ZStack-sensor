#include <HX711.h>
unsigned long  INzero; //���ֵ
unsigned long  AD_val;	//ADֵ����ֵ
long AD_Compar;//AD���ֵ
unsigned long ReadCount(char AB)
{ 
unsigned long Count;    
unsigned char i; 
CLR_ADSK() ; 
Count=0; 
while(!DATA); 
asm("NOP");
while(DATA); 
for (i=0;i<24;i++){
SET_ADSK() ; 
Count=Count<<1; 
CLR_ADSK() ; 
if(DATA) Count++; 
} 
SET_ADSK() ; 
Count=Count^0x800000; 
CLR_ADSK() ;
if(AB==1)
{
SET_ADSK() ;
asm("NOP");
CLR_ADSK() ;
} 
SET_ADSK(); 
return(Count); 
} 

void AD_filter() ///////////////////////�Զ��˲�////////////////////////////
{
AD_val= ReadCount(0);
AD_Compar=AD_val;
AD_Compar>>=8; 
AD_val>>=6;
AD_Compar=AD_Compar-INzero;//------Ҫ
}

 void Tozero()/////////////////////////�����Զ�����/////////////////////////
{AD_val= ReadCount(0);
AD_Compar=AD_val;
AD_Compar>>=8; 
if(AD_Compar<80000)
{	
INzero=AD_Compar;
}
} 