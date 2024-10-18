//==============================================================================
//Definition objects TVTCommandTechData
//TVTGetHardware, TVTGetNumberOfSoftKeys, TVTGetTextFontData,TVTGetMemory,
//TVTGetSupportedWideChars,
//
//TVTGetVersion, TVTStoreVersion, TVTLoadVersion, TVTDeleteVersion,
//TVTExtendedGetVersion, TVTExtendedStoreVersion, TVTExtendedLoadVersion, TVTExtendedDeleteVersion,
//
//TVTGetWindowMaskData,TVTGetSupportedObjects,TVTIdentifyVT, TVTScreenCapture,
//TVTProprietaryCommand,
//
//TVT_DiagConformance,
//
//==============================================================================
//unit UnitVTCommandTechData.h
//==============================================================================
#ifndef UnitVTObjConsts_h
 #define UnitVTObjConsts_h
 #include "UnitVTObjConsts.h"
#endif


//==============================================================================
#ifndef UnitVTObject_h
 #define UnitVTObject_h
 #include "UnitVTObject.h"
#endif

//==============================================================================
#ifndef UnitVTActivationMsg_h
 #define UnitVTActivationMsg_h
 #include "UnitVTActivationMsg.h"
#endif

//==============================================================================
//PROCEDURES
//==============================================================================
bool VT_CAN_Transmit(TVT_Net *pVT_Net,CANMsg *pMsg);
//
bool writeImageDirect(TVT_Net *pVT_Net);
bool writeImageScreen(const char * path,TVT_Net *pVT_Net);
bool readImageScreen (const char *path, TVT_Net *pVT_Net);


//==============================================================================
//CLASSES
//==============================================================================
//type    TVTTransportProtocol Implementaion 
class  TVTTransportProtocol {
private:
   //
  protected:
   //
  public:
   bool getTransportProtcol(CANMsg *pMsg,TVT_Net *pVT_Net,LoopbackStream *pStream, uint32_t rPGN=0);
   bool setTransportProtcol(CANMsg *pMsg,TVT_Net *pVT_Net,uint32_t rPGN=0);
};



//==============================================================================
//==============================================================================
/*
246.800 TX1 18FEE626  8  15 08 13 01 68 26 7D 7D
[FEE6] TimeDate (00)
TimeDate_LOC=26.01.2023 19:08:05
TimeDate_UTC=26.01.2023 19:08:05*
Byte0=[15]  21    Seconds=5.25
Byte1=[08]  8   Minutes=8
Byte2=[13]  19    Hour=19
Byte3=[01]  1   Month=1
Byte4=[68]  104   Day=26.75  PM
Byte5=[26]  38    Year(+1985)=38->2023
Byte6=[7D]  125   MinuteOffset=0 [valid]
Byte7=[7D]  125   HourOffset=0 [Local time offset]
*/
//type    TVT_TimeDate Implementaion    Request_PGN
class  TVT_TimeDate { //class(TVTMacroCommandObject)
private:
   //
  protected:
   //
  public:
    uint8_t  VT_Seconds=21;
    uint8_t  VT_Minutes=8;
    uint8_t  VT_Hour=19;
    uint8_t  VT_Month=1;
    uint8_t  VT_Day=104;
    uint8_t  VT_Year=38;
    uint8_t  VT_MinuteOffset=0;
    uint8_t  VT_HourOffset=0;
    //
    //QString  setWSNameSetToMsgAndStr(CANMsg *pMsg,TVT_Net *pVT_Net);
    //void    getWSNameFromMsg (CANMsg *pMsg,TVT_Net *pVT_Net);
    //QString  setWorkingSetName(CANMsg *pMsg,TVT_Net *pVT_Net);
    bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
};




//==============================================================================
//type    TVTAddressClaim Implementaion    AddrClm_PGN
class  TVTAddressClaim { //class(TVTMacroCommandObject)
private:
   //
  protected:
   //
  public:
    uint8_t  VT_ID=0x64;
    uint8_t  VT_Manufacture=0xFB;
    uint8_t  VT_ECUInstance=0x00;
    uint8_t  VT_FunctionInstance=0x00;
    uint8_t  VT_Function=0x1D;
    uint8_t  VT_DeviceClass=0x00;
    uint8_t  VT_DevClassInst=0x00;
    uint8_t  VT_IndustryGroup=0x02;
    uint8_t  VT_ReserveBit=0x00;
    uint8_t  VT_Arbitrary=0x00;
    //
    QString  setWSNameSetToMsgAndStr(CANMsg *pMsg,TVT_Net *pVT_Net);
    void    getWSNameFromMsg (CANMsg *pMsg,TVT_Net *pVT_Net);
    QString  setWorkingSetName(CANMsg *pMsg,TVT_Net *pVT_Net);
    bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
};


//==============================================================================
//type    TVTAddressClaimResponse Implementaion    AddrClm_PGN
class  TVTAddressClaimResponse :public TVTAddressClaim { 
private:
   //
  protected:
   //
  public:
    //
    bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
};



//==============================================================================
//type    TVTLanguage Implementaion    request_PGN
class  TVTLanguage { 
private:
   //
  protected:
   //
  public:
    QString VT_Language[3]={"en","de","nl"};
    //
    bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
};


//==============================================================================
//==============================================================================
//type    //199 $C7
class  TVTGetHardware { 
private:
   //
  protected:
   //
  public:
    uint8_t  VT0PCommFunction=0xC7;
    uint8_t  VTBootTime=0xFF;
    uint8_t  VTGraphicType=0x02;
    uint8_t  VTHardware=0x0C;
    uint16_t VTXPixel=240; 
    uint16_t VTYPixel=240; 
    //
    bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
};



//==============================================================================
//type   //194  $C2
  class TVTGetNumberOfSoftKeys {
  private:
   //
  protected:
   //
  public:
    uint8_t  VT0PCommFunction=0xC2;
    uint8_t  VTXDots           =80;
    uint8_t  VTYDots           =40;
    uint8_t  VTVirtualSoftKeys =64;
    uint8_t  VTPhysicalSoftKeys=6;
    //
    bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
  };
  
//==============================================================================
//type   //195  $C3
  class TVTGetTextFontData  { 
  private:
   //
  protected:
   //
  public:
    uint8_t  VT0PCommFunction=0xC3;
    uint8_t  VTSmallFontSize=0xFF;
    uint8_t  VTLargeFontSize=0xFF;
    uint8_t  VTFontStyle    =0xFF;
    //
    bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
  };


//------------------------------------------------------------------------------
//type  //192 $C0
  class TVTGetMemory { 
  private:
   //
  protected:
   //
  public:
   uint8_t  VT0PCommFunction=0xC0;
   uint32_t VTMemory           =0x00;  //0xFFFFFFFF;
   uint8_t  VTVersionNumber    =0x06;
   uint8_t  VTStatus           =0x00;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
  };


//----------------------------------------------------------------------------
//POOLDATA
//----------------------------------------------------------------------------
//type  //223 $B2
  class TVTDeleteObjectPool { 
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0xB2;
   uint8_t VTError=0x01;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
  };


//----------------------------------------------------------------------------
//type TVTEndOfObjectPool //$12
  class TVTEndOfObjectPool { 
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0x12;
   uint8_t VTError=0x00;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
  };



//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//type  Version global basis
  class TVTVersion { 
  private:
   //
  protected:
   //
  public:
   //
   uint8_t VT0PCommFunction=0xFF;
   uint8_t VTNumberOfVersionLabels=0;
   QString  VTVersionLabel="";
   QString  VTVersionFolder="";
   uint8_t VTError=0;
   //
   QString  formatBytes(size_t bytes);
   //
   int8_t  getValidCharacters (TVT_Net *pVT_Net);
   int8_t  getLastVersionLabel(TVT_Net *pVT_Net);
   //
   bool writeObjectFile(const char * path,TVT_Net *pVT_Net);
   bool storeFile(TVT_Net *pVT_Net);
   //
   bool writeFile (const char * path,TVT_Net *pVT_Net);
   bool writeStreamToFile(const char * path,LoopbackStream *pStream,TVT_Net *pVT_Net);
   //
   bool writeImage(const char * path,TVT_Net *pVT_Net);
   bool readFile  (const char * path, LoopbackStream *pStream,TVT_Net *pVT_Net);
   //
   bool deleteRecursive(const char *path,TVT_Net *pVT_Net);
   bool deleteFile(const char * path, LoopbackStream *pStream,TVT_Net *pVT_Net);
   bool createDir (const char * dirname,TVT_Net *pVT_Net);
   bool listDir   (const char * dirname, uint8_t levels,TVT_Net *pVT_Net);
   //
  };


//----------------------------------------------------------------------------
//type  //223 $DF or  224 $E0
  class TVTGetVersion : public TVTVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0xE0;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net,LoopbackStream *pStream);
  };


//----------------------------------------------------------------------------
//type   //208  $D0
  class TVTStoreVersion : public TVTVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0xD0;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net,LoopbackStream *pStream);
  };


//----------------------------------------------------------------------------
//type   //209  $D1
  class TVTLoadVersion : public TVTVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0xD1;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net,LoopbackStream *pStream);
  };


//----------------------------------------------------------------------------
//type    //210 $D2
  class TVTDeleteVersion : public TVTVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0xD2;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net,LoopbackStream *pStream);
  };
  

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//type  //211 $D3
  class TVTExtendedGetVersion : public TVTGetVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0xD3;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net,LoopbackStream *pStream);
  };


//----------------------------------------------------------------------------
//type   //212  $D4
  class TVTExtendedStoreVersion : public TVTStoreVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0xD4;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net,LoopbackStream *pStream);
  };



//----------------------------------------------------------------------------
//type   //213  $D5
  class TVTExtendedLoadVersion : public TVTLoadVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0xD5;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net,LoopbackStream *pStream);
  };

//----------------------------------------------------------------------------
//type   //214 $D6
  class TVTExtendedDeleteVersion : public TVTDeleteVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0xD6;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net,LoopbackStream *pStream);
  };



//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//type    //193 $C1
  class TVTGetSupportedWideChars : public TVTVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0xC1;
   //
   uint8_t  VTCodePlane=0x10;
   uint16_t VTFirstChar=0x0000;
   uint16_t VTLastChar =0xFFFF;
   uint8_t  VTRangeNumber=0x03;
   uint16_t VTRange[6]={0x0000,0x0FFF,0x1000,0x1FFF,0x2000,0x2FFF};
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net,LoopbackStream *pStream);
  };

//----------------------------------------------------------------------------
//type    //196 $C4
  class TVTGetWindowMaskData : public TVTVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0xC4;
   uint8_t VTDataMaskColour=0x01;
   uint8_t VTKeyColour     =0x01;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
  };


//----------------------------------------------------------------------------
//type    //197 $C5
  class TVTGetSupportedObjects : public TVTVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0xC5;
   uint16_t VTDataCount    =0;
   QString   VTStructure="";
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net,LoopbackStream *pStream);
  };

//------------------------------------------------------------------------------
//type    //187  $BB
  class TVTIdentifyVT : public TVTVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0xBB;
   uint8_t VTInstance=0;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
  };


//------------------------------------------------------------------------------
//type    //198  $C6
  class TVTScreenCapture : public TVTVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t  VT0PCommFunction=0xC6;
   uint8_t  VTItemRequested=0;
   uint8_t  VTPath=0;
   uint16_t VTImageID=0;
   //
   bool  setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
   bool  writeImage(const char *path,TVT_Net *pVT_Net);
   bool  readImage (const char *path,TVT_Net *pVT_Net);
  };


//--------------------------------------------------------------------------
//type  //$60 to $7F range
  class TVTProprietaryCommand : public TVTVersion {
  private:
   //
  protected:
   //
  public:
   uint8_t VT0PCommFunction=0x60;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
  };


//==============================================================================
//==============================================================================
//TVT_DiagConformance Implementaion
//DIAG_CONFORM_PGN  =0x00FD4200;
//DIAG_SOFTW_PGN    =0x00FEDA00;
//DIAG_HARDW_PGN    =0x00FDC500;
//DIAG_PROT_PGN     =0x00FD3200;
//DIAG_ACT_PGN      =0x00FECA00;
//DIAG_PRV_PGN      =0x00FECB00;
//DIAG_FUN_PGN      =0x00FC8E00;
//DIAG_PID_PGN      =0x00FC8D00;
//Request PGN       =0x00EA0000;
  class TVT_DiagConformance : public TVTVersion {
  private:
   //
  protected:
   //
  public:
   uint32_t VTPGN=0xFFFFFFFF;
   uint8_t  VT0PCommFunction=0xEA; //request PGN
   uint16_t VTDataCount=0;
   QString   VTStructure="";
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net,LoopbackStream *pStream);
   void    GetData_DiagConformance(LoopbackStream *pStream);
   QString  getDiagInfo(TVT_Net *pVT_Net, QString mStr, LoopbackStream *pStream);
   QString  getDiagHS_Str(TVT_Net *pVT_Net, uint32_t r_PGN);
   
  };



//==============================================================================
//==============================================================================
