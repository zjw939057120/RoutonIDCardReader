
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SDTAPI_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STDCALL SDTAPI_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#include "stdafx.h"

#ifdef SDTAPI_EXPORTS
#define SDTAPI_API __declspec(dllexport)
#else
#define SDTAPI_API __declspec(dllimport)
#endif

#ifdef  _WIN32
#define STDCALL  __stdcall
#else
#define STDCALL
#endif
//#ifndef SDTAPI_
//#define SDTAPI_

// This class is exported from the Sdtapi.dll
#ifdef __cplusplus

#define CPUCARD 0

extern "C"{
#endif
typedef void (WINAPI *TimerOutCallBack)();


SDTAPI_API	int STDCALL SDT_SetMaxRFByte(int iPortID,unsigned char ucByte,int bIfOpen);
SDTAPI_API	int STDCALL SDT_GetCOMBaud(int iComID,unsigned int *puiBaud);
SDTAPI_API	int STDCALL SDT_SetCOMBaud(int iComID,unsigned int  uiCurrBaud,unsigned int  uiSetBaud);
SDTAPI_API	int STDCALL SDT_SetOpenCOMBaud(unsigned int setBaud);
SDTAPI_API	int STDCALL SDT_OpenPort(int iPortID);
SDTAPI_API	int STDCALL SDT_ClosePort(int iPortID);
SDTAPI_API	int STDCALL SDT_GetErrorString(int ErrorCode, char * ErrorString);

SDTAPI_API	int STDCALL SDT_GetSAMStatus(int iPortID,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ResetSAM(int iPortID,int iIfOpen);
SDTAPI_API	int STDCALL SDT_GetSAMID(int iPortID,unsigned char *pucSAMID,int iIfOpen);
SDTAPI_API	int STDCALL SDT_GetSAMIDToStr(int iPortID,char *pcSAMID,int iIfOpen);
SDTAPI_API	int STDCALL	CardOn(void);
SDTAPI_API	int STDCALL	SDT_StartFindIDCard(int iPortID,unsigned char *pucIIN,int iIfOpen);
SDTAPI_API	int STDCALL	SDT_SelectIDCard(int iPortID,unsigned char *pucSN,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ReadBaseMsg(int iPortID,unsigned char * pucCHMsg,unsigned int *	puiCHMsgLen,unsigned char * pucPHMsg,unsigned int  *puiPHMsgLen,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ReadFPMsg(int iPortID,unsigned char * pucFPMsg,unsigned int *puiFPMsgLen,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ReadIINSNDN(int iPortID,unsigned char * pucIINSNDN,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ReadNewAppMsg(int iPortID,unsigned char * pucAppMsg,unsigned int *puiAppMsgLen,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ReadMngInfo(int iPortID, unsigned char * pucManageMsg,int iIfOpen);  //????????????

SDTAPI_API	int STDCALL SDT_ReadBaseMsgToFile(int iPortID,char * pcCHMsgFileName,unsigned int *puiCHMsgFileLen,char * pcPHMsgFileName,unsigned int  *puiPHMsgFileLen,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ReadIINSNDNToASCII(int iPortID, unsigned char *pucRecvData,int iIfOpen);

int SDTAPI_API STDCALL  InitComm( int iPort );
int SDTAPI_API STDCALL  CloseComm(void);
int SDTAPI_API STDCALL  Authenticate(void);

//int SDTAPI_API STDCALL  Read_Content(int  Active, char* Path);
int SDTAPI_API STDCALL  ReadBaseMsgWPhoto( unsigned char * pMsg, int * len,char * directory);
int SDTAPI_API STDCALL  ReadBaseMsgPhoto( unsigned char * pMsg, int * len,char * directory);
int SDTAPI_API STDCALL  ReadBaseInfosPhoto( char * Name, char * Gender, char * Folk,
						   char *BirthDay, char * Code, char * Address,
						   char *Agency, char * ExpireStart,char* ExpireEnd,char * directory);

int SDTAPI_API STDCALL ReadBaseInfosFPPhoto(char * Name, char * Gender, char * Folk,
										  char *BirthDay, char * Code, char * Address,
										  char *Agency, char * ExpireStart,char* ExpireEnd,char * directory, unsigned char * pucFPMsg,unsigned int  *puiFPMsgLen);


int SDTAPI_API STDCALL  ReadBaseMsgW( unsigned char * pMsg, int * len);
int SDTAPI_API STDCALL  ReadBaseMsg( unsigned char * pMsg, int * len);
int SDTAPI_API STDCALL  ReadBaseInfos( char * Name, char * Gender, char * Folk,
						   char *BirthDay, char * Code, char * Address,
						   char *Agency, char * ExpireStart,char* ExpireEnd);

int SDTAPI_API STDCALL  ReadNewAppMsgW( unsigned char * pMsg, int * num );
int SDTAPI_API STDCALL  ReadNewAppMsg( unsigned char * pMsg, int * len );
int SDTAPI_API STDCALL ReadNewAppInfos( unsigned char * addr1, unsigned char * addr2,
							 unsigned char * addr3, unsigned char * addr4,
							 int * num );

int SDTAPI_API STDCALL ReadIINSNDN( char * pMsg );

int SDTAPI_API STDCALL GetSAMIDToStr(char *pcSAMID );

// ????????????????????
int SDTAPI_API STDCALL UsbOpenBt();  //????usb????????????????????????
int SDTAPI_API STDCALL UsbCloseBt(); //????usb????????????????
int SDTAPI_API STDCALL ReadBtMac(char *macAddr, int BtType);  //macAddr:????mac????, BtType:???????? 0-2.1, 1-4.0
int SDTAPI_API STDCALL ConnectBtDevice(char *macAddr);     //????????mac????????????
int SDTAPI_API STDCALL ConnectBtDeviceTimeOut(char *macAddr, int TimeOut);    //????????mac?????????????? ????????????????
int SDTAPI_API STDCALL DisConnectBtDevice();  //????????
int SDTAPI_API STDCALL WriteBtDevice(char* pBuf, int iBufLen);  //??????????
int SDTAPI_API STDCALL ReadBtDevice(char* pBuf, int iBufLen);    //??????????
int SDTAPI_API STDCALL Routon_LT_BT_Handshake();   //????????????????
int SDTAPI_API STDCALL Routon_LT_BT_ChangeBtName(char *name, int BtType);  //????????????????
int SDTAPI_API STDCALL setBt3DESKey(char *key);  //????3DESkey
int SDTAPI_API STDCALL setBtPin(char *pinStr, int BtType); //????????pin
int SDTAPI_API STDCALL setBtSleep(int BtSleep); //????????????????
int SDTAPI_API STDCALL setSecretKey(char* key);
int SDTAPI_API STDCALL setBtKey_3DES(unsigned char *inputKey);
int SDTAPI_API STDCALL Routon_setBtKey_3DES();
int SDTAPI_API STDCALL Routon_setStandbySleep(int sleep); //???????????????????? (iDR240????)  sleep??????????30????
int SDTAPI_API STDCALL Routon_setLongPressedOFF(int seconds); //???????????????????? (iDR240????) seconds????????????????3~6??(????3,6)
int SDTAPI_API STDCALL Routon_setBtClose();  //????????????????
int SDTAPI_API STDCALL Routon_setBtNowSleep();  //??????????????????????????


int SDTAPI_API STDCALL Routon_GetBtName(char *name, int BtType);//????????????  0-android, 1-ios
int SDTAPI_API STDCALL Routon_GetBtPin(char *pinStr, int BtType); //????????PIN
int SDTAPI_API STDCALL Routon_GetBtSleep(); //????????????????  ????: ????
int SDTAPI_API STDCALL Routon_GetMainVersion(char *ver);  //?????? ????
int SDTAPI_API STDCALL Routon_GetCardVersion(char *ver);  //?????? ????
int SDTAPI_API STDCALL Routon_GetBtDevVersion(char *ver);  //???????? ????
int SDTAPI_API STDCALL Routon_GetBtDevBatteryPower();  //??????????????
int SDTAPI_API STDCALL Routon_GetStandbySleep(); //???????????????????? (iDR240????)  ????????????????30????
int SDTAPI_API STDCALL Routon_GetLongPressedOFF(); //???????????????????? (iDR240????) ??????????????3~6??(????3,6)



//????SAM_V????????????????????????????????
int SDTAPI_API STDCALL Routon_Samv_Comm_MaxLen(int maxLen);
int SDTAPI_API STDCALL Routon_LED_BEEP_Control(int led, int beep); //led: 0-led??, 1-led??;  beep: 0-??, 1-??


int SDTAPI_API STDCALL Routon_StartFindIDCard( unsigned char *err );
int SDTAPI_API STDCALL Routon_ReadBaseMsg( unsigned char * pucCHMsg,unsigned int *	puiCHMsgLen );
int SDTAPI_API STDCALL Routon_DecideIDCardType();
int SDTAPI_API STDCALL Routon_ReadForeignBaseInfos(char *enName, char *Gender, char *Code, char *Nation, char *cnName, char *BirthDay, char * ExpireStart,char* ExpireEnd);
int SDTAPI_API STDCALL Routon_ReadAllForeignBaseInfos(char *EnName, char *Gender, char *Code, char *Nation, char *CnName, char *BirthDay, char * ExpireStart,char* ExpireEnd,char* CardVertion,char* Agency,char* CardType, char* FutureItem);
int SDTAPI_API STDCALL Routon_ReadForeignBaseInfosPhoto(char *enName, char *Gender, char *Code, char *Nation, char *cnName, char *BirthDay, char * ExpireStart,char* ExpireEnd,char* directory);
int SDTAPI_API STDCALL Routon_ReadAllForeignBaseInfosPhoto(char *EnName, char *Gender, char *Code, char *Nation, char *CnName, char *BirthDay, char * ExpireStart,char* ExpireEnd,char* CardVertion,char* Agency,char* CardType, char* FutureItem,char* Directory);
int SDTAPI_API STDCALL Routon_ReadAllGATBaseInfos( char *Name, char *Gender, char *FutureItem1, char*BirthDay, char * Address, char *Code, char *Agency, char* ExpireStart, char* ExpireEnd, char* PassID, char* SignCnt, char *FutureItem2, char *CardType, char *FutureItem3);
int SDTAPI_API STDCALL Routon_BeepLED(bool BeepON,bool LEDON,unsigned int duration);
int SDTAPI_API STDCALL Routon_SetNewVersion(bool flag);
int SDTAPI_API STDCALL Routon_IC_FindCard(void);
int SDTAPI_API STDCALL Routon_IC_HL_ReadCardSN(char * SN);
int SDTAPI_API STDCALL Routon_IC_HL_ReadCard (int SID,int BID,int KeyType,unsigned char * Key,unsigned char * data);
int SDTAPI_API STDCALL Routon_IC_HL_WriteCard (int SID,int BID,int KeyType,unsigned char * Key,unsigned char * data);
/*
int SDTAPI_API STDCALL Routon_IC_Halt();  //??????????????
int SDTAPI_API STDCALL Routon_IC_Request(int mode); //???????? 0-Standard??????1-All????  ??????-??????????????????
int SDTAPI_API STDCALL Rotuon_IC_Anticoll();   //????????????????????????
int SDTAPI_API STDCALL Routon_IC_Select(char * SN); //????????????????????????????????   Sn-????????
int SDTAPI_API STDCALL Routon_IC_Auth_PassAddr(int SID,int BID, int KeyType, unsigned char * Key, char * SN);//????????????
int SDTAPI_API STDCALL Routon_IC_ReadCard(int SID,int BID, unsigned char * data);  //????????????
int SDTAPI_API STDCALL Routon_IC_WriteCard(int SID,int BID, unsigned char * data);  //??????????????
*/
int SDTAPI_API STDCALL Routon_IC_Format(int SID,int BID,int KeyType,unsigned char * Key, unsigned char * data, unsigned char * addr);  //????????
int SDTAPI_API STDCALL Routon_IC_Value(unsigned char * type,  int sSID,int sBID, unsigned char * data, int tSID,int tBID); //


int SDTAPI_API STDCALL Routon_Get210Version(unsigned char *ver);
int SDTAPI_API STDCALL Routon_Set210Update(void);
int SDTAPI_API STDCALL Routon_GetIdrType();

int SDTAPI_API STDCALL dc_init(int port,long baud);
int SDTAPI_API STDCALL dc_exit(int dev);
int SDTAPI_API STDCALL dc_request(int icdev,unsigned char _Mode,unsigned int *TagType);
int SDTAPI_API STDCALL dc_anticoll(int icdev,unsigned char _Bcnt,unsigned long *_Snr);
int SDTAPI_API STDCALL dc_select(int icdev,unsigned long _Snr,unsigned char *_Size);
int SDTAPI_API STDCALL dc_authentication_passaddr(int icdev, unsigned char _Mode, unsigned char Addr, unsigned char *passbuff);
int SDTAPI_API STDCALL dc_read(int icdev,unsigned char _Adr,unsigned char *_Data);
int SDTAPI_API STDCALL dc_write(int icdev,unsigned char _Adr,unsigned char *_Data); 
int SDTAPI_API STDCALL dc_halt(int icdev);
int SDTAPI_API STDCALL dc_BeepLED(int icdev,bool BeepON,bool LEDON,unsigned int duration);
int SDTAPI_API STDCALL HID_BeepLED(bool BeepON,bool LEDON,unsigned int duration);

int SDTAPI_API STDCALL PSAM_FunTest(void);
int SDTAPI_API STDCALL PSAM_ReadATR(unsigned char CardIndex,unsigned char SpeedIndex,unsigned char TypeIndex, unsigned char  *_Data);
int SDTAPI_API STDCALL PSAM_SendCMD(unsigned char CardIndex,unsigned char *_Cmd,int Len, unsigned char *_Data);
int SDTAPI_API STDCALL PSAM_PowerOff(unsigned char CardIndex);

int SDTAPI_API STDCALL GetHIDCount(void);
bool SDTAPI_API STDCALL HIDSelect(int index);
#if CPUCARD
int SDTAPI_API STDCALL Routon_ReadCitizenCard(char * CNo,char * Name,int * IDType,char *IDCode,char * AppInfo);
#endif
int SDTAPI_API STDCALL SDT_ReadBaseMsgFingerPrint(int iPortID,unsigned char * pucCHMsg,unsigned int *	puiCHMsgLen,unsigned char * pucPHMsg,unsigned int  *puiPHMsgLen,unsigned char * pucFPMsg,unsigned int  *puiFPMsgLen,int iIfOpen);
int SDTAPI_API STDCALL SDT_ReadBaseFPMsg(int iPortID,unsigned char * pucCHMsg,unsigned int *	puiCHMsgLen,unsigned char * pucPHMsg,unsigned int  *puiPHMsgLen,unsigned char * pucFPMsg,unsigned int  *puiFPMsgLen,int iIfOpen);

int SDTAPI_API STDCALL Routon_APDU (char * apdu,unsigned char * data,int * datalen);

int SDTAPI_API STDCALL SDT_ReadBaseFPMsgToFile(int iPort,char *pcCHMsgFileName, unsigned int *  puiCHMsgFileLen, char * pcPHMsgFileName, unsigned int  * puiPHMsgFileLen, char *pcFPMsgFileName, unsigned int  * puiFPMsgFileLen, int iIfOpen );
int SDTAPI_API STDCALL IsFingerPrintDevice(void);
int SDTAPI_API STDCALL ReadBaseFPMsg( unsigned char * pMsg, int * len ,unsigned char * pucFPMsg,int  *puiFPMsgLen);

int SDTAPI_API STDCALL Routon_CPUCard_PowerOFF(void);
int SDTAPI_API STDCALL Routon_CPUCard_Active(void);
int SDTAPI_API STDCALL Routon_CPUCard_ATS(unsigned char * ATSMsg,unsigned int * ATSLen);
int SDTAPI_API STDCALL Routon_CPUCard_PPS(unsigned char PPS0,unsigned char PPS1);
int SDTAPI_API STDCALL Routon_ShutDownAntenna(void);
int SDTAPI_API STDCALL Routon_Mute(bool isMute);
int SDTAPI_API STDCALL Routon_FindPassport(void);
int SDTAPI_API STDCALL Routon_ReadPassport(char * MRZL1,char * MRZL2,char * MRZL3);
int SDTAPI_API STDCALL Routon_RepeatRead(bool );
int SDTAPI_API STDCALL Routon_IsSaveWlt(bool );
bool SDTAPI_API STDCALL Routon_isComBase64(void);

int SDTAPI_API STDCALL Routon_ReadIINSNDN(char * pMsg);   //??????????????????????????
/*
* ????PSAM??????????ATR????  
* ??????  CardID??????????????0x01??????1??0X02??????2??
*         Speed??CPU????????(0:4800,1:9600,2:19200,3:38400)
*         Type ??CPU??????????(0:5V,1:3V)
*         ATSMsg?? ??????ATS????
*         ATSLen?? ??????ATS????????
*???????? 1-????  ????-????
*/
int SDTAPI_API STDCALL Routon_PSAMCard_ATRS(int Cardid, int Speed, int Type, unsigned char * ATSMsg,unsigned int * ATSLen);
/*
* ??PSAM??????????
* ?????? psamCmd??PSAM?????? ??????????
*        data????????????????
*        datalen??????????????????
* ????????1-????   ????-????
*/
int SDTAPI_API STDCALL Routon_PSAMCard_SendCmd(char* psamCmd, unsigned char * data,int * datalen);
/*
* ???? PSAM????
* ????????1-????   ????-????
*/
int SDTAPI_API STDCALL Routon_PSAMCard_PowerOFF(void);
/*
* ???????????????? iDR260????????
* ????????1-????   ????-????
*/
int SDTAPI_API STDCALL Routon_IDR260_PowerOFF(void);

/*
* ??SD?????????????? iDR260????????
* ??????  filename????????????????????16??????????\0??????   
          msg????????????????,????40????  byte????
          msgLen??????????
* ????????1-????   ????-????
*/
int SDTAPI_API STDCALL Routon_SDCard_Write(char* filename, unsigned char* msg, unsigned int msgLen);

/*
* ????SD???????????????????? iDR260????????
* ??????  filename????????????????????????16??????????\0??????   
          msgLen????????????????????
          msg????????????????
          OutmsgLen?? ??????????????????
* ????????1-????   ????-????
*/
int SDTAPI_API STDCALL Routon_SDCard_Read(char* filename, unsigned int msgLen, unsigned char* msg, unsigned int* OutmsgLen);

/*
* ????LED???????? iDR260????????
* ??????  Color??0x00:??????????????0x01????????????0x02????????????0x03????????????0x04??????????   
* ????????1-????   ????-????
*/
int SDTAPI_API STDCALL Routon_PowerLED_Color(unsigned int Color);

/* 
Routon_SerialTypeACMD - ????????A?????????????????????????? 
?????? 
ACmd: 1???????? 
in_data:??????????????????????????
in_len:??????????????????????????????????1????????255 
out_data: ????????????????????????
out_len:??????????????

????????1????????0???? 
*/
int SDTAPI_API STDCALL	Routon_SerialTypeACMD(int ACmd,unsigned char* in_data, int in_len, unsigned char* out_data, int* out_len);

int SDTAPI_API STDCALL Routon_SetComtimeout(int timeout);

int SDTAPI_API STDCALL Routon_bmpToJpgBase64(char *bmpPath, char *jpgBase64);

int SDTAPI_API STDCALL Routon_2UsbDev_GetParam(int inCode, unsigned char *outParam, int *outParamLan);
int SDTAPI_API STDCALL Routon_2UsbDev_SetParam(int inCode, unsigned char *inParam, int inParamLan);

void SDTAPI_API STDCALL Routon_SM3(unsigned char *data, int datalen,unsigned char *digest);
//mode: 0-???? 1-????
void SDTAPI_API STDCALL Routon_SM4_ECB(int mode, unsigned char *key, unsigned char *input, int length, unsigned char *output);
//mode: 0-???? 1-????
void SDTAPI_API STDCALL Routon_SM4_CBC(int mode, unsigned char *key, unsigned char *iv, unsigned char *input, int length, unsigned char *output);

int SDTAPI_API STDCALL Routon_GetEncChipID(unsigned char *id);
int SDTAPI_API STDCALL Routon_GetChipRandom(unsigned char *random, int randomLen);
//mode: 0x00 - ECB???? 0x01 - ECB???? 0x02 - CBC???? 0x03 - CBC????
int SDTAPI_API STDCALL Routon_GetChipSM4(int mode, unsigned char *key, unsigned char *iv, unsigned char *input, int dataLen, unsigned char *output, int *time);
//mode: 0x00 - Start 0x01 - Update 0x02 - Final 0x03 - compute
int SDTAPI_API STDCALL Routon_GetChipSM3(int mode, unsigned char *input, int dataLen, unsigned char *output);
int SDTAPI_API STDCALL Routon_EncChipInit(unsigned char *SecID);
int SDTAPI_API STDCALL Routon_UpateEncChipKey(int KeyType, unsigned char *SecID, unsigned char *oldKey, unsigned char *newKey);
int SDTAPI_API STDCALL Routon_UpateNewChipKey(unsigned char *SecID, unsigned char *newKey, unsigned char *keyVerify);
int SDTAPI_API STDCALL Routon_GetEncChipKey(int KeyType, unsigned char *SecID, unsigned char *OutKey);
int SDTAPI_API STDCALL Routon_UpgradeEncChip();
int SDTAPI_API STDCALL Routon_EncChipReadBaseMsg(unsigned char *EnSM3Data, unsigned char *BaseInfos, unsigned int *BaseInfosLen, unsigned char *SamID);

int SDTAPI_API STDCALL Routon_ChipReadBaseMsgDist(unsigned char *BaseInfos, int BaseInfosLen, char * Name, char * Gender, char * Folk,
												   char *BirthDay, char * Code, char * Address,
												   char *Agency, char * ExpireStart,char* ExpireEnd,char * directory, unsigned char * pucFPMsg,unsigned int  *puiFPMsgLen);

//uint8_t VerifyAuthCode(uint8_t* pData, uint8_t uDatalen, uint8_t* pRandomNum, uint8_t* pSecID, uint8_t uSecLen, uint8_t* pAuthKey, unsigned char* outAuthCode);
//uint8_t CalculateKeyCheckCode(uint8_t* pKeyData, uint8_t* pSecID, uint8_t* pCheckCode);
SDTAPI_API int  STDCALL Routon_StartTimerOut(TimerOutCallBack fnCallback, int TimerInterval);
SDTAPI_API void STDCALL Routon_StopTimerOut();
SDTAPI_API int STDCALL FindAllUSB(int *SCount, int *HCount);
SDTAPI_API int STDCALL SelectUSB(int index);
SDTAPI_API int STDCALL CloseSDTandHIDComm(int index);
SDTAPI_API int STDCALL InitSDTandHIDComm(int index);
SDTAPI_API int STDCALL Routon_ReadAllTypeCardInfos(int port, char* pMsg, char *PhotoPath);


extern "C" int SDTAPI_API __cdecl Routon_Any_Function(const char* funcName, void* result, ...);

#ifdef __cplusplus
}
//#endif 
#endif

