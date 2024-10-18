//==============================================================================
//Parent Basic Objcects Classes
//TVTObject, TVTObjectBgCol
//TVTPointList, TVTMacroListObject, TVTMacroList, TVTMacroCommandObject, TVTCommandList
//TVTObjectReferenceList
//TVTDeviceObjectList, TVTColourMapItemList, TVTAuxAssignList
//==============================================================================
//UnitVTObject.cpp
//==============================================================================

#ifndef UnitVTObject_h
#define UnitVTObject_h
#include "UnitVTObject.h" 

#include <QDebug>
//
//
#ifndef UnitVTObjConsts_h
#define UnitVTObjConsts_h
#include "UnitVTObjConsts.h"
#endif
//
#ifndef UnitVTTopLevelObjects_h
#define UnitVTTopLevelObjects_h
#include "UnitVTTopLevelObjects.h"
#endif
//
#ifndef UnitVTKeyObjects_h
#define UnitVTKeyObjects_h
#include "UnitVTKeyObjects.h"
#endif
//
#ifndef UnitVTOutputFieldObjects_h
#define UnitVTOutputFieldObjects_h
#include "UnitVTOutputFieldObjects.h"
#endif
//
#ifndef UnitVTInputFieldObjects_h
#define UnitVTInputFieldObjects_h
#include "UnitVTInputFieldObjects.h"
#endif
//
#ifndef UnitVTVariableObjects_h
#define UnitVTVariableObjects_h
#include "UnitVTVariableObjects.h"
#endif
//
#ifndef UnitVTAttributeObjects_h
#define UnitVTAttributeObjects_h
#include "UnitVTAttributeObjects.h"
#endif
//
#ifndef UnitVTOutputShapeObjects_h
#define UnitVTOutputShapeObjects_h
#include "UnitVTOutputShapeObjects.h"
#endif
//
#ifndef UnitVTOutputGraphicObjects_h
#define UnitVTOutputGraphicObjects_h
#include "UnitVTOutputGraphicObjects.h"
#endif
//
#ifndef UnitVTAttributeObjects_h
#define UnitVTAttributeObjects_h
#include "UnitVTAttributeObjects.h"
#endif
//
#ifndef UnitVTPointerObject_h
#define UnitVTPointerObject_h
#include "UnitVTPointerObject.h"
#endif
//
#ifndef UnitVTMacroObject_h
#define UnitVTMacroObject_h
#include "UnitVTMacroObject.h"
#endif
//
#ifndef UnitVTPictureGraphicObject_h
#define UnitVTPictureGraphicObject_h
#include "UnitVTPictureGraphicObject.h"
#endif
//
#ifndef UnitVTAuxiliaryObjects_h
#define UnitVTAuxiliaryObjects_h
#include "UnitVTAuxiliaryObjects.h"
#endif
//
#ifndef UnitVTGraphicContextObject_h
#define UnitVTGraphicContextObject_h
#include "UnitVTGraphicContextObject.h"
#endif
//
#ifndef UnitVTExternalObject_h
#define UnitVTExternalObject_h
#include "UnitVTExternalObject.h"
#endif
//
#ifndef UnitVTActivationMsg_h
#define UnitVTActivationMsg_h
#include "UnitVTActivationMsg.h"
#endif
//
//
// JPEG decoder library
//
#endif //UnitVTObjConsts_h



//==============================================================================
//Files
QString getInsertLineValue(TVT_Net *pVT_Net,QString str){
    QString lStr=pVT_Net->inputLineString,ss="";
    int16_t k=-1;
    //setSerialPrint(pVT_Net,lStr);
    k=lStr.indexOf("=");lStr=lStr.mid(0,k);
    //qWarning() << lStr;
    pVT_Net->inputLineString.remove(0,k+1);
    //qWarning() << pVT_Net->inputLineString;
    //
    k=str.indexOf(lStr);
    k=str.indexOf("=",k);
    //qWarning() << k;
    ss=str.mid(0,k+1);
    //qWarning() << delm0;
    //qWarning() << ss;
    //
    k=str.indexOf("\"",k);
    //qWarning() << delm0;
    //qWarning() << k;
    str.remove(0,k);
    //qWarning() << delm0;
    //qWarning() << str;
    //
    str=ss + pVT_Net->inputLineString + str;
    return str;
};//getInsertLineValue


//==============================================================================
uint8_t getVTInpFontType(TVT_Net *pVT_Net){
    uint8_t fntType=0,nn=5;
    int16_t objIdx=-1;
    //get Font type of input
    if (pVT_Net->VTInpFont<0xFFFF){
        objIdx=getVTObjID(pVT_Net,pVT_Net->VTInpFont);
        if (objIdx>=0){
            //getStreamStrInfo(pVT_Net);
            fntType=pVT_Net->streamStr.readBytesVal(1,nn);
        }//objIdx>=0
    }//<0xFFFF
    return fntType;
};//getVTInpFontType  



//==============================================================================
//get UniCode Text
void setUniCodeTextDirect(QString str, TVT_Net *pVT_Net)
{
    uint16_t un=0, index=0,  w=pVT_Net->w,len=str.length(),k = 0,wx=0;
    uint8_t tw=0, th=1,i=0,fntType=pVT_Net->fntType;
    uint8_t fntW = pVT_Net->fontSet[pVT_Net->fntNr][4], fntH=pVT_Net->fontSet[pVT_Net->fntNr][5];
    int16_t x=pVT_Net->x, y=pVT_Net->y, xx = x, yy = y;
    bool smFont=true,oCode=false,TEST=false;
    fntW+=8;
    oCode=pVT_Net->uniCode;pVT_Net->uniCode=true;
    //
    if (!Set_smFont(pVT_Net)) smFont=false;
    //check uniCode
    if (pVT_Net->uniCode) {
        fntType=0;len=len/2;
    }
    //
    for (k = 0; k < len; k++) {
        un=getUniCodeFontIndex(str,k,pVT_Net);
        pVT_Net->tft.getUnicodeIndex(un, &index);
        //
        tw = 0;
        if ((smFont) && (index>=0)) {
            if (fntW > pVT_Net->tft.gWidth[index]) tw = (fntW - pVT_Net->tft.gWidth[index]) / 2;
            if (tw > pVT_Net->tft.gdX[index]) tw = tw - pVT_Net->tft.gdX[index];
        }
        //
        xx = x + k * fntW + tw; yy = y + i * fntH + th;
        //
        //TEST
        if (TEST){
            //xx=x+k*fntW; yy=y + i*fntH;
            qWarning() << index;
            qWarning() << xx;
            qWarning() << yy;
            qWarning() << delm0;
        }//TEST
        //
        Set_setCursor(pVT_Net,xx, yy);
        if (smFont) {
            Set_drawGlyph(pVT_Net,un);
        }else{
            Set_drawString(pVT_Net,str,xx+2,yy+2);
            return;
        }
        wx+=fntW;
    } //for k
    //
    pVT_Net->uniCode=oCode;
    //
};//setUniCodeTextDirect


//==============================================================================
void reset_FontImageMode(TVT_Net *pVT_Net) {
    pVT_Net->fntName=pVT_Net->fntNamePool[pVT_Net->listNr];
    if (pVT_Net->PSRam) pVT_Net->ImgMode=2;
    setSerialPrint(pVT_Net,"0.last_fntName=",true);
    setSerialPrint(pVT_Net,pVT_Net->fntName);
    Set_loadFont(pVT_Net,pVT_Net->fntName);
};//reset_FontImageMode



//==============================================================================
//Date and Time
//VTDateTime variable
//==============================================================================
void printDateTimeStructure(QString info,TVT_Net *pVT_Net) {
    QString str="";
    if (!pVT_Net->RTC_active) info=info + "[not active]";
    str=+"\n" + info + " Now is : %d-%02d-%02d %02d:%02d:%02d\n";
    //
    Serial.printf(str.constData(),
                  (pVT_Net->tmstruct.tm_year)+1900,(pVT_Net->tmstruct.tm_mon)+1,(pVT_Net->tmstruct.tm_mday),
                  (pVT_Net->tmstruct.tm_hour)     ,(pVT_Net->tmstruct.tm_min)  ,(pVT_Net->tmstruct.tm_sec));

    qWarning() << delm0;

};//printDateTimeStructure

//==============================================================================
void getDateTimeStructure(TVT_Net *pVT_Net) {
    pVT_Net->tmstruct.tm_year = pVT_Net->RTCDate.Year-1900;
    pVT_Net->tmstruct.tm_mon  = pVT_Net->RTCDate.Month-1;    // Month, 0 - jan
    pVT_Net->tmstruct.tm_mday = pVT_Net->RTCDate.Date;       // Day of the month
    pVT_Net->tmstruct.tm_hour = pVT_Net->RTCtime.Hours;
    pVT_Net->tmstruct.tm_min  = pVT_Net->RTCtime.Minutes;
    pVT_Net->tmstruct.tm_sec  = pVT_Net->RTCtime.Seconds;
    //pVT_Net->tmstruct.tm_wday =Days since Sunday [0-6].
    pVT_Net->tmstruct.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
};//getDateTimeStructure


//==============================================================================
void setDateTimeStructure(TVT_Net *pVT_Net) {
    pVT_Net->RTCDate.Year   =pVT_Net->tmstruct.tm_year+1900;
    pVT_Net->RTCDate.Month  =pVT_Net->tmstruct.tm_mon+1; // Month, 0 - jan
    pVT_Net->RTCDate.Date   =pVT_Net->tmstruct.tm_mday;  // Day of the month
    pVT_Net->RTCtime.Hours  =pVT_Net->tmstruct.tm_hour;
    pVT_Net->RTCtime.Minutes=pVT_Net->tmstruct.tm_min;
    pVT_Net->RTCtime.Seconds=pVT_Net->tmstruct.tm_sec;
};//setDateTimeStructure



//==============================================================================
time_t VTDateTimeMinute(TVT_Net *pVT_Net,bool info,int8_t mOffset) {
    //struct tm *t;
    time_t t_of_day;
    getDateTimeStructure(pVT_Net);
    t_of_day = mktime(&pVT_Net->tmstruct);
    //
    //get Offset
    if (mOffset!=0) {
        t_of_day-=60*mOffset;
        pVT_Net->tmstruct=*localtime(&t_of_day);
        setDateTimeStructure(pVT_Net);
        getDateTimeStructure(pVT_Net);
        //set new time
        Set_CheckDateTime(pVT_Net);
        //
        sprintf(pVT_Net->timeStrbuff, "%02d.%02d.%d %02d:%02d:%02d",
                pVT_Net->RTCDate.Date,pVT_Net->RTCDate.Month, pVT_Net->RTCDate.Year,
                pVT_Net->RTCtime.Hours, pVT_Net->RTCtime.Minutes,pVT_Net->RTCtime.Seconds);
    }
    //
    if ((info) && (pVT_Net->VTPageSelect==1)) {
        qWarning() << t_of_day;
    }
    return t_of_day;
};//VTDateTime



//==============================================================================
time_t VTDateTime(TVT_Net *pVT_Net,bool info,int8_t hOffset) {
    //struct tm *t;
    time_t t_of_day;
    getDateTimeStructure(pVT_Net);
    t_of_day = mktime(&pVT_Net->tmstruct);
    //
    //get Offset
    if (hOffset!=0) {
        t_of_day-=3600*hOffset;
        pVT_Net->tmstruct=*localtime(&t_of_day);
        setDateTimeStructure(pVT_Net);
        getDateTimeStructure(pVT_Net);
        sprintf(pVT_Net->timeStrbuff, "%02d.%02d.%d %02d:%02d:%02d",
                pVT_Net->RTCDate.Date,pVT_Net->RTCDate.Month, pVT_Net->RTCDate.Year,
                pVT_Net->RTCtime.Hours, pVT_Net->RTCtime.Minutes,pVT_Net->RTCtime.Seconds);
    }
    //
    if ((info) && (pVT_Net->VTPageSelect==1)) {
        qWarning() << t_of_day;
    }
    return t_of_day;
};//VTDateTime

//==============================================================================
time_t  VTFlushTime(TVT_Net *pVT_Net,bool info) {
    time_t t_of_day;
    if (pVT_Net->RTC_active) {
        M5.Rtc.GetTime(&pVT_Net->RTCtime);  // Gets the time in the real-time clock.
        M5.Rtc.GetDate(&pVT_Net->RTCDate);
    } else {
        getDateTimeStructure(pVT_Net);
        t_of_day = mktime(&pVT_Net->tmstruct);
        t_of_day+=1;
        pVT_Net->tmstruct=*localtime(&t_of_day);
        setDateTimeStructure(pVT_Net);
    }
    //
    sprintf(pVT_Net->timeStrbuff, "%02d.%02d.%d %02d:%02d:%02d",
            pVT_Net->RTCDate.Date,pVT_Net->RTCDate.Month, pVT_Net->RTCDate.Year,
            pVT_Net->RTCtime.Hours, pVT_Net->RTCtime.Minutes,pVT_Net->RTCtime.Seconds);
    getDateTimeStructure(pVT_Net);
    //
    return VTDateTime(pVT_Net,info);
};//VTFlushTime



//==============================================================================
time_t VTDateTimeInit(TVT_Net *pVT_Net,bool compile,bool setWiFi)
{
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
    char s_month[5];
    int day,month,year,hour,minute,second;
    time_t t_of_day0,t_of_day1;
    //

    pVT_Net->TargetTime=QDateTime::currentDateTime().toMSecsSinceEpoch();
    //
    t_of_day0=VTDateTime(pVT_Net);
    qWarning() << delm1;
    //
    if ((compile) && (!setWiFi)) {
        qWarning() << "Compiled: " __DATE__ ", " __TIME__ ", " __VERSION__;
        sscanf(__DATE__,"%s %d %d", s_month, &day, &year);
         month = (strstr(month_names, s_month)-month_names)/3+1;
        sscanf(__TIME__,"%02d:%02d:%02d", &hour, &minute, &second);
        //
        sprintf(pVT_Net->timeStrbuff, "%02d.%02d.%d",day,month,year);
        qWarning() << "COMPILED:\t";
        qWarning() << pVT_Net->timeStrbuff << " ";
        sprintf(pVT_Net->timeStrbuff, "%02d:%02d:%02d",hour,minute,second);
        qWarning() << pVT_Net->timeStrbuff;
        qWarning() << delm0;
        //
        pVT_Net->RTCDate.Year=year;
        pVT_Net->RTCDate.Month=month;      // Month, 0 - jan
        pVT_Net->RTCDate.Date=day;         // Day of the month
        pVT_Net->RTCtime.Hours=hour;
        pVT_Net->RTCtime.Minutes=minute;
        pVT_Net->RTCtime.Seconds=second;
        t_of_day1=VTDateTime(pVT_Net);
        qWarning() << "compile:"  << t_of_day1;
        qWarning() << "actual:" << t_of_day0;
        //set compiled DateTime to actual DateTime
        if (t_of_day1>t_of_day0) {
            qWarning() << delm0;
            qWarning() << "set compiled DateTime to actual DateTime";
            Set_CheckDateTime(pVT_Net);
        }
    }
    //
    if (setWiFi) {
        setDateTimeStructure(pVT_Net);
        Set_CheckDateTime(pVT_Net);
    }
    //
    VTFlushTime(pVT_Net);
    qWarning() << "actual DateTime:\t" <<  pVT_Net->timeStrbuff << delm1;
    return t_of_day0;
};//VTDateTimeInit



//==============================================================================
void setup_VTDateTime(TVT_Net *pVT_Net) {
    QString fntName="arial3-0";
    //DateTime screen
    if (pVT_Net->VTPageSelect==1) {
        pVT_Net->fntNamePool[pVT_Net->listNr]=pVT_Net->fntName;
        //
        resetKeyButtonInputList(pVT_Net);
        pVT_Net->ImgMode=0;
        if (Set_fontLoaded) Set_unloadFont(pVT_Net);
        //
        Set_fillScreen(pVT_Net,TFT_BLACK);
        Set_resetViewport(pVT_Net);
        Set_setTextColorBg(pVT_Net,TFT_YELLOW, TFT_BLACK);
        //
        Set_loadFont(pVT_Net,fntName);
    }else{
        //normal screen
        reset_FontImageMode(pVT_Net);
    }//pVT_Net->VTPageSelect==1
    //
};//setup_VTDateTime


//==============================================================================
//==============================================================================
void VT_CAN_Init(TVT_Net *pVT_Net){
    QString infoStr="";
    pVT_Net->fntNr=4; pVT_Net->fntSr=0;
};//,VT_CAN_Init


//==============================================================================
void VT_CAN_ResetStatusInfo(TVT_Net *pVT_Net,uint8_t yMax) {
    pVT_Net->tft.fillRect(0,0,320,yMax,TFT_BLACK); //TFT_BLUE);
};//VT_CAN_ResetStatusInfo


//==============================================================================
void WiFi_resetNetworks(TVT_Net *pVT_Net, QString str) {
    pVT_Net->SSID_List.clear();
    pVT_Net->SSID_ListIdx=-1;
    pVT_Net->SSID_ListIdxMax=-1;
    pVT_Net->VTTraceLine=0;
    if (str.length()>0){
        VT_CAN_ResetStatusInfo(pVT_Net,200);
        pVT_Net->tft.drawString(str,0,0);
    }
};//WiFi_resetNetworks



//==============================================================================
bool VT_CAN_TraceMsg(TVT_Net *pVT_Net,CANMsg *pMsg){
    QString str="";
    float  tStamp=0.000;
    uint8_t lh=16;
    bool vtStatus=false,ecuStatus=false,getTrace=true;
    if ((pVT_Net->VTPageSelect==3) && (pVT_Net->VTTraceActive)){
        //
        vtStatus= ((pMsg->ID & 0x00FF0000)==VTtoECU_PGN);
        ecuStatus=((pMsg->ID & 0x00FF0000)==ECUtoVT_PGN);
        //
        if ((vtStatus)  && (pMsg->DATA[0]==0xFE)) getTrace=(pVT_Net->VTTraceFilter & 0x01);
        if ((ecuStatus) && (pMsg->DATA[0]==0xFF)) getTrace=(pVT_Net->VTTraceFilter & 0x02);
        //
        if ((pVT_Net->CAN_active) && (getTrace)){
            tStamp=1.000*(pMsg->TimeStamp-pVT_Net->VTTimeStamp)/1000;
            if (pVT_Net->VTStampActive){
                str+=QString::number(tStamp, 'f', 3); str+=" ";
            }
            //
            if (pMsg->MSG_TX==0) str+="R ";else str+="T ";
            //
            if (lh*pVT_Net->VTTraceLine>(200-lh)) pVT_Net->VTTraceLine=0;
            if (pVT_Net->VTTraceLine==0) {
                VT_CAN_ResetStatusInfo(pVT_Net,200);
            }
            //
            str+=getMsgFrameStr(pMsg);
            //TEST
            //qWarning() << str;
            pVT_Net->tft.drawString(str,0,lh*pVT_Net->VTTraceLine);
            pVT_Net->VTTraceLine++;
        }//CAN_active
    }//VTTraceActive
    //
    return getTrace;
};//VT_CAN_TraceMsg


//==============================================================================
void VT_CAN_MsgFrameStr(TVT_Net *pVT_Net,CANMsg *pMsg) {
    String rxtx[2]={"RX1","TX1"};
    //
    pMsg->TimeStamp=QDateTime::currentDateTime().toMSecsSinceEpoch();
    if ((pVT_Net->VTPageSelect==3) && (pVT_Net->VTTraceActive)){
        VT_CAN_TraceMsg(pVT_Net,pMsg);
    }
    //
    if (pVT_Net->LOG_active) {
        //
        if((pMsg->ID & 0x80000000) == 0x80000000){     // Determine if ID is standard (11 bits) or extended (29 bits)
            sprintf(pMsg->msgString, "%.3f %s %.8lX  %1d  ", pMsg->TimeStamp/1000.000,rxtx[pMsg->MSG_TX],(pMsg->ID & 0x1FFFFFFF),pMsg->LEN);
        }else {
            sprintf(pMsg->msgString, "%.3f %s %.3lX  %1d  ", pMsg->TimeStamp/1000.000,rxtx[pMsg->MSG_TX],(pMsg->ID & 0x1FFFFFFF), pMsg->LEN);
        }
        //
        if (pVT_Net->LOG_active) {
            setSerialPrint(pVT_Net,pMsg->msgString,true);
            pVT_Net->tft.printf(pMsg->msgString);
        }
        //
        if((pMsg->ID & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
            if (pVT_Net->LOG_active) {
                sprintf(pMsg->msgString, " REMOTE REQUEST FRAME");
                setSerialPrint(pVT_Net,pMsg->msgString,true);
            }
        } else {
            for(byte i = 0; i<pMsg->LEN; i++){
                if (pVT_Net->LOG_active) {
                    sprintf(pMsg->msgString, " %.2X", pMsg->DATA[i]);
                    setSerialPrint(pVT_Net,pMsg->msgString,true);
                    pVT_Net->tft.printf(pMsg->msgString);
                }
            }
        }
        //
        if (pVT_Net->LOG_active) {
            pVT_Net->tft.printf("\n");
            setSerialPrint(pVT_Net,"");
        }
    }//pVT_Net->LOG_active
};//VT_CAN_MsgFrameStr


//==============================================================================
/*
class CANMsg {
public:
   long unsigned int ID=0;               // CAN ID
   uint8_t   LEN=8;                      // Data Length Code
   uint8_t   DATA[256]={};               // Data array
   uint8_t   MSGTYPE=0;                  // Remote request flag
   uint8_t   MSG_TX=0;                   // TX transmit flag
   uint32_t  TimeStamp=QDateTime::currentDateTime().toMSecsSinceEpoch();         // CAN Timestamp
   char      msgString[128];
*/
void VT_CAN_MsgSend(TVT_Net *pVT_Net,CANMsg *pMsg){
    bool valid=false;
    uint8_t dst=0xFF,ctrlByte=0xFF;
    byte sndStat;
    //TECU MonitorMode
    dst=(pMsg->ID>>8) & 0xFF;
    if (pMsg->LEN>0) ctrlByte=pMsg->DATA[0];
    //
    if ((pVT_Net->listNr==(listMax-1)) && ((pMsg->ID & 0x00FF0000)==VTtoECU_PGN) && (dst==0xFF)) {
        //check not send CAN message
        //TEST
        //qWarning() << "pVT_Net->listNr";
        //qWarning() << getMsgFrameStr(pMsg);
        //qWarning() << ctrlByte;
        //not VTActivation messages
        //select input, key activation
        if (ctrlByte<=0x0A) return;
    }
    //
#ifdef COM_CAN_MODE
    CAN_frame_t tx_frame;
    tx_frame.FIR.B.RTR= CAN_no_RTR;
    tx_frame.FIR.B.FF = CAN_frame_ext;
    tx_frame.MsgID=pMsg->ID;
    tx_frame.FIR.B.DLC = pMsg->LEN;
    /*
    TEST frame
    tx_frame.FIR.B.RTR= CAN_no_RTR;
    tx_frame.FIR.B.FF = CAN_frame_ext;
    tx_frame.MsgID = 0x1CE6FF26;
    tx_frame.FIR.B.DLC = 8;
    //
    tx_frame.data.u8[0] = 0xFE;
    tx_frame.data.u8[1] = 0x26;
    tx_frame.data.u8[2] = 0xFF;
    tx_frame.data.u8[3] = 0xFF;
    tx_frame.data.u8[4] = 0xFF;
    tx_frame.data.u8[5] = 0xFF;
    tx_frame.data.u8[6] = 0x00;
    tx_frame.data.u8[7] = 0xFF;
    */
    for (int i=0;i<pMsg->LEN;i++){
        tx_frame.data.u8[i]=pMsg->DATA[i];
    }
    //send CAN message
    valid=(ESP32Can.CANWriteFrame(&tx_frame)==0);
#else
    sndStat=VTCAN0.sendMsgBuf(pMsg->ID, pMsg->MSGTYPE, pMsg->LEN, pMsg->DATA);
    valid=(sndStat == CAN_OK);
#endif //COM_CAN_MODE
    //
    if (valid) {
        //pVT_Net->LOG_active=true;
        VT_CAN_MsgFrameStr(pVT_Net,pMsg); pMsg->TimeStamp=QDateTime::currentDateTime().toMSecsSinceEpoch();
    }else {
        if (pVT_Net->LOG_active) {
            setSerialPrint(pVT_Net,"Error Sending Message...");
        }
    }
};//VT_CAN_MsgSend



//==============================================================================
bool VT_CAN_MsgReceive(TVT_Net *pVT_Net,CANMsg *pMsg){
    bool abortAddr=false,valid=false;
    pMsg->TimeStamp=QDateTime::currentDateTime().toMSecsSinceEpoch();
    //Check Status ECU-addresses
    for (int i=0;i<2;i++){
        if ((pVT_Net->VT_DST[i]<0xFE) && (pMsg->TimeStamp-pVT_Net->VT_DST_TIME[i]>6000)) {
            pVT_Net->VT_DST[i]=0xFF;
            pVT_Net->VT_DST_WS[i]="FFFFFFFFFFFFFFFF";
            abortAddr=true;
        }
    }//for i
    //
    if (abortAddr) {
        for (int i=0;i<2;i++){
            setSerialPrint(pVT_Net,getStringHEX(pVT_Net->VT_DST[i],2),true);
            setSerialPrint(pVT_Net,"\t" + pVT_Net->VT_DST_WS[i]);
        }
        setSerialPrint(pVT_Net,delm1);
    }//abortAddr
    //
    //Read Messages
    if (pVT_Net->CAN_active){
        //
#ifdef COM_CAN_MODE
        CAN_frame_t rx_frame;
        if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) ==pdTRUE) {
            valid=((rx_frame.FIR.B.FF==CAN_frame_ext) && (rx_frame.FIR.B.RTR==CAN_no_RTR));
            if (valid) {
                pMsg->MSG_TX=0; pMsg->MSGTYPE=0;
                pMsg->ID=rx_frame.MsgID;
                pMsg->LEN=rx_frame.FIR.B.DLC;
                //
                for (int i=0;i<pMsg->LEN;i++){
                    pMsg->DATA[i]=rx_frame.data.u8[i];
                }//for i
                //
                VT_CAN_MsgFrameStr(pVT_Net,pMsg);
                //setSerialPrint(pVT_Net,getMsgFrameStr(pMsg));
            }//valid
        }//xQueueReceive
        //
#else
        if(!digitalRead(CAN0_INT)) {                              // If CAN0_INT pin is low, read receive buffer
            VTCAN0.readMsgBuf(&pMsg->ID, &pMsg->LEN, pMsg->DATA);    // Read data: len = data length, buf = data byte(s)
            pMsg->MSG_TX=0;
            VT_CAN_MsgFrameStr(pVT_Net,pMsg);
            //setSerialPrint(pVT_Net,getMsgFrameStr(pMsg));
            valid=true;
            //
            //CANMsgPGN(pMsg);
        }
#endif //COM_CAN_MODE
    }//pVT_Net->CAN_active
    return valid;
};//VT_CAN_MsgReceive



//==============================================================================
//SET PROTOTYPES
//=============================================================================
void setSerialPrint(TVT_Net *pVT_Net, QString str, bool pln){
    if (pVT_Net->serialOut) {
        str.replace("\n","\n\r");
        if (pln)
            qWarning() << str;
        else
            qWarning( << str;
    }
}//setSerialPrint  


//==============================================================================
//get heap
uint32_t getHeapStatus(TVT_Net *pVT_Net,uint8_t hNr) {
    uint32_t i=ESP.getFreeHeap();
    uint32_t heapTime=QDateTime::currentDateTime().toMSecsSinceEpoch(),dTime=heapTime-pVT_Net->heapTime;
#ifdef ESP32
    pVT_Net->heapTime=heapTime;
    if (hNr<255) {
        setSerialPrint(pVT_Net,delm0 + "\n" + QString(hNr),true);
        setSerialPrint(pVT_Net,".ESP.getFreeHeap_Res/Max/Stack=",true);
        setSerialPrint(pVT_Net,String(i) + "/" + QString(ESP.getHeapSize()),true);
        void* SpActual = NULL;
        setSerialPrint(pVT_Net,"/" + QString((uint32_t)&SpActual - (uint32_t) pVT_Net->StackPtrEnd),true);
        setSerialPrint(pVT_Net,"/Time[ms]=" + QString(dTime),true);
        /*
     setSerialPrint(pVT_Net,"/Objects=" + QString(getVTObjectListSize(pVT_Net)),true);
     setSerialPrint(pVT_Net,"/List=" + QString(pVT_Net->listNr),true);
     setSerialPrint(pVT_Net,"/ImageMode=" + QString(pVT_Net->ImgMode) + "/InfoMode=" + QString(pVT_Net->VT_InfoMode),true);
     */
        setSerialPrint(pVT_Net,"\n" + delm0 + "\n",true);
    }
#endif
    return i;
} //getHeapStatus   


//==============================================================================
bool getMsgFromCmd(TVT_Net *pVT_Net, CANMsg *pMsg, QString str)
{
    // FIXME I smell a rat here!
    QByteArray byteArray;
    QString ss="";
    int i = 0;
    str = str.trimmed();

    pMsg->MSG_TX=(str.indexOf("=#")>0);
    str.remove(0,str.indexOf(" "));
    str = str.trimmed();
    ss=str.mid(0,str.indexOf(" "));
    ss = ss.trimmed();
    str.remove(0,str.indexOf(" "));
    str = str.trimmed();
    pMsg->LEN=8;

    byteArray = hexCharacterStringToBytes(ss);
    pMsg->ID=0; pMsg->LEN=8;
    for (i=0;i<4;i++)
        pMsg->ID+=byteArray[i]<<8*(3-i);

    ss=str.mid(0,str.indexOf(" "));
    ss = ss.trimmed();

    str.remove(0,str.indexOf(" "));
    str = str.trimmed();

    pMsg->LEN=ss.toInt();
    str.replace(" ","");
    byteArray = hexCharacterStringToBytes(str);
    for (i=0;i<pMsg->LEN;i++)
        pMsg->DATA[i]=byteArray[i];
    //
    return (pMsg->ID>0);
};//getMsgFromCmd



//==============================================================================
void paintSelectionFrame(TVT_Net *pVT_Net){
    uint8_t dw=4,nn=3;
    uint8_t cl=cl_magenta;//magenta=13
    int16_t  x=-dw,y=-dw;
    uint16_t w=0, h=0, objID=0xFFFF;
    if (pVT_Net->TFT_KeySelectObjID<0xFFFF)    {
        if (getVTDrawID(pVT_Net,pVT_Net->TFT_KeySelectObjID)<0) pVT_Net->TFT_KeySelectObjID=0xFFFF;
    }
    if (pVT_Net->TFT_ButtonSelectObjID<0xFFFF){
        if (getVTDrawID(pVT_Net,pVT_Net->TFT_ButtonSelectObjID)<0) pVT_Net->TFT_ButtonSelectObjID=0xFFFF;
    }
    if (pVT_Net->TFT_InputSelectObjID<0xFFFF) {
        if (getVTDrawID(pVT_Net,pVT_Net->TFT_InputSelectObjID)<0) pVT_Net->TFT_InputSelectObjID=0xFFFF;
    }
    //
    if (objID==0xFFFF) objID=pVT_Net->TFT_KeySelectObjID;
    if (objID==0xFFFF) objID=pVT_Net->TFT_ButtonSelectObjID;
    if (objID==0xFFFF) objID=pVT_Net->TFT_InputSelectObjID;
    //
    if (objID<0xFFFF){
        setSerialPrint(pVT_Net,"SelectObjID=" + QString(objID));
        x=pVT_Net->streamDraw.readBytesVal(2,nn); nn+=2;
        y=pVT_Net->streamDraw.readBytesVal(2,nn); nn+=2;
        w=pVT_Net->streamDraw.readBytesVal(2,nn); nn+=2;
        h=pVT_Net->streamDraw.readBytesVal(2,nn); nn+=2;
        //
        Set_fillRect(pVT_Net,x, y, w, dw, cl);
        Set_fillRect(pVT_Net,x+w-dw, y, dw, h, cl);
        Set_fillRect(pVT_Net,x, y+h-dw, w, dw, cl);
        Set_fillRect(pVT_Net,x, y, dw, h, cl);
    }
};//paintSelectionFrame     



//==============================================================================
/*
TX1 1CE60A26  8  00 01 89 13 E8 03 01 00
_VTSoftKeyActivation (00)
ActiveMask=1000  State=[1] Pressed
KeyObjID=5001  KeyNumber=1

TX1 1CE60A26  8  00 00 89 13 E8 03 01 00
_VTSoftKeyActivation (00)
ActiveMask=1000  State=[0] Released
KeyObjID=5001  KeyNumber=1
  const uint32_t VTtoECU_PGN  =0x00E60000;
  const uint8_t  ECU_VT_PRIO  =0x1C;  //Prio=7
*/
bool setKeyDownUpSelect(TVT_Net *pVT_Net, CANMsg *pMsg, QString str){
    bool valid=(getVTObjectListSize(pVT_Net)>0),TEST=false;
    uint16_t objID=0xFFFF,kk=pVT_Net->listNr;
    int16_t  refIdx=-1,keyNr=0;
    uint32_t inpVal=0;
    uint8_t  funct=0x00;
    if (valid) {
        valid=false;
        //qWarning() << str;
        //qWarning() << pVT_Net->TFT_KeySelect;
        //set ACKN message
        if (str=="A") {
            refIdx=0;
        } else {
            //Key
            if (pMsg->DATA[0]==0x00) {
                uint8_t kSel=pVT_Net->TFT_KeySelect % pVT_Net->TFT_KeyNr;
                refIdx=getVTDrawSelect(pVT_Net,kSel,5);
                if (refIdx>=0) {
                    keyNr=pVT_Net->TFT_KeySelect+1;
                    setVTDrawListClearSelect(pVT_Net,pVT_Net->VTObjID);
                }
            }
            //Button
            if (pMsg->DATA[0]==0x01) {
                refIdx=getVTDrawSelect(pVT_Net,pVT_Net->TFT_ButtonSelect,6);
                if (refIdx>=0){
                    keyNr=pVT_Net->TFT_ButtonSelect+1;
                    setVTDrawListClearSelect(pVT_Net,pVT_Net->VTObjID);
                }
            }
            //
            //Inputs
            if (pMsg->DATA[0]==0x03) {
                refIdx=getVTDrawSelect(pVT_Net,pVT_Net->TFT_InputSelect,7);
                if (refIdx>=0){
                    keyNr=pVT_Net->TFT_InputSelect+1;
                    setVTDrawListClearSelect(pVT_Net,pVT_Net->VTObjID);
                }
            }
            //get last Input object
            if (pMsg->DATA[0]==0xFF) {
                if (pVT_Net->TFT_KeySelectObjID<0xFFFF)    objID=pVT_Net->TFT_KeySelectObjID;
                if (pVT_Net->TFT_ButtonSelectObjID<0xFFFF) objID=pVT_Net->TFT_ButtonSelectObjID;
                if (pVT_Net->TFT_InputSelectObjID<0xFFFF)  objID=pVT_Net->TFT_InputSelectObjID;
                refIdx=getVTDrawID(pVT_Net,objID);
                //qWarning() << "refIdx=" + QString(refIdx);
            }
            objID=pVT_Net->VTObjID;
        } //str=="A"
        //
        if ((refIdx>=0) && (pVT_Net->VT_ActiveMask<0xFFFF)) {
            pMsg->ID=VTtoECU_PGN + (ECU_VT_PRIO<<24) + (pVT_Net->VT_DST[kk]<<8) + pVT_Net->VT_SRC;
            pMsg->MSG_TX=1;  pMsg->MSGTYPE=1; pMsg->LEN=8;
            //TEST
            if (TEST) {
                setSerialPrint(pVT_Net,"ActiveMask=" + QString(pVT_Net->VT_ActiveMask));
                setSerialPrint(pVT_Net,"ActiveSoftKeyMask=" + QString(pVT_Net->VT_ActiveSoftKeyMask));
                setSerialPrint(pVT_Net,"KeyNr=" + QString(keyNr));
                setSerialPrint(pVT_Net,"ObjID=" + QString(objID));
            }
            pVT_Net->TFT_ButtonPressed=-1;
            //
            if ((str=="P") || (str=="H") || (str=="R") || (str=="A") || (str=="S")) {
                if (pMsg->DATA[0]==0x01) {
                    funct=0x01;
                    if (str=="P") pVT_Net->TFT_ButtonPressed=1; //pressed
                    if (str=="H") pVT_Net->TFT_ButtonPressed=2; //still pressed
                    if (str=="R") pVT_Net->TFT_ButtonPressed=0; //release
                }
                //
                if (str=="P") setSerialPrint(pVT_Net,"Pressed");
                if (str=="H") setSerialPrint(pVT_Net,"StillPtressed");
                if (str=="R") setSerialPrint(pVT_Net,"Released");
                //
                if ((str=="A") || (str=="S")){
                    if (str=="A")  setSerialPrint(pVT_Net,"Pressed ACKN");
                    if (str=="S")  setSerialPrint(pVT_Net,"Released ACKN");
                    pVT_Net->VTObjID=0xFFFF;
                }
            } else {
                if ((str=="D") || (str=="E") || (keyNr>=255)) {
                    pVT_Net->TFT_KeySelect=255;
                    pVT_Net->TFT_ButtonSelect=255;
                    pVT_Net->TFT_InputSelect=255;
                    //setVTDrawListClearSelect(pVT_Net,objID);
                    if (TEST) {
                        qWarning() << delm0;
                        qWarning() << pVT_Net->TFT_KeySelectObjID;
                        qWarning() << pVT_Net->TFT_ButtonSelectObjID;
                        qWarning() << pVT_Net->TFT_InputSelectObjID;
                        qWarning() << delm0;
                    }
                }
                funct=0x03;
                if (str=="E") funct=0x04; //ESC
                //
                //VT_ChangeNumericValue
                if (str.indexOf("V")==0) {
                    setSerialPrint(pVT_Net,str);
                    str.remove(0,1);
                    if (str.length()>0) setSerialPrint(pVT_Net,str);
                    pVT_Net->VTValueStr=str;
                    pVT_Net->VTValue=str.toInt();
                    funct=0x05; //EntryOfValue//EntryOfNewValue
                    if  (pVT_Net->VTObjType==8) funct=0x08;
                }
            }
            //
            //
            if (funct==0x00) {
                pMsg->DATA[1]=((str=="P") || (str=="A"));
                if (str=="H") pMsg->DATA[1]=2; //still held
                TVT_VTSoftKeyActivation msgObj;
                return msgObj.setMsgToAttr (pMsg,pVT_Net);
            }
            if (funct==0x01) {
                pMsg->DATA[1]=((str=="P") || (str=="A"));
                if (str=="H") pMsg->DATA[1]=2; //still held
                TVT_VTButtonActivation msgObj;
                return msgObj.setMsgToAttr (pMsg,pVT_Net);
            }
            if (funct==0x02) {
                TVT_VTPointingEvent msgObj;
                return msgObj.setMsgToAttr (pMsg,pVT_Net);
            }
            if (funct==0x03) {
                TVT_VTSelectInput msgObj;
                return msgObj.setMsgToAttr (pMsg,pVT_Net);
            }
            if (funct==0x04) {
                pMsg->DATA[3]=(keyNr==255);
                TVT_VTESC msgObj;
                return msgObj.setMsgToAttr (pMsg,pVT_Net);
            }
            if (funct==0x05) {
                TVT_VTChangeNumericValue msgObj;
                return msgObj.setMsgToAttr (pMsg,pVT_Net);
            }
            if (funct==0x06) {
                TVT_VTChangeActiveMask msgObj;
                return msgObj.setMsgToAttr (pMsg,pVT_Net);
            }
            if (funct==0x07) {
                TVT_VTChangeSoftKeyMask msgObj;
                return msgObj.setMsgToAttr (pMsg,pVT_Net);
            }
            if (funct==0x08) {
                TVT_VTInputStringValue msgObj;
                return msgObj.setMsgToAttr (pMsg,pVT_Net);
            }
            valid=true;
        } //refIdx>=0
    }
    return valid;
};//setKeyDownUpSelect


//==============================================================================
bool setKeyNumberSelect(TVT_Net *pVT_Net, CANMsg *pMsg, QString str){
    bool valid=(getVTObjectListSize(pVT_Net)>0);
    uint16_t objID=0xFFFF,kk=0;
    int16_t objIdx=-1,keyNr=-1,keyMax=-1,nn=4,refIdx=-1,i=0,keyFound=0;
    pMsg->MSG_TX=false;
    //TEST
    //qWarning() << str;
    //qWarning() << pVT_Net->TFT_KeySelect;
    if ((str=="P") || (str=="H") || (str=="R") || (str=="A") || (str=="D") || (str=="E") || (str.indexOf("V")==0)) {
        //key pressed="P" or held="H" or release="R" or ACKN="A" or deselect="D" or ESC="E"
        keyNr=pVT_Net->TFT_KeySelect;
        if (pMsg->DATA[0]==0x01) keyNr=pVT_Net->TFT_ButtonSelect;
        if (pMsg->DATA[0]==0x03) keyNr=pVT_Net->TFT_InputSelect;
        valid=setKeyDownUpSelect(pVT_Net,pMsg,str);
        return valid;
    }
    //
    if ((str=="N") || (str=="B")) {
        keyNr=pVT_Net->TFT_KeySelect;
        if (pMsg->DATA[0]==0x01) keyNr=pVT_Net->TFT_ButtonSelect;
        if (pMsg->DATA[0]==0x03) keyNr=pVT_Net->TFT_InputSelect;
        if (str=="N") keyNr++; //next key
        if (str=="B") keyNr--; //before key
    } else keyNr=str.toInt();
    //
    if (keyNr<0) keyNr=0;
    //Key Select/Activation
    if ((valid) && (keyNr>=0) && (pMsg->DATA[0]==0x00)) {
        objIdx=getVTObjID(pVT_Net,pVT_Net->VT_ActiveSoftKeyMask);
        keyMax=pVT_Net->streamStr.readBytesVal(1,nn);
        if (keyNr>=keyMax) keyNr=keyMax-1;
        if (keyNr<0) keyNr=0;
        pVT_Net->TFT_KeySelect=keyNr;
        //refresh keypage
        if (pVT_Net->TFT_KeyPage!=pVT_Net->TFT_KeySelect/pVT_Net->TFT_KeyNr) {
            VTPoolDataRefreshDirect(pVT_Net);
        }
        valid=setKeyDownUpSelect(pVT_Net,pMsg,str);
        setSerialPrint(pVT_Net,"TFT_KeySelectObjID=" + QString(pVT_Net->TFT_KeySelectObjID));
        if (valid) {
            pVT_Net->VTPoolRefresh=true; pVT_Net->VTPoolClear=false;
        }
        return valid;
    }//valid Key
    //
    //Button activation
    if ((valid) && (keyNr>=0) && (pMsg->DATA[0]==0x01)) {
        refIdx=getVTDrawSelect(pVT_Net,keyNr,6);
        if (refIdx<0) keyNr=0;
        pVT_Net->TFT_ButtonSelect=keyNr;
        valid=setKeyDownUpSelect(pVT_Net,pMsg,str);
        setSerialPrint(pVT_Net,"TFT_ButtonSelectObjID=" + QString(pVT_Net->TFT_ButtonSelectObjID));
        if (valid) {
            pVT_Net->VTPoolRefresh=true; pVT_Net->VTPoolClear=false;
        }
        return valid;
    }
    //Input select activation
    if ((valid) && (keyNr>=0) && (pMsg->DATA[0]==0x03)) {
        refIdx=getVTDrawSelect(pVT_Net,keyNr,7);
        if (refIdx<0) keyNr=0;
        pVT_Net->TFT_InputSelect=keyNr;
        valid=setKeyDownUpSelect(pVT_Net,pMsg,str);
        setSerialPrint(pVT_Net,"TFT_InputSelectObjID=" + QString(pVT_Net->TFT_InputSelectObjID));
        if (valid) {
            pVT_Net->VTPoolRefresh=true; pVT_Net->VTPoolClear=false;
        }
        return valid;
    }
    //
    return valid;
};//setKeyNumberSelect



//==============================================================================
//global procedure
//==============================================================================
//ColorMap to default
void resetColorMap(TVT_Net *pVT_Net) {
    for (int i=0;i<256;i++) pVT_Net->gISO_ColourMap[i]=pVT_Net->ggISO_ColourMap[i];
};//resetColorMap

//------------------------------------------------------------------------------
uint8_t getColourMapInverse(TVT_Net *pVT_Net,uint8_t cIdx){
    //uint32_t cc0=(pVT_Net->gISO_ColourMap[cIdx] & 0xFFFFFF), cc1=~cc0;
    uint32_t cc=pVT_Net->gISO_ColourMap[cIdx]; cIdx=254;
    pVT_Net->gISO_ColourMap[cIdx]=((~cc) | (cc & 0xFF000000));
    return cIdx;
};//getColourMapInverse


//==============================================================================
uint16_t  get_TFTWidth(TVT_Net *pVT_Net){
    uint16_t ww=0;
    if (pVT_Net->ImgMode){
        ww=pVT_Net->ImgTFT.width();
    }else {
        ww=pVT_Net->tft.width();
    }
    return ww;
};//get_TFTWidth

//==============================================================================
uint16_t  get_TFTHeight(TVT_Net *pVT_Net){
    uint16_t hh=0;
    if (pVT_Net->ImgMode){
        hh=pVT_Net->ImgTFT.height();
    }else {
        hh=pVT_Net->tft.height();
    }
    return hh;
};//get_TFTHeight

//==============================================================================
//ggISO_ColourMap[256]
TVTColorAlpha getColorIndex(uint8_t idx, TVT_Net *pVT_Net) {
    uint32_t rgb  = pVT_Net->gISO_ColourMap[idx];
    TVTColorAlpha ca;
    if (pVT_Net->VTDefaultColour) rgb  = pVT_Net->ggISO_ColourMap[idx];
    ca.color = 0x0000;
    ca.alpha = (rgb >> 24) & 0xFF;
    uint8_t red   = (rgb >> 16) & 0xFF;
    uint8_t green = (rgb >> 8)  & 0xFF;
    uint8_t blue  = (rgb >> 0)  & 0xFF;
    //set 565Color
    //ca.color=((red & 0xF8)<<8) + ((green & 0xFC) <<3) + (blue>>3);
    ca.color = pVT_Net->tft.color565(red, green, blue);
    //
    return ca;
};//getColorIndex




//------------------------------------------------------------------------------
bool Set_fillPolygonDirect(TVT_Net *pVT_Net,TVTPoints points[],uint16_t pNr,uint8_t fillColor,uint8_t* tft_pic){
    bool valid=(getVTObjectListSize(pVT_Net)>0);
    int16_t  x=pVT_Net->x, y=pVT_Net->y,nx=0,ny=0;
    uint16_t w=pVT_Net->w, h=pVT_Net->h,aw=0,ah=0;
    int  nodes, nodeX[pNr], pixelX, pixelY, ii, jj, swap ;
    uint8_t cIdx=fillColor;
    uint8_t* buff=pVT_Net->streamStr.getBuffer();
    if ((valid) && (points!=NULL)) {
        //
        if (tft_pic!=NULL) {
            aw=buff[5] + (buff[6]<<8);
            ah=buff[7] + (buff[8]<<8);
        }
        //
        //  Loop through the rows of the image.
        for (pixelY=0; pixelY<h; pixelY++) {
            //  Build a list of nodes.
            nodes=0; jj=pNr-1;
            for (ii=0; ii<pNr; ii++) {
                if (((points[ii].pointY<(double)pixelY) && (points[jj].pointY>=(double)pixelY))  ||  ((points[jj].pointY<(double)pixelY) && (points[ii].pointY>=(double)pixelY))) {
                    float erg=(points[jj].pointY-points[ii].pointY);
                    if (erg!=0) {
                        erg=(points[jj].pointX-points[ii].pointX)*(pixelY-points[ii].pointY)/erg;
                        nodeX[nodes++]=points[ii].pointX+round(erg);
                    }
                }
                jj=ii;
            }//for ii
            //  Sort the nodes, via a simple “Bubble” sort.
            ii=0;
            //
            while (ii<nodes-1) {
                if (nodeX[ii]>nodeX[ii+1]) {
                    swap=nodeX[ii]; nodeX[ii]=nodeX[ii+1]; nodeX[ii+1]=swap;
                    if (ii) ii--;
                } else {
                    ii++;
                }
            }//while
            //  Fill the pixels between node pairs.
            for (ii=0; ii<nodes; ii+=2) {
                if   (nodeX[ii  ]>=w) break;
                //
                if   (nodeX[ii+1]> 0) {
                    if (nodeX[ii  ]< 0 ) nodeX[ii]=0 ;
                    if (nodeX[ii+1]> w) nodeX[ii+1]=w;
                    //
                    for (pixelX=nodeX[ii]; pixelX<nodeX[ii+1]; pixelX++) {
                        cIdx=fillColor;
                        if (tft_pic!=NULL) {
                            nx=(x+pixelX) % aw;
                            ny=(y+pixelY) % ah;

                            cIdx=tft_pic[ny*aw+nx];
                        }
                        Set_drawPixel(pVT_Net,x+pixelX,y+pixelY,cIdx);
                    }
                }
            }//for ii
        }//for pixelY
        //
    }//valid
    return valid;
};//Set_fillPolygonDirect


//------------------------------------------------------------------------------
bool Set_fillPolygon(TVT_Net *pVT_Net,TVTPoints points[],uint16_t pNr,uint8_t fillColor){
    bool valid=(getVTObjectListSize(pVT_Net)>0);
    uint16_t aw=0,ah=0;
    int  nodes, nodeX[pNr], pixelX, pixelY, ii, jj, swap ;
    uint8_t* buff;
    TVTPixelXY pXY;
    if ((valid) && (points!=NULL)) {
        //
        if (pVT_Net->VTFillAttribute<0xFFFF) {
            int16_t refIdx=getVTObjID(pVT_Net,pVT_Net->VTFillAttribute);
            if (refIdx>=0) {
                getVTObjectFromList(pVT_Net,refIdx);
                buff=pVT_Net->streamStr.getBuffer();
                //getStreamStrInfo(pVT_Net);
                //
                aw=buff[5] + (buff[6]<<8);
                ah=buff[7] + (buff[8]<<8);
                if ((aw>0) && (ah>0)) {
                    uint8_t tft_pic[aw*ah];
                    PaintPictureToDirect(pVT_Net,&pXY, (uint8_t*) tft_pic);
                    //getArray8Info(pVT_Net,(uint8_t*) tft_pic,aw*ah);
                    //pVT_Net->ImgTFT.pushImage(0,0,aw,ah,(uint16_t*) tft_pic,8);
                    //return valid;
                    return Set_fillPolygonDirect(pVT_Net,points,pNr,fillColor,(uint8_t*) tft_pic);
                }
            }
        }
        //
        return Set_fillPolygonDirect(pVT_Net,points,pNr,fillColor,NULL);
    }//valid
    return valid;
};//Set_fillPolygon




//==============================================================================
bool GraphicDataPaintObjTo(TVT_Net *pVT_Net,TVTPixelXY *pXY, uint16_t nn) {
    bool valid=false;
    uint16_t i=0, r16=pVT_Net->streamStr.readBytesVal(2,nn);
    int8_t picFormat=-1;
    //check picture format
    if (r16==0x5089) picFormat=0; //png
    if (r16==0x4D42) picFormat=1; //bmp
    if (r16==0xD8FF) picFormat=2; //jpg
    //TEST
    //qWarning() << QString(r16,HEX);
    //qWarning() << "picFormat=" + QString(picFormat);
    //
    //paint
    //png format
    if (picFormat==0) {
        if  (Set_getScreenShot(pVT_Net)) valid=PaintPNGDirect(pVT_Net); else valid=PaintPNGToDirect(pVT_Net);
    }
    //bmp format
    if (picFormat==1) {
        if  (Set_getScreenShot(pVT_Net)) valid=drawBmpDirect(pVT_Net,pXY); else valid=PaintBMPToDirect(pVT_Net,pXY);
    }
    //jpg format
    if (picFormat==2) {
        if  (Set_getScreenShot(pVT_Net)) valid=PaintJPGDirect(pVT_Net); else valid=PaintJPGToDirect(pVT_Net);
    }
    return valid;
};//GraphicDataPaintObjTo


//==============================================================================
bool setVTScaleTypeOptions(TVT_Net *pVT_Net,TVTPixelXY *pXY) {
    bool valid=false;
    uint16_t wa=pXY->pixelW,ha=pXY->pixelH,w=pVT_Net->w, h=pVT_Net->h;
    if ((pVT_Net->VTScaleType>=0) && (pVT_Net->VTScaleOptions>=0) && (wa>0) && (ha>0)) {
        valid=true;
        pXY->flash=false;

        switch (pVT_Net->VTScaleType & 0x07) {
            //case 0:pXY->pixelXF=1.000; pXY->pixelYF=1.000;break;            //none
            case 1:pXY->pixelXF=1.000*w/wa; pXY->pixelYF=pXY->pixelXF;break;  //width
            case 2:pXY->pixelYF=1.000*h/ha; pXY->pixelXF=pXY->pixelYF;break;  //height
            case 3:pXY->pixelXF=1.000*w/wa; pXY->pixelYF=1.000*h/ha;break;    //width_height
            case 4:pXY->pixelXF=1.000*w/wa; pXY->pixelYF=1.000*h/ha;          //fit_width_height
                if (pXY->pixelXF*ha>h)  pXY->pixelXF=pXY->pixelYF;
                if (pXY->pixelYF*wa>w)  pXY->pixelYF=pXY->pixelXF;
                break;
        }
        uint16_t ww=round(1.000*pXY->pixelXF*wa);
        uint16_t hh=round(1.000*pXY->pixelYF*ha);
        //
        //h_middle
        if ((pVT_Net->VTScaleType & 0x08)>0) pXY->pixelXOffs=(w-ww)/2;
        //h_right
        if ((pVT_Net->VTScaleType & 0x10)>0) pXY->pixelXOffs=(w-ww);
        //v_middle
        if ((pVT_Net->VTScaleType & 0x20)>0) pXY->pixelYOffs=(h-hh)/2;
        //v_bottom
        if ((pVT_Net->VTScaleType & 0x40)>0) pXY->pixelYOffs=(h-hh);
    }
    //
    return valid;
};//setVTScaleTypeOptions



//==============================================================================
//X-Scale picture
bool setPictureScaleX(TVT_Net *pVT_Net,TVTPixelXY *pXY,uint16_t* tft_buffer,uint16_t* usPixels) {
    bool valid=false;
    int16_t  xx=pXY->pixelXX,pxs=0,xs=0;
    uint16_t ww=pXY->pixelW, nn=0;
    if ((tft_buffer!=NULL) && (usPixels!=NULL)) {
        valid=true;
        //
        for (xx=0;xx<ww;xx++){
            pxs=xx*pXY->pixelXF;nn=0;
            for (xs=xx*pXY->pixelXF;xs<(xx+1)*pXY->pixelXF;xs++) {
                //check new line
                if ((nn==0) || ((nn>0) && (xs>pxs))) {
                    tft_buffer[xs]=usPixels[xx];
                }
                pxs=xs;nn++;
            }//for xs
        }//for xx
    }//NULL
    //
    return valid;
};//setPictureScaleX



//==============================================================================
//Y-Scale picture
bool setPictureScaleY(TVT_Net *pVT_Net,TVTPixelXY *pXY,uint16_t* tft_buffer,uint8_t* tft_alpha,uint16_t color) {
    bool valid=false;
    int16_t  x=pVT_Net->x, y=pVT_Net->y,xOffs=pXY->pixelXOffs,yOffs=pXY->pixelYOffs,pys=0,ys=0;
    uint16_t ww=pXY->pixelS,yy=pXY->pixelYY,nn=0;
    if ((tft_buffer!=NULL) and (ww>0)) {
        valid=true;
        pys=yy*pXY->pixelYF;nn=0;
        for (ys=yy*pXY->pixelYF;ys<(yy+1)*pXY->pixelYF;ys++) {
            //check new line
            if ((nn==0) || ((nn>0) && (ys>pys))) {
                Set_pushImageAlpha(pVT_Net,x+xOffs,y+yOffs+ys,ww,1,(uint16_t*) tft_buffer,tft_alpha,color);
                //TEST
                //pVT_Net->tft.alpha=0x7F;
                //Set_pushImageAlpha(pVT_Net,x+xOffs,y+yOffs+ys,ww,1,(uint16_t*) tft_buffer,NULL,color);
                //Set_pushImageAlpha(pVT_Net,x+xOffs,y+yOffs+ys,ww,1,NULL,NULL,color);
            }
            pys=ys;nn++;
        }//for ys
    }//NULL
    return valid;
};//setPictureScaleY



//==============================================================================
TVT_Net *ppVT_Net=NULL;

//------------------------------------------------------------------------------
//callback function
void PNGDraw(PNGDRAW *pDraw){
    int16_t  x=ppVT_Net->x, y=ppVT_Net->y;
    uint16_t w=ppVT_Net->w, ww=pDraw->iWidth;
    TVTPixelXY pXY;
    //
    if (ppVT_Net!=NULL) {
        uint16_t usPixels[ww]; //TEST h=122, 4bpp pixeltype=3
        //PNG_RGB565_BIG_ENDIAN, PNG_RGB565_LITTLE_ENDIAN
        ppVT_Net->png.getLineAsRGB565(pDraw, usPixels, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
        //
        pXY.pixelW=ppVT_Net->png.getWidth();  pXY.pixelH=ppVT_Net->png.getHeight();
        pXY.pixelXF=1.000;pXY.pixelYF=1.000;
        pXY.pixelXX=0; pXY.pixelYY=0;
        pXY.pixelXOffs=0; pXY.pixelYOffs=0;
        setVTScaleTypeOptions(ppVT_Net,&pXY);
        //pXY.pixelXF=1.000;
        //X-Scale picture
        w=round(1.000*pXY.pixelXF*ww);
        uint16_t tft_buffer[w];
        setPictureScaleX(ppVT_Net,&pXY,(uint16_t*) tft_buffer,(uint16_t*) usPixels);
        //
        //Y-Scale picture
        pXY.pixelS=w; pXY.pixelYY=pDraw->y;
        setPictureScaleY(ppVT_Net,&pXY,(uint16_t*) tft_buffer,NULL,0xFFFF);
    }//NULL
}; //PNGDraw()



//------------------------------------------------------------------------------
bool PaintPNGToDirect(TVT_Net *pVT_Net) {
    bool valid=(getVTObjectListSize(pVT_Net)>0);
    uint32_t pCount=pVT_Net->streamStr.readBytesVal(4,4);
    if (valid){
        ppVT_Net=pVT_Net;
        if ((pCount>0) && (pCount<=pVT_Net->streamStr.available())){
            valid=PaintPNGDirect(pVT_Net);
        } //count
        ppVT_Net=NULL;
    }//valid
    return valid;
};//PaintPNGToDirect



//------------------------------------------------------------------------------
bool PaintPNGDirect(TVT_Net *pVT_Net) {
    bool valid=(getVTObjectListSize(pVT_Net)>0);
    int16_t rc=0;
    uint32_t  pCount=pVT_Net->streamStr.available();
    uint8_t*  buff=pVT_Net->streamStr.getBuffer();
    if (valid){
        ppVT_Net=pVT_Net; valid=false;
        rc = pVT_Net->png.openRAM((uint8_t*) buff+8, pCount, PNGDraw);
        //
        if (rc == PNG_SUCCESS) {
            Serial.printf("image specs: (%d x %d), %d bpp, pixel type: %d\n", pVT_Net->png.getWidth(), pVT_Net->png.getHeight(), pVT_Net->png.getBpp(), pVT_Net->png.getPixelType());
            rc = pVT_Net->png.decode(NULL, 0);
            valid=true;
            //pVT_Net->png.close();
        }//rc
        ppVT_Net=NULL;
    }//valid
    return valid;
};//PaintPNGDirect




//------------------------------------------------------------------------------
bool drawBmpDirect(TVT_Net *pVT_Net,TVTPixelXY *pXY) {
    uint32_t fileSize=0, reserved=0,seekOffset=0,dib_size=0 , w=0,h=0,r32=0,num_colors=0,sCount=0;
    uint16_t r16=0,j=0,sOffset=8;
    bool getBmpData=false;
    sOffset=(!Set_getScreenShot(pVT_Net))*8;
    pVT_Net->streamStr.setPos(sOffset);
    sCount=pVT_Net->streamStr.available();
    r16=pVT_Net->streamStr.readBytesVal(2);
    if (r16==0x4D42) {
        getBmpData=true;
        //qWarning() << getStringHEX(r16,4);
        fileSize=pVT_Net->streamStr.readBytesVal(4);
        reserved=pVT_Net->streamStr.readBytesVal(4);
        seekOffset=pVT_Net->streamStr.readBytesVal(4);
        dib_size=pVT_Net->streamStr.readBytesVal(4);
        w=pVT_Net->streamStr.readBytesVal(4);
        h=pVT_Net->streamStr.readBytesVal(4);
        //planes
        r16=pVT_Net->streamStr.readBytesVal(2);
        //
        if (r16==1) {
            //bitCount
            r16=pVT_Net->streamStr.readBytesVal(2);
            //check encoded
            r32=pVT_Net->streamStr.readBytesVal(4);
            Serial.printf("image: fileSize=%d, dib_size=%d, planes=%d, encoded=%d\n", fileSize, dib_size, r16, r32);
            //
            if (r32==0) {
                pVT_Net->streamStr.setPos(pVT_Net->streamStr.getPos()+12);
                num_colors=pVT_Net->streamStr.readBytesVal(4);
                //qWarning() << "nn=" + QString(14+dib_size);
                pVT_Net->streamStr.setPos(sOffset+14+dib_size);
                //TEST
                Serial.printf("image specs: (%d x %d), %d bpp, seekOffset=%d, num_colors=%d, sCount=%d\n", w, h, r16, seekOffset, num_colors, sCount);
                //qWarning() << dib_size;
                pXY->pixelW=w;pXY->pixelH=h;   pXY->pixelXOffs=seekOffset; pXY->pixelYOffs=dib_size;
                pXY->pixelS=num_colors;pXY->pixelN=r16;
                //
                // Capture the colour lookup table or bpp<=8
                if (num_colors>0) {
                    uint32_t pixel_color[num_colors];
                    for (j = 0; j < num_colors; j++) {
                        pixel_color[j]=pVT_Net->streamStr.readBytesVal(4);
                    }
                    //TEST
                    //getArray32Info(pVT_Net, (uint32_t*) pixel_color,num_colors);
                    getBitmapData(pVT_Net,pXY,(uint32_t*) pixel_color);
                } else getBitmapData(pVT_Net,pXY,NULL);

            }//check encoded
        }//(r16==1) planes
    } else qWarning() << "BMP format not recognized.";
    return getBmpData;
};//drawBmpDirect




//------------------------------------------------------------------------------
void getBitmapData(TVT_Net *pVT_Net,TVTPixelXY* pXY,uint32_t* pixel_color) {
    int16_t x=pVT_Net->x, y=pVT_Net->y,i=0,j=0;
    uint32_t seekOffset=pXY->pixelXOffs, nn=seekOffset,nMax=0;
    uint16_t bpp=pXY->pixelN,num_colors=pXY->pixelS,w=pXY->pixelW,h=pXY->pixelH,row=0, col=0,ww=w,sOffset=8;
    uint8_t  r=0, g=0, b=0, a=0,c=0,kk=0;
    uint8_t* buff=pVT_Net->streamStr.getBuffer();
    bool oldSwapBytes=Set_getSwapBytes(pVT_Net);
    sOffset=(!Set_getScreenShot(pVT_Net))*8;
    Set_setSwapBytes(pVT_Net,true);
    if (pXY->swap) Set_setSwapBytes(pVT_Net,false);
    pXY->pixelXF=1.000;pXY->pixelYF=1.000;
    pXY->pixelXOffs=0;pXY->pixelYOffs=0;
    pXY->pixelXX=0;pXY->pixelYY=0;
    setVTScaleTypeOptions(pVT_Net,pXY);
    ww=round(1.000*pXY->pixelXF*w);
    //pVT_Net->streamStr.setPos(0);
    //nMax=pVT_Net->streamStr.available();
    //qWarning() << "nMaxAll=" + QString(nMax);
    nn+=sOffset;
    pVT_Net->streamStr.setPos(nn);
    nMax=pVT_Net->streamStr.available();
    //
    uint16_t tft_buffer[ww];
    //
    y = h - 1;
    //
    uint16_t padding = (4 - ((w * 3) & 3)) & 3;
    uint16_t lSize=w * 3 + padding;
    if (bpp==16) {
        padding=w % 4;
        lSize=w * 2 + padding;
    }
    //
    if (bpp<16) {
        kk=32/bpp;
        if ((w % kk)>0) {
            lSize=w/kk;
            lSize=kk*(lSize + 1);
            lSize=3*lSize;
        } else lSize=3*w;
    }

    //TEST
    /*
  qWarning() << "padding=" + QString(padding);
  qWarning() << "nMax="    + QString(nMax);
  qWarning() << "w="       + QString(w);
  qWarning() << "h="       + QString(h);
  qWarning() << "lSize="   + QString(lSize);
  qWarning() << "nn="      + QString(nn);
  qWarning() << "bpp="     + QString(bpp);
  */
    //
    uint8_t  lineBuffer[lSize];
    //
    //getArray32Info(pVT_Net, (uint32_t*) pixel_color,num_colors);
    //qWarning() << nn;
    //qWarning() << lSize;
    //
    for (row = 0; row < h; row++) {
        //
        if ((bpp<=8) && (pixel_color!=NULL) and (num_colors>0)) {
            //qWarning() << row;
            i=0;
            while (i<lSize) {
                //nn=seekOffset;
                a=buff[nn++];
                kk=8/bpp;
                for (j=kk; j>0;j--){
                    c=a;
                    if (kk==2) c=(a>>4*(j-1)) & 0x0F;
                    if (kk==8) c=(a>>(j-1))   & 0x01;
                    //qWarning() << getStringHEX(c,2) + "|";
                    if (c>=num_colors) c=num_colors-1;
                    //lineBuffer[i++]=(pixel_color[c]>>24) & 0xFF; //a
                    lineBuffer[i++]=(pixel_color[c]>>0)  & 0xFF;   //b
                    lineBuffer[i++]=(pixel_color[c]>>8)  & 0xFF;   //g
                    lineBuffer[i++]=(pixel_color[c]>>16) & 0xFF;   //r
                }//for j
            }//while
            //qWarning() << "";
        }
        //
        if (bpp>=16){
            if (nn+lSize>nMax) {
                pVT_Net->streamStr.clear();
                break;
            } else {
                pVT_Net->streamStr.readBytes((uint8_t*)lineBuffer,lSize,nn); nn+=lSize;
            }
        }
        //TEST
        //qWarning() << row;
        //getArray8Info(pVT_Net, (uint8_t*) lineBuffer,lSize);
        //
        uint8_t*  bptr = lineBuffer;
        uint16_t* tptr = (uint16_t*)lineBuffer;
        // Convert 24 to 16 bit colours
        for (uint16_t col = 0; col < w; col++) {
            if (bpp==16) {
                *tptr++;
            } else {
                b = *bptr++;
                g = *bptr++;
                r = *bptr++;
                *tptr++ = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
            }
        }//for col
        //
        if ((Set_getScreenShot(pVT_Net)) && (pVT_Net->ImgMode)){
            pVT_Net->ImgTFT.pushImage(0,y,ww,1,(uint16_t*) lineBuffer);
        } else {
            //X-Scale picture
            setPictureScaleX(pVT_Net,pXY,(uint16_t*) tft_buffer,(uint16_t*) lineBuffer);
            //
            //Y-Scale picture
            pXY->pixelS=ww; pXY->pixelYY=y;
            setPictureScaleY(pVT_Net,pXY,(uint16_t*) tft_buffer,NULL,0xFFFF);
        }
        //TEST
        //Set_pushImageAlpha(pVT_Net,0,y,ww,1,(uint16_t*) lineBuffer,NULL,0xFFFF);
        //pVT_Net->tft.pushImageAlpha(0,y,ww,1,(uint16_t*) lineBuffer,NULL,0xFFFF);
        y--;
    }//for row
    //
    if ((Set_getScreenShot(pVT_Net)) && (pVT_Net->ImgMode)) pVT_Net->ImgTFT.pushSprite(0,0);
    //
    Set_setSwapBytes(pVT_Net,oldSwapBytes);
};//getBitmapData




//------------------------------------------------------------------------------
bool PaintBMPToDirect(TVT_Net *pVT_Net,TVTPixelXY* pXY) {
    bool valid=(getVTObjectListSize(pVT_Net)>0);
    uint32_t pCount=pVT_Net->streamStr.readBytesVal(4,4);
    uint16_t rc=pVT_Net->streamStr.readBytesVal(2,8);
    uint8_t* buff=pVT_Net->streamStr.getBuffer();
    if (valid){
        valid=false;
        //qWarning() << getStringHEX(rc,4);
        if ((rc==0x4D42) && (pCount>0) && (pCount<=pVT_Net->streamStr.available())){
            //qWarning() << pCount;
            valid=drawBmpDirect(pVT_Net,pXY);
        } //count
    }//valid
    return valid;
};//PaintBMPToDirect


//==============================================================================
bool PaintJPGToDirect(TVT_Net *pVT_Net) {
    bool valid=(getVTObjectListSize(pVT_Net)>0);
    uint32_t  pCount=0,i=0;
    uint16_t rc=0;
    if (valid){
        pCount=pVT_Net->streamStr.readBytesVal(4,4);
        rc=pVT_Net->streamStr.readBytesVal(2,8);
        pVT_Net->streamStr.setPos(8);
        //
        if ((rc==0xD8FF) && (pCount>0) && (pCount<=pVT_Net->streamStr.available())){
            //qWarning() << pCount;
            valid=PaintJPGDirect(pVT_Net);
        } //count
    }//valid
    return valid;
};//PaintJPGToDirect




//==============================================================================
bool PaintJPGDirect(TVT_Net *pVT_Net) {
    bool valid=true;
    uint32_t pCount=pVT_Net->streamStr.available();
    uint8_t* buff=pVT_Net->streamStr.getBuffer();
    TVTPixelXY pXY;
    //TEST
    //getStreamStrInfo(pVT_Net,32);
    //qWarning() << pCount;
    //qWarning() << getStringHEX(rc,4);
    //
    pVT_Net->streamStr.setPos(0);
    JpegDec.decodeArray((uint8_t*) buff+8, pCount);
    //
    if (pVT_Net->VT_InfoMode) {
        qWarning() << F("===============");
        qWarning() << F("JPEG image info");
        qWarning() << F("===============");
        qWarning() << F(  "Width      :")); qWarning( << JpegDec.width;
                qWarning() << F(  "Height     :")); qWarning( << JpegDec.height;
                qWarning() << F(  "Components :")); qWarning( << JpegDec.comps;
                qWarning() << F(  "MCU / row  :")); qWarning( << JpegDec.MCUSPerRow;
                qWarning() << F(  "MCU / col  :")); qWarning( << JpegDec.MCUSPerCol;
                qWarning() << F(  "Scan type  :")); qWarning( << JpegDec.scanType;
                qWarning() << F(  "MCU width  :")); qWarning( << JpegDec.MCUWidth;
                qWarning() << F(  "MCU height :")); qWarning( << JpegDec.MCUHeight;
                qWarning() << F("===============");
    }
    //
    pXY.pixelW=JpegDec.width;pXY.pixelH=JpegDec.height;
    pXY.pixelXF=1.000;pXY.pixelYF=1.000;
    pXY.pixelXOffs=0;pXY.pixelYOffs=0;
    pXY.pixelXX=0;pXY.pixelYY=0;
    setVTScaleTypeOptions(pVT_Net,&pXY);
    //TEST
    //qWarning() << pXY.pixelXOffs;
    //qWarning() << pXY.pixelYOffs;
    //qWarning() << pXY.pixelXF,3;
    //qWarning() << pXY.pixelYF,3;
    //
    renderJPEG(pVT_Net,&pXY);
    return valid;
};//PaintJPGDirect



//------------------------------------------------------------------------------
// Draw a JPEG on the TFT, images will be cropped on the right/bottom sides if they do not fit
//------------------------------------------------------------------------------
// This function assumes xpos,ypos is a valid screen coordinate. For convenience images that do not
// fit totally on the screen are cropped to the nearest MCU size and may leave right/bottom borders.
void renderJPEG(TVT_Net *pVT_Net,TVTPixelXY *pXY) {
    int16_t x=pVT_Net->x, y=pVT_Net->y,xOffs=pXY->pixelXOffs,yOffs=pXY->pixelYOffs, xx=x+xOffs,yy=y+yOffs;
    // retrieve information about the image
    uint16_t *pImg;
    uint16_t mcu_w = JpegDec.MCUWidth ,mcu_x=0,ww=0;
    uint16_t mcu_h = JpegDec.MCUHeight,mcu_y=0,hh=0;
    uint32_t max_x = JpegDec.width;
    uint32_t max_y = JpegDec.height;
    // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
    // Typically these MCUs are 16x16 pixel blocks
    // Determine the width and height of the right and bottom edge image blocks
    uint32_t min_w = min(mcu_w, max_x % mcu_w);
    uint32_t min_h = min(mcu_h, max_y % mcu_h);
    //
    // save the current image block size
    uint32_t win_w = mcu_w;
    uint32_t win_h = mcu_h;
    bool oldSwapBytes=Set_getSwapBytes(pVT_Net);
    Set_setSwapBytes(pVT_Net,true);
    //
    //read each MCU block until there are no more
    while (JpegDec.read()) {    // While there is more data in the file
        // save a pointer to the image block
        pImg = JpegDec.pImage ;
        // calculate where the image block should be drawn on the screen
        // Calculate coordinates of top left corner of current MCU
        mcu_x = JpegDec.MCUx * mcu_w;
        mcu_y = JpegDec.MCUy * mcu_h;
        //
        //check if the image block size needs to be changed for the right and bottom edges
        if (mcu_x + mcu_w <= max_x) win_w = mcu_w;  else win_w = min_w;
        if (mcu_y + mcu_h <= max_y) win_h = mcu_h;  else win_h = min_h;

        ww=round(1.000*pXY->pixelXF*win_w);
        hh=round(1.000*pXY->pixelYF*win_h);
        uint16_t mcu_xx=round(1.000*pXY->pixelXF*mcu_x);
        uint16_t mcu_yy=round(1.000*pXY->pixelYF*mcu_y);
        pXY->pixelW=win_w;pXY->pixelS=ww;
        pXY->pixelXOffs=xOffs+mcu_xx; pXY->pixelYOffs=yOffs+mcu_yy;
        //
        uint16_t lineBuffer[win_w];
        uint16_t tft_buffer[ww];
        //
        for (yy=0;yy<win_h;yy++) {
            for (xx=0;xx<win_w;xx++) lineBuffer[xx]=*pImg++;
            //X-Scale picture
            setPictureScaleX(pVT_Net,pXY,(uint16_t*) tft_buffer,(uint16_t*) lineBuffer);
            //
            //Y-Scale picture
            pXY->pixelYY=yy;
            setPictureScaleY(pVT_Net,pXY,(uint16_t*) tft_buffer,NULL,0xFFFF);
            //TEST
            //Set_pushImageAlpha(pVT_Net,x + pXY->pixelXOffs, y + pXY->pixelYOffs + yy, ww,1, (uint16_t*) tft_buffer,NULL,0xFFFF);
        }//for yy
    } //while
    Set_setSwapBytes(pVT_Net,oldSwapBytes);
};//renderJPEG


//==============================================================================
bool PaintPictureToDirect(TVT_Net *pVT_Net,TVTPixelXY *pXY, uint8_t* tft_pic) {
    bool valid=(getVTObjectListSize(pVT_Net)>0),setBreak=false;
    int16_t   x=pVT_Net->x, y=pVT_Net->y;
    uint16_t  w=pVT_Net->w, h=pVT_Net->h;
    uint8_t* buff=pVT_Net->streamStr.getBuffer();
    //
    uint8_t VTTransparencyColour=buff[11];
    uint16_t ws=buff[3] + (buff[4]<<8);
    uint16_t wa=buff[5] + (buff[6]<<8);
    uint16_t ha=buff[7] + (buff[8]<<8);
    uint8_t  VTFormat=buff[9];
    uint8_t  VTOptions=buff[10];
    uint16_t objID=pVT_Net->VTObjID,xx=0,yy=0;
    //
    bool transp=((VTOptions & 0x01)==0x01);
    bool flash =((VTOptions & 0x02)==0x02);
    bool lenEnc=((VTOptions & 0x04)==0x04);
    uint32_t bCount=0, bNr=0, aIdx=17; //pVT_Net->aIdx+5,
    uint16_t xByte=0,BytesPerLine=0,i=0,nn=0;
    uint8_t  bb=0,bv=0;
    TVTColorAlpha ct=getColorIndex(VTTransparencyColour,pVT_Net);
    //
    if ((wa==0) || (ha==0)) return valid;
    //
    if (tft_pic!=NULL) {
        ws=wa;flash=false;transp=false;
    }
    //
    pXY->pixelXF=1.000*ws/wa;
    pXY->pixelYF=1.000*ws/wa;
    //
    pXY->pixelW=wa;pXY->pixelH=ha;pXY->pixelC=0;
    pXY->pixelXX=0; pXY->pixelYY=0;pXY->flash=flash;
    pXY->pixelXOffs=0; pXY->pixelYOffs=0;
    //
    //set scaleOptions
    setVTScaleTypeOptions(pVT_Net,pXY);
    flash=pXY->flash;
    //
    uint16_t ww=round(1.000*pXY->pixelXF*wa);
    uint16_t hh=round(1.000*pXY->pixelYF*ha);
    //
    pXY->pixelFormat=VTFormat;
    pXY->pixelX=x;pXY->pixelY=y;
    pXY->pixelXX=xx;pXY->pixelYY=yy;
    pXY->pixelN=0;
    //
    if ((pXY->pixelXF==0) || (pXY->pixelYF==0)) return valid;
    //TEST
    //getStreamStrInfo(pVT_Net);
    for (int i=0;i<4;i++) bCount+=buff[12+i]<<8*i;
    //
    if (tft_pic!=NULL) {
        pXY->pixelXF=1.000;pXY->pixelYF=1.000;
        flash=false;transp=false;
    }
    //
    if ((valid) and (bCount>0)) {
        if (flash){
            pVT_Net->FlashList+=QString(objID) + "," + QString(x) + "," + QString(y) + "," + QString(wa) + "," + QString(ha) + ",\n";
            if (pVT_Net->Flash>=3) {
                //Set_fillRect(pVT_Net,x,y,ww,hh,pVT_Net->FlashColor);
                return valid;
            }
        } //flash
        //
        if (pXY->pixelFormat==0) BytesPerLine= trunc(wa/8.000+0.875);
        if (pXY->pixelFormat==1) BytesPerLine= trunc(wa/2.000+0.500);
        if (pXY->pixelFormat==2) BytesPerLine= wa;
        //
        uint16_t tft_buffer[ww];
        uint8_t  tft_alpha[ww];
        //
        pXY->pixelS=ww;
        Set_setTransp(pVT_Net,transp); Set_alpha(pVT_Net,0xFF);
        ct.color=(ct.color>>8 | ct.color<<8);
        //
        while ((BytesPerLine>0) && (yy<ha)) {
            xByte=0; pXY->pixelXX=0; pXY->pixelYY=yy;
            //
            while (xByte<BytesPerLine){
                //
                if (lenEnc) {
                    if (bNr==0) {
                        if (aIdx<pVT_Net->streamStr.available()){
                            bb=buff[aIdx]; aIdx++;
                        } else bb=0;
                        bNr=bb;
                        if (aIdx<pVT_Net->streamStr.available()){
                            bb=buff[aIdx]; aIdx++;
                        } else bb=0;
                        //
                        if (aIdx<max_size) continue; //while xx
                    } else bNr--;
                } else {
                    if (aIdx<pVT_Net->streamStr.available()){
                        bb=buff[aIdx];aIdx++;
                    } else bb=0;
                }
                //
                if (aIdx>=max_size) break; //while xx
                //
                pXY->pixelC=bb;
                PaintToPixelDirect(pVT_Net,pXY,(uint16_t*) tft_buffer,(uint8_t*) tft_alpha,tft_pic);
                xByte++;
            }//while xx
            //
            //Y-Scale picture
            if (tft_pic==NULL) {
                //TEST
                //pVT_Net->tft.setTransp=true;
                //getArray16Info(pVT_Net,(uint16_t*) tft_buffer,ww);
                setPictureScaleY(pVT_Net,pXY,(uint16_t*) tft_buffer,(uint8_t*) tft_alpha,ct.color);
            }//NULL
            //
            yy++;
            if (aIdx>=max_size) break;
        }//while yy
        //
        Set_setTransp(pVT_Net,false); Set_alpha(pVT_Net,0xFF);
    } else valid=false;
    //
    return valid;
};//PaintPictureToDirect



//------------------------------------------------------------------------------
void PaintToPixelDirect(TVT_Net *pVT_Net,TVTPixelXY *pXY,uint16_t* tft_buffer,uint8_t* tft_alpha,uint8_t* tft_pic){
    uint16_t xx=pXY->pixelXX,xs=0;
    uint8_t  bCol[8],bb=pXY->pixelC,colNr=1,i=0;
    bool inRange=(xx<pXY->pixelW);
    TVTColorAlpha ca;
    //get VTPicture format
    switch (pXY->pixelFormat) {
        case 0:colNr=8;
            if ((pXY->pixelW-xx)<colNr) colNr=pXY->pixelW-xx;
            for (i=0;i<colNr;i++) bCol[i]=((bb >>(7-i)) & 0x01);
            break;   //1bit
            //
        case 1: colNr=2;
            if ((pXY->pixelW-xx)<colNr) colNr=pXY->pixelW-xx;
            for (i=0;i<colNr;i++) bCol[i]=((bb >>(4-4*i)) & 0x0F);
            break; //4bit
            //
        default: bCol[0]=bb;colNr=1;
            break;//8bit
    }//switch;
    //
    for (i=0;i<colNr;i++) {
        ca=getColorIndex(bCol[i],pVT_Net); ca.color=(ca.color>>8 | ca.color<<8);
        //X-Scale picture
        if (inRange) {
            for (xs=xx*pXY->pixelXF;xs<(xx+1)*pXY->pixelXF;xs++) {
                tft_buffer[xs]=ca.color; tft_alpha[xs]=ca.alpha;
                if (tft_pic!=NULL) tft_pic[pXY->pixelN++]=bCol[i];
            }
        }//inRange
        //
        xx++;
    }//for i
    pXY->pixelXX=xx;
};//PaintToPixelDirect




//==============================================================================
//==============================================================================
void Set_drawWideLine(TVT_Net *pVT_Net,int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t lw, uint8_t cIdx){
    float d0=sqrt(sq(x0 - x1) + sq(y0 - y1));
    float dy = (lw / 2.0) * (x0 - x1) / d0;
    float dx = (lw / 2.0) * (y0 - y1) / d0;
    float ddx = lw * (x1 - x0) / d0;
    float ddy = lw * (y1 - y0) / d0;
    uint16_t pCount=round(d0/lw);
    float xx0,yy0,xx1,yy1;
    bool setLine=true;
    int8_t k=15;
    //TEST
    //Set_resetViewport(pVT_Net);
    //Set_drawLine(pVT_Net,x0, y0, x1, y1,cl_red);
    xx0=x0;yy0=y0; xx1=x1; yy1=y1;
    //
    if (pVT_Net->lineArt<0xFFFF) {
        xx1=xx0+ddx; yy1=yy0+ddy;
        for (int i=0;i<pCount;i++) {
            setLine=(((pVT_Net->lineArt>>k) & 0x01)>0);
            k--;
            if (k<0) k=15;
            //
            if (setLine) {
                Set_fillTriangle(pVT_Net,xx0 + dx, yy0 - dy, xx0 - dx, yy0 + dy, xx1 + dx, yy1 - dy, cIdx);
                Set_fillTriangle(pVT_Net,xx0 - dx, yy0 + dy, xx1 - dx, yy1 + dy, xx1 + dx, yy1 - dy, cIdx);
                //TEST
                //Set_drawTriangle(pVT_Net,xx0 + dx, yy0 - dy, xx0 - dx, yy0 + dy, xx1 + dx, yy1 - dy, cIdx);
                //Set_drawTriangle(pVT_Net,xx0 - dx, yy0 + dy, xx1 - dx, yy1 + dy, xx1 + dx, yy1 - dy, cIdx);
            }
            xx0=xx1;yy0=yy1;
            xx1=xx0+ddx;
            yy1=yy0+ddy;
        }//for i
    }else {
        Set_fillTriangle(pVT_Net,xx0 + dx, yy0 - dy, xx0 - dx, yy0 + dy, xx1 + dx, yy1 - dy, cIdx);
        Set_fillTriangle(pVT_Net,xx0 - dx, yy0 + dy, xx1 - dx, yy1 + dy, xx1 + dx, yy1 - dy, cIdx);
    }//lineArt
};//Set_drawWideLine


//------------------------------------------------------------------------------
void Set_setTextDatum(TVT_Net *pVT_Net,uint8_t dt){
    if (pVT_Net->ImgMode){
        pVT_Net->ImgTFT.setTextDatum(dt);
    }else {
        pVT_Net->tft.setTextDatum(dt);
    }
};//Set_setTextDatum      


//------------------------------------------------------------------------------
void Set_setTextSize(TVT_Net *pVT_Net,uint8_t sIdx){
    if (pVT_Net->ImgMode){
        pVT_Net->ImgTFT.setTextSize(sIdx);
    }else {
        pVT_Net->tft.setTextSize(sIdx);
    }
}; //Set_setTextSize     


//------------------------------------------------------------------------------
void Set_setTextColor(TVT_Net *pVT_Net,uint8_t cIdx){
    TVTColorAlpha ca=getColorIndex(cIdx,pVT_Net);
    if (pVT_Net->ImgMode){
        pVT_Net->ImgTFT.setTextColor(ca.color);
    }else {
        pVT_Net->tft.setTextColor(ca.color);
    }
}; //Set_setTextColor     


//------------------------------------------------------------------------------
void Set_setTextColorBg(TVT_Net *pVT_Net,uint16_t fgColor,uint16_t bgColor){
    if (pVT_Net->ImgMode){
        pVT_Net->ImgTFT.setTextColor(fgColor,bgColor);
    }else {
        pVT_Net->tft.setTextColor(fgColor,bgColor);
    }
}; //Set_setTextColor     


//------------------------------------------------------------------------------
void Set_setTextFont(TVT_Net *pVT_Net,uint8_t fntNr){
    if (pVT_Net->ImgMode){
        pVT_Net->ImgTFT.setTextFont(fntNr);
    }else {
        pVT_Net->tft.setTextFont(fntNr);
    }
}; //Set_setTextFont     



//------------------------------------------------------------------------------
#ifdef LOAD_GFXFF
void Set_setFreeFont(TVT_Net *pVT_Net,const GFXfont *f){
    if (pVT_Net->ImgMode){
        pVT_Net->ImgTFT.setFreeFont(f);
    }else {
        pVT_Net->tft.setFreeFont(f);
    }
}; //Set_setFreeFont     
#endif //LOAD_GFXFF

//------------------------------------------------------------------------------
bool Set_fontLoaded(TVT_Net *pVT_Net){
    bool valid=false;
    if (pVT_Net->ImgMode){
        valid=pVT_Net->ImgTFT.fontLoaded;
    }else {
        valid=pVT_Net->tft.fontLoaded;
    }
    return valid;
}; //Set_fontLoaded     


//------------------------------------------------------------------------------
void Set_fillScreen(TVT_Net *pVT_Net,uint16_t color){
    if (pVT_Net->ImgMode){
        pVT_Net->ImgTFT.fillScreen(color);
        //pVT_Net->tft.fillScreen(color);
    }else {
        pVT_Net->tft.fillScreen(color);
    }
}; //Set_fillScreen     


//------------------------------------------------------------------------------
void Set_M5Stack_PSRAM(TVT_Net *pVT_Net,uint8_t psRam){
    pVT_Net->tft.init();
    pVT_Net->tft.invertDisplay(true);
    pVT_Net->tft.setRotation(1);
    Set_fillScreen(pVT_Net,TFT_BLACK);
    //Set_fillScreen(pVT_Net,TFT_BLUE);
    //set/get PSRAM active
    pVT_Net->tft.setAttribute(PSRAM_ENABLE,psRam);
    pVT_Net->PSRam=pVT_Net->tft.getAttribute(PSRAM_ENABLE);
    //
    qWarning() << "PSRAM_ENABLE="); qWarning( << pVT_Net->PSRam;
            if (!pVT_Net->PSRam) pVT_Net->ImgMode=0;
}; //Set_M5Stack     


//------------------------------------------------------------------------------
void Set_CheckDateTime(TVT_Net *pVT_Net){
    if (!M5.Rtc.SetTime(&pVT_Net->RTCtime)) qWarning() << "wrong time set!";
    if (!M5.Rtc.SetDate(&pVT_Net->RTCDate)) qWarning() << "wrong date set!";
}; //Set_CheckDateTime     


//------------------------------------------------------------------------------
void Set_alphaColor(TVT_Net *pVT_Net,uint16_t alphaColor){
    pVT_Net->tft.alphaColor=alphaColor;
}; //Set_alphaColor     



//------------------------------------------------------------------------------
void Set_alpha(TVT_Net *pVT_Net,uint8_t alpha){
    pVT_Net->tft.alpha=alpha;
}; //Set_alpha     


//------------------------------------------------------------------------------
void Set_setTransp(TVT_Net *pVT_Net,bool active){
    pVT_Net->tft.setTransp=active;
}; //Set_setTransp     


//------------------------------------------------------------------------------
bool Set_getScreenShot(TVT_Net *pVT_Net){
    bool active=false;
    active=pVT_Net->tft.setScreenShot;
    return active;
}; //Set_setScreenShot     


//------------------------------------------------------------------------------
void Set_setScreenShot(TVT_Net *pVT_Net,bool active){
    pVT_Net->tft.setScreenShot=active;
}; //Set_setScreenShot     


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Set_drawString(TVT_Net *pVT_Net,QString str,int16_t x, int16_t y,uint8_t tSize){
    if (pVT_Net->ImgMode){
        pVT_Net->ImgTFT.drawString(str,x,y,tSize);
    }else {
        pVT_Net->tft.drawString(str,x,y,tSize);
    }
}; //Set_drawQString     


//------------------------------------------------------------------------------
void Set_drawCentreString(TVT_Net *pVT_Net,QString str,int16_t x, int16_t y,uint8_t tSize){
    if (pVT_Net->ImgMode){
        pVT_Net->ImgTFT.drawCentreString(str,x,y,tSize);
    }else {
        pVT_Net->tft.drawCentreString(str,x,y,tSize);
    }
}; //Set_drawQString     


//------------------------------------------------------------------------------
void Set_drawChar(TVT_Net *pVT_Net,char cc,int16_t x, int16_t y,uint8_t tSize){
    if (pVT_Net->ImgMode){
        pVT_Net->ImgTFT.drawChar(cc,x,y,tSize);
    }else {
        pVT_Net->tft.drawChar(cc,x,y,tSize);
    }
}; //Set_drawChar     


//------------------------------------------------------------------------------
void Set_drawNumber(TVT_Net *pVT_Net,int nn,int16_t x, int16_t y,uint8_t tSize){
    if (pVT_Net->ImgMode){
        pVT_Net->ImgTFT.drawNumber(nn,x,y,tSize);
    }else {
        pVT_Net->tft.drawNumber(nn,x,y,tSize);
    }
}; //Set_drawNumber     


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool Set_smFont(TVT_Net *pVT_Net){
    bool smFont=true;
    //Check SD and SPIFFS for font-data
    if ((!pVT_Net->valid_sd) && (!pVT_Net->valid_sp)){
        smFont=false;
    }
    if (pVT_Net->stream_Font[0][0].getSize()==0) smFont=false;
    //
    return smFont;
}  



//------------------------------------------------------------------------------
uint16_t Set_fontsLoaded(TVT_Net *pVT_Net){
    uint16_t fonts=0;
    //Check SD and SPIFFS for font-data
    if (Set_smFont(pVT_Net)) {
        fonts= pVT_Net->tft.fontsLoaded();
    }
    return fonts;
};//Set_fontsLoaded      


//------------------------------------------------------------------------------
void Set_unloadFont(TVT_Net *pVT_Net){
    //Check SD and SPIFFS for font-data
    if (Set_smFont(pVT_Net)) {
        if (pVT_Net->ImgMode) pVT_Net->ImgTFT.unloadFont();
        pVT_Net->tft.unloadFont();
    }
};//Set_unloadFont      


//------------------------------------------------------------------------------
bool Set_loadFont(TVT_Net *pVT_Net, QString fntName){
    bool valid=false;
    bool psRam=true, TEST=false;
    QString  str=fntName, ss="";
    uint8_t  i=2,j=1,ii=2,jj=1;
    uint32_t lCount=0,nn=0;
    if (TEST) {
        qWarning() << "Set_loadFont=";
    }
    //Check SD and SPIFFS for font-data
    if (!Set_smFont(pVT_Net)) return valid;
    //
    if ((pVT_Net->PSRam) && (psRam)) {
        str.replace("arial","");   j=str.indexOf("-");
        ss=str.mid(0,j); str.remove(0,j+1);
        ss = ss.trimmed();
        str = str.trimmed();
        i=ss.toInt();j=str.toInt();
        valid=((i>=0) && (i<15) && (j>=0) && (j<4));
        if (!valid) {
            i=ii;j=jj;
        }
        lCount=pVT_Net->stream_Font[i][j].available();
        //
        if (pVT_Net->VTPageSelect==0){
            qWarning() << "lCount=" + QString(lCount) + "\t" + fntName;
        }
        valid=(lCount>16);
        //
        if (valid) {
            Set_unloadFont(pVT_Net);
            //
            if (pVT_Net->ImgMode) pVT_Net->ImgTFT.loadFont(pVT_Net->stream_Font[i][j].getBuffer());
            pVT_Net->tft.loadFont(pVT_Net->stream_Font[i][j].getBuffer());
            //
            if (TEST) {
                fntName="arial" + QString(i) + "-" + QString(j);
                qWarning() << "STREAM:valid new loadFont="); qWarning( << fntName;
            }
        }//valid
    }else {
        //Check SPIFFS=flash, fntName="arial2-1";
        //TEST
        //fntName="arial2-1";
        str="/" + fntName + ".vlw";
        //qWarning() << str;
        valid = QFile::exists(":/" + str);
        //
        if (valid){
            if (pVT_Net->VTPageSelect==0){
                qWarning() << "SPIFFS-FONT="); qWarning( << str;
            }
            Set_unloadFont(pVT_Net);
            //
            if (pVT_Net->ImgMode) pVT_Net->ImgTFT.loadFont(fntName,true);
            pVT_Net->tft.loadFont(fntName,true);
            //
            //TEST=true;
            if (TEST) {
                qWarning() << "SPIFFS:valid new loadFont="); qWarning( << fntName;
            }
        }else{
            //SD check
            valid = QFile::exists(":/" + str);
            if (pVT_Net->VTPageSelect==0){
                qWarning() << "SD-FONT=";
                qWarning() << str;
            }
            //
            if (valid){
                Set_unloadFont(pVT_Net);
                //
                if (pVT_Net->ImgMode)
                    pVT_Net->ImgTFT.loadFont(fntName);
                pVT_Net->tft.loadFont(fntName);
                //
                if (TEST) {
                    qWarning() << "SD:valid new loadFont="); qWarning( << fntName;
                }
            }//valid
        }//valid
    }//PSRam
    //
    if ((valid) && (pVT_Net->VTPageSelect==0)) pVT_Net->fntName=fntName;
    //
    return valid;
}; //Set_loadFont     


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Set_setCursor(TVT_Net *pVT_Net,int16_t x,int16_t y){
    if (pVT_Net->ImgMode) {
        pVT_Net->ImgTFT.setCursor(x, y);
    } else {
        pVT_Net->tft.setCursor(x, y);
    }
}; //Set_setCursor     


//------------------------------------------------------------------------------
bool Set_ColorAlpha(TVT_Net *pVT_Net,TVTColorAlpha* pCa,uint8_t cIdx){
    TVTColorAlpha ca=getColorIndex(cIdx,pVT_Net);
    pCa->color=ca.color; pCa->alpha=ca.alpha;
    //check object type for transparency
    return ((pVT_Net->VTObjType>4) && (ca.alpha<0xFF));
};  //Set_ColorAlpha    


//------------------------------------------------------------------------------
void Set_drawGlyph(TVT_Net *pVT_Net,uint16_t un){
    TVTColorAlpha ca;
    bool Set_Alpha=Set_ColorAlpha(pVT_Net,&ca,pVT_Net->color);
    if (Set_Alpha) Set_alpha(pVT_Net,ca.alpha);
    //
    if (pVT_Net->ImgMode) {
        pVT_Net->ImgTFT.drawGlyph(un);
    } else {
        pVT_Net->tft.drawGlyph(un);
    }
    Set_alpha(pVT_Net,0xFF);
};//Set_drawGlyph      


//------------------------------------------------------------------------------
void Set_frameViewport(TVT_Net *pVT_Net,uint8_t cIdx,int16_t sel){
    TVTColorAlpha ca;
    bool Set_Alpha=Set_ColorAlpha(pVT_Net,&ca,cIdx);
    if (pVT_Net->ImgMode) {
        pVT_Net->ImgTFT.frameViewport(ca.color, sel);
    } else {
        pVT_Net->tft.frameViewport(ca.color, sel);
    }
};//Set_frameViewport      


//------------------------------------------------------------------------------
void Set_setViewport(TVT_Net *pVT_Net,int16_t x, int16_t y, uint16_t w, uint16_t h){
    if (pVT_Net->ImgMode) {
        pVT_Net->ImgTFT.setViewport(x, y, w, h, false);
    }else {
        pVT_Net->tft.setViewport(x, y, w, h, false);
    }
}; //Set_setViewport  


//------------------------------------------------------------------------------
void Set_resetViewport(TVT_Net *pVT_Net){
    if (pVT_Net->ImgMode) {
        pVT_Net->ImgTFT.resetViewport();
    }else {
        pVT_Net->tft.resetViewport();
    }
}; //Set_resetViewport  


//------------------------------------------------------------------------------
void Set_drawRect(TVT_Net *pVT_Net,int16_t x, int16_t y, uint16_t w, uint16_t h, uint8_t cIdx){
    TVTColorAlpha ca;
    bool Set_Alpha=Set_ColorAlpha(pVT_Net,&ca,cIdx);
    if (Set_Alpha){
        Set_drawWideLine(pVT_Net,x+1,y+1,x+w,y+1,1,cIdx);
        Set_drawWideLine(pVT_Net,x+w,y+1,x+w,y+h,1,cIdx);
        Set_drawWideLine(pVT_Net,x+w-1,y+h-1,x+1,y+h-1,1,cIdx);
        Set_drawWideLine(pVT_Net,x+1,y+h-1,x+1,y+1,1,cIdx);
    }else {
        if (pVT_Net->ImgMode) {
            pVT_Net->ImgTFT.drawRect(x,y,w,h,ca.color);
        }else {
            pVT_Net->tft.drawRect(x,y,w,h,ca.color);
        }
    }
};//Set_drawRect



//------------------------------------------------------------------------------
void Set_drawRoundRect(TVT_Net *pVT_Net,int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t r, uint16_t color){
    if (pVT_Net->ImgMode) {
        pVT_Net->ImgTFT.drawRoundRect(x,y,w,h,r,color);
    }else {
        pVT_Net->tft.drawRoundRect(x,y,w,h,r,color);
    }
};//Set_drawRoundRect


//------------------------------------------------------------------------------
void Set_fillRect(TVT_Net *pVT_Net,int16_t x, int16_t y, uint16_t w, uint16_t h, uint8_t cIdx)
{
    uint16_t cc=0,rc=0;
    TVTColorAlpha ca;
    bool Set_Alpha=Set_ColorAlpha(pVT_Net,&ca,cIdx);
    if (Set_Alpha) {
        Set_alpha(pVT_Net,ca.alpha);Set_alphaColor(pVT_Net,ca.color);
        Set_setTransp(pVT_Net,false);
        for (int i=0;i<h;i++){
            Set_pushImageAlpha(pVT_Net,x,y+i,w,1,NULL,NULL,ca.color);
        }
        Set_alpha(pVT_Net,0xFF);Set_alphaColor(pVT_Net,0xFFFF);
        Set_setTransp(pVT_Net,false);
    } else {
        if (pVT_Net->ImgMode) {
            pVT_Net->ImgTFT.fillRect(x,y,w,h,ca.color);
        }else {
            pVT_Net->tft.fillRect(x,y,w,h,ca.color);
        }
    }
};//Set_fillRect



//------------------------------------------------------------------------------
void Set_drawLine(TVT_Net *pVT_Net,int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t cIdx){
    TVTColorAlpha ca;
    bool Set_Alpha=Set_ColorAlpha(pVT_Net,&ca,cIdx);
    if (Set_Alpha){
        Set_drawWideLine(pVT_Net,x0, y0, x1, y1, 1,cIdx);
    }else {
        if (pVT_Net->ImgMode) {
            pVT_Net->ImgTFT.drawLine(x0, y0, x1, y1, ca.color);
        }else {
            pVT_Net->tft.drawLine(x0, y0,x1, y1, ca.color);
        }
    }
};//Set_drawLine

//------------------------------------------------------------------------------
void Set_fillTriangle(TVT_Net *pVT_Net,int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t cIdx){
    TVTColorAlpha ca;
    bool Set_Alpha=Set_ColorAlpha(pVT_Net,&ca,cIdx);
    int16_t x=pVT_Net->x,y=pVT_Net->y;
    TVTPoints points[3];
    //
    points[0].pointX=x0-x;points[0].pointY=y0-y;
    points[1].pointX=x1-x;points[1].pointY=y1-y;
    points[2].pointX=x2-x;points[2].pointY=y2-y;
    //
    if ((Set_Alpha) || (pVT_Net->VTFillAttribute<0xFFFF)) {
        Set_fillPolygon(pVT_Net,points,3,cIdx);
    }else {
        if (pVT_Net->ImgMode) {
            pVT_Net->ImgTFT.fillTriangle(x0, y0, x1, y1, x2, y2, ca.color);
        }else {
            pVT_Net->tft.fillTriangle(x0, y0, x1, y1, x2, y2, ca.color);
        }
    }
};//Set_fillTriangle

//------------------------------------------------------------------------------
void Set_drawTriangle(TVT_Net *pVT_Net,int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t cIdx){
    TVTColorAlpha ca;
    bool Set_Alpha=Set_ColorAlpha(pVT_Net,&ca,cIdx);
    if (Set_Alpha){
        Set_drawWideLine(pVT_Net,x0,y0,x1,y1,1,cIdx);
        Set_drawWideLine(pVT_Net,x1,y1,x2,y2,1,cIdx);
        Set_drawWideLine(pVT_Net,x2,y2,x0,y0,1,cIdx);
    }else {
        if (pVT_Net->ImgMode)  {
            pVT_Net->ImgTFT.drawTriangle(x0, y0, x1, y1, x2, y2, ca.color);
        }else{
            pVT_Net->tft.drawTriangle(x0, y0, x1, y1, x2, y2, ca.color);
        }
    }
};//Set_drawTriangle


//------------------------------------------------------------------------------
void Set_drawPixel(TVT_Net *pVT_Net,int16_t x0, int16_t y0, uint8_t cIdx){
    TVTColorAlpha ca;
    bool Set_Alpha=Set_ColorAlpha(pVT_Net,&ca,cIdx);
    if (pVT_Net->ImgMode) {
        if (Set_Alpha) {
            Set_alpha(pVT_Net,ca.alpha);
            Set_alphaColor(pVT_Net,ca.color);
            Set_setTransp(pVT_Net,false);
            pVT_Net->ImgTFT.pushImageAlpha(x0, y0, 1,1,NULL,NULL,ca.color);
            Set_alpha(pVT_Net,0xFF);
            Set_alphaColor(pVT_Net,0xFFFF);
            Set_setTransp(pVT_Net,false);
        }else {
            pVT_Net->ImgTFT.drawPixel(x0, y0, ca.color);
        }
    }else {
        if (Set_Alpha) {
            pVT_Net->tft.drawPixel(x0, y0, ca.color,ca.alpha);
        }else {
            pVT_Net->tft.drawPixel(x0, y0, ca.color);
        }
    }
};//Set_drawPixel




//------------------------------------------------------------------------------
uint16_t Set_readPixel(TVT_Net *pVT_Net,int16_t x0, int16_t y0){
    uint16_t color=0;
    if (pVT_Net->ImgMode) {
        color=pVT_Net->ImgTFT.readPixel(x0, y0);
    }else {
        color=pVT_Net->tft.readPixel(x0, y0);
    }
    return color;
};//Set_readPixel



//------------------------------------------------------------------------------
void Set_setSwapBytes(TVT_Net *pVT_Net,bool swap){
    uint16_t color=0;
    if (pVT_Net->ImgMode) {
        pVT_Net->ImgTFT.setSwapBytes(swap);
    }else {
        pVT_Net->tft.setSwapBytes(swap);
    }
};//Set_setSwapBytes

//------------------------------------------------------------------------------
bool Set_getSwapBytes(TVT_Net *pVT_Net){
    uint16_t color=0;
    if (pVT_Net->ImgMode) {
        return pVT_Net->ImgTFT.getSwapBytes();
    }else {
        return pVT_Net->tft.getSwapBytes();
    }
};//Set_getSwapBytes



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Set_pushImageAlpha(TVT_Net *pVT_Net,int32_t x,int32_t y,int32_t w,int32_t h,uint16_t* tft_buffer,uint8_t* tft_alpha,uint16_t color){
    if (pVT_Net->ImgMode) {
        pVT_Net->ImgTFT.pushImageAlpha(x,y,w,h,(uint16_t*) tft_buffer,(uint8_t*) tft_alpha,color);
    }else {
        color=color<<8 | color>>8;
        pVT_Net->tft.pushImageAlpha(x,y,w,h,(uint16_t*) tft_buffer,(uint8_t*) tft_alpha,color);
    }
};//Set_pushImageAlpha




//==============================================================================
// Draw a circular or elliptical arc with a defined thickness
//==============================================================================
#define DEG2RAD 0.0174532925
//==============================================================================
void getEllipseAngleLength(double _angle,int16_t rx,int16_t ry, int16_t *rxx,int16_t *ryy,double *sx,double *sy){
    double erg=1.000*_angle * DEG2RAD;
    *sx = cos(erg);
    *sy = sin(erg);
    erg=sqrt(sq(ry*(*sx)) + sq(rx*(*sy)));
    if (erg>0) {
        *rxx=round((rx*ry)/erg);
        *ryy=*rxx;
    }
};//getEllipseAngleLength



//==============================================================================
// x,y == coords of centre of arc
// start_angle = 0 - 359
// seg_count = number of 6 degree segments to draw (60 => 360 degree arc)
// rx = x axis outer radius
// ry = y axis outer radius
// w  = width (thickness) of arc in pixels
// colour = 16 bit colour value
// Note if rx and ry are the same then an arc of a circle is drawn
//==============================================================================
// Draw segments every 3 degrees, increase to 6 for segmented ring
TVT_StartEndPoint drawArcTicks(TVT_Net *pVT_Net,int16_t start_angle, int16_t end_angle, int8_t dw, uint8_t cIdx){
    pVT_Net->arcSeg=2;
    double sumDst=0.000, wj=0.000 ,sx=0.000,sy=0.000,sx2=0.000,sy2=0.000;
    double seg = pVT_Net->arcSeg,inc=seg,seg_count=0.000; // Segments are 3 degrees wide = 120 segments for 360 degrees,default=6
    uint8_t  lw=pVT_Net->arcTickLength,dwx=dw,dwy=dw;
    int16_t  nTicks=pVT_Net->arcTicks,i=0,k=15;
    bool  setLine=true;
    int16_t rx=(pVT_Net->w)/2, ry=(pVT_Net->h)/2, rxx=rx,ryy=ry;
    int16_t x=(pVT_Net->x)+rx, y=(pVT_Net->y)+ry;
    int16_t xx[3]={x,x,x},yy[3]={y,y,y},xm[4]={x,x,x,x},ym[4]={y,y,y,y};
    int16_t xp[4]={x,x,x,x},yp[4]={y,y,y,y},xs=x,ys=y;
    TVT_StartEndPoint pp;
    //
    /*
 start_angle=2*start_angle;
 end_angle  =2*end_angle;
 qWarning() << start_angle;
 qWarning() << end_angle;
 sx=1.0000*abs(sin(PI*start_angle/180));
 sy=1.0000*abs(sin(PI*end_angle/180));
 qWarning() << QString(sx,3);
 qWarning() << QString(sy,3);
 qWarning() << delm0;
 //
 for (int j=0;j<2;j++){
   setLine=true;
   qWarning() << delm0;
   qWarning() << j;
   //
   if (j>0) {
      if (dw>rx) dw=rx;
      if (dw>ry) dw=ry;
      rxx=rx-dw; ryy=ry-dw;
   }
   for (int16_t i=0;i<=rxx;i++) {
    yy[1]=yy[2];
    wj=1.000*sq(i)/sq(rxx);
    wj=1.000-wj;
    wj=1.000*wj*sq(ryy);
    wj=1.000*sqrt(wj);
    yy[2]=round(abs(wj));
    //
     if (i>0){
      xx[1]=i-1;xx[2]=i;
      wj=1.000*sqrt((sq(xx[1]) + sq(yy[1])));
      wj=1.000*yy[2]/wj;

      qWarning() << QString(i) + "\t" +String(wj,3) + "\t" + QString(sx,3) + "\t" + QString(wj>=sx);

      //
       if ((start_angle>=0) && (start_angle<90)) {
         if (wj>=sx)  {
          Set_drawLine(pVT_Net,x+xx[1],y-yy[1],x+xx[2],y-yy[2],cIdx); //q1
          pp.startX[j]=x+xx[2]; pp.startY[j]=y-yy[2];
         }
         //
         //
         if (end_angle>=90) {
           if (end_angle<=180){
             if ((wj>=sy) || (end_angle==180)) {
               Set_drawLine(pVT_Net,x-xx[1],y-yy[1],x-xx[2],y-yy[2],cIdx); //q2
               pp.endX[j]=x-xx[2]; pp.endY[j]=y-yy[2];
             }
           }
         }
         //
         if (end_angle>180){
           Set_drawLine(pVT_Net,x-xx[1],y-yy[1],x-xx[2],y-yy[2],cIdx); //q2
             if (end_angle<270){
               if (wj<=sy) {
                 Set_drawLine(pVT_Net,x-xx[1],y+yy[1],x-xx[2],y+yy[2],cIdx); //q3
               } else {
                pp.endX[j]=x-xx[1]; pp.endY[j]=y+yy[1];
               }
             }
         }

         if (end_angle>=270) {
           Set_drawLine(pVT_Net,x-xx[1],y+yy[1],x-xx[2],y+yy[2],cIdx); //q3
             if  (end_angle<360) {
               if (wj>=sy) {
                Set_drawLine(pVT_Net,x+xx[1],y+yy[1],x+xx[2],y+yy[2],cIdx); //q4
                pp.endX[j]=x+xx[2]; pp.endY[j]=y+yy[2];
               }
             }
         }
         //
       }//start_angle1
       //
     }//i>0
   }//for i
   //
 }//for j

Set_drawLine(pVT_Net,pp.startX[0],pp.startY[0],pp.startX[1],pp.startY[1],cIdx);
Set_drawLine(pVT_Net,pp.endX[0]  ,pp.endY[0]  ,pp.endX[1]  ,pp.endY[1]  ,cIdx);

return pp;
*/

    if ((dw>=rx) || (dw>=ry)) {
        dwx=rx; dwy=ry;
    }
    //
    if (seg>0) {
        seg_count=360/seg;
        start_angle=2*start_angle;end_angle=2*end_angle;
        //
        if (start_angle!=end_angle){
            if (start_angle>end_angle) {
                if (nTicks>0){
                    if (nTicks==1) nTicks=3;
                    seg_count=nTicks-1;
                    seg=1.000*abs(end_angle+360-start_angle)/seg_count;
                    inc=seg;
                } else {
                    seg_count=1.000*abs(end_angle+360-start_angle)/seg;
                }
            }else {
                if (nTicks>0){
                    if (nTicks==1) nTicks=3;
                    seg_count=nTicks-1;
                    seg=1.000*abs(end_angle-start_angle)/seg_count;
                    inc=seg;
                } else {
                    seg_count=1.000*abs(end_angle-start_angle)/seg;
                }
            }
        } else {
            if (nTicks>0){
                if (nTicks==1) nTicks=3;
                seg_count=nTicks-1;
                seg=1.000*360/seg_count;
                inc=seg;
            } else {
                seg_count=1.000*360/seg;
            }
        }
        //
        start_angle=360-start_angle;
        // Calculate first pair of coordinates for segment start
        getEllipseAngleLength(start_angle,rx,ry,&rxx,&ryy,&sx,&sy);
        //
        xp[0] = round(1.000*(sx * (rxx - dwx) + x));
        yp[0] = round(1.000*(sy * (ryy - dwy) + y));
        xp[1] = round(1.000*(sx * rxx + x));
        yp[1] = round(1.000*(sy * ryy + y));

        xp[2] = xp[0];
        yp[2] = yp[0];
        xp[3] = xp[1];
        yp[3] = yp[1];
        //
        wj=1.000*start_angle;
        // Calculate last pair of coordinates for segment end,SectionClose
        if (pVT_Net->VTEllipseType==3){
            for (i = start_angle; i<start_angle + seg * seg_count; i += inc) {
                if (wj-seg<0) wj=1.000*(360 + (wj-seg)); else  wj=1.000*(wj-seg);
            }//for i
        }
        //
        getEllipseAngleLength(wj,rx,ry,&rxx,&ryy,&sx2,&sy2);
        //
        xm[0] = round(1.000*(sx2 * ((rxx-lw) - dwx) + x));
        ym[0] = round(1.000*(sy2 * ((ryy-lw) - dwy) + y));
        xm[1] = round(1.000*(sx2 * (rxx-lw) + x));
        ym[1] = round(1.000*(sy2 * (ryy-lw) + y));

        xm[2] = xm[0];
        ym[2] = ym[0];
        xm[3] = xm[1];
        ym[3] = ym[1];
        //
        xs=xp[3]+(xm[3]-xp[3])/2;
        ys=yp[3]+(ym[3]-yp[3])/2;
        //TEST
        //int16_t xs=x, ys=y0;
        //Set_drawTriangle(pVT_Net,xp[0], yp[0], x, y, xm[0], ym[0], cIdx);

        //
        wj=1.000*start_angle;
        //set check lineArt
        if (pVT_Net->lineArt<0xFFFF) {
            setLine=(((pVT_Net->lineArt>>k) & 0x01)>0);
        }
        //
        //
        // Draw colour blocks every inc degrees
        for (i = start_angle; i<start_angle + seg * seg_count; i += inc) {
            if (wj-seg<0) wj=1.000*(360 + (wj-seg)); else  wj=1.000*(wj-seg);
            //
            getEllipseAngleLength(wj,rx,ry,&rxx,&ryy,&sx2,&sy2);
            //
            xp[2] = round(1.000*(sx2 * (rxx - dwx) + x));
            yp[2] = round(1.000*(sy2 * (ryy - dwy) + y));
            xp[3] = round(1.000*(sx2 * rxx + x));
            yp[3] = round(1.000*(sy2 * ryy + y));
            //
            xm[2] = round(1.000*(sx2 * (rxx-lw - dwx) + x));
            ym[2] = round(1.000*(sy2 * (ryy-lw - dwy) + y));
            xm[3] = round(1.000*(sx2 * (rxx-lw) + x));
            ym[3] = round(1.000*(sy2 * (ryy-lw) + y));
            //
            xx[1]=xp[1];yy[1]=yp[1];xx[2]=xp[2];yy[2]=yp[2];
            //Ellipse fillMode
            if (pVT_Net->VTFillMode) {
                xx[1]=x;yy[1]=y;xx[2]=xx[1];yy[2]=yy[1];
                if (pVT_Net->VTEllipseType==3) {
                    xx[1]=xs;yy[1]=ys; xx[2]=xx[1];yy[2]=yy[1];
                }
            }
            //not arcValue
            if (!pVT_Net->arcValue) {
                //paint arc
                if (nTicks>0) {
                    Set_drawLine(pVT_Net,xm[0],ym[0],xp[0],yp[0],cIdx);
                    nTicks--;
                } else {
                    //
                    if (setLine){
                        if (!pVT_Net->VTFillMode) Set_fillTriangle(pVT_Net,xp[0], yp[0], xx[1], yy[1], xp[2], yp[2], cIdx);
                        Set_fillTriangle(pVT_Net,xp[1], yp[1], xx[2], yy[2], xp[3], yp[3], cIdx);

                        //TEST
                        //Set_drawTriangle(pVT_Net,xp[0], yp[0], xx[1], yy[1], xp[2], yp[2], cIdx);
                        //Set_drawTriangle(pVT_Net,xp[1], yp[1], xx[2], yy[2], xp[3], yp[3], cIdx);
                    } //setLine
                    //
                    //set lineArt
                    if (pVT_Net->lineArt<0xFFFF) {
                        //outer line distance
                        //TEST
                        //Set_drawLine(pVT_Net,xp[1], yp[1], xp[3], yp[3], TFT_RED);
                        sumDst=sumDst + sqrt(sq(xp[3]-xp[1]) + sq(yp[3]-yp[1]));
                        //compare lineWidth
                        if (sumDst>=dw) {
                            sumDst=0.000;k--;
                            if (k<0) k=15;
                            setLine=(((pVT_Net->lineArt>>k) & 0x01)>0);
                        }//sumDst
                        //
                    }//lineArt
                }//nTicks
            }//not arcValue
            //
            if (i==start_angle) {
                pp.startXX=xp[0];   pp.startYY=yp[0];
                pp.startX[0]=xp[0]; pp.startY[0]=yp[0];
                pp.startX[1]=xx[1]; pp.startY[1]=yy[1];
                pp.startX[2]=xp[2]; pp.startY[2]=yp[2];
                pp.startX[3]=xp[3]; pp.startY[3]=yp[3];
            }
            //
            pp.endXX=xp[2];      pp.endYY=yp[2];
            pp.endX[0]=xp[0]; pp.endY[0]=yp[0];
            pp.endX[1]=xp[1]; pp.endY[1]=yp[1];
            pp.endX[2]=xx[2]; pp.endY[2]=yy[2];
            pp.endX[3]=xp[3]; pp.endY[3]=yp[3];
            //
            // Copy segment end to sgement start for next segment
            xp[0] = xp[2];
            yp[0] = yp[2];
            xp[1] = xp[3];
            yp[1] = yp[3];
            //
            xm[0] = xm[2];
            ym[0] = ym[2];
            xm[1] = xm[3];
            ym[1] = ym[3];
        }//for i
        //
        //pVT_Net->arcTicks
        if ((nTicks>0) && (!pVT_Net->arcValue)) {
            Set_drawLine(pVT_Net,xm[2],ym[2],pp.endXX,pp.endYY,cIdx);
            nTicks--;
        }
    } //valid
    return pp;
};//drawArcTicks


//==============================================================================
//==============================================================================
bool getStreamHEX(LoopbackStream *pStream,TVT_Net *pVT_Net) {
    bool valid=(pStream!=NULL);
    uint32_t vSize=0;
    if (valid){
        qWarning() << "STREAM RESULT:";
        vSize=pStream->available();
        if (vSize>0){
            uint8_t* buff=pStream->getBuffer();
            //
            for (uint32_t i=0; i<vSize;i++) {
                if ((i>0) && (i % 16==0)) qWarning() << "";
                qWarning() << getStringHEX(buff[i],2) + "|";
            }
            //
            qWarning() << "";
            valid=(pStream->available());
        }
    } //valid
    //
    return valid;
};//getStreamHEX


//------------------------------------------------------------------------------
void getStreamStrInfo(TVT_Net *pVT_Net,uint32_t dCount,bool last) {
    uint32_t lCount=pVT_Net->streamStr.available(),aCount=lCount, k=0;
    uint8_t  cc=0;
    uint8_t* buff=pVT_Net->streamStr.getBuffer();
    if ((dCount>0) and (dCount<=lCount)) lCount=dCount;
    //
    if (lCount>0){
        qWarning() << delm0;
        while(k<lCount){
            cc=buff[k];
            qWarning() << getStringHEX(cc,2) + "|";
            k++;
            if ((k>0) && (k % 16==0)) qWarning() << "";
        }//while k
        if (k % 16>0) qWarning() << "";
        //
        qWarning() << delm0;
    }//lCount>0
    //
    lCount=aCount;

    if ((last) && (lCount>=2*dCount))  {
        k=lCount-dCount;
        qWarning() << delm0;
        qWarning() << "lCount=" + QString(lCount);
        qWarning() << "dCount=" + QString(dCount);
        qWarning() << "StartIndex=" + QString(k);
        //
        while(k<lCount){
            cc=buff[k];
            qWarning() << getStringHEX(cc,2) + "|";
            k++;
            if ((k>0) && (k % 16==0)) qWarning() << "";
        }//while k
        //
        if (k % 16>0) qWarning() << "";
        //
        qWarning() << delm0;
    }
};//getStreamStrInfo

//------------------------------------------------------------------------------
void getStreamDrawInfo(TVT_Net *pVT_Net,uint32_t dCount) {
    uint32_t lCount=pVT_Net->streamDraw.available(),k=0;
    uint8_t  cc=0;
    uint8_t* buff=pVT_Net->streamDraw.getBuffer();
    if ((dCount>0) and (dCount<=lCount)) lCount=dCount;
    //
    if (lCount>0){
        qWarning() << delm0;
        while(k<lCount){
            cc=buff[k];
            qWarning() << getStringHEX(cc,2) + "|";
            k++;
            if ((k>0) && (k % 16==0)) qWarning() << "";
        }//while k
        if (k % 16>0) qWarning() << "";
        //
        qWarning() << delm0;
    }//lCount>0
};//getDrawStrInfo


//------------------------------------------------------------------------------
bool getStreamInfo(LoopbackStream *pStream,TVT_Net *pVT_Net) {
    bool  valid=pStream!=NULL;
    uint32_t vSize=0;
    uint8_t* buff=pStream->getBuffer();
    if (valid) {
        pStream->setPos(0);
        vSize=pStream->available();
        if ((pVT_Net->VT_InfoMode>0) && (vSize>0)){
            qWarning() << "STREAM RESULT:";
            //
            for (uint32_t i=0; i<vSize;i++) {
                if ((i>0) && (i % 16==0)) qWarning() << "";
                qWarning() << getStringHEX(buff[i],2) + "|";
            }//for i
            //
            qWarning() << "");Serial.println("";
                    valid=true;

        } //VT_InfoMode
    }//valid
    //
    return valid;
};//getStreamInfo



//------------------------------------------------------------------------------
QString getStreamTextInfo(LoopbackStream *pStream,TVT_Net *pVT_Net) {
    bool  valid=pStream!=NULL;
    uint32_t vSize=0;
    QString str="";
    uint8_t* buff=pStream->getBuffer();
    if (valid) {
        pStream->setPos(0);
        vSize=pStream->available();
        if (vSize>0){
            qWarning() << "TEXT STREAM RESULT:";
            //
            for (uint32_t i=0; i<vSize;i++) {
                str+=char(buff[i]);
                //qWarning() << char(buff[i]);
            }//for i
            //
            if (pVT_Net->inputLineString.length()==0){
                qWarning() << str;
                qWarning() << "");Serial.println("";
            }
            //
            valid=true;

        } //vSize>0
    }//valid
    //
    return str;
};//getStreamTextInfo



//------------------------------------------------------------------------------
uint16_t getArray8Info(TVT_Net *pVT_Net,uint8_t *ay,uint16_t lCount,bool info) {
    uint16_t k=0,un=0;
    uint8_t cc=0;
    if ((ay!=NULL) && (lCount>0)){
        if (info) qWarning() << delm0;
        //
        while(k<lCount){
            cc=ay[k];
            if (k<2) un+=cc<<8*k;
            //
            if (info) qWarning() << getStringHEX(cc,2) + "|";
            k++;
            if ((info) && (k>0) && (k % 16==0)) qWarning() << "";
        }//while k
        //
        if ((info) && (k % 16!=0)) qWarning() << "";
        if (info) qWarning() << delm0;
    }//lCount>0
    //
    return un;
};//getArray8Info



//------------------------------------------------------------------------------
void getArray16Info(TVT_Net *pVT_Net,uint16_t *ay,uint16_t lCount) {
    uint16_t k=0;
    uint16_t cc=0;
    if ((ay!=NULL) && (lCount>0)){
        qWarning() << delm0;
        while(k<lCount){
            cc=ay[k];
            qWarning() << getStringHEX(cc,4) + "|";
            k++;
            if ((k>0) && (k % 8==0)) qWarning() << "";
        }//while k
        //
        if (k % 8!=0) qWarning() << "";
        qWarning() << delm0;
    }//lCount>0
};//getArray16Info


//------------------------------------------------------------------------------
void getArray32Info(TVT_Net *pVT_Net,uint32_t *ay,uint16_t lCount) {
    uint16_t k=0;
    uint32_t cc=0;
    if ((ay!=NULL) && (lCount>0)){
        qWarning() << delm0;
        while (k<lCount){
            cc=ay[k];
            qWarning() << getStringHEX(cc,8) + "|";
            k++;
            if ((k>0) && (k % 4==0)) qWarning() << "";
        }//while k
        if (k % 4!=0) qWarning() << "";
        //
        qWarning() << delm0;
    }//lCount>0
};//getArray32Info


//------------------------------------------------------------------------------
void getAIDInfo(TVT_Net *pVT_Net) {
    uint32_t ww=0;
    uint8_t  k=0,bb=0,len=0;
    QString   str="",ss="";
    if (pVT_Net->VT_AID_Nr>0){
        qWarning() << delm0;
        for (k=0;k<pVT_Net->VT_AID_Nr;k++){
            bb=pVT_Net->VTAttrAID[k].nameAID.length();
            if (bb>len) len=bb;
        }//for k
        //
        for (k=0;k<pVT_Net->VT_AID_Nr;k++){
            str=QString(k) + " ";
            if (str.length()<3) str="0"+ str;
            ss=String(pVT_Net->VTAttrAID[k].numAID);
            if (ss.length()<2) ss="0"+ ss;

            str+="numAID="  + ss + " ";
            str+="byteAID=" + QString(pVT_Net->VTAttrAID[k].byteAID)+ " ";
            str+="typeAID=" + QString(pVT_Net->VTAttrAID[k].typeAID)+ " ";
            //
            ss=pVT_Net->VTAttrAID[k].nameAID;
            while (ss.length()<len) ss+=" ";
            str+="nameAID=" + ss + " ";
            //str+="valueAID="+ pVT_Net->VTAttrAID[k].valueAID;
            ww=0; ss="";

            for (int j=0;j<pVT_Net->VTAttrAID[k].valueAID.length();j++){
                bb=char(pVT_Net->VTAttrAID[k].valueAID[j].toLatin1());
                ss+=getStringHEX(bb,2);
                ww+=bb<<8*j;
            }//for j

            str+="valueAID="+ QString(ww) + " [" + ss + "]";
            qWarning() << str;
        }//for k
        //
        qWarning() << delm0;
    }//lCount>0
};//getAIDInfo


//==============================================================================
//VTStatusMessage
//==============================================================================
void setVTStatusMessage(TVT_Net *pVT_Net,CANMsg *pMsg) {
    //qWarning() << QDateTime::currentDateTime().toMSecsSinceEpoch()-pVT_Net->pTime;
    if (QDateTime::currentDateTime().toMSecsSinceEpoch()-pVT_Net->pTime>=3000) {
        qWarning() << "VTStatus="); qWarning() << QDateTime::currentDateTime().toMSecsSinceEpoch(;
                                                  pVT_Net->pTime=QDateTime::currentDateTime().toMSecsSinceEpoch();
        pMsg->ID=VTtoECU_PGN + (ECU_VT_PRIO<<24) + (0xFF<<8) + pVT_Net->VT_SRC;
        pMsg->MSG_TX=1;  pMsg->MSGTYPE=1; pMsg->LEN=8;
        pMsg->DATA[0]=0xFE;
        pMsg->DATA[1]=pVT_Net->VT_ActiveSRC;
        pMsg->DATA[2]=(pVT_Net->VT_ActiveMask>>0) & 0xFF;
        pMsg->DATA[3]=(pVT_Net->VT_ActiveMask>>8) & 0xFF;
        pMsg->DATA[4]=(pVT_Net->VT_ActiveSoftKeyMask>>0) & 0xFF;
        pMsg->DATA[5]=(pVT_Net->VT_ActiveSoftKeyMask>>8) & 0xFF;
        pMsg->DATA[6]=0x00;
        pMsg->DATA[7]=0xFF;
        //
        //VT_CAN_MsgSend(pVT_Net,pMsg);
    }
};//setVTStatusMessage    


//==============================================================================
//VTDrawtList
//==============================================================================
void getVTDrawListInfo(TVT_Net *pVT_Net,int16_t objIdx,uint8_t showAttr) {
    uint16_t i=0,objNr=getVTDrawListSize(pVT_Net),aObj=0,eObj=objNr-1;
    if (objNr>0){
        qWarning() << delm1;
        if (objIdx>=0){
            aObj=objIdx; eObj=objIdx;
        }
        //
        for (i=aObj;i<=eObj;i++){
            getVTDrawListInfoPrint(pVT_Net,i,showAttr);
        }//for i
        //
        qWarning() << delm1;
    }//objNr>0
};//getVTDrawListInfo


//==============================================================================
void getVTDrawListInfoPrint(TVT_Net *pVT_Net,int16_t objIdx,uint8_t showAttr) {
    uint16_t objID=0xFFFF, pObjID=0xFFFF, i=0, k=0,objNr=getVTDrawListSize(pVT_Net);
    uint16_t aObj=0,eObj=objNr-1,w=0,h=0;
    int16_t  x=0, y=0,refIdx=-1;
    uint8_t objType=0xFF,level=0,selected=0,kIndex=255;
    uint8_t* buff;
    QString str="",ss="\t";
    if ((objNr>0) && (objIdx>=0) && (objIdx<objNr)){
        getVTDrawListValue(pVT_Net,objIdx);
        //getStreamDrawInfo(pVT_Net);
        buff=pVT_Net->streamDraw.getBuffer();
        objID=buff[k++] + (buff[k++]<<8);   objType=buff[k++];
        x=buff[k++] + (buff[k++]<<8);
        y=buff[k++] + (buff[k++]<<8);
        w=buff[k++] + (buff[k++]<<8);
        h=buff[k++] + (buff[k++]<<8);
        pObjID=buff[k++] + (buff[k++]<<8);
        level   =buff[k++];
        selected=buff[k++];
        kIndex  =buff[k++];
        //
        pVT_Net->VTObjID=objID; pVT_Net->VTObjType=objType; pVT_Net->VTObjName="INFO";
        runClassObj(pVT_Net,NULL,NULL);
        //
        str+=QString(objIdx);
        while (str.length()<3) str="0" +str;
        str+=ss;
        //
        str+=String(pObjID) + "->" + QString(objID);
        //
        while (str.length()<12) str+=" ";
        //
        str+=ss + QString(objType) + ss;
        str+=String(x) + ss + QString(y) + ss + QString(w) + ss +String(h) + ss;
        str+=String(level) + ss + QString(selected) + ss + QString(kIndex) + ss;
        str+=pVT_Net->VTObjName;
        qWarning() << str;
        //
        if (((showAttr & 0x01)>0) || ((showAttr & 0x02)>0)) {
            if ((showAttr & 0x03)>0) getStreamDrawInfo(pVT_Net);
            //
            if (((showAttr & 0x01)>0) || ((showAttr & 0x02)>0)) {
                refIdx=getVTObjID(pVT_Net,objID);
                if (refIdx>=0) getVTObjectListInfo(pVT_Net,refIdx,showAttr);
            }
            qWarning() << delm0;
        }
        //
    }//objNr>0
};//getVTDrawListInfoPrint



//==============================================================================
uint16_t getVTDrawListSize(TVT_Net *pVT_Net) {
    pVT_Net->stream_Draw[pVT_Net->listNr].setPos(0);
    return pVT_Net->stream_Draw[pVT_Net->listNr].available()/16;
};//getVTDrawListSize


//------------------------------------------------------------------------------
uint16_t setVTDrawListClear(TVT_Net *pVT_Net) {
    uint16_t lCount=getVTDrawListSize(pVT_Net);
    getHeapStatus(pVT_Net,54);
    pVT_Net->stream_Draw[pVT_Net->listNr].clear();
    getHeapStatus(pVT_Net,55);
    return lCount;
};//setVTDrawListClear


//------------------------------------------------------------------------------
uint16_t getVTDrawListAdd(TVT_Net *pVT_Net) {
    uint16_t i=getVTDrawListSize(pVT_Net);
    uint16_t lCount=pVT_Net->stream_Draw[pVT_Net->listNr].getBufferSize()/16;
    uint32_t sSize=pVT_Net->streamDraw.available();
    uint16_t objID=0xFFFF;
    uint8_t  objType=0xFF;
    uint8_t* buff=pVT_Net->streamDraw.getBuffer();
    bool TEST=false;
    //getStreamDrawInfo(pVT_Net);
    if (i<lCount){
        //TEST=true;
        if (TEST) {
            objID=buff[0] + (buff[1]<<8);  objType=buff[2];
            qWarning() << i);   Serial.print("\t");Serial.print(objID;
                    qWarning() << "\t");qWarning( << objType;
        }
        //
        pVT_Net->stream_Draw[pVT_Net->listNr].writeBytes((uint8_t*)buff,sSize);
        i=getVTDrawListSize(pVT_Net);
    }
    //
    return i;
};//getVTDrawListAdd


//------------------------------------------------------------------------------
void resetKeyButtonInputList(TVT_Net *pVT_Net) {
#ifdef M5CORE2_MODE
    for (int i=0;i<pVT_Net->butMax;i++) {
        if (pVT_Net->softkey_list[i]!=NULL) {
            pVT_Net->softkey_list[i]->delHandlers();
            delete(pVT_Net->softkey_list[i]); pVT_Net->softkey_list[i]=NULL;
        }
        if (pVT_Net->button_list[i]!=NULL) {
            pVT_Net->button_list[i]->delHandlers();
            delete(pVT_Net->button_list[i]); pVT_Net->button_list[i]=NULL;
        }
        if (pVT_Net->input_list[i]!=NULL) {
            pVT_Net->input_list[i]->delHandlers();
            delete(pVT_Net->input_list[i]); pVT_Net->input_list[i]=NULL;
        }
    }//for i
#endif
}//resetKeyButtonInputList   


//------------------------------------------------------------------------------
QString setVTDrawListSoftKey(TVT_Net *pVT_Net) {
    uint16_t lCount=getVTDrawListSize(pVT_Net),objID=0xFFFF,objType=0xFF,i=0,j=0,k=0,m=0;
    int16_t  xx=0,yy=0,ww=0,hh=0;
    QString str="",ss="";
    bool TEST=false;
    ButtonColors col = {NODRAW, NODRAW, NODRAW};
    //
#ifdef M5CORE2_MODE
    resetKeyButtonInputList(pVT_Net);
#endif
    //
    //
    if (lCount>0){
        for (i=0;i<lCount;i++) {
            getVTDrawListValue(pVT_Net,i); ss="";
            objID=pVT_Net->streamDraw.readBytesVal(2,0);
            objType=pVT_Net->streamDraw.readBytesVal(1,2);
            xx=pVT_Net->streamDraw.readBytesVal(2,3);
            yy=pVT_Net->streamDraw.readBytesVal(2,5);
            ww=pVT_Net->streamDraw.readBytesVal(2,7);
            hh=pVT_Net->streamDraw.readBytesVal(2,9);
            //check KeyObject
            if (objType==5) {
                ss="KEY" + QString(j); str+=String(objID) + ",";
#ifdef M5CORE2_MODE
                if (j<pVT_Net->butMax) pVT_Net->softkey_list[j] = new Button(xx,yy-5,ww,hh,false, ss.constData(),col,col);
#endif
                j++;
            }//objType==5
            //
            //check ButtonObject
            if (objType==6) {
                ss="BUTTON" + QString(k); //str+=String(objID) + ",";
#ifdef M5CORE2_MODE
                if (k<pVT_Net->butMax)pVT_Net->button_list[k] = new Button(xx,yy-5,ww,hh,false, ss.constData(),col,col);
#endif
                k++;
            }//objType==6
            //
            //check InputObject
            if (HasInArray(objType,inpAllObjSet)) {
                ss="INPUT" + QString(m); //str+=String(objID) + ",";
#ifdef M5CORE2_MODE
                if (m<pVT_Net->butMax) pVT_Net->input_list[m] = new Button(xx,yy-1,ww,hh,false, ss.constData(),col,col);
#endif
                m++;
            }//objType==inpAllObjSet
            //
            if (ss.length()>0){
                if (TEST){
                    qWarning() << ss + "\t"); qWarning( << objID;
                            qWarning() << xx;
                    qWarning() << yy;
                    qWarning() << ww;
                    qWarning() << hh;
                    qWarning() << delm0;
                }
            }
        }//for i
    }//lCount>0
    return str;
};//setVTDrawListSoftKey


//------------------------------------------------------------------------------
//14=select 15=keyIndex, last index
bool setVTDrawListClearSelect(TVT_Net *pVT_Net,uint16_t VTObjID) {
    uint16_t lCount=getVTDrawListSize(pVT_Net),objID=0xFFFF,objType=0xFF,i=0;
    if ((lCount>0) && (VTObjID<0xFFFF)){
        for (i=0;i<lCount;i++) {
            getVTDrawListValue(pVT_Net,i);
            objID=pVT_Net->streamDraw.readBytesVal(2,0);
            objType=pVT_Net->streamDraw.readBytesVal(1,2);
            if ((objType==5) || (objType==6) || (HasInArray(objType,inpAllObjSet))) {
                if (objID==VTObjID){
                    pVT_Net->TFT_KeySelectObjID=0xFFFF;    pVT_Net->TFT_KeySelectObjType=0xFF;
                    pVT_Net->TFT_ButtonSelectObjID=0xFFFF; pVT_Net->TFT_ButtonSelectObjType=0xFF;
                    pVT_Net->TFT_InputSelectObjID=0xFFFF;  pVT_Net->TFT_InputSelectObjType=0xFF;
                    pVT_Net->TFT_KeySelectObjID=0xFFFF;    pVT_Net->TFT_KeySelectObjType=0xFF;
                }
            }//objType==5,6,inputs
            //
            //check KeyObject
            if (objType==5) {
                if (objID==VTObjID){
                    pVT_Net->TFT_KeySelectObjID=objID;     pVT_Net->TFT_KeySelectObjType=objType;
                }
            }//objType==5
            //
            if (objType==6) {
                if (objID==VTObjID) {
                    pVT_Net->TFT_ButtonSelectObjID=objID; pVT_Net->TFT_ButtonSelectObjType=objType;
                }
            }//objType==6
            //
            if (HasInArray(objType,inpAllObjSet)) {
                if (objID==VTObjID) {
                    pVT_Net->TFT_InputSelectObjID=objID;  pVT_Net->TFT_InputSelectObjType=objType;
                }
            }//objType==inpAllObjSet
        }//for i
    }//lCount>0
    return (lCount>0);
};//setVTDrawListClearSelect


//------------------------------------------------------------------------------
void getVTDrawListRemove(TVT_Net *pVT_Net,int16_t objIdx) {
    uint16_t lCount=getVTDrawListSize(pVT_Net);
    uint32_t pPos0=0,pPos1=0,len=0,sSize=0;
    uint8_t* buff=pVT_Net->stream_Draw[pVT_Net->listNr].getBuffer();
    if ((objIdx>=0) && (objIdx < lCount)) {
        pPos0=16*objIdx;  pPos1=16*(objIdx+1);
        len=lCount-pPos1;
        sSize=pVT_Net->stream_Draw[pVT_Net->listNr].getSize();
        if (len>=16){
            pVT_Net->stream_Draw[pVT_Net->listNr].writeBytes((uint8_t*) buff,len,pPos0,pPos1);
        }
        pVT_Net->stream_Draw[pVT_Net->listNr].setPos(0);
        pVT_Net->stream_Draw[pVT_Net->listNr].setSize(sSize-16);
    }
};//getVTDrawListRemove



//------------------------------------------------------------------------------
void setVTDrawListValue(TVT_Net *pVT_Net,int16_t idx) {
    uint16_t lCount=getVTDrawListSize(pVT_Net);
    int16_t  pPos=-1;
    uint8_t* buff=pVT_Net->streamDraw.getBuffer();
    if ((idx>=0) && (idx<lCount)) pPos=16*idx;
    pVT_Net->stream_Draw[pVT_Net->listNr].writeBytes((uint8_t*) buff,16,pPos);
};//setVTDrawListValue


//------------------------------------------------------------------------------
void getVTDrawListValue(TVT_Net *pVT_Net,uint16_t idx) {
    uint16_t lCount=getVTDrawListSize(pVT_Net);
    uint8_t* buffDraw=pVT_Net->stream_Draw[pVT_Net->listNr].getBuffer();
    uint32_t pPos=0;
    pVT_Net->streamDraw.clear();
    if ((idx>=0) && (idx < lCount)) {
        pPos=16*idx;
        pVT_Net->streamDraw.writeBytes((uint8_t*)buffDraw,16,-1,pPos);
    }
};//getVTDrawListValue




//------------------------------------------------------------------------------
int16_t getVTDrawID(TVT_Net *pVT_Net, uint16_t objID,bool typeMode) {
    uint16_t lCount=getVTDrawListSize(pVT_Net);
    uint16_t i=0,oID=0xFFFF;
    uint32_t p=0;
    int16_t  objIdx=-1;
    uint8_t* buff;
    uint8_t  oType=0xFF,keyNr=255,len=0;
    if (lCount>0) {
        for (i=0;i<lCount;i++) {
            getVTDrawListValue(pVT_Net,i); len=pVT_Net->streamDraw.available();
            buff=pVT_Net->streamDraw.getBuffer();
            oID=buff[0] + (buff[1]<<8);  oType=buff[2]; keyNr=buff[len-1];
            //
            if (typeMode) p=(oType==objID); else p=(oID==objID);
            //
            if (p) {
                pVT_Net->VTObjID=oID;pVT_Net->VTObjType=oType;
                pVT_Net->TFT_SelectNr=keyNr;
                objIdx=i;break;
            }
        }//for i
    }//lCount
    return objIdx;
};//getVTDrawID



//------------------------------------------------------------------------------
int16_t getVTDrawSelect(TVT_Net *pVT_Net, uint8_t keyNr,uint8_t selObjType) {
    uint16_t lCount=getVTDrawListSize(pVT_Net),objID=0xFFFF,len=0,i=0;
    bool  selFound=false;
    int16_t  objIdx = -1;
    uint8_t  cc=0,objType=0xFF,keyIdx=0xFF;
    uint8_t* buff;
    if ((lCount>0) && (keyNr>=0) && (keyNr < 0xFF)) {
        for (i = 0; i<lCount; i++) {
            getVTDrawListValue(pVT_Net,i); len=pVT_Net->streamDraw.available();
            buff=pVT_Net->streamDraw.getBuffer();
            objID=buff[0] + (buff[1]<<8);  objType=buff[2];
            keyIdx=buff[len-1];
            if (selObjType==7) {
                selFound=HasInArray(objType,inpAllObjSet);
            } else selFound=(objType == selObjType);
            //
            if ((selFound) && (keyNr==keyIdx)) {
                objIdx = i;
                pVT_Net->VTObjID=objID;  pVT_Net->VTObjType=objType;
                pVT_Net->TFT_SelectNr=keyNr;
                break;
            }
        }//for i
    }//>0
    return objIdx;
};//getVTDrawSelect


//==============================================================================
//VTObjectList
//==============================================================================
void getVTObjectListInfo(TVT_Net *pVT_Net,int16_t objIdx,uint8_t showAttr) {
    uint16_t lCount=getVTObjectListSize(pVT_Net);
    uint16_t i=0,aObj=0,eObj=lCount-1;
    if (lCount>0){
        if (objIdx>=0){
            aObj=objIdx; eObj=objIdx;
        }
        for (i=aObj;i<=eObj;i++){
            getVTObjectListValue(pVT_Net,i);
            if (pVT_Net->streamStr.available()<3) break;
            //
            pVT_Net->objNr=i;pVT_Net->VTObjName="INFO";
            runClassObj(pVT_Net,NULL,NULL);
            qWarning() << QString(i) + "->" + QString(pVT_Net->VTObjID) + "," + QString(pVT_Net->VTObjType) + "," + pVT_Net->VTObjName;
            //
            if ((showAttr & 0x02)>0) getAIDInfo(pVT_Net);
            if ((showAttr & 0x04)>0) getStreamStrInfo(pVT_Net);
            //
            qWarning() << delm0;
        }//for i
        //
        if ((showAttr & 0x08)>0) getStreamHEX(&pVT_Net->stream_Pool[pVT_Net->listNr],pVT_Net);
        if ((showAttr & 0x10)>0) getStreamHEX(&pVT_Net->streamObj[pVT_Net->listNr],pVT_Net);
        //
        qWarning() << delm1;
    }
};//getVTObjectListInfo


//------------------------------------------------------------------------------
uint16_t getVTObjectListSize(TVT_Net *pVT_Net) {
    pVT_Net->stream_Pool[pVT_Net->listNr].setPos(0);
    return pVT_Net->stream_Pool[pVT_Net->listNr].getSize()/7;
};//getVTObjectListSize



//------------------------------------------------------------------------------
uint16_t setVTObjectListClear(TVT_Net *pVT_Net) {
    uint16_t lCount=getVTObjectListSize(pVT_Net);
    getHeapStatus(pVT_Net,50);
    if (lCount>0) {
        pVT_Net->streamStr.clear();
        pVT_Net->streamObj[pVT_Net->listNr].clear();
        pVT_Net->stream_Pool[pVT_Net->listNr].clear();
        //
        setVTAuxAssignListClear(pVT_Net);
    }
    getHeapStatus(pVT_Net,51);
    return lCount;
};//setVTObjectListClear



//------------------------------------------------------------------------------
bool getVTObjectListRemove(TVT_Net *pVT_Net,int16_t objIdx) {
    uint16_t lCount=getVTObjectListSize(pVT_Net);
    uint8_t* buff;
    uint32_t buffSize=0,buffPos0=0,buffPos1=0;
    bool setRemove=false;
    if ((objIdx>=0) && (objIdx < lCount)) {
        /*
   getStreamHEX(&pVT_Net->stream_Pool[pVT_Net->listNr],pVT_Net);
   qWarning() << pVT_Net->streamObj[pVT_Net->listNr].getSize();
   getStreamHEX(&pVT_Net->streamObj[pVT_Net->listNr],pVT_Net);
   */
        buff=pVT_Net->streamObj[pVT_Net->listNr].getBuffer();
        buffSize=pVT_Net->streamObj[pVT_Net->listNr].getSize();
        buffPos0=getVTObjPos(pVT_Net,objIdx);
        buffPos1=getVTObjPos(pVT_Net,objIdx+1);

        pVT_Net->streamObj[pVT_Net->listNr].writeBytes((uint8_t*) buff,buffSize-buffPos1,buffPos0,buffPos1);
        pVT_Net->streamObj[pVT_Net->listNr].setSize(buffSize-(buffPos1-buffPos0));
        /*
   qWarning() << pVT_Net->streamObj[pVT_Net->listNr].getSize();
   getStreamHEX(&pVT_Net->streamObj[pVT_Net->listNr],pVT_Net);
   */
        //
        buff=pVT_Net->stream_Pool[pVT_Net->listNr].getBuffer();
        buffSize=pVT_Net->stream_Pool[pVT_Net->listNr].getSize();
        buffPos0=7*objIdx;
        buffPos1=7*(objIdx+1);
        pVT_Net->stream_Pool[pVT_Net->listNr].writeBytes((uint8_t*) buff,buffSize-buffPos1,buffPos0,buffPos1);
        pVT_Net->stream_Pool[pVT_Net->listNr].setSize(buffSize-(buffPos1-buffPos0));
        //
        //getStreamHEX(&pVT_Net->stream_Pool[pVT_Net->listNr],pVT_Net);
        setRemove=true;
    }
    return setRemove;
};//getVTObjectListRemove


//------------------------------------------------------------------------------
uint16_t getVTObjectListAdd(TVT_Net *pVT_Net) {
    uint32_t pos=0,len=pVT_Net->streamStr.available();
    int16_t objIdx=-1;
    uint8_t* buff=pVT_Net->streamStr.getBuffer();
    bool TEST=false,setRemove=false;
    //check upload mode
    if (pVT_Net->VTUpLoad) objIdx=getVTObjID(pVT_Net,pVT_Net->VTObjID,false,false);
    //Upload
    if (objIdx>=0) {
        setVTObjectListValue(pVT_Net,objIdx);
    } else {
        //
        if (pVT_Net->objNr==0) {
            pVT_Net->stream_Pool[pVT_Net->listNr].clear();
            pVT_Net->streamObj[pVT_Net->listNr].clear();
        }
        //
        pVT_Net->streamObj[pVT_Net->listNr].writeBytes((uint8_t*) buff,len);
        //
        pVT_Net->stream_Pool[pVT_Net->listNr].writeBytes((uint8_t*) buff,3);
        pVT_Net->stream_Pool[pVT_Net->listNr].writeBytesVal(len,4);
        //TEST
        if (TEST){
            qWarning() << "Nr="); Serial.print(pVT_Net->objNr;
                    qWarning() << "\t");  Serial.print(pVT_Net->VTObjID;
                    qWarning() << "\t");  Serial.print(pVT_Net->VTObjType;
                    qWarning() << "\t");  qWarning( << len;
        }
        //
    }
    return pVT_Net->objNr;
    //
};//getVTObjectListAdd



//------------------------------------------------------------------------------
bool setVTObjectListValue(TVT_Net *pVT_Net,int16_t idx) {
    uint16_t lCount=getVTObjectListSize(pVT_Net);
    int16_t  objNr=pVT_Net->objNr;
    uint8_t* buff=pVT_Net->streamStr.getBuffer();
    uint32_t len=pVT_Net->streamStr.available(),pos=0,p=0,len0=len;
    bool setRemove=false;
    if (idx>=0) objNr=idx;
    if ((objNr>=0) && (objNr < lCount)) {
        len0=getVTObjLength(pVT_Net,objNr);
        p=7*objNr; pos=getVTObjPos(pVT_Net,objNr);
        if ((len==len0) || (objNr==lCount-1)) {
            //qWarning() << lCount;
            //qWarning() << objNr;
            //qWarning() << pVT_Net->streamObj[pVT_Net->listNr].getSize();

            //getStreamHEX(&pVT_Net->streamObj[pVT_Net->listNr],pVT_Net);

            pVT_Net->stream_Pool[pVT_Net->listNr].writeBytes((uint8_t*) buff ,3,p);
            pVT_Net->stream_Pool[pVT_Net->listNr].writeBytesVal(len ,4,p+3);


            pVT_Net->streamObj[pVT_Net->listNr].writeBytes((uint8_t*) buff,len,pos);
            if (objNr==lCount-1) pVT_Net->streamObj[pVT_Net->listNr].setSize(pos+len);

            //getStreamHEX(&pVT_Net->streamObj[pVT_Net->listNr],pVT_Net);
            //qWarning() << pVT_Net->streamObj[pVT_Net->listNr].getSize();



        } else {
            setRemove=getVTObjectListRemove(pVT_Net,objNr);
            //pVT_Net->stream_Pool[pVT_Net->listNr]
            lCount=getVTObjectListSize(pVT_Net);
            //qWarning() << lCount;
            //getStreamHEX(&pVT_Net->streamObj[pVT_Net->listNr],pVT_Net);

            pVT_Net->stream_Pool[pVT_Net->listNr].writeBytes((uint8_t*) buff ,3);
            pVT_Net->stream_Pool[pVT_Net->listNr].writeBytesVal(len ,4);
            //getStreamHEX(&pVT_Net->stream_Pool[pVT_Net->listNr],pVT_Net);
            //
            //getStreamStrInfo(pVT_Net);

            pVT_Net->streamObj[pVT_Net->listNr].writeBytes((uint8_t*) buff,len);


            //getStreamHEX(&pVT_Net->streamObj[pVT_Net->listNr],pVT_Net);
        }
    }
    return setRemove;
};//setVTObjectListValue


//------------------------------------------------------------------------------
void getVTObjectListValue(TVT_Net *pVT_Net,uint16_t idx) {
    uint16_t lCount=getVTObjectListSize(pVT_Net);
    uint8_t* buffObj=pVT_Net->streamObj[pVT_Net->listNr].getBuffer();
    uint32_t len=0,pos=0;
    //
    if ((idx>=0) && (idx < lCount)) {
        len=getVTObjLength(pVT_Net,idx); pos=getVTObjPos(pVT_Net,idx);
        //qWarning() << len;
        //qWarning() << pos;
        //
        pVT_Net->streamStr.clear();
        pVT_Net->streamStr.writeBytes((uint8_t*)buffObj,len,-1,pos);
        uint8_t* buff=pVT_Net->streamStr.getBuffer();
        pVT_Net->VTObjID=pVT_Net->streamStr.readBytesVal(2);
        pVT_Net->VTObjType=pVT_Net->streamStr.readBytesVal(1);
        pVT_Net->streamStr.setPos(0);
    }
};//getVTObjectListValue



//------------------------------------------------------------------------------
uint32_t getVTObjLength(TVT_Net *pVT_Net, uint16_t objIdx) {
    uint16_t lCount=getVTObjectListSize(pVT_Net);
    uint16_t i=0,oID=0xFFFF;
    uint32_t len=0,p=0;
    uint8_t* buff=pVT_Net->stream_Pool[pVT_Net->listNr].getBuffer();
    uint8_t  oType=0xFF;
    if (objIdx<lCount) {
        p=7*objIdx;
        oID=buff[p++] + (buff[p++]<<8); oType=buff[p++];
        len=buff[p++] + (buff[p++]<<8) + (buff[p++]<<16) + (buff[p++]<<24);
    }//lCount
    return len;
};//getVTObjLength



//------------------------------------------------------------------------------
uint32_t getVTObjPos(TVT_Net *pVT_Net, uint16_t objIdx) {
    uint16_t lCount=getVTObjectListSize(pVT_Net),i=0;
    uint32_t pos=0;
    if (objIdx<lCount) {
        for (i=0;i<lCount;i++) {
            if (i==objIdx) break;
            pos+=getVTObjLength(pVT_Net,i);
        }
    }//lCount
    return pos;
};//getVTObjPos



//------------------------------------------------------------------------------
int16_t getVTObjID(TVT_Net *pVT_Net, uint16_t objID,bool typeMode,bool setStreamStr) {
    uint16_t lCount=getVTObjectListSize(pVT_Net);
    uint16_t i=0,oID=0xFFFF;
    uint32_t len=0,pos=0,p=0;
    int16_t  objIdx=-1;
    uint8_t* buff=pVT_Net->stream_Pool[pVT_Net->listNr].getBuffer();
    uint8_t* buffObj=pVT_Net->streamObj[pVT_Net->listNr].getBuffer();
    uint8_t  oType=0xFF;
    if (lCount>0) {
        for (i=0;i<lCount;i++) {
            p=7*i;
            oID=buff[p++] + (buff[p++]<<8); oType=buff[p++];
            len=buff[p++] + (buff[p++]<<8) + (buff[p++]<<16) + (buff[p++]<<24);
            //


            if (typeMode) p=(oType==objID); else p=(oID==objID);
            //
            if (p) {
                if (setStreamStr) {
                    pVT_Net->streamStr.clear();
                    pVT_Net->streamStr.writeBytes((uint8_t*) buffObj,len,-1,pos);
                }
                //if (oID==30100){
                //qWarning() << "oType=" + QString(oType);
                //}
                //
                pVT_Net->VTObjID=oID;pVT_Net->VTObjType=oType;
                pVT_Net->VTObjLen=len;pVT_Net->VTObjPos=pos;
                objIdx=i;break;
            }
            pos+=len;
        }//for i
    }//lCount
    return objIdx;
};//getVTObjID


//------------------------------------------------------------------------------
void getVTAuxObjectList(TVT_Net *pVT_Net) {
    uint16_t lCount=getVTObjectListSize(pVT_Net);
    uint16_t i=0,j=0,oID=0xFFFF;
    uint32_t p=0;
    uint8_t* buff;
    uint8_t  oType=0xFF,listNr=pVT_Net->listNr;
    bool  TEST=true;
    pVT_Net->VTAuxFuncList.clear(); pVT_Net->VTAuxInpList.clear();
    //
    for (j=0;j<listMax-1;j++) {
        pVT_Net->listNr=j;
        lCount=getVTObjectListSize(pVT_Net);
        buff=pVT_Net->stream_Pool[pVT_Net->listNr].getBuffer();
        //
        if (lCount>0) {
            for (i=0;i<lCount;i++) {
                p=7*i;
                oID=buff[p++] + (buff[p++]<<8); oType=buff[p++];
                //auxFunc=31
                if (oType==gAuxFuncType) {
                    pVT_Net->VTAuxFuncList+=pVT_Net->VT_DST_WS[pVT_Net->listNr];
                    pVT_Net->VTAuxFuncList+=getStringHEX(oID,4);
                    pVT_Net->VTAuxFuncList+="\n";
                }
                //auxInp=32
                if (oType==gAuxInpType) {
                    pVT_Net->VTAuxInpList+=pVT_Net->VT_DST_WS[pVT_Net->listNr];
                    pVT_Net->VTAuxInpList+=getStringHEX(oID,4);
                    pVT_Net->VTAuxInpList+="\n";
                }
            }//for i
        }//lCount
    }//for j
    //
    if (TEST){
        qWarning() << "pVT_Net->VTAuxFuncList";
        qWarning() << pVT_Net->VTAuxFuncList;
        qWarning() << delm0;
        //
        qWarning() << "pVT_Net->VTAuxInpList";
        qWarning() << pVT_Net->VTAuxInpList;
        qWarning() << delm0;
    }
    pVT_Net->listNr=listNr;

};//getVTAuxObjectList



//==============================================================================
//==============================================================================
TVT_ViewRect getViewRect(TVT_ViewRect *pViewRect) {
    TVT_ViewRect vRect;
    //
    if (pViewRect!=NULL) {
        vRect.viewX = pViewRect->viewX;
        vRect.viewY = pViewRect->viewY;
        vRect.viewW = pViewRect->viewW;
        vRect.viewH = pViewRect->viewH;
    }
    //
    return vRect;
};//getViewRect


//==============================================================================
//==============================================================================
//get WSName from Name 
QString getWSNameFromName(TVT_Net *pVT_Net, QString wsName){
    QString str="",ss="";
    for (int i=0;i<WS_ListCount;i++) {
        ss=pVT_Net->WS_List[i];
        ss.remove(0,3);
        if (ss==wsName) str=ss;
    }
    return str;
};//getWSNameFromName


//==============================================================================
//get WSName from Name 
int8_t getWSlistNrFromName(TVT_Net *pVT_Net, QString wsName){
    int8_t listNr=-1;
    for (int i=0;i<listMax;i++) {
        if (pVT_Net->VT_DST_WS[i]==wsName) listNr=i;
    }//for i
    return listNr;
};//getWSlistNrFromName



//==============================================================================
//get WSName from address 
QString getWSNameFromAddress(TVT_Net *pVT_Net, uint8_t src){
    QString str="",ss="";
    for (int i=0;i<WS_ListCount;i++) {
        ss=pVT_Net->WS_List[i].mid(0,2);
        //qWarning() << ss;
        if (ss==getStringHEX(src,2)){
            str=pVT_Net->WS_List[i];
            str.remove(0,3);
        }
    }
    return str;
};//getWSNameFromAddress


//==============================================================================
void setECUListNumber(TVT_Net *pVT_Net,CANMsg msg) {
    uint8_t ecuAddr=msg.ID & 0xFF;
    for (int i=0; i<2;i++) {
        if (pVT_Net->VT_DST[i]==ecuAddr) {
            pVT_Net->listNr=i;
            break;
        }
    }//for i
};//setECUListNumber


//==============================================================================
void setECUAddress(TVT_Net *pVT_Net,CANMsg msg) {
    uint8_t ecuAddr=msg.ID & 0xFF;
    bool foundAddr=false;
    QString str=getWSNameFromAddress(pVT_Net, ecuAddr);
    int i=0;
    if (str.length()==0) {
        str="FFFFFFFFFFFFFFFF";
        for (i=0; i<2;i++) {
            if (pVT_Net->VT_DST[i]==ecuAddr) {
                pVT_Net->VT_DST[i]=0xFF; pVT_Net->VT_DST_WS[i]=str;
            }
        }//for i
    }else {
        for (i=0; i<2;i++) {
            if (pVT_Net->VT_DST[i]==ecuAddr) {
                foundAddr=true;
                break;
            };
        }//for i
        //
        if (!foundAddr){
            for (i=0; i<2;i++) {
                if (pVT_Net->VT_DST[i]==0xFF) {
                    pVT_Net->VT_DST[i]=ecuAddr; pVT_Net->VT_DST_WS[i]=str;
                    break;
                }
            }//for i
        }
        //
    }
    //
    for (i=0;i<2;i++) {
        if (pVT_Net->VT_DST[i]==ecuAddr) pVT_Net->VT_DST_TIME[i]=QDateTime::currentDateTime().toMSecsSinceEpoch();
        //TEST
        //qWarning() << getStringHEX(pVT_Net->VT_DST[i],2);
        //qWarning() << "\t" + pVT_Net->VT_DST_WS[i];
    }
    //TEST
    //qWarning() << delm0;
};//setECUAddress



//==============================================================================
bool getVTActiveMask(TVT_Net *pVT_Net) {
    bool valid = (getVTObjectListSize(pVT_Net) > 0);
    uint16_t objMask = 0xFFFF, objSoftMask = 0xFFFF;
    int16_t objIdx=-1;
    uint8_t dst=pVT_Net->VT_SRC;
    uint8_t *buff;
    if (valid) {
        objIdx=getVTObjID(pVT_Net,gWSetObjType,true);
        if (objIdx>=0) {
            buff=pVT_Net->streamStr.getBuffer();
            //ActiveMask
            objMask=buff[5] + (buff[6]<<8);
            objIdx=getVTObjID(pVT_Net,objMask);
            if (objIdx>=0) {
                buff=pVT_Net->streamStr.getBuffer();
                objSoftMask=buff[4] + (buff[5]<<8);
            }
        }
        dst=pVT_Net->VT_DST[pVT_Net->listNr];
        valid = true;
    }//valid
    //
    pVT_Net->VT_ActiveSRC =dst;
    pVT_Net->VT_ActiveMask = objMask;
    pVT_Net->VT_ActiveSoftKeyMask = objSoftMask;
    return valid;
};//getVTActiveMask


//==============================================================================
bool PaintActiveSoftKeyMask(uint16_t maskID, TVT_ViewRect *pViewRect,TVT_Net *pVT_Net) {
    bool valid=(getVTObjectListSize(pVT_Net) > 0);
    int16_t  x = pVT_Net->x, y = pVT_Net->y;
    uint16_t w = pVT_Net->w, h = pVT_Net->h;
    TVT_ViewRect vRect = getViewRect(pViewRect);
    if (valid){
        x = pVT_Net->TFT_Height;
        vRect.viewX = pVT_Net->TFT_Height;
        vRect.viewY = 0;
        vRect.viewW = pVT_Net->TFT_KeyWidth;
        vRect.viewH = pVT_Net->TFT_Height;
        //
        pVT_Net->x = vRect.viewX, pVT_Net->y = vRect.viewY;
        pVT_Net->w = vRect.viewW, pVT_Net->h = vRect.viewH;
        //
        Set_fillRect(pVT_Net,pVT_Net->x,pVT_Net->y,pVT_Net->w,pVT_Net->h,cl_silver);

        SetObjPaintObjToRef(&vRect,pVT_Net,maskID);
        //pVT_Net->x = x; pVT_Net->y = y;
        //pVT_Net->w = w; pVT_Net->h = h;
    }//valid
    return valid;
};//PaintActiveSoftKeyMask


//==============================================================================
bool PaintActiveMask(uint16_t maskID, TVT_ViewRect *pViewRect,TVT_Net *pVT_Net) {
    bool valid=(getVTObjectListSize(pVT_Net) > 0);
    int16_t  x=pVT_Net->x, y=pVT_Net->y;
    uint16_t w=pVT_Net->w, h=pVT_Net->h;
    TVT_ViewRect vRect = getViewRect(pViewRect);
    if (valid) {
        vRect.viewX = 0;
        vRect.viewY = 0;
        vRect.viewW = pVT_Net->TFT_Width;
        vRect.viewH = pVT_Net->TFT_Height;
        //
        pVT_Net->x = vRect.viewX, pVT_Net->y = vRect.viewY;
        pVT_Net->w = vRect.viewW, pVT_Net->h = vRect.viewH;
        //
        SetObjPaintObjToRef(&vRect,pVT_Net,maskID);
        pVT_Net->x = x; pVT_Net->y = y;
        pVT_Net->w = w; pVT_Net->h = h;
    }//valid
    return valid;
};//PaintActiveMask


//==============================================================================
void setClearScreen(TVT_Net *pVT_Net,bool listClear) {
    uint16_t i=0,x=0,y=0,w=pVT_Net->TFT_Width,h=pVT_Net->TFT_Height;
    QString str="",fntName="",ss="";
    uint8_t fntNr=pVT_Net->fntNr, fntSr=pVT_Net->fntSr;
    getHeapStatus(pVT_Net,21);
    //
    Set_setTextColor(pVT_Net,0);
    Set_setTextDatum(pVT_Net,0);
    pVT_Net->fntNr=4;pVT_Net->fntSr=1;
    fntName="arial" + QString(pVT_Net->fontSet[pVT_Net->fntNr][6]) + "-" + QString(pVT_Net->fntSr);
    Set_loadFont(pVT_Net,fntName);
    //
    Set_resetViewport(pVT_Net);
    Set_setCursor(pVT_Net,0, 0);
    //Set_fillRect(pVT_Net,x,y,w,h,cl_silver);
    Set_fillRect(pVT_Net,x,y,w,h,cl_white);
    pVT_Net->infoStr[4]="VT6 ImgMode=" + QString(pVT_Net->ImgMode) + " KeyNr=" + QString(pVT_Net->TFT_KeyNr);
    str+="Mask=" + QString(h) + "x" + QString(h) + " Key=";
    str+=String(pVT_Net->TFT_KeyWidth) + "x" + QString(pVT_Net->TFT_KeyHeight);
    pVT_Net->infoStr[5]=str;
    //
    x=h;y=0;w=pVT_Net->TFT_KeyWidth;h=pVT_Net->TFT_KeyHeight;
    pVT_Net->infoStr[1]="Serial:115200";

    for (i=0;i<pVT_Net->TFT_KeyNr;i++) {
        Set_fillRect(pVT_Net,x,i*h,w,h,cl_silver);
        //Set_fillRect(pVT_Net,x,i*h,w,h,cl_white);
        Set_drawRect(pVT_Net,x,i*h,w,h,cl_blue);
        str=String(i);
        Set_setTextSize(pVT_Net,1);
        Set_drawString(pVT_Net,str,x+10,i*h+10);
        str+=".";
        if ((i<2) || (i>3)) str+=pVT_Net->infoStr[i];
        //
        if (i==2) {
            if (pVT_Net->ssid_w.length()>0) pVT_Net->infoStr[i]=pVT_Net->ssid_w;
            str+=pVT_Net->infoStr[i];
            ss="[" + pVT_Net->ip_w + "]";
            Set_drawString(pVT_Net,ss,25,i*h+28);
        }
        if (i==3) {
            if (pVT_Net->ssid_a.length()>0) pVT_Net->infoStr[i]=pVT_Net->ssid_a;
            str+=pVT_Net->infoStr[i];
            ss=" [" + pVT_Net->ip_a + "]";
            str+=ss;
            //Set_drawString(pVT_Net,ss,25,i*h+28);
        }
        //
        Set_drawString(pVT_Net,str,10,i*h+10);
    }//for i
    //
    Set_resetViewport(pVT_Net);
    Set_setTextColor(pVT_Net,cl_black);
    Set_setTextDatum(pVT_Net,0);
    Set_setCursor(pVT_Net,0, 0);
    //
    if (listClear){
        setVTObjectListClear(pVT_Net);
        Set_unloadFont(pVT_Net);
    }
    //
    pVT_Net->fntNr=fntNr;pVT_Net->fntSr=fntSr;
    getHeapStatus(pVT_Net,22);
};//setClearScreen   



//==============================================================================
bool VTPoolDataRefreshDirect(TVT_Net *pVT_Net,bool push) {
    bool valid=false;
    Set_resetViewport(pVT_Net);
    //
    if (pVT_Net->VTPoolClear){
        setClearScreen(pVT_Net,true);
    } else {
        if (getPoolObjectPaint(pVT_Net)) {
            getHeapStatus(pVT_Net,8);
            valid=true;
        } else setClearScreen(pVT_Net,true);
    }
    Set_resetViewport(pVT_Net);
    //
    if ((push) && (pVT_Net->VTPageSelect==0)) {
        paintSelectionFrame(pVT_Net);
        if (pVT_Net->ImgMode) pVT_Net->ImgTFT.pushSprite(0,0);
    }
    pVT_Net->VTPoolRefresh=false; pVT_Net->VTPoolClear=false;
    //
    return valid;
};//VTPoolDataRefreshDirect


//==============================================================================
//Start paint and drawList
bool getPoolObjectPaint(TVT_Net *pVT_Net) {
    bool valid=(getVTObjectListSize(pVT_Net) > 0);
    TVT_ViewRect VT_ViewRect;
    setVTDrawListClear(pVT_Net); pVT_Net->VTParentReference=0xFFFF;
    //
    if (valid) {
        resetColorMap(pVT_Net);
        SetObjPaintObjToRef(&VT_ViewRect,pVT_Net,gWSControlType,true);
        //
        VT_ViewRect.viewX = 0;   VT_ViewRect.viewY = 0;
        VT_ViewRect.viewW = pVT_Net->TFT_Height; VT_ViewRect.viewH = VT_ViewRect.viewW;
        //
        pVT_Net->x = VT_ViewRect.viewX; pVT_Net->y = VT_ViewRect.viewY;
        pVT_Net->w = VT_ViewRect.viewW; pVT_Net->h = VT_ViewRect.viewH;
        //
        SetObjPaintObjToRef(&VT_ViewRect,pVT_Net,gWSetObjType,true);
    }//valid
    //
    return valid;
};//getPoolObjectPaint

//==============================================================================
bool removeClassObj(TVT_Net *pVT_Net,int16_t objIdx) {
    bool  valid=(objIdx>=0);
    if (valid) {
        getVTObjectListRemove(pVT_Net,objIdx);
    }//valid
    return valid;
};//removeClassObj 



//==============================================================================
bool runClassObj(TVT_Net *pVT_Net, TVT_ViewRect *pViewRect,LoopbackStream *pStream) {
    bool valid =((pStream!=NULL) && (pStream->available()));
    uint8_t  objType=pVT_Net->VTObjType,err=0x01;
    uint16_t objID=pVT_Net->VTObjID;
    int16_t  objIdx=-1;
    if ((valid) || (pStream==NULL)) {
        //-------------------
        //TVTWorkingSet
        //-------------------
        if (objType == 0)  {
            TVTWorkingSet mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTDataMask
        //-------------------
        if (objType == 1)  {
            TVTDataMask mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTAlarmMask
        //-------------------
        if (objType == 2)  {
            TVTAlarmMask mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                // qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTContainer
        //-------------------
        if (objType == 3)  {
            TVTContainer mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTSoftKeyMask
        //-------------------
        if (objType == 4)  {
            TVTSoftKeyMask mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTKey
        //-------------------
        if (objType == 5)  {
            TVTKey mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTButton
        //-------------------
        if (objType == 6)  {
            TVTButton mObj;    mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTInputBooleanField
        //-------------------
        if (objType == 7)  {
            TVTInputBooleanField mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTInputStringField
        //-------------------
        if (objType == 8)  {
            TVTInputStringField mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTInputNumberField
        //-------------------
        if (objType == 9)  {
            TVTInputNumberField mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTInputListField
        //-------------------
        if (objType == 10) {
            TVTInputListField mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTOutputStringField
        //-------------------
        if (objType == 11) {
            TVTOutputStringField mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTOutputNumberField
        //-------------------
        if (objType == 12) {
            TVTOutputNumberField mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTLine
        //-------------------
        if (objType == 13) {
            TVTLine mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTRectangle
        //-------------------
        if (objType == 14) {
            TVTRectangle mObj;  mObj.VTObjID=objID; mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTEllipse
        //-------------------
        if (objType == 15) {
            TVTEllipse mObj;  mObj.VTObjID=objID; mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTPolygon
        //-------------------
        if (objType == 16) {
            TVTPolygon  mObj;   mObj.VTObjID=objID; mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTMeter
        //-------------------
        if (objType == 17) {
            TVTMeter  mObj;   mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTLinearBarGraph
        //-------------------
        if (objType == 18) {
            TVTLinearBarGraph mObj;   mObj.VTObjID=objID; mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTArchedBarGraph
        //-------------------
        if (objType == 19) {
            TVTArchedBarGraph mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTPictureGraphic
        //-------------------
        if (objType == 20) {
            TVTPictureGraphic mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTNumberVariable
        //-------------------
        if (objType == 21) {
            TVTNumberVariable mObj;  mObj.VTObjID=objID; mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTStringVariable
        //-------------------
        if (objType == 22) {
            TVTStringVariable mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTFontAttribute
        //-------------------
        if (objType == 23) {
            TVTFontAttribute mObj; mObj.VTObjID=objID; mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTLineAttribute
        //-------------------
        if (objType == 24) {
            TVTLineAttribute mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTFillAttribute
        //-------------------
        if (objType == 25) {
            TVTFillAttribute mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTInputAttribute
        //-------------------
        if (objType == 26) {
            TVTInputAttribute mObj; mObj.VTObjID=objID; mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTObjectPointer
        //-------------------
        if (objType == 27) {
            TVTObjectPointer mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTMacroObject
        //-------------------
        if (objType == 28) {
            TVTMacroObject mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTAuxiliaryFunction
        //-------------------
        if (objType == 29) {
            TVTAuxiliaryFunction mObj; mObj.VTObjID=objID; mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTAuxiliaryInput
        //-------------------
        if (objType == 30) {
            TVTAuxiliaryInput mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTAuxiliaryFunction2
        //-------------------
        if (objType == 31) {
            TVTAuxiliaryFunction2 mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTAuxiliaryInput2
        //-------------------
        if (objType == 32) {
            TVTAuxiliaryInput2 mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTAuxDesignPointer
        //-------------------
        if (objType == 33) {
            TVTAuxDesignPointer mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTWindowMaskObject
        //-------------------
        if (objType == 34) {
            TVTWindowMaskObject mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTKeyGroupObject
        //-------------------
        if (objType == 35) {
            TVTKeyGroupObject mObj; mObj.VTObjID=objID; mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTGraphicsContext
        //-------------------
        if (objType == 36) {
            TVTGraphicsContext mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTOutputListField
        //-------------------
        if (objType == 37) {
            TVTOutputListField mObj;mObj.VTObjID=objID; mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTExtendedInputAttribute
        //-------------------
        if (objType == 38) {
            TVTExtendedInputAttribute mObj;mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTColourMap
        //-------------------
        if (objType == 39) {
            TVTColourMap mObj;    mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTLabelReferenceListObject
        //-------------------
        if (objType == 40) {
            TVTLabelReferenceListObject mObj;   mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTExternalObjectDefinition
        //-------------------
        if (objType == 41) {
            TVTExternalObjectDefinition mObj;   mObj.VTObjID=objID; mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTExternalReferenceName
        //-------------------
        if (objType == 42) {
            TVTExternalReferenceName mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTExternalObjectPointer
        //-------------------
        if (objType == 43) {
            TVTExternalObjectPointer mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTAnimationObject
        //-------------------
        if (objType == 44) {
            TVTAnimationObject mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTColourPalette
        //-------------------
        if (objType == 45) {
            TVTColourPalette mObj; mObj.VTObjID=objID; mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTGraphicData
        //-------------------
        if (objType == 46) {
            TVTGraphicData mObj;  mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTWorkingSetControl
        //-------------------
        if (objType == 47) {
            TVTWorkingSetControl mObj; mObj.VTObjID=objID;mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //-------------------
        //TVTScaledGraphic
        //-------------------
        if (objType == 48) {
            TVTScaledGraphic mObj; mObj.VTObjID=objID; mObj.VTObjType=objType;
            if (pVT_Net->VTObjName=="INFO") pVT_Net->VTObjName=mObj.VTObjName;
            if (pStream==NULL) {
                //qWarning() << objID;
                //getStreamStrInfo(pVT_Net);
                valid=mObj.PaintObjTo(pViewRect,pVT_Net);
            } else valid=mObj.readFromStream(pVT_Net,pStream);
            return valid;
        }
        //
    }//valid
    return valid;
};//runClassObj


//=============================================================================
//=============================================================================
QString getHexCharacterString(QString str,bool reverse) {
    String tStr="";
    uint16_t len=str.length(),j=0;
    if (len>0){
        for (int i=0;i<len;i++) {
            j=i;
            if (reverse) j=len-1-i;
            tStr+=getStringHEX(char(str[j]),2);
        }//for i
    }//>0
    return tStr;
};//getHexCharacterString


//=============================================================================
QByteArray hexCharacterStringToBytes(QString string_)
{
    QByteArray ret;
    QString sStr="", tStr="", str=hexString;
    int i=0,j=0;
    while (str.length()>0) {
        sStr=str.mid(0,2);
        str = str.mid(2);
        for (i=0;i<256;i++) {
            tStr=getStringHEX(i,2);
            if (tStr==sStr){
                ret.append(i);
                break;
            }
        }//for i
        j++;
    }//while
    return ret;
};//hexCharacterStringToBytes


//------------------------------------------------------------------------------
TVTListValues setVTListValues(QString listAttr) {
    QString ss = "";
    TVTListValues listVal;
    for (int i = 0; i < 3; i++) {
        if (listAttr.indexOf(',') >= 0) {
            ss = listAttr.mid(0, listAttr.indexOf(','));
            listAttr.remove(0, listAttr.indexOf(',') + 1);
            listVal.VTListValue[i] = ss.toInt();
        } else {
            listVal.VTListValue[i] = listAttr.toInt();
            break;
        }//indexOf
    }//for i
    return listVal;
};//setVTListValues

//------------------------------------------------------------------------------
//VTAttrAID[0].numAID=0;  VTAttrAID[0].byteAID=1; VTAttrAID[0].typeAID=0; VTAttrAID[0].nameAID="VTObjType";VTAttrAID[0].valueAID=QString::number(VTObjType);
uint32_t getVTObjectAttributeInt32(QString nameAttr, TVT_Net *pVT_Net) {
    uint8_t err = 0x01,len=0;
    uint16_t aIdx=2;//offset VTObjID
    uint32_t nn=0,i=0,j=0;
    QString attrStr="";
    uint8_t* buff=pVT_Net->streamStr.getBuffer();
    for (i=0;i<pVT_Net->VT_AID_Nr;i++) {
        if (pVT_Net->VTAttrAID[i].nameAID==nameAttr) {
            nn=pVT_Net->VTAttrAID[i].byteAID;
            for (j=0;j<nn;j++) attrStr+=char(buff[aIdx+j]);
            break;
        }
        //
        //check inputstring VTLength for attribute VTEnabled
        if ((pVT_Net->VTObjType==8) && (i==9)) {
            len=buff[aIdx]; aIdx+=len;
            //qWarning() << pVT_Net->VTAttrAID[i].nameAID;
            //qWarning() << len;
        }
        //
        aIdx+=pVT_Net->VTAttrAID[i].byteAID;
    } //for i
    pVT_Net->aIdx=aIdx; nn=0;
    if (attrStr.length()>0){
        for (i=0;i<attrStr.length();i++) nn+=(char(attrStr[i]))<<8*i;
    }
    //
    return nn;
};//getVTObjectAttributeInt32


//------------------------------------------------------------------------------
void getViewport(TVT_Net *pVT_Net, TVT_ViewRect *pViewRect, int16_t x, int16_t y, uint16_t w, uint16_t h) {
    int16_t vX0=pViewRect->viewX, vY0=pViewRect->viewY, vX1=vX0 + pViewRect->viewW, vY1=vY0 + pViewRect->viewH;
    int16_t x0=x, y0=y, x1=x+w, y1=y+h;
    if (x>vX1) {x0=vX1;x1=vX1;}
    if (y>vY1) {y0=vY1;y1=vY1;}
    //
    if (x+w<vX0) {x0=vX0;x1=vX0;}
    if (y+h<vY0) {y0=vY0;x1=vY0;}
    //
    if (x < vX0) x0 = vX0;
    if (y < vY0) y0 = vY0;
    //
    if (x1 > vX1) x1 = vX1;
    if (y1 > vY1) y1 = vY1;
    //
    pViewRect->viewX = x0;
    pViewRect->viewY = y0;
    pViewRect->viewW=x1-x0;
    pViewRect->viewH=y1-y0;
    //
    Set_resetViewport(pVT_Net);
    Set_setViewport(pVT_Net,pViewRect->viewX, pViewRect->viewY, pViewRect->viewW, pViewRect->viewH);
};//getViewport


//------------------------------------------------------------------------------
bool SetObjPaintObjToRef(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net,uint16_t objID,bool TypeMode) {
    uint16_t lCount=getVTObjectListSize(pVT_Net);
    int16_t  objIdx=getVTObjID(pVT_Net,objID,TypeMode);
    bool  valid=((lCount>0) && (objIdx>=0) && (objIdx<lCount)), TEST=false;
    if (TEST) {
        qWarning() << "SetObjPaintObjToRef objIdx=" + QString(objIdx) + "\tObjID=" + QString(pVT_Net->VTObjID) + "\tObjType=" + QString(pVT_Net->VTObjType);
    }
    //
    if (valid) {
        pVT_Net->objNr=objIdx;
        //check gPointerType=27
        if (pVT_Net->VTObjType==gPointerType) {
            if (getVTObjectLoop(pVT_Net)) return valid;
        }
        valid=runClassObj(pVT_Net, pViewRect,NULL);
    }//valid
    //
    return valid;
};//SetObjPaintObjToRef


//------------------------------------------------------------------------------
//check object loop in drawList
bool getVTObjectLoop(TVT_Net *pVT_Net) {
    uint16_t lCount=getVTObjectListSize(pVT_Net),dCount=getVTDrawListSize(pVT_Net), pObjID=pVT_Net->VTObjID;
    bool  valid=(lCount>0),objLoop=false,TEST=false;
    uint16_t objID = 0xFFFF,pLevel=0,level=0,idx=0;
    uint8_t  objType=0xFF;
    valid=((valid) && (pVT_Net->objNr>=0) && (pVT_Net->objNr<lCount));
    if ((valid) && (dCount>1)) {
        idx=dCount-1;
        getVTDrawListValue(pVT_Net,idx);
        objID=pVT_Net->streamDraw.readBytesVal(2,0);
        objType=pVT_Net->streamDraw.readBytesVal(1,2);
        pLevel=pVT_Net->streamDraw.readBytesVal(1,13);
        //TEST
        if (TEST){
            getStreamDrawInfo(pVT_Net,-1);
            qWarning() << objID;
            qWarning() << pLevel;
            qWarning() << delm0;
        }
        //
        while (idx>0) {
            idx--;
            getVTDrawListValue(pVT_Net,idx);
            objID=pVT_Net->streamDraw.readBytesVal(2,0);
            objType=pVT_Net->streamDraw.readBytesVal(1,2);
            if (HasInArray(objType,topObjSet)) break;
            //
            if (objID==pObjID) {
                level=pVT_Net->streamDraw.readBytesVal(1,13);
                if (level<pLevel) {
                    objLoop=true;
                    qWarning() << "getVTObjectLoop=" + QString(objID);
                    break;
                }
            }
        }//while
    }//valid
    //
    return objLoop;
};//getVTObjectLoop   


//------------------------------------------------------------------------------
bool getVTObjectsPaint(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net) {
    uint16_t lCount=getVTObjectListSize(pVT_Net),dCount=getVTDrawListSize(pVT_Net), pObjID=pVT_Net->VTObjID;
    bool  valid=(lCount>0),posMode=true,getObjLoop=false;
    uint16_t i=0,j=0,nn=0, an=0, aIdx=2,objID = 0xFFFF,pLevel=0,level=0;
    uint16_t w=pVT_Net->w,h=pVT_Net->h, parentRef=pVT_Net->VTParentReference;
    int16_t  xx = 0, yy = 0, x = pVT_Net->x, y = pVT_Net->y,keyPage=-1,idx=-1;
    QString   attrName="VTObjects";
    uint8_t*buff;
    TVT_ViewRect vRect  = getViewRect(pViewRect);
    TVT_ViewRect vvRect = getViewRect(pViewRect);
    valid=((valid) && (pVT_Net->objNr>=0) && (pVT_Net->objNr<lCount));
    if (valid) {
        //check object loop in drawList
        if (getVTObjectLoop(pVT_Net)) return valid;
        //
        if (pVT_Net->VTObjType == gKeyMaskObjType) {
            attrName="VTItemList";posMode=false;keyPage=0;
            if (pVT_Net->TFT_KeySelect<255) {
                pVT_Net->TFT_KeyPage=pVT_Net->TFT_KeySelect/pVT_Net->TFT_KeyNr;
            }
        }
        nn=getVTObjectAttributeInt32(attrName,pVT_Net);
        //check animation object
        if (pVT_Net->animationIdx>=0){
            if (pVT_Net->animationIdx<nn) {
                an=pVT_Net->animationIdx; nn=an+1; aIdx+=6*an;
            }else nn=0;
        }//animation
        //
        if (nn>0){
            //qWarning() << "nn=" + QString(nn);
            //
            for (i=0;i<pVT_Net->VT_AID_Nr;i++) aIdx+=pVT_Net->VTAttrAID[i].byteAID;
            //
            for (i=an;i<nn;i++){
                buff=pVT_Net->streamStr.getBuffer();
                objID=buff[aIdx++] + (buff[aIdx++]<<8);
                if (posMode) {
                    xx=buff[aIdx++] + (buff[aIdx++]<<8);
                    yy=buff[aIdx++] + (buff[aIdx++]<<8);
                }else{
                    if (j==pVT_Net->TFT_KeyNr) {
                        j=0;keyPage++;
                    }
                    xx = 0; yy = pVT_Net->TFT_KeyHeight * j;
                    j++;
                }
                //
                vvRect = getViewRect(pViewRect);
                xx = x + xx; yy = y + yy;
                pVT_Net->x = xx; pVT_Net->y = yy;
                //
                if ((keyPage<0) || (keyPage==pVT_Net->TFT_KeyPage)) {
                    valid = SetObjPaintObjToRef(&vvRect,pVT_Net,objID);
                }
                //
                getVTObjID(pVT_Net,pObjID);
                pVT_Net->VTParentReference=parentRef;
                pVT_Net->x = x; pVT_Net->y = y;
                pVT_Net->w = w; pVT_Net->h = h;
                getViewport(pVT_Net,&vRect,x,y,w,h);
            }//for i
        } //nn>0
    }//valid
    return valid;
};//getVTObjectsPaint


//==============================================================================
void getVTObjectFromList(TVT_Net *pVT_Net,int16_t objNr) {
    uint16_t lCount=getVTObjectListSize(pVT_Net),w=4*8,h=10;
    int16_t x=pVT_Net->x,y=pVT_Net->y;
    uint8_t* buff;
    pVT_Net->streamStr.clear();pVT_Net->VTObjID=0xFFFF;pVT_Net->VTObjType=0xFF;
    pVT_Net->objNr=objNr;
    if ((objNr>=0) && (objNr < lCount)) {
        getVTObjectListValue(pVT_Net,objNr);
        runClassObj(pVT_Net,NULL,NULL);
        //setLabelReference
        if (pVT_Net->SetLabel==2){
            QString str=QString::number(pVT_Net->VTObjID);w=8*str.length();
            Set_resetViewport(pVT_Net);
            Set_fillRect(pVT_Net,x,y,w,h,TFT_LIGHTGREY);
            Set_setTextColor(pVT_Net,TFT_BLACK);
            Set_setTextDatum(pVT_Net,0);
            Set_drawString(pVT_Net,str,x+1,y+1);
        }//SetLabel
    }//lCount>0
};//getVTObjectFromList



//==============================================================================
//==============================================================================
bool TVTObject::getMsgToAttr(uint8_t cFunc, CANMsg *pMsg, TVT_Net *pVT_Net) {
    bool valid = false;
    uint8_t src = ((pMsg->ID) >> 0) & 0xFF;
    uint8_t dst = ((pMsg->ID) >> 8) & 0xFF;
    if (((pMsg->ID & 0x00FF0000) == ECUtoVT_PGN) && (dst == pVT_Net->VT_SRC)) {
        pMsg->MSG_TX = 1; pMsg->MSGTYPE = 1; pMsg->LEN = 8;
        pMsg->ID = (ECU_VT_PRIO << 24) + VTtoECU_PGN + (src << 8) + pVT_Net->VT_SRC;
        pMsg->DATA[0] = cFunc;
        valid = true;
    }
    return valid;
};//TVTObject::getMsgToAttr


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
uint16_t  TVTObject::getVTItemsNumber(uint8_t idx, QString attrName,TVT_Net *pVT_Net) {
    uint16_t objID=0xFFFF,aIdx=2;
    uint8_t nn=0,i=0,bb[2]={0,0};
    //TEST
    //getStreamStrInfo(pVT_Net);
    nn=getVTObjectAttributeInt32(attrName,pVT_Net);
    uint8_t *buff=pVT_Net->streamStr.getBuffer();
    //
    for (i=0;i<VT_AID_Nr;i++) aIdx+=VTAttrAID[i].byteAID;
    if ((nn>0) && (idx>=0) && (idx<nn)){
        aIdx=aIdx+2*idx;
        bb[0]=buff[aIdx];
        bb[1]=buff[aIdx+1];
        objID=bb[0] + (bb[1]<<8);
    }
    return objID;
};//TVTObject::getVTItemsNumber



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TVTObject::getVTDrawListAddObj(TVT_Net *pVT_Net,bool enabled,TVT_ViewRect *pViewRect) {
    QString str="";
    uint16_t objNr=getVTDrawListSize(pVT_Net);
    uint8_t selected=0x00,kIndex=0xFF;
    pVT_Net->streamDraw.clear();
    //objID,objType,absBounds,Parent,level,selected,index
    pVT_Net->streamDraw.writeBytesVal(VTObjID,2);
    pVT_Net->streamDraw.writeBytesVal(VTObjType,1);
    if (VTObjType==5) kIndex=pVT_Net->VTKeyIndex;    //Key
    if (VTObjType==6) kIndex=pVT_Net->VTButtonIndex; //Button
    if (HasInArray(VTObjType,inpAllObjSet)) kIndex=pVT_Net->VTInputIndex; //Input
    //
    pVT_Net->streamDraw.writeBytesVal(pViewRect->viewX,2);
    pVT_Net->streamDraw.writeBytesVal(pViewRect->viewY,2);
    pVT_Net->streamDraw.writeBytesVal(pViewRect->viewW,2);
    pVT_Net->streamDraw.writeBytesVal(pViewRect->viewH,2);
    //
    pVT_Net->streamDraw.writeBytesVal(pVT_Net->VTParentReference,2);
    pVT_Net->streamDraw.writeBytesVal(pVT_Net->level,1);
    //change
    pVT_Net->streamDraw.writeBytesVal(selected,1);
    //TEST
    //pVT_Net->streamDraw.writeBytesVal(enabled,1);
    //
    pVT_Net->streamDraw.writeBytesVal(kIndex,1);

    //getStreamDrawInfo(pVT_Net);
    //Sum=16
    if (enabled) {
        runClassObj(pVT_Net,NULL,NULL);
        objNr=getVTDrawListAdd(pVT_Net);
        if (pVT_Net->VT_InfoMode) getVTDrawListInfoPrint(pVT_Net,objNr-1,0);
    }
    //
    pVT_Net->VTParentReference=pVT_Net->VTObjID;
    pVT_Net->VTParentType=pVT_Net->VTObjType;
};//TVTObject::getVTDrawListAddObj


//------------------------------------------------------------------------------
int8_t TVTObject::SetSelectState(TVT_Net *pVT_Net, bool enabled, TVT_ViewRect *pViewRect) {
    int8_t sel = -1;
    pVT_Net->VTDefaultColour=true;
    if (enabled) {
        if (VTSelect > 0) sel = -2;
        Set_frameViewport(pVT_Net,cl_lime, sel);
    } else {
        VTSelect = 0x00;
        int16_t  x = pViewRect->viewX;
        int16_t  y = pViewRect->viewY;
        uint16_t w = pViewRect->viewW;
        uint16_t h = pViewRect->viewH;
        //
        //disabled
        Set_drawRect(pVT_Net,x, y, w, h, cl_silver);
        for (int i = 0; i < 8; i++) {
            Set_drawLine(pVT_Net,x + i * w / 8, y, x + w, y + h - i * h / 8, cl_silver);
            Set_drawLine(pVT_Net,x, y + i * h / 8, x + w - i * w / 8, y + h, cl_silver);
        }
    }
    pVT_Net->VTDefaultColour=false;
    //
    return sel;
};//TVTObject::SetSelectState


//------------------------------------------------------------------------------
uint16_t TVTObject::setVTEvents(bool writeMode) {
    //TODO
    return 0;
};//TVTObject::setVTEvents


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool TVTObject::getVTColourItems(TVT_Net *pVT_Net,uint16_t nn, LoopbackStream *pStream) {
    bool valid=((pStream->available()) && (nn>0));
    uint8_t bMax=1;
    if (valid) {
        if (VTObjType==gColorPalType) bMax=4;
        uint8_t buff[bMax*nn];
        pStream->readBytes(buff,bMax*nn);
        pVT_Net->streamStr.writeBytes((uint8_t*) buff,bMax*nn);
    }
    return valid;
};//TVTObject::getVTColourItems


//------------------------------------------------------------------------------
bool  TVTObject::getVTString(TVT_Net *pVT_Net,uint16_t nn, LoopbackStream *pStream) {
    bool valid=((pStream->available()) && (nn>0));
    if (valid) {
        uint8_t buff[nn];
        pStream->readBytes(buff,nn);
        pVT_Net->streamStr.writeBytes((uint8_t*) buff,nn);
    }
    return valid;
};//TVTObject::getVTString


//------------------------------------------------------------------------------
bool TVTObject::getVTLabels(TVT_Net *pVT_Net,uint16_t nn, LoopbackStream *pStream) {
    bool valid=((pStream->available()) && (nn>0));
    uint8_t kk=7;
    if (valid) {
        uint8_t buff[kk*nn];
        pStream->readBytes(buff,kk*nn);
        pVT_Net->streamStr.writeBytes((uint8_t*) buff,kk*nn);
    }
    return valid;
};//TVTObject::getVTLabels


//------------------------------------------------------------------------------
bool TVTObject::getVTObjects(TVT_Net *pVT_Net,uint8_t nn, LoopbackStream *pStream) {
    bool valid=((pStream->available()) && (nn>0));
    uint8_t kk=6;
    if (valid) {
        uint8_t buff[kk*nn];
        pStream->readBytes(buff,kk*nn);
        pVT_Net->streamStr.writeBytes((uint8_t*) buff,kk*nn);
    }
    return valid;
};//TVTObject::getVTObjects


//------------------------------------------------------------------------------
bool TVTObject::getVTItems(TVT_Net *pVT_Net,uint8_t nn, LoopbackStream *pStream) {
    bool valid=((pStream->available()) && (nn>0));
    uint8_t kk=2;
    if (valid) {
        uint8_t buff[kk*nn];
        pStream->readBytes(buff,kk*nn);
        pVT_Net->streamStr.writeBytes((uint8_t*) buff,kk*nn);
    }
    return valid;
};//TVTObject::getVTItems


//------------------------------------------------------------------------------
//check ExtendedMacroObjects
bool TVTObject::getVTMacros(TVT_Net *pVT_Net,uint8_t nn, LoopbackStream *pStream) {
    bool valid=((pStream->available()) && (nn>0));
    uint8_t  buff[4],eventID=0xFF,kk=2,i=0;
    if (valid) {
        for (i=0;i<nn;i++){
            if (pStream->available()){
                eventID = pStream->peek();kk=2;
                if (eventID==0xFF) kk=4;
                pStream->readBytes(buff,kk);
                pVT_Net->streamStr.writeBytes((uint8_t*) buff,kk);
            } else break;
        }//for i
    }
    return valid;
};//TVTObject::getVTMacros


//------------------------------------------------------------------------------
uint8_t TVTObject::getVTPoints(TVT_Net *pVT_Net,uint8_t nn, LoopbackStream *pStream) {
    bool valid=((pStream->available()) && (nn>0));
    uint8_t kk=4;
    if (valid) {
        uint8_t buff[kk*nn];
        pStream->readBytes(buff,kk*nn);
        pVT_Net->streamStr.writeBytes((uint8_t*) buff,kk*nn);
    }
    return nn;
};//TVTObject::getVTPoints


//------------------------------------------------------------------------------
bool TVTObject::getVTLanguages(TVT_Net *pVT_Net,uint8_t nn, LoopbackStream *pStream) {
    bool valid=((pStream->available()) && (nn>0));
    uint8_t kk=2,bMax=1;
    if (valid) {
        if (VTObjType==gWSControlType) bMax=2;
        kk=kk*bMax;
        uint8_t buff[kk*nn];
        pStream->readBytes(buff,kk*nn);
        pVT_Net->streamStr.writeBytes((uint8_t*) buff,kk*nn);
    }
    return valid;
};//TVTObject::getVTLanguages



//------------------------------------------------------------------------------
bool TVTObject::getVTCodePlanes(TVT_Net *pVT_Net,uint8_t nn, LoopbackStream *pStream) {
    bool valid=((pStream->available()) && (nn>0));
    uint8_t kk=0,bb=0;
    //number of code planes
    if (valid) {
        for (int i = 0; i < nn; i++) {
            bb=pStream->read(); pVT_Net->streamStr.write(bb); //plane number
            bb=pStream->read(); pVT_Net->streamStr.write(bb); kk = bb; //number of characters
            if (kk > 0) {
                uint8_t buff[4*kk];
                pStream->readBytes(buff,4*kk);
                pVT_Net->streamStr.writeBytes((uint8_t*) buff,4*kk);
            }//kk>0
        }//for i
    } //valid
    return valid;
};//TVTObject::getVTCodePlanes


//------------------------------------------------------------------------------
uint16_t TVTObject::getVTCommands(TVT_Net *pVT_Net,LoopbackStream *pStream) {
    bool valid=(pStream->available());
    uint16_t nn=0; //number of bytes 8-Block
    uint8_t  bb=0;
    bb=pStream->read();pVT_Net->streamStr.write(bb);
    nn+=bb<<0;
    bb=pStream->read();pVT_Net->streamStr.write(bb);
    nn+=bb<<8;
    //
    if (nn > 0) {
        uint8_t buff[nn];
        pStream->readBytes((uint8_t*)buff,nn);
        pVT_Net->streamStr.writeBytes((uint8_t*) buff,nn);
    }
    return nn;
};//TVTObject::getVTCommands


//------------------------------------------------------------------------------
uint8_t TVTObject::setChangeAIDValue(uint8_t attrID, uint32_t attr, TVT_Net *pVT_Net) {
    uint8_t err = 0x01;
    if (VT_AID_Nr > 0) {
        setAID();
        for (int i = 0; i < VT_AID_Nr; i++) {
            if (attrID == VTAttrAID[i].numAID) {
                //check GetAttribute
                if (pVT_Net->VT_CMD == 0xB9) {
                    if (VTAttrAID[i].typeAID <= 1) {
                        pVT_Net->VT_AttrValue = VTAttrAID[i].valueAID.toInt();
                        err = 0x00;
                    }
                } else {
                    if (VTAttrAID[i].typeAID == 1) {
                        pVT_Net->VT_ChangeAttr = VTAttrAID[i].valueAID != QString(attr);
                        VTAttrAID[i].valueAID = QString(attr);
                        err = 0x00;
                    }
                }
                //
                setVTEvents(true);
                getAID();
                break;
            }
        }//for i
    }//nr>0
    return err;
};//TVTObject::setChangeAIDValue


//------------------------------------------------------------------------------
uint16_t TVTObject::writeStringToStream(LoopbackStream *pStream) {
    QString attrStr = "";
    uint16_t len = 0;
    int j = 0;
    for (j = 0; j < VT_AID_Nr; j++) {
        if (VTAttrAID[j].nameAID == "VTLength") {
            attrStr = VTAttrAID[j].valueAID;
            break;
        }
    }
    //
    if (attrStr.length() > 0) {
        len = attrStr.length();
        pStream->write((len >> 0) & 0xFF);
        if (HasInArray(VTObjType, _objStringTypeSet)) pStream->write((len >> 8)  & 0xFF);
        //
        if (len > 0) {
            char  ch[len + 1];
            attrStr.toCharArray(ch, len + 1);
            for (j = 0; j < len; j++) pStream->write(ch[j]);
        }
    }
    return len;
};//TVTObject::writeStringToStream



//------------------------------------------------------------------------------
QString  TVTObject::readStringFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream) {
    QString attrStr = "";
    uint8_t b=0, objType=0xFF, bb[2]={0x00,0x00};  //FFFE uniCode
    uint16_t len=0;
    if (pStream->available()) {
        objType = VTObjType;
        b=pStream->read(); pVT_Net->streamStr.write(b);
        len = (b<<0);
        if (HasInArray(objType, _objStringTypeSet)) {
            b=pStream->read(); pVT_Net->streamStr.write(b);
            len += (b<<8);
        }
        //
        if (len > 0) {
            for (int i = 0; i < len; i++) {
                b=pStream->read(); pVT_Net->streamStr.write(b);
                attrStr += char(b);
            }//for i
        }//len>0
    }
    return attrStr;
};//TVTObject::readStringFromStream

//------------------------------------------------------------------------------
bool TVTObject::writeToStreamDirect(TVT_Net *pVT_Net,LoopbackStream *pStream){
    bool valid=(getVTObjectListSize(pVT_Net)>0);
    int16_t objIdx=getVTObjID(pVT_Net,VTObjID);
    uint32_t i=0;
    byte bb=0;
    if ((valid) and (objIdx>=0)) {
        getVTObjectFromList(pVT_Net,objIdx);
        while (pVT_Net->streamStr.available()){
            pStream->write(pVT_Net->streamStr.read());
        }//while
    }//valid
    return valid;
};//TVTObject::writeToStreamDirect



//------------------------------------------------------------------------------
//get reference VTFontAttribute
void TVTObject::setVTObjectTextDirect(QString str, TVT_Net *pVT_Net) {
    uint16_t un = 0, index = 0, color=pVT_Net->color, w=pVT_Net->w,len=str.length(),k = 0,wx=0;
    uint8_t tw = 0, th = 1, fntType = pVT_Net->fntType, fntStyle = pVT_Net->fntStyle;
    uint8_t fntW = pVT_Net->fontSet[pVT_Net->fntNr][4], fntH = pVT_Net->fontSet[pVT_Net->fntNr][5];
    int16_t x = pVT_Net->x, y = pVT_Net->y, xx = x, yy = y, i = pVT_Net->fntLine;
    bool smFont=true;
    //check uniCode
    if (pVT_Net->uniCode) {fntType=0;len=len/2;}
    //Check font on SD or SPIFFS
    if (!Set_smFont(pVT_Net)) smFont=false;
    //
    for (k = 0; k < len; k++) {
        un=getUniCodeFontIndex(str,k,pVT_Net);
        pVT_Net->tft.getUnicodeIndex(un, &index);
        //
        tw = 0;
        if ((smFont) && (index>=0)) {
            if (fntW > pVT_Net->tft.gWidth[index]) tw = (fntW - pVT_Net->tft.gWidth[index]) / 2;
            if (tw > pVT_Net->tft.gdX[index]) tw = tw - pVT_Net->tft.gdX[index];
        }
        //
        xx = x + k * fntW + tw; yy = y + i * fntH + th;
        //
        /*
    //TEST
    //xx=x+k*fntW; yy=y + i*fntH;
    qWarning() << index;
    qWarning() << xx;
    qWarning() << yy;
    qWarning() << delm0;
    */
        //
        Set_setCursor(pVT_Net,xx, yy);
        if (smFont) {
            Set_drawGlyph(pVT_Net,un);
        }else{
            Set_drawString(pVT_Net,str,xx+2,yy+2);
            return;
        }
        wx+=fntW;
    } //for k
    //
    //numeric string leading zeros
    if ((HasInArray(VTObjType,numObjSet)) && ((pVT_Net->optn & 0x02)>0)){
        un=0x0030; //uniCode for "0"
        pVT_Net->tft.getUnicodeIndex(un, &index);
        //
        tw = 0;
        if (smFont){
            if (fntW > pVT_Net->tft.gWidth[index]) tw = (fntW - pVT_Net->tft.gWidth[index]) / 2;
            if (tw > pVT_Net->tft.gdX[index]) tw = tw - pVT_Net->tft.gdX[index];
        }
        //
        k=0;xx=x;
        //
        while (wx+fntW<=w){
            wx+=fntW;
            if ((pVT_Net->firstMinus) && (wx+fntW>w)) {
                un=0x002D;
                //
                pVT_Net->tft.getUnicodeIndex(un, &index);tw = 0;
                if (smFont){
                    if (fntW > pVT_Net->tft.gWidth[index]) tw = (fntW - pVT_Net->tft.gWidth[index]) / 2;
                    if (tw > pVT_Net->tft.gdX[index]) tw = tw - pVT_Net->tft.gdX[index];
                }
            }
            //
            k++; len++;
            xx = x - k * fntW + tw; yy = y + i * fntH + th;
            Set_setCursor(pVT_Net,xx, yy);
            //
            if (smFont){
                Set_drawGlyph(pVT_Net,un);
            } else{
                Set_drawString(pVT_Net,str,xx+2,yy+2);
                return;
            }
            //
        }//while
        //
        x=xx;
    }
    //qWarning() << delm0;
    //
    for (k = 0; k < len; k++) {
        xx = x + k * fntW; yy = y + i * fntH;
        //strikeOut mode
        if ((fntStyle & 0x02) > 0) {
            Set_drawLine(pVT_Net,xx + 1, yy + fntH / 2 - 1, xx + fntW - 1, yy + fntH / 2 - 1, color);
        }
        //underLine mode
        if ((fntStyle & 0x04) > 0) {
            Set_drawLine(pVT_Net,xx + 1, yy + fntH - 1, xx + fntW - 1, yy + fntH - 1, color);
        }
    }
};//TVTObject::setVTObjectTextDirect



//------------------------------------------------------------------------------
void TVTObject::getVTTextDirect(QString str, TVT_Net *pVT_Net, bool textMode) {
    uint16_t w = pVT_Net->w, len = str.length(),un=0;
    int16_t  x = pVT_Net->x, xx = x;
    uint8_t  fntJust = pVT_Net->fntJust, fntNr = pVT_Net->fntNr;
    uint8_t  fntW = pVT_Net->fontSet[fntNr][4];
    if (textMode) {
        str = str.trimmed();
        len = str.length();
        //check uniCode
        if (pVT_Net->uniCode) len=len/2;
        //
        //
        //check numeric leading zeros with leading minus
        if ((HasInArray(VTObjType,numObjSet)) && ((pVT_Net->optn & 0x02)>0)){
            un=char(str[0].toLatin1());
            if (un==0x002D){
                pVT_Net->firstMinus=true;str.remove(0,1);len=str.length();
            }
        }
        //
        //Horizontal Center
        if ((fntJust == 1) || (fntJust == 5) || (fntJust == 9)  || (fntJust == 13)) xx = x + (w - len * fntW) / 2;
        //Horizontal Right
        if ((fntJust == 2) || (fntJust == 6) || (fntJust == 10) || (fntJust == 14)) xx = x + (w - len * fntW);
        //
        pVT_Net->x=xx;
        setVTObjectTextDirect(str, pVT_Net);
        pVT_Net->x=x;
        pVT_Net->firstMinus=false;
    }//textMode
};//TVTObject::getVTTextDirect


//------------------------------------------------------------------------------
void TVTObject::getVTWrapModeText(QString str, TVT_Net *pVT_Net, bool textMode) {
    uint16_t w = pVT_Net->w;
    uint8_t fntJust = pVT_Net->fntJust, fntNr = pVT_Net->fntNr, optn = pVT_Net->optn;
    uint8_t fntW = pVT_Net->fontSet[fntNr][4];
    int nn0 = -1, nn1 = -1, j = -1;
    QString tStr = str;
    uint16_t wd = w/fntW;
    String sr="\r",sn="\n";
    //
    if (pVT_Net->uniCode){
        getVTWrapModeTextUniCode(str, pVT_Net,textMode);
        return;
    }
    //
    str.replace(sr+sn, sr); str.replace(sn, sr);
    pVT_Net->fntLine = 0;
    //
    while (str.length() > 0) {
        j = str.indexOf(sr);
        if (j >= 0) {
            tStr=str.mid(0,j);
            if (tStr.length()==0) pVT_Net->fntLine++;
            str.remove(0, j + 1);
        } else {
            tStr = str; str = "";
        }
        //
        if ((optn & 0x02) == 0x02) {
            while (wd < tStr.length()) {
                nn0 = -1; nn1 = -1;
                //
                for (int k = 0; k < wd; k++) {
                    if (tStr[k] == ' ') nn0 = k;
                    if (tStr[k] == '-') nn1 = k;
                }
                //
                if (((optn & 0x04) == 0x04) && (nn1 > nn0)) {
                    getVTTextDirect(tStr.mid(0, nn1+1), pVT_Net, textMode);
                    tStr.remove(0, nn1 + 1);
                    pVT_Net->fntLine++;
                } else {
                    if (nn0 < 0) {
                        getVTTextDirect(tStr.mid(0, wd), pVT_Net, textMode);
                        tStr.remove(0, wd);
                        pVT_Net->fntLine++;
                    } else {
                        getVTTextDirect(tStr.mid(0, nn0), pVT_Net, textMode);
                        tStr.remove(0, nn0 + 1);
                        pVT_Net->fntLine++;
                    }
                }
                //
            }//while
            //
            if (tStr.length() > 0) {
                getVTTextDirect(tStr, pVT_Net, textMode);
                pVT_Net->fntLine++;
            }
        } else {
            if (tStr.length() > 0) {
                getVTTextDirect(tStr, pVT_Net, textMode);
                pVT_Net->fntLine++;
            };
        } ////opt wrap
    } //while text
};//TVTObject::getVTWrapModeText


//------------------------------------------------------------------------------
void TVTObject::getVTWrapModeTextUniCode(QString str, TVT_Net *pVT_Net, bool textMode) {
    uint16_t w = pVT_Net->w;
    uint8_t fntJust = pVT_Net->fntJust, fntNr = pVT_Net->fntNr, optn = pVT_Net->optn;
    uint8_t fntW = pVT_Net->fontSet[fntNr][4];
    int nn0 = -1, nn1 = -1, j = -1,k=-1;
    QString tStr = str;
    uint16_t wd = w/fntW;
    wchar_t sr=0x000D, sn=0x000A,sc=0x0020,sm=0x002D,wcm=0x0000; //line_return, line_feed,space,minus
    //qWarning() << getUniCodeInfo(str,true);
    j=getUniCodeIndexOf(str,sr,sn);
    while (j>=0) {
        str=getUniCodeRemove(str,j,1);
        //qWarning() << getUniCodeInfo(str,true);
        j=getUniCodeIndexOf(str,sr,sn);
    } //while
    //
    //qWarning() << getUniCodeInfo(str,true);
    str=getUniCodeReplace(str,sn,sr);
    //qWarning() << getUniCodeInfo(str,true);
    pVT_Net->fntLine = 0;
    //
    while (str.length() > 0) {
        j=getUniCodeIndexOf(str,sr,0);
        if (j >= 0) {
            tStr=getUniCod.mid(str,0,j/2);
            str=getUniCodeRemove(str,0,j/2+1);
        } else {
            tStr = str; str = "";
        }

        //AutoWrap
        if ((optn & 0x02) == 0x02) {
            while (wd < tStr.length()/2) {
                nn0 = -1; nn1 = -1;
                //
                for (int k = 0; k < wd; k++) {
                    wcm=char(tStr[2*k]) + (char(tStr[2*k+1])<<8);
                    if (wcm==sc) nn0 = k; //check space
                    if (wcm==sm) nn1 = k; //check minus
                }//for k
                //HypenWrap
                if (((optn & 0x04) == 0x04) && (nn1 > nn0)) {
                    getVTTextDirect(getUniCod.mid(tStr,0,nn1+1), pVT_Net, textMode);
                    getUniCodeRemove(tStr,0,nn1+1);
                    pVT_Net->fntLine++;
                } else {
                    if (nn0 < 0) {
                        getVTTextDirect(getUniCod.mid(tStr,0,wd), pVT_Net, textMode);
                        tStr=getUniCodeRemove(tStr,0,wd);
                        pVT_Net->fntLine++;
                    } else {
                        getVTTextDirect(getUniCod.mid(tStr,0,nn0+1), pVT_Net, textMode);
                        tStr=getUniCodeRemove(tStr,0,nn0+2);
                        pVT_Net->fntLine++;
                    }
                }
                //
            }//while
            //
            if (tStr.length() > 0) {
                getVTTextDirect(tStr, pVT_Net, textMode);
                pVT_Net->fntLine++;
            }
        } else {
            if (tStr.length() > 0) {
                getVTTextDirect(tStr, pVT_Net, textMode);
                pVT_Net->fntLine++;
            };
        } ////opt wrap
    } //while text
};//TVTObject::getVTWrapModeTextUniCode


//------------------------------------------------------------------------------
//get reference VTFontAttribute
uint16_t TVTObject::setVTObjectText(QString str,TVT_ViewRect *pViewRect, TVT_Net *pVT_Net, uint16_t fntID) {
    uint8_t color=0,fntColor=0,fntSize=0,fntType=0,fntStyle=0,fntNr0=0,fntNr=0,fntSr=0,fntW=0,fntH=0,cIdx=0,optn=0,en=1;
    bool fntFlash_hs=false, fntFlash_is=false;
    int16_t  x = pVT_Net->x, y = pVT_Net->y, xx = x, yy = y, refIdx=-1,objIdx=pVT_Net->objNr;
    uint16_t w = pVT_Net->w, h = pVT_Net->h, len=str.length();
    uint8_t fntJust = pVT_Net->fntJust;
    wchar_t mc=0x0000,uni=0xFFFE;
    QString fntName="arial0_0";
    //
    optn=getVTObjectAttributeInt32("VTOptions",pVT_Net);
    cIdx=getVTObjectAttributeInt32("VTBackgroundColour",pVT_Net);
    if (HasInArray(VTObjType,inpObjSet)) en=getVTObjectAttributeInt32("VTEnabled",pVT_Net);
    //
    pVT_Net->optn = optn;
    pVT_Net->uniCode=false;pVT_Net->fntLine=1;
    //
    //check uniCode
    if (len>=2) {
        mc=(char(str[0].toLatin1())<<8) + (char(str[1].toLatin1())<<0);
        if (mc==uni) {
            str=getUniCodeRemove(str,0,1);
            pVT_Net->uniCode=true;
        }
    }
    //
    refIdx=getVTObjID(pVT_Net,fntID);
    if (refIdx>=0) {
        //get Attribues
        getVTObjectFromList(pVT_Net,refIdx);
        fntColor = getVTObjectAttributeInt32("VTFontColour",pVT_Net);
        fntSize  = getVTObjectAttributeInt32("VTFontSize",pVT_Net);
        fntType  = getVTObjectAttributeInt32("VTFontType",pVT_Net);
        fntStyle = getVTObjectAttributeInt32("VTFontStyle",pVT_Net);
        getVTObjectFromList(pVT_Net,objIdx);
    }
    //
    color = fntColor;
    fntFlash_is=((fntStyle & 0x20) > 0);
    fntFlash_hs=((fntStyle & 0x40) > 0);
    //
    //Flash inverted mode or hidden mode
    if ((fntFlash_hs) ||  (fntFlash_is)) {
        pVT_Net->FlashList+=QString::number(VTObjID) + "," + QString(x) + "," + QString(y) + "," + QString(w) + "," + QString(h) + ",\n";
        //
        if (fntFlash_hs) {
            if (pVT_Net->Flash>=3) {
                //Set_fillRect(pVT_Net,x,y,w,h,pVT_Net->FlashColor);
                return color;
            }
        } else {
            if (fntFlash_is) {
                if (pVT_Net->Flash>=3) fntStyle=(fntStyle | 0x10); else fntStyle=(fntStyle & 0xEF);
            }
        }
    }//fntFlash
    //
    //Inverted mode
    if ((fntStyle & 0x10) > 0) {
        if ((optn & 0x01) == 0) {
            Set_fillRect(pVT_Net,x, y, w, h, color);
        }
        color = cIdx;
    } else {
        if ((optn & 0x01)==0) {
            Set_fillRect(pVT_Net,x,y,w,h,cIdx);
        }
    }
    //
    if ((fntSize != pVT_Net->fntSize) || (fntStyle != pVT_Net->fntStyle)) {
        fntNr=fntSize;
        //
        if ((fntStyle & 0x09) == 0x01) fntSr = 1; //Bold
        if ((fntStyle & 0x09) == 0x08) fntSr = 2; //Italic
        if ((fntStyle & 0x09) == 0x09) fntSr = 3; //Bold+Italic
        //
        if (pVT_Net->fontSet[fntNr][fntSr] == 0) {
            fntSr = 0; fntNr0=fntNr;
            for (int i = fntNr0; i >= 0; i--) {
                if (pVT_Net->fontSet[i][fntSr]==1) {
                    fntNr = i;
                    break;
                }
            }//for i
        }
        //
        if ((fntNr != pVT_Net->fntNr) || (fntSr != pVT_Net->fntSr)) {
            fntName = "arial" + QString::number(pVT_Net->fontSet[fntNr][6]) + "-" +  QString(fntSr);
            //qWarning() << fntName;
            //
            //Load new font
            if (!Set_loadFont(pVT_Net,fntName)) {
                fntNr = pVT_Net->fntNr; fntSr = pVT_Net->fntSr;
                fntSize=pVT_Net->fntSize; fntStyle=pVT_Net->fntStyle; fntType=pVT_Net->fntType;
            }
        }
    } else {
        fntNr = pVT_Net->fntNr; fntSr = pVT_Net->fntSr;
    }
    //
    pVT_Net->fntNr = fntNr; pVT_Net->fntSr = fntSr;
    pVT_Net->fntSize = fntSize; pVT_Net->fntStyle = fntStyle; pVT_Net->fntType = fntType;
    pVT_Net->fntColor = fntColor; pVT_Net->color = color; pVT_Net->optn = optn;
    //
    fntW = pVT_Net->fontSet[fntNr][4];
    fntH = pVT_Net->fontSet[fntNr][5];
    //
    Set_setTextColor(pVT_Net,color);
    //
    if (HasInArray(VTObjType,strgObjSet)) {
        //getStringHEXInfo(str,pVT_Net);
        //text string
        while ((str.indexOf(0x0D)==0) && (str.indexOf(0x0A)==1)) {
            str.remove(0,2);y+=fntH; yy=y;
        }
        while (str.indexOf(0x0A)==0) {
            str.remove(0,1);y+=fntH; yy=y;
        }
        while (str.indexOf(0x0D)==0) {
            str.remove(0,1);
        }
        //
        getVTWrapModeText(str, pVT_Net, false);
    }
    //Vertical Middle/Bottom
    switch (fntJust) {
        case 4 ... 7:  yy = y + (h - pVT_Net->fntLine * fntH) / 2; break; //Middle
        case 8 ... 11: yy = y + (h - pVT_Net->fntLine * fntH);  break;    //Bottom
    }
    //
    pVT_Net->y = yy;
    if (HasInArray(VTObjType,strgObjSet)) {
        //text string
        getVTWrapModeText(str, pVT_Net, true);
    }else {
        //numeric string
        if ((pVT_Net->optn & 0x02)>0) pVT_Net->fntJust=2;//set right for leading zeros
        pVT_Net->fntLine = 0;
        getVTTextDirect(str,pVT_Net,true);
    }
    //
    if (HasInArray(VTObjType,inpObjSet)) SetSelectState(pVT_Net,en,pViewRect);
    //
    pVT_Net->x = x; pVT_Net->y = y;
    //
    Set_setTextDatum(pVT_Net,MC_DATUM);
    Set_setTextColor(pVT_Net,TFT_BLACK);
    pVT_Net->fntJust=0;
    pVT_Net->uniCode=false;
    pVT_Net->optn =0x00;
    return color;
};//TVTObject::setVTObjectText


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
QString TVTObject::getAttributeStringValue(QString valueAttr, QString nameAttr, bool writeMode) {
    for (int i = 1; i < VT_AID_Nr; i++) {
        if (VTAttrAID[i].nameAID == nameAttr) {
            if (writeMode)
                VTAttrAID[i].valueAID = valueAttr;
            else
                valueAttr = VTAttrAID[i].valueAID;
            break;
        }
    }//for i
    return valueAttr;
};//TVTObject::getAttributeStringValue


//==============================================================================
void  TVTObject::setAID_Net(TVT_Net *pVT_Net,bool streamMode) {
    uint32_t aIdx=2,i=0,j=0,ww=0;
    uint8_t* buff=pVT_Net->streamStr.getBuffer();
    pVT_Net->VT_AID_Nr=VT_AID_Nr;
    for (i=0;i<VT_AID_Nr;i++){
        pVT_Net->VTAttrAID[i].numAID=VTAttrAID[i].numAID;
        pVT_Net->VTAttrAID[i].byteAID=VTAttrAID[i].byteAID;
        pVT_Net->VTAttrAID[i].typeAID=VTAttrAID[i].typeAID;
        pVT_Net->VTAttrAID[i].nameAID=VTAttrAID[i].nameAID;
        if (streamMode){
            VTAttrAID[i].valueAID=""; ww=0;
            for (j=0;j<VTAttrAID[i].byteAID;j++){
                VTAttrAID[i].valueAID+=char(buff[aIdx]);
                ww+=char(buff[aIdx])<<(8*j);
                aIdx++;
            }//for j
            //
            if ((VTObjType==8)  && (i==9)) aIdx+=ww;
            if ((VTObjType==11) && (i==8)) aIdx+=ww;
        }//streamMode
        pVT_Net->VTAttrAID[i].valueAID=VTAttrAID[i].valueAID;
    }//for i
};//TVTObject::setAID_Net



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//VTAttrAID[0].numAID=0;  VTAttrAID[0].byteAID=1; VTAttrAID[0].typeAID=0; VTAttrAID[0].nameAID="VTObjType";VTAttrAID[0].valueAID=QString::number(VTObjType);
QString TVTObject::getVTObjectAttributeString(QString nameAttr, TVT_Net *pVT_Net) {
    uint16_t aIdx=2;//offset VTObjID
    uint32_t nn=0,i=0,j=0,k=0;
    QString attrStr="";
    uint8_t* buff=pVT_Net->streamStr.getBuffer();
    //TEST
    //getStreamStrInfo(pVT_Net);
    for (i=0;i<pVT_Net->VT_AID_Nr;i++) {
        if (pVT_Net->VTAttrAID[i].nameAID==nameAttr) {
            nn=pVT_Net->VTAttrAID[i].byteAID;
            for (j=0;j<nn;j++) {
                k+=buff[aIdx]<<(8*j); aIdx++;
            }
            break;
        }
        aIdx+=pVT_Net->VTAttrAID[i].byteAID;
    } //for i
    //
    if (k>0){
        for (i=0;i<k;i++) attrStr+=char(buff[aIdx+i]);
    }
    pVT_Net->aIdx=aIdx;
    return attrStr;
} //TVTObject::getVTObjectAttributeString




//------------------------------------------------------------------------------
//VTAttrAID[0].numAID=0;  VTAttrAID[0].byteAID=1; VTAttrAID[0].typeAID=0; VTAttrAID[0].nameAID="VTObjType";VTAttrAID[0].valueAID=QString::number(VTObjType);
QString TVTObject::getVTObjectAttributeDirect(QString nameAttr, TVT_Net *pVT_Net) {
    uint8_t err = 0x01;
    uint16_t aIdx=2,len=0;//offset VTObjID
    uint32_t nn=0,i=0,j=0;
    QString attrStr="";
    uint8_t* buff=pVT_Net->streamStr.getBuffer();
    for (i=0;i<pVT_Net->VT_AID_Nr;i++) {
        if (pVT_Net->VTAttrAID[i].nameAID==nameAttr) {
            nn=pVT_Net->VTAttrAID[i].byteAID;
            for (j=0;j<nn;j++) attrStr+=char(buff[aIdx+j]);
            break;
        }
        //
        if (pVT_Net->VTAttrAID[i].nameAID=="VTLength"){
            nn=pVT_Net->VTAttrAID[i].byteAID;
            for (j=0;j<nn;j++) len+=char(buff[aIdx+j]);
            aIdx+=len;
            //qWarning() << len;
            //qWarning() << nn;
            //qWarning() << aIdx;
        }
        aIdx+=pVT_Net->VTAttrAID[i].byteAID;
    } //for i
    //
    pVT_Net->aIdx=aIdx;
    return attrStr;
};//TVTObject::getVTObjectAttributeDirect


//------------------------------------------------------------------------------
//VTAttrAID[0].numAID=0;  VTAttrAID[0].byteAID=1; VTAttrAID[0].typeAID=0; VTAttrAID[0].nameAID="VTObjType";VTAttrAID[0].valueAID=QString::number(VTObjType);
uint8_t TVTObject::SetVTObjectAttributeDirect(QString nameAttr, QString newValueAttr, TVT_Net *pVT_Net) {
    uint8_t err = 0x01,posMode=0;
    uint16_t aIdx=2;//offset VTObjID
    uint32_t nn=0,i=0,j=0,sSize=0,pPos=0, w=0,h=0,nw=0,nh=0;
    int16_t xx=0,yy=0,len=0;
    bool change=false,sAID=true,TEST=false;
    QString attrStr="",str="";
    uint8_t* buff;
    TVTObjIDPoints points;
    setAID_Net(pVT_Net);
    //
    if ((nameAttr=="VTSelect") && (newValueAttr.length()>0)) {
        //TEST
        if (HasInArray(VTObjType, inpObjSet)) {
            qWarning() << "TEST";
            qWarning() << VTObjID;
            qWarning() << VTObjType;
            qWarning() << nameAttr;
            VTSelect=char(newValueAttr[0].toLatin1());
            qWarning() << VTSelect;
            err=0;
        }
        return err;
    }//VTSelect
    //
    if (nameAttr=="VTScale") {
        //TEST
        qWarning() << nameAttr;
        getStreamStrInfo(pVT_Net);
        getStringHEXInfo(newValueAttr);
        //
        nameAttr="VTPoints";
        attrStr=getVTObjectAttributeDirect(nameAttr,pVT_Net);
        for (i=0;i<attrStr.length();i++) nn+=char(attrStr[i])<<8*i;
        nameAttr="VTWidth";
        attrStr=getVTObjectAttributeDirect(nameAttr,pVT_Net);
        for (i=0;i<attrStr.length();i++) w+=char(attrStr[i])<<8*i;
        buff=pVT_Net->streamStr.getBuffer();

        buff[pVT_Net->aIdx+0]=char(newValueAttr[0].toLatin1());
        buff[pVT_Net->aIdx+1]=char(newValueAttr[1].toLatin1());
        nameAttr="VTHeight";
        attrStr=getVTObjectAttributeDirect(nameAttr,pVT_Net);
        for (i=0;i<attrStr.length();i++) h+=char(attrStr[i])<<8*i;
        buff[pVT_Net->aIdx+0]=char(newValueAttr[2].toLatin1());
        buff[pVT_Net->aIdx+1]=char(newValueAttr[3].toLatin1());
        //
        nw=char(newValueAttr[0].toLatin1()) + (char(newValueAttr[1].toLatin1())<<8);
        nh=char(newValueAttr[2].toLatin1()) + (char(newValueAttr[3].toLatin1())<<8);
        for (i=0;i<VT_AID_Nr;i++) aIdx+=VTAttrAID[i].byteAID;
        //
        if ((w>0) && (h>0) && (nn>0)){
            points.xScale=1.000*nw/w;
            points.yScale=1.000*nh/h;
            for (i=0;i<nn;i++){
                xx=buff[aIdx+4*i+0] + (buff[aIdx+4*i+1]<<8);
                yy=buff[aIdx+4*i+2] + (buff[aIdx+4*i+3]<<8);
                xx=xx*points.xScale;
                yy=yy*points.yScale;
                buff[aIdx+4*i+0]=char((xx>>0) & 0xFF);
                buff[aIdx+4*i+1]=char((xx>>8) & 0xFF);
                buff[aIdx+4*i+2]=char((yy>>0) & 0xFF);
                buff[aIdx+4*i+3]=char((yy>>8) & 0xFF);
            }

            //TEST
            getStreamStrInfo(pVT_Net);
            err=0x00;
            pVT_Net->VT_ChangeAttr=true;
            setVTObjectListValue(pVT_Net);
        }
        return err;
    }//VTScale
    //
    //
    if (nameAttr=="VTPoints") {
        //TEST
        //getStreamStrInfo(pVT_Net);
        //getStringHEXInfo(newValueAttr);
        //
        attrStr=getVTObjectAttributeDirect(nameAttr,pVT_Net);
        len=attrStr.length();
        for (i=0;i<attrStr.length();i++) nn+=char(attrStr[i])<<8*i;
        for (i=0;i<VT_AID_Nr;i++) aIdx+=VTAttrAID[i].byteAID;
        uint8_t idx=char(newValueAttr[0].toLatin1());
        buff=pVT_Net->streamStr.getBuffer();
        if (idx<nn){
            for (i=1;i<newValueAttr.length();i++)
                buff[aIdx+4*idx+i-1]=char(newValueAttr[i].toLatin1());
            //TEST
            //getStreamStrInfo(pVT_Net);
            //
            err=0x00;
            pVT_Net->VT_ChangeAttr=true;
            setVTObjectListValue(pVT_Net);
        }
        return err;
    }//VTPoints
    //
    //
    if (nameAttr=="VTLength") {
        //TEST
        //getStreamStrInfo(pVT_Net);
        attrStr=getVTObjectAttributeDirect(nameAttr,pVT_Net);
        for (i=0;i<attrStr.length();i++) nn+=char(attrStr[i])<<8*i;
        aIdx=pVT_Net->aIdx;
        nn=nn+attrStr.length(); attrStr="";
        buff=pVT_Net->streamStr.getBuffer();
        sSize=pVT_Net->streamStr.getSize();
        for (i=aIdx+nn;i<sSize;i++) attrStr+=char(buff[i]);
        pVT_Net->streamStr.setSize(aIdx);
        len=newValueAttr.length();
        pVT_Net->streamStr.writeBytesVal(len,1 + (VTObjType!=gInpStringType));
        //
        pVT_Net->streamStr.writeBytes((uint8_t*)newValueAttr.constData(),len);
        len=attrStr.length();
        pVT_Net->streamStr.writeBytes((uint8_t*) attrStr.constData(),len);
        //TEST
        //getStreamStrInfo(pVT_Net);
        err=0x00;
        pVT_Net->VT_ChangeAttr=true;
        setVTObjectListValue(pVT_Net);
        return err;
    }//VTLength
    //
    //
    if (nameAttr.indexOf("VTItemList")>=0) {
        attrStr=getVTObjectAttributeDirect(nameAttr,pVT_Net);
        nn=char(attrStr[0]);attrStr="";j=char(newValueAttr[0].toLatin1());
        pVT_Net->VT_ChangeAttr=false;
        buff=pVT_Net->streamStr.getBuffer();
        for (i=0;i<VT_AID_Nr;i++) aIdx+=VTAttrAID[i].byteAID;
        //
        if ((j>=0) && (j<nn)){
            str="";
            str+=char(buff[aIdx+2*j]);
            str+=char(buff[aIdx+2*j+1]);
            attrStr+=str;
            if ((str[0]!=newValueAttr[1]) && (str[1]!=newValueAttr[2])){
                buff[aIdx+2*j]=char(newValueAttr[1].toLatin1());
                buff[aIdx+2*j+1]=char(newValueAttr[2].toLatin1());
                pVT_Net->VT_ChangeAttr=true;
                setVTObjectListValue(pVT_Net);
            }
            err=0x00;
        }
        return err;
    }//VTItemsList
    //
    //
    if (nameAttr.indexOf("VTObjects=")>=0) {
        str=nameAttr;str.replace("VTObjects=",""); posMode=str.toInt();
        nameAttr="VTObjects";
        attrStr=getVTObjectAttributeDirect(nameAttr,pVT_Net);
        //TEST
        //getStreamStrInfo(pVT_Net);
        //getStringHEXInfo(attrStr);
        //getStringHEXInfo(newValueAttr);
        //
        nn=char(attrStr[0]);attrStr="";
        pVT_Net->VT_ChangeAttr=false;
        buff=pVT_Net->streamStr.getBuffer();
        for (i=0;i<VT_AID_Nr;i++) aIdx+=VTAttrAID[i].byteAID;
        //
        for (i=0;i<nn;i++){
            str="";
            str+=char(buff[aIdx+6*i]);
            str+=char(buff[aIdx+1+6*i]);
            attrStr+=str;
            if ((str[0]==newValueAttr[0]) && (str[1]==newValueAttr[1])){
                //qWarning() << char(str[0]) + (char(str[1])<<8);
                if (posMode==0){
                    int16_t xPos=buff[aIdx+1+6*i+1] + (buff[aIdx+1+6*i+2]<<8);
                    int16_t yPos=buff[aIdx+1+6*i+3] + (buff[aIdx+1+6*i+4]<<8);
                    //qWarning() << xPos;
                    //qWarning() << yPos;
                    int8_t xChange=  char(newValueAttr[2].toLatin1())-0x7F;
                    int8_t yChange=  char(newValueAttr[3].toLatin1())-0x7F;
                    xPos=xPos + xChange;
                    yPos=yPos + yChange;
                    newValueAttr=newValueAttr.mid(0,2);
                    newValueAttr+=char((xPos >>0) & 0xFF);
                    newValueAttr+=char((xPos >>8) & 0xFF);
                    newValueAttr+=char((yPos >>0) & 0xFF);
                    newValueAttr+=char((yPos >>8) & 0xFF);
                    //getStringHEXInfo(newValueAttr);
                }
                //
                for (j=1;j<=4;j++) {
                    change=(buff[aIdx+1+6*i+j] != char(newValueAttr[j+1].toLatin1()));
                    pVT_Net->VT_ChangeAttr=((pVT_Net->VT_ChangeAttr) || (change));
                    buff[aIdx+1+6*i+j]=char(newValueAttr[j+1].toLatin1());
                }//for j
                //
                err=0x00;
            }
        }
        //getStringHEXInfo(attrStr);
        setVTObjectListValue(pVT_Net);
        return err;
    }//VTObjects
    //
    //
    if (nameAttr.indexOf("VT_AID=")>=0) {
        str=nameAttr;str.replace("VT_AID=",""); posMode=str.toInt();
        //TEST
        //qWarning() << str;
        //qWarning() << posMode;
        //
        if (posMode>=VT_AID_Nr) {
            pVT_Net->VT_ChangeAttr=false; err=1;
            return err;
        }
        //
        for (i=0;i<VT_AID_Nr;i++) {
            j=VTAttrAID[i].numAID;
            //
            if (j==posMode)   {
                nameAttr=VTAttrAID[i].nameAID;
                sAID=pVT_Net->VT_ChangeAttr;pVT_Net->VT_ChangeAttr=false;
                err=0;
                break;
            }
        }//for i
        //not return err;
    }//VT_AID
    //
    //TEST
    //getStringHEXInfo(newValueAttr);
    //getStreamStrInfo(pVT_Net);
    //
    for (i=0;i<VT_AID_Nr;i++) {
        //
        if (VTAttrAID[i].nameAID==nameAttr) {
            attrStr=getVTObjectAttributeDirect(nameAttr,pVT_Net);
            TEST=false;
            //TEST
            if (TEST){
                getStreamStrInfo(pVT_Net);
                getStringHEXInfo(attrStr);
                getStringHEXInfo(newValueAttr);
            }
            //
            pVT_Net->VT_AttrValue=0;
            nn=VTAttrAID[i].byteAID;
            //
            if ((newValueAttr!=attrStr) || (VTAttrAID[i].typeAID==0)){
                buff=pVT_Net->streamStr.getBuffer();
                //
                for (j=0;j<nn;j++) {
                    pVT_Net->VT_AttrValue+=char(attrStr[j])<<8*j;
                    //TEST
                    //getStringHEXInfo(newValueAttr);
                    //qWarning() << aIdx+j;
                    if (sAID) buff[aIdx+j]=char(newValueAttr[j].toLatin1());
                }//for j
                //
                if (sAID) {
                    //TEST
                    if (nameAttr=="VTOptions"){
                        //getStreamStrInfo(pVT_Net);
                        //qWarning() << pVT_Net->objNr;
                    }
                    if (nameAttr=="VTEnabled"){
                        //getStreamStrInfo(pVT_Net);
                        //qWarning() << pVT_Net->objNr;
                        //qWarning() << pVT_Net->VTObjID;
                        //qWarning() << pVT_Net->VTObjType;
                    }
                    //
                    //qWarning() << pVT_Net->objNr;
                    //getStreamStrInfo(pVT_Net);
                    setVTObjectListValue(pVT_Net);
                    //TEST
                    //getVTObjectListInfo(pVT_Net,pVT_Net->objNr);
                    pVT_Net->VT_ChangeAttr=true;
                }
            }//change
            //getStreamStrInfo(pVT_Net);
            err=0x00;
            break;
        }
        //
        //check input string VTLength for attribute=VTEnabled
        if ((pVT_Net->VTObjType==8) && (i==9)){
            nn=pVT_Net->streamStr.readBytesVal(1,aIdx);aIdx+=nn;
            //TEST
            if (TEST) {
                qWarning() << VTAttrAID[i].nameAID;
                qWarning() << nn;
                qWarning() << aIdx;
                getStreamStrInfo(pVT_Net);
            }
        }
        //
        aIdx+=VTAttrAID[i].byteAID;
    } //for i
    return err;
};//TVTObject::SetVTObjectAttributeDirect


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool getVTAttrValueDirect(TVT_Net *pVT_Net,TVTObject *pObj,TVTAttrValue *pAttr){
    bool valid=((getVTObjectListSize(pVT_Net)>0) && (pObj!=NULL));
    uint8_t i=0;
    QString attrStr="";
    if (valid) {
        attrStr=pObj->getVTObjectAttributeDirect(pAttr->attrName[0],pVT_Net);
        for (i=0;i<attrStr.length();i++) pAttr->attrValue[0]+=(char(attrStr[i]))<<8*i;
        attrStr=pObj->getVTObjectAttributeDirect(pAttr->attrName[1],pVT_Net);
        for (i=0;i<attrStr.length();i++) pAttr->attrValue[1]+=(char(attrStr[i]))<<8*i;
        attrStr=pObj->getVTObjectAttributeDirect(pAttr->attrName[2],pVT_Net);
        for (i=0;i<attrStr.length();i++) pAttr->attrValue[2]+=(char(attrStr[i]))<<8*i;
    }//valid
    return valid;
};//getVTAttrValueDirect


//------------------------------------------------------------------------------
bool getVTAttrValue(TVT_Net *pVT_Net,uint16_t attrID,TVTAttrValue *pAttr){
    bool valid=(getVTObjectListSize(pVT_Net)>0);
    int16_t objIdx=getVTObjID(pVT_Net,attrID);
    uint8_t* buff;
    valid=((valid) && (objIdx>=0));
    if (valid) {
        getVTObjectListValue(pVT_Net,objIdx);
        buff=pVT_Net->streamStr.getBuffer();

        pVT_Net->VTObjType=buff[2];
        pAttr->attrValue[0]=0;pAttr->attrValue[1]=0;pAttr->attrValue[2]=0;
        //
        if (pVT_Net->VTObjType==24){
            pAttr->attrName[0]="VTLineColour";pAttr->attrName[1]="VTLineWidth";pAttr->attrName[2]="VTLineArt";
            TVTLineAttribute *pObj = new TVTLineAttribute();
            pObj->setAID();
            valid=getVTAttrValueDirect(pVT_Net,pObj,pAttr);
            delete((TVTLineAttribute*) pObj);
            return valid;
        }
        if (pVT_Net->VTObjType==25){
            pAttr->attrName[0]="VTFillType";pAttr->attrName[1]="VTFillColour";pAttr->attrName[2]="VTFillPattern";
            TVTFillAttribute *pObj = new TVTFillAttribute();
            pObj->setAID();
            valid=getVTAttrValueDirect(pVT_Net,pObj,pAttr);
            delete((TVTFillAttribute*) pObj);
            return valid;
        }
    }//valid
    return valid;
};//getVTAttrValue


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//VTAttrAID[0].numAID=0;  VTAttrAID[0].byteAID=1; VTAttrAID[0].typeAID=0; VTAttrAID[0].nameAID="VTObjType";VTAttrAID[0].valueAID=QString::number(VTObjType);
QString getVTObjectAttribute(QString nameAttr,TVT_Net *pVT_Net) {
    uint8_t err = 0x01,optn=0x00;
    String attrStr="";
    if (pVT_Net->getAttributeMode) {
        if (pVT_Net->VTObjType==20) {
            TVTPictureGraphic vtObj;
            vtObj.setAID();
            attrStr=vtObj.getVTObjectAttributeDirect(nameAttr,pVT_Net);
        }
    }
    //
    qWarning() << "getVTObjectAttribute=";
    qWarning() << pVT_Net->VTObjType;
    return attrStr;
};//getVTObjectAttribute

//------------------------------------------------------------------------------
//set Attribute from CAN-message
uint8_t SetVTObjectAttribute(QString nameAttr, QString newValueAttr, TVT_Net *pVT_Net) {
    uint8_t err = 0x01;
    pVT_Net->nameAttr=nameAttr;pVT_Net->newValueAttr=newValueAttr;
    if (runClassObj(pVT_Net,NULL,NULL)) err=0x00;
    pVT_Net->nameAttr="";pVT_Net->newValueAttr="";
    return err;
};//SetVTObjectAttribute



//==============================================================================
uint8_t runMacroCommands(TVT_Net *pVT_Net, uint16_t objID) {
    uint8_t  error=0,bb=0xFF;
    int16_t  refIdx=getVTObjID(pVT_Net,objID);
    uint16_t len=8;
    bool  TEST=false;
    if (refIdx>=0) {
        getStreamStrInfo(pVT_Net);
        pVT_Net->streamStr.removeBytes(0,5);
        //getStreamStrInfo(pVT_Net);
        while (pVT_Net->streamStr.available()>=8){
            len=8;
            bb=pVT_Net->streamStr.peek();
            //SetActiveWorkingSet
            if (bb==0x90) len=9;
            //ChangeChildPosition
            if (bb==0xB4) len=9;
            //ChangeStringValue
            if (bb==0xB3) {
                len=pVT_Net->streamStr.getPos()+3;
                len=pVT_Net->streamStr.readBytesVal(2,len);
                len+=5;
            }
            //ExecuteMacro
            if (bb==0xBE) {
                qWarning() << "ExecuteMacro";
                //pVT_Net,pVT_Net->stream_Cmd[pVT_Net->listNr].clear();
            }
            //ExecuteExtendedMacro
            if (bb==0xBC) {
                qWarning() << "ExecuteExtendedMacro";
                //pVT_Net,pVT_Net->stream_Cmd[pVT_Net->listNr].clear();
            }
            //
            uint8_t mDATA[len];
            pVT_Net->streamStr.readBytes((uint8_t*)mDATA,len);
            pVT_Net->stream_Cmd[pVT_Net->listNr].write(len);
            pVT_Net->stream_Cmd[pVT_Net->listNr].writeBytes((uint8_t*)mDATA,len);
        }//while
        //
        TEST=true;
        if (TEST) {
            qWarning() << delm0;
            qWarning() << "stream_Cmd";
            getArray8Info(pVT_Net,pVT_Net->stream_Cmd[pVT_Net->listNr].getBuffer(),pVT_Net->stream_Cmd[pVT_Net->listNr].available());
            qWarning() << delm0;
        }
    } else error=0x01;
    //
    return error;
};//runMacroCommands

//------------------------------------------------------------------------------
QString getVTMacrosList(uint8_t eventID,TVT_Net *pVT_Net) {
    QString str="";
    uint16_t objID=0xFFFF,eID=0xFF;
    uint8_t mCount=pVT_Net->nameAttr.toInt();
    bool TEST=false;
    pVT_Net->nameAttr="";
    //TEST
    if (TEST){
        qWarning() << "mCount=" + QString(mCount);
        getStreamStrInfo(pVT_Net);
    }
    //
    while ((mCount>0) && (pVT_Net->streamStr.available())) {
        mCount--; objID=pVT_Net->streamStr.readBytesVal(1);
        if (objID==0xFF) {
            objID=pVT_Net->streamStr.readBytesVal(1);
            eID=pVT_Net->streamStr.readBytesVal(1);
            objID+=(pVT_Net->streamStr.readBytesVal(1)<<8);
        } else {
            eID=objID;
            objID=pVT_Net->streamStr.readBytesVal(1);
        }
        //
        //TEST
        if (TEST){
            qWarning() << eID;
            qWarning() << eventID;
            qWarning() << objID;
            qWarning() << delm0;
        }
        //
        if (eID==eventID) {
            str+=char((objID>>0) & 0xFF);
            str+=char((objID>>8) & 0xFF);
        }
    }//while
    //
    if (TEST){
        getStringHEXInfo(str,true);
        qWarning() << delm0;
    }
    return str;
};//getVTMacrosList

//------------------------------------------------------------------------------
bool getVTMacrosListEvents(TVT_Net *pVT_Net,uint16_t objID,uint8_t eventID){
    QString str="";
    uint32_t nn=0;
    int16_t refIdx=getVTObjID(pVT_Net,objID);
    bool TEST=false;
    //
    //TEST
    if (TEST){
        qWarning() << eventID;
        qWarning() << objID;
    }
    //
    if (refIdx>=0) {
        pVT_Net->nameAttr="VTMacros";
        //TEST
        if (TEST){
            getStreamStrInfo(pVT_Net);
            qWarning() << pVT_Net->VTObjID;
            qWarning() << pVT_Net->VTObjType;
        }
        runClassObj(pVT_Net,NULL,NULL);

        nn=pVT_Net->newValueAttr.toInt();
        //qWarning() << "VTMacroPos=" + QString(nn);
        pVT_Net->newValueAttr="";
        //TEST
        //qWarning() << nn;
        //qWarning() << delm0;
        //
        if (nn>0) {
            pVT_Net->streamStr.removeBytes(0,nn);
            //TEST
            //getStreamStrInfo(pVT_Net);
            str+=getVTMacrosList(eventID,pVT_Net);
            //if (str.length()>=2) getArray8Info(pVT_Net,(uint8_t*) str.constData(),str.length());
            //
            while (str.length()>=2) {
                objID=char(str[0]) + (char(str[1])<<8);
                str.remove(0,2);
                //TEST
                if (TEST) qWarning() << "Macro_objID=" + QString(objID);
                //run Macros in array
                runMacroCommands(pVT_Net,objID);
            }//while
        }//nn>0
    } //refIdx
    return (nn>0);
};//getVTMacrosListEvents


//==============================================================================
//Auxiliary procedure
//==============================================================================
void setVTAuxAssignListClear(TVT_Net *pVT_Net) {
    if (pVT_Net->listNr<listMax-1) {
        pVT_Net->VTAuxAssignList.clear();
        pVT_Net->VTPoolRefresh=true;
    }
};//setVTAuxAssignListClear



//==============================================================================
//==============================================================================
