/**************************************************************************************************
  Filename:       GenericApp.h
  Revised:        $Date: 2007-10-27 17:22:23 -0700 (Sat, 27 Oct 2007) $
  Revision:       $Revision: 15795 $

  Description:    This file contains the Generic Application definitions.
*/
/***********************************************************************
 * FT/ZIGBEE/��������������
 ***********************************************************************/
/*
ZDO_COORDINATOR=0             //0 ����·�ɳ���  1 ��������Э��������
SENSOR_TYPE='K'               //���������� ���� SENSOR_TYPE='K' �� SENSOR_TYPE=0X03
CHANLIST_C_R_E=11             //�ŵ�  11-26
ZDAPP_CONFIG_PAN_ID=0xFFFF    // 0XFFFF   PAN_ID�������    ����0XFFFFʱ��PAN_ID����� �Ƕ��� 
ZigBee_C_R_E_Engineering      //�㲥ģʽ�� ��x ��Ե�ģʽ
ZigBee_C_R_E_IEEE             //IEEE����ַ���ݸ�ʽ ��x ����IEEE����ַ���ݸ�ʽ
SENSOR_TYPE_R_E=0X01          //�������̵�ַ���ã� ��x �̵�ַ���ڵ����
SENSOR_TYPE_POWER_ON         //������Ѱ������ ��  ��x Ѱ�Ҳ����������
*/
#if(SENSOR_TYPE =='E')
#define NB_IOT_S10   //��� �򿪴˶��� ������NBIOT���

#endif

#if defined (NB_IOT_S10)
extern   unsigned char NBliucheng;
extern unsigned char NB_IMEI[16];//IMEI��
extern unsigned char NB_S;//���ݳ���
#endif
/***********************************************************************
 * FT/ZIGBEE/��������������
 ***********************************************************************/
/*
A//���          A
J//��ȼ����      J
L//����	        L
M//���-��¶     M
N//����          N
0X03//315M������  0X03 
0X04 //��    0X04 
0X22 //������̼  0x22
���Ͽ��������

G//RFID          G
T//������        T****************************8
O//������������  O*************************88
0X20//��������      0X20
0X23//ָ��    0X23
0X02//ֱ���������  0X02 

P//����ѧϰң��  P
0X06//����С��    0X06****************************8
0X09//�๦�ܿ��ư� 0X09*****************************
0X0A//���ܻ���ISO15693  0X0A************************
0X0B//  125K��Ƶ 0x0B
���ڿ���

B//������ٶ�    B
C//��ǿ          C
D//��ɫ          D
E//��ʪ��        E
F//��ѹ����      F
I//ң����	I
Q//���ӳ�        Q****************************
U//18B20         U**************************8

0x01//���ӳ�        0x01****************************

0X10 //������  0X10
0x11 //���������� 0X11
0X21 //����   0X21
AD�ɼ�




K//R���߿���      K
0X12 //�����     0x12
S//R����ģ��      S****************************
H//R���ߴ�������  H*****************************	
0X05// �������  0x05
0X07// ����Ƶ  0x07
0X08//  1443A 0x08


���ƺ�ȫ���� R ·��
���տ���ģ��
//ZCD_NV_APP_PANID_H   //PAN
**************************************************************************************************/

#ifndef GENERICAPP_H
#define GENERICAPP_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "ZComDef.h" 

/*********************************************************************
 * CONSTANTS 
 */

//#define CC2530_V30    //�������5�ֽ� ��־λ�汾
//#define CC2530_RF_433M    //���ݴ��ڴ����RF_433Mģ�鷢��
// These constants are only for example and should be changed to the
// device's needs
#define GENERICAPP_ENDPOINT           10

#define GENERICAPP_PROFID             0x0F04
#define GENERICAPP_DEVICEID           0x0001
#define GENERICAPP_DEVICE_VERSION     0
#define GENERICAPP_FLAGS              0

#define GENERICAPP_MAX_CLUSTERS       1
#define GENERICAPP_CLUSTERID          1

// Send Message Timeout
#define GENERICAPP_SEND_MSG_TIMEOUT   500     // Every 0.5 seconds

// Application Events (OSAL) - These are bit weighted definitions.
#define GENERICAPP_SEND_MSG_EVT       0x0001

 #if(SENSOR_TYPE ==0X0D) 
  #define TGRD15693   //��� ��̩����¸�Ƶ15693ģ��򿪴˶���
 //#define PN532   //��� ��PN532-NFCģ��򿪴˶���
#endif 
#if(SENSOR_TYPE ==0X0E)  
 //#define STM2_4G   //��� 
 #define NRF2_4G   //��� NRF
#endif
  

#if(SENSOR_TYPE =='F')  
//#define BMP085 //���� 
#define BMP180 //���� 
#endif
  
#if(SENSOR_TYPE =='Q')  
//#define SHINING100MIL //���� ��һ�� ���ӳ� 100mil
#define SHINING75MIL //���� �ڶ��� ���ӳ�  75mil
#endif
  
#if(SENSOR_TYPE ==0X6A) 
  //#define ADCP //AD �ɼ�
#define HX711P //���ݲɼ�HX711
                    
#endif 
  
#if(SENSOR_TYPE ==0X07)  
  extern unsigned char AB;
//#define AB //���� �����ϴ������α����ϴ�   ��д����ʱ �����ϴδ򿪴ζ���
//#define UHF //���� ������
#define RLM100 //���� RLM100
#endif
  
#if(SENSOR_TYPE ==0X72)
//#define SDS011 //���� SDS011����PM2.5������  //����PM2.5���δ˶���
#endif
#if(SENSOR_TYPE ==0X78)
extern  unsigned char data_buf[9];
extern  unsigned char data_RPY;
#endif
#if(SENSOR_TYPE ==0X13)
#define HUABANG  //���廪���� IEEE754
//#define ammeter  //������ʽ���
#endif

#if(SENSOR_TYPE ==0X14) 
//#define PH_A   //�Ϻ�ŵ������PH ORP�����    ��� ��֮ǰ�汾��PH�ƴ򿪴˶���
#define PH_ORP   //���������Զ����������޹�˾(MIK-PH160)  ��� ��PH/ORP�����ǣ��򿪴˶���
//#define PH_E201C   //ֱ���״�PH���ϵ缫���źŴ���ɼ� �򿪴˶���
//���Ϻ궨�� ֻ����һ���
#endif   
/*********************************************************************
 * MACROS
 */
extern uint8 AF_OK;
extern uint8 AF_RF;
extern uint8 AF_RFn;

extern unsigned int GenericApp_applicationdata;
extern unsigned int  GenericApp_applicationbuf;
extern unsigned int GenericApp_uart_data;
extern unsigned char  GenericApp_CR;
extern uint8 openoff;
extern unsigned char  GenericApp_appIO;
extern unsigned int GenericApp_KSH;  
extern unsigned int GenericApp_KSH86;
extern uint8 Send_data[];
extern uint8 Send_datalend;
extern  unsigned int GenericApp_ON_OFF;
extern  unsigned char GenericApp_BX;
extern unsigned char OSAL_SET_CPU_INTO_SLEEP;

#if(ZDO_COORDINATOR==2)  //ZIGBEE  AT����ģʽ ͸��ģʽ
extern uint8 FT_AT;//0 ����ģʽ//1 ͸��ģʽ
#endif

#if(SENSOR_TYPE ==0X23)
extern unsigned char  SFG_R30X;
extern unsigned char  SFG_R30XA[3];
#endif 
#if(SENSOR_TYPE ==0X31)
#define RFID125K   //��� �ǵ�Ƶ���򿪴˶���
//#define RFID_NFC   //��� ��NFC��Ƶ���򿪴˶���

extern  uint8 Uart_Rev_Buff_1[6];
extern  uint8 Uart_Rev_Buff_2[6];
extern uint8 car_stata;
extern uint8 car_op;
extern uint8 car_sum;
extern uint8  holzer;
#endif

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task Initialization for the Generic Application
 */
extern void GenericApp_Init( byte task_id );

/*
 * Task Event Processor for the Generic Application
 */
extern UINT16 GenericApp_ProcessEvent( byte task_id, UINT16 events );
extern void GenericApp_SendTheMessage(void);
extern void GenericApp_SendFT(void);
extern void GenericAppEndDeviceEB(void);
extern void GenericAppCoordEB(void);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* GENERICAPP_H */
