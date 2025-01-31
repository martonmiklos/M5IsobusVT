//==============================================================================
//Parent Basic Objcects Classes
//TVTAttrAIDList, TVTObjectGlobalListList
//TVTObject, TVTObjectBgCol
//TVTObjectGlobalList, TVTPointObject,TVTLabelObject TVTObjectPointerList, TVTObjectItemList
//TVTPointList, TVTMacroListObject, TVTMacroList, TVTMacroCommandObject, TVTCommandList
//TVTObjectReferenceList
//TVTDeviceObjectList, TVTColourMapItemList, TVTAuxAssignList
//==============================================================================
//unit UnitVTObject.h;
//==============================================================================
#ifndef _UnitVTObject_
#define _UnitVTObject_

//==============================================================================
//==============================================================================
#ifndef UnitVTObjConsts_h
 #define UnitVTObjConsts_h
 #include "UnitVTObjConsts.h"
#endif
//



//==============================================================================
//Basic object of pooldata objects
//------------------------------------------------------------------------------
//CLASSES
//------------------------------------------------------------------------------
class TVT_StartEndPoint {
 public:
 int16_t startXX=0;
 int16_t startYY=0;
 int16_t endXX=0;
 int16_t endYY=0;
 //
 //int16_t startX0=0,startX1=0,startX2=0,startX3=0; 
 //int16_t startY0=0,startY1=0,startY2=0,startY3=0; 
 //
 //int16_t endX0=0  ,endX1=0  ,endX2=0,  endX3=0; 
 //int16_t endY0=0  ,endY1=0  ,endY2=0,  endY3=0; 

 int16_t startX[4]={0,0,0,0}; 
 int16_t startY[4]={0,0,0,0}; 
 //
 int16_t endX[4]={0,0,0,0}; 
 int16_t endY[4]={0,0,0,0}; 
};


//------------------------------------------------------------------------------
class TVT_ViewRect {
 public:
 int16_t viewX=0;
 int16_t viewY=0;
 uint16_t viewW=240;
 uint16_t viewH=240;
};


//------------------------------------------------------------------------------
class TVTListValues {
 public:
 uint16_t VTListValue[3]={0,0,0};
};


//------------------------------------------------------------------------------
class TVTPoints {
 public:
 float    pointX;
 float    pointY;
};


//------------------------------------------------------------------------------
class TVTObjIDPoints {
 public:
 float    pointID[256];
 float    pointX[256];
 float    pointY[256];
 uint8_t  pointNr=0;
 //
 int16_t pointIndex=-1;
 int16_t xPos =0;
 int16_t yPos =0;
 //
 float xScale=1;
 float yScale=1;
};


//------------------------------------------------------------------------------
//TVTObject
//------------------------------------------------------------------------------
//type global
class TVTObject {
  private:
  protected:
  public:
   QString   VTObjName="VTObject";
   uint8_t  VTObjType=0xFF;
   uint16_t VTObjID=0xFFFF;
   //
   uint8_t  VTError=0x00;
   uint8_t  VTSelect=0x00;
   uint32_t VTEvent=0;
   //
   uint8_t  VT_AID_Nr=32;
   TVTAttrAID VTAttrAID[32];
   //
   //procedure
   void     getVTDrawListAddObj(TVT_Net *pVT_Net,bool enabled,TVT_ViewRect *pViewRect);
   int8_t   SetSelectState     (TVT_Net *pVT_Net,bool enabled,TVT_ViewRect *pViewRect);
   //
   uint16_t getVTItemsNumber(uint8_t idx, QString attrName,TVT_Net *pVT_Net);
   //
   uint16_t setVTEvents (bool writeMode);
   //
   bool getVTColourItems(TVT_Net *pVT_Net,uint16_t nn, LoopbackStream *pStream);
   bool getVTString (TVT_Net *pVT_Net,uint16_t nn, LoopbackStream *pStream);
   bool getVTLabels (TVT_Net *pVT_Net,uint16_t nn, LoopbackStream *pStream);
   bool getVTObjects(TVT_Net *pVT_Net,uint8_t  nn, LoopbackStream *pStream);
   bool getVTItems  (TVT_Net *pVT_Net,uint8_t  nn, LoopbackStream *pStream);
   bool getVTMacros (TVT_Net *pVT_Net,uint8_t  nn, LoopbackStream *pStream);
   uint8_t getVTPoints (TVT_Net *pVT_Net,uint8_t  nn, LoopbackStream *pStream);
   //   
   bool  getVTLanguages (TVT_Net *pVT_Net,uint8_t nn,LoopbackStream *pStream);
   bool  getVTCodePlanes(TVT_Net *pVT_Net,uint8_t nn,LoopbackStream *pStream);
   uint16_t getVTCommands  (TVT_Net *pVT_Net,LoopbackStream *pStream);
   //
   void setAID_Net(TVT_Net *pVT_Net,bool streamMode=true);
   //
   virtual QString  getVTObjName(){return VTObjName;};
   virtual bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net){ return false;};
   virtual bool writeToStream  (TVT_Net *pVT_Net,LoopbackStream *pStream){};
   virtual bool readFromStream (TVT_Net *pVT_Net,LoopbackStream *pStream){};
   virtual bool readPictureFromStream(TVT_Net *pVT_Net,uint32_t bCount,LoopbackStream *pStream){};
   //
   uint16_t writeStringToStream (LoopbackStream *pStream);
   QString   readStringFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
   //AID
   virtual void setAID(){};
   virtual void getAID(){};
   //
   uint8_t setChangeAIDValue(uint8_t attrID,uint32_t attr,TVT_Net *pVT_Net);
   bool writeToStreamDirect(TVT_Net *pVT_Net,LoopbackStream *pStream);
   //set text
   void     setVTObjectTextDirect(QString str,TVT_Net *pVT_Net);
   uint16_t setVTObjectText      (QString str,TVT_ViewRect *pViewRect,TVT_Net *pVT_Net,uint16_t fntID);
   void     getVTTextDirect      (QString str,TVT_Net *pVT_Net,bool textMode);
   void     getVTWrapModeText       (QString str,TVT_Net *pVT_Net,bool textMode);
   void     getVTWrapModeTextUniCode(QString str,TVT_Net *pVT_Net,bool textMode);
   //
   QString   getAttributeStringValue(QString valueAttr, QString nameAttr,bool writeMode);
   
   uint8_t  SetVTObjectAttributeDirect(QString nameAttr, QString newValueAttr, TVT_Net *pVT_Net);
   //
   QString   getVTObjectAttributeDirect(QString nameAttr,TVT_Net *pVT_Net);
   QString   getVTObjectAttributeString(QString nameAttr, TVT_Net *pVT_Net);
   
   //Commands
   bool getMsgToAttr(uint8_t cFunc, CANMsg *pMsg,TVT_Net *pVT_Net);

};


//------------------------------------------------------------------------------
//Background Color object with backgroundColour attribute
//------------------------------------------------------------------------------
//type global
 class TVTObjectBgCol :public TVTObject {
  private:
    //Private-Deklarationen
  protected:
    //Protected-Deklarationen
    QString VTObjName="VTObjectBgCol";
    //Events
    //fVTOnChangeBackgroundColour :TVTOnChangeBackgroundColour;
  public:
    //{ Public-Deklarationen }
    uint8_t VTBackgroundColour=0;
    //procedure
 };


//------------------------------------------------------------------------------
//PROCEDURES
//==============================================================================
QString  getInsertLineValue(TVT_Net *pVT_Net, QString str);
uint8_t getVTInpFontType(TVT_Net *pVT_Net);
void    setUniCodeTextDirect(QString str, TVT_Net *pVT_Net);

//==============================================================================
//CAN Transmit/Receive
//==============================================================================
void VT_CAN_ResetStatusInfo(TVT_Net *pVT_Net,uint8_t yMax);
void WiFi_resetNetworks(TVT_Net *pVT_Net,QString str);

bool VT_CAN_TraceMsg(TVT_Net *pVT_Net,CANMsg *pMsg);
void VT_CAN_Init(TVT_Net *pVT_Net);
void VT_CAN_MsgFrameStr(TVT_Net *pVT_Net,CANMsg *pMsg);
void VT_CAN_MsgSend    (TVT_Net *pVT_Net,CANMsg *pMsg);
//
bool VT_CAN_MsgReceive(TVT_Net *pVT_Net,CANMsg *pMsg);
//
void setVTStatusMessage(TVT_Net *pVT_Net,CANMsg *pMsg);

//------------------------------------------------------------------------------
//global procedure
//------------------------------------------------------------------------------
void reset_FontImageMode(TVT_Net *pVT_Net);
//
void printDateTimeStructure(QString info,TVT_Net *pVT_Net);
void getDateTimeStructure(TVT_Net *pVT_Net);
void setDateTimeStructure(TVT_Net *pVT_Net);
//
time_t VTDateTimeMinute (TVT_Net *pVT_Net,bool info=false,int8_t mOffset=0);
time_t VTDateTime (TVT_Net *pVT_Net,bool info=false,int8_t hOffset=0);
time_t VTFlushTime(TVT_Net *pVT_Net,bool info=false);
time_t VTDateTimeInit(TVT_Net *pVT_Net,bool compile=false,bool setWiFi=false);
void   setup_VTDateTime(TVT_Net *pVT_Net);
//
void setSerialPrint(TVT_Net *pVT_Net,QString str, bool pln=false);

uint32_t getHeapStatus (TVT_Net *pVT_Net,uint8_t hNr=0);
bool  getMsgFromCmd (TVT_Net *pVT_Net,CANMsg *pMsg,QString str);
bool  setKeyNumberSelect (TVT_Net *pVT_Net,CANMsg *pMsg,QString str);
bool  setKeyDownUpSelect (TVT_Net *pVT_Net,CANMsg *pMsg,QString str);
void     paintSelectionFrame(TVT_Net *pVT_Net);
//
void     resetColorMap(TVT_Net *pVT_Net);
uint8_t  getColourMapInverse(TVT_Net *pVT_Net,uint8_t cIdx);

//------------------------------------------------------------------------------
uint16_t  get_TFTWidth(TVT_Net *pVT_Net);
uint16_t  get_TFTHeight(TVT_Net *pVT_Net);
//
TVTColorAlpha getColorIndex(uint8_t idx,TVT_Net *pVT_Net);
bool Set_ColorAlpha(TVT_Net *pVT_Net,TVTColorAlpha *pCa,uint8_t cIdx);
//
bool Set_fillPolygonDirect(TVT_Net *pVT_Net,TVTPoints points[],uint16_t pNr,uint8_t fillColor,uint8_t* tft_pic);
bool Set_fillPolygon(TVT_Net *pVT_Net,TVTPoints points[],uint16_t pNr,uint8_t fillColor);
//
bool GraphicDataPaintObjTo(TVT_Net *pVT_Net,TVTPixelXY *pXY, uint16_t nn);
bool setVTScaleTypeOptions(TVT_Net *pVT_Net,TVTPixelXY *pXY);
bool setPictureScaleX(TVT_Net *pVT_Net,TVTPixelXY *pXY,uint16_t* tft_buffer,uint16_t* usPixels);
bool setPictureScaleY(TVT_Net *pVT_Net,TVTPixelXY *pXY,uint16_t* tft_buffer,uint8_t* tft_alpha,uint16_t color);
//
bool PaintPNGToDirect(TVT_Net *pVT_Net);
bool PaintPNGDirect(TVT_Net *pVT_Net);
//
bool drawBmpDirect(TVT_Net *pVT_Net,TVTPixelXY* pXY);
void    getBitmapData(TVT_Net *pVT_Net,TVTPixelXY* pXY, uint32_t* pixel_color);
bool PaintBMPToDirect(TVT_Net *pVT_Net,TVTPixelXY* pXY);
//
bool PaintJPGToDirect(TVT_Net *pVT_Net);
bool PaintJPGDirect(TVT_Net *pVT_Net);
void    renderJPEG(TVT_Net *pVT_Net,TVTPixelXY *pXY);
//
bool PaintPictureToDirect(TVT_Net *pVT_Net,TVTPixelXY *pXY, uint8_t* tft_pic);
void    PaintToPixelDirect(TVT_Net *pVT_Net,TVTPixelXY *pXY,uint16_t* tft_buffer,uint8_t* tft_alpha,uint8_t* tft_pic);
//
void Set_setTextDatum(TVT_Net *pVT_Net,uint8_t dt);
//
void Set_setTextSize(TVT_Net *pVT_Net,uint8_t sIdx);
void Set_setTextColor(TVT_Net *pVT_Net,uint8_t cIdx);
void Set_setTextColorBg(TVT_Net *pVT_Net,uint16_t fgColor,uint16_t bgColor);
void Set_setTextFont(TVT_Net *pVT_Net,uint8_t fntNr);
//
#ifdef LOAD_GFXFF
void Set_setFreeFont(TVT_Net *pVT_Net,const GFXfont *f = NULL);
#endif
//
void Set_fillScreen(TVT_Net *pVT_Net,uint16_t color);
void Set_M5Stack_PSRAM(TVT_Net *pVT_Net,uint8_t psRam=1);
//
void Set_CheckDateTime(TVT_Net *pVT_Net);
void Set_alpha(TVT_Net *pVT_Net,uint8_t alpha);
void Set_alphaColor(TVT_Net *pVT_Net,uint16_t alphaColor);
void Set_setTransp(TVT_Net *pVT_Net,bool active);

bool Set_getScreenShot(TVT_Net *pVT_Net);
void Set_setScreenShot(TVT_Net *pVT_Net,bool active);
//
void Set_drawString(TVT_Net *pVT_Net,QString str, int16_t x, int16_t y,uint8_t tSize=1);
void Set_drawCentreString(TVT_Net *pVT_Net, QString str,int16_t x, int16_t y,uint8_t tSize=1);
void Set_drawChar  (TVT_Net *pVT_Net,char cc, int16_t x, int16_t y,uint8_t tSize=1);
void Set_drawNumber(TVT_Net *pVT_Net,int nn, int16_t x, int16_t y,uint8_t tSize=1);
//
bool Set_smFont(TVT_Net *pVT_Net);
void Set_unloadFont(TVT_Net *pVT_Net);
bool Set_loadFont(TVT_Net *pVT_Net,QString fntName);
bool Set_fontLoaded(TVT_Net *pVT_Net);
uint16_t Set_fontsLoaded(TVT_Net *pVT_Net);

void Set_setCursor(TVT_Net *pVT_Net,int16_t x,int16_t y);
void Set_drawGlyph(TVT_Net *pVT_Net,uint16_t un);

void Set_frameViewport(TVT_Net *pVT_Net,uint8_t cIdx,int16_t sel);
void Set_setViewport(TVT_Net *pVT_Net,int16_t x, int16_t y, uint16_t w, uint16_t h);
void Set_resetViewport(TVT_Net *pVT_Net);
void Set_drawRect(TVT_Net *pVT_Net,int16_t x, int16_t y, uint16_t w, uint16_t h, uint8_t cIdx);
void Set_drawRoundRect(TVT_Net *pVT_Net,int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t r, uint16_t color);
//
void Set_pushImageAlpha(TVT_Net *pVT_Net,int32_t x,int32_t y,int32_t w,int32_t h,uint16_t* tft_buffer,uint8_t* tft_alpha,uint16_t color);

void Set_fillRect(TVT_Net *pVT_Net,int16_t x, int16_t y, uint16_t w, uint16_t h, uint8_t cIdx);
void Set_drawWideLine(TVT_Net *pVT_Net,int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t lw, uint8_t cIdx);
void Set_drawLine    (TVT_Net *pVT_Net,int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t cIdx);
void Set_fillTriangle(TVT_Net *pVT_Net,int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t cIdx);
void Set_drawTriangle(TVT_Net *pVT_Net,int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t cIdx);
void Set_drawPixel   (TVT_Net *pVT_Net,int16_t x0, int16_t y0, uint8_t cIdx);
uint16_t Set_readPixel(TVT_Net *pVT_Net,int16_t x0, int16_t y0);
//
void    Set_setSwapBytes(TVT_Net *pVT_Net,bool swap);
bool Set_getSwapBytes(TVT_Net *pVT_Net);
//
//Ellipse, Meter, ArchedBarGraph
void getEllipseAngleLength(double _angle,int16_t rx,int16_t ry, int16_t *rxx,int16_t *ryy,double *sx,double *sy);
TVT_StartEndPoint drawArcTicks(TVT_Net *pVT_Net,int16_t start_angle, int16_t end_angle, int8_t w, uint8_t cIdx);

//------------------------------------------------------------------------------
bool getStreamHEX(LoopbackStream *pStream,TVT_Net *pVT_Net);
//------------------------------------------------------------------------------
void getStreamStrInfo (TVT_Net *pVT_Net,uint32_t dCount=0,bool last=false);
void getStreamDrawInfo(TVT_Net *pVT_Net,uint32_t dCount=0);
bool getStreamInfo(LoopbackStream *pStream,TVT_Net *pVT_Net);
QString  getStreamTextInfo(LoopbackStream *pStream,TVT_Net *pVT_Net);
uint16_t getArray8Info(TVT_Net *pVT_Net,uint8_t   *ay, uint16_t lCount,bool info=true);
void getArray16Info(TVT_Net *pVT_Net,uint16_t *ay, uint16_t lCount);
void getArray32Info(TVT_Net *pVT_Net,uint32_t *ay, uint16_t lCount);
//
void getAIDInfo(TVT_Net *pVT_Net);
//
//------------------------------------------------------------------------------
//VTObjectList
//------------------------------------------------------------------------------
void     getVTObjectListInfo  (TVT_Net *pVT_Net,int16_t objIdx,uint8_t showAttr=2);
uint16_t getVTObjectListSize  (TVT_Net *pVT_Net);
uint16_t setVTObjectListClear (TVT_Net *pVT_Net);
//
uint16_t getVTObjectListAdd   (TVT_Net *pVT_Net);
bool  getVTObjectListRemove(TVT_Net *pVT_Net,int16_t objIdx);
bool  setVTObjectListValue (TVT_Net *pVT_Net,int16_t idx=-1);
//
void     getVTObjectListValue(TVT_Net *pVT_Net,uint16_t idx);
//
uint32_t getVTObjPos   (TVT_Net *pVT_Net,uint16_t objIdx);
uint32_t getVTObjLength(TVT_Net *pVT_Net,uint16_t objIdx);
int16_t  getVTObjID    (TVT_Net *pVT_Net,uint16_t objID,bool typeMode=false,bool setStreamStr=true);
void     getVTAuxObjectList(TVT_Net *pVT_Net);

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//VTDrawList
//------------------------------------------------------------------------------
void     getVTDrawListInfo       (TVT_Net *pVT_Net,int16_t objIdx,uint8_t showAttr=2);
void     getVTDrawListInfoPrint  (TVT_Net *pVT_Net,int16_t objIdx,uint8_t showAttr=2);
uint16_t getVTDrawListSize  (TVT_Net *pVT_Net);
uint16_t setVTDrawListClear (TVT_Net *pVT_Net);
//
void     resetKeyButtonInputList(TVT_Net *pVT_Net);
QString   setVTDrawListSoftKey(TVT_Net *pVT_Net);
bool  setVTDrawListClearSelect (TVT_Net *pVT_Net,uint16_t objID);
uint16_t getVTDrawListAdd   (TVT_Net *pVT_Net);
void     getVTDrawListRemove(TVT_Net *pVT_Net,int16_t objIdx);
void     setVTDrawListValue (TVT_Net *pVT_Net,int16_t idx=-1);
//
void    getVTDrawListValue(TVT_Net *pVT_Net,uint16_t idx);
int16_t getVTDrawID       (TVT_Net *pVT_Net, uint16_t objID,bool typeMode=false);
int16_t getVTDrawSelect   (TVT_Net *pVT_Net, uint8_t keyNr,uint8_t selObjType);
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
uint32_t getVTObjectAttributeInt32(QString nameAttr, TVT_Net *pVT_Net);
TVT_ViewRect  getViewRect(TVT_ViewRect *pViewRect);

//------------------------------------------------------------------------------
QString  getWSNameFromName(TVT_Net *pVT_Net, QString wsName);
int8_t  getWSlistNrFromName(TVT_Net *pVT_Net, QString wsName);
QString  getWSNameFromAddress(TVT_Net *pVT_Net, uint8_t src);
void    setECUListNumber(TVT_Net *pVT_Net,CANMsg msg);
void    setECUAddress(TVT_Net *pVT_Net,CANMsg msg);
bool getVTActiveMask(TVT_Net *pVT_Net);
bool PaintActiveMask       (uint16_t maskID,TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
bool PaintActiveSoftKeyMask(uint16_t maskID,TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
//
void    getViewport(TVT_Net *pVT_Net, TVT_ViewRect *pViewRect, int16_t x, int16_t y, uint16_t w, uint16_t h);
bool getPoolObjectPaint(TVT_Net *pVT_Net);

//------------------------------------------------------------------------------
bool IsStringNumeric(QString str);
QString  getHexCharacterString(QString str,bool reverse=false);
QByteArray hexCharacterStringToBytes(QString string_);
//
//------------------------------------------------------------------------------
bool  SetObjPaintObjToRef (TVT_ViewRect *pViewRect,TVT_Net *pVT_Net,uint16_t objID,bool TypeMode=false);
bool  getVTObjectLoop(TVT_Net *pVT_Net);
bool  getVTObjectsPaint(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
void     getVTObjectFromList(TVT_Net *pVT_Net,int16_t objNr);


//------------------------------------------------------------------------------
uint8_t SetVTObjectAttribute(QString nameAttr, QString newValueAttr, TVT_Net *pVT_Net);
QString  getVTObjectAttribute(QString nameAttr,TVT_Net *pVT_Net);
//
void    setClearScreen(TVT_Net *pVT_Net,bool listClear);
bool VTPoolDataRefreshDirect(TVT_Net *pVT_Net,bool push=true);


//------------------------------------------------------------------------------
//global procedure
//------------------------------------------------------------------------------
bool removeClassObj(TVT_Net *pVT_Net,int16_t objIdx);
bool runClassObj      (TVT_Net *pVT_Net,TVT_ViewRect *pViewRect,LoopbackStream *pStream);
//
bool getVTAttrValueDirect(TVT_Net *pVT_Net,TVTObject *pObj,TVTAttrValue *pAttr);
bool getVTAttrValue      (TVT_Net *pVT_Net,uint16_t attrID, TVTAttrValue *pAttr);
QString  getVTMacrosList(uint8_t eventID, TVT_Net *pVT_Net);
uint8_t runMacroCommands(TVT_Net *pVT_Net, uint16_t objID);
bool getVTMacrosListEvents(TVT_Net *pVT_Net,uint16_t objID,uint8_t eventID);
//
void setVTAuxAssignListClear(TVT_Net *pVT_Net);

 
//==============================================================================
//==============================================================================

#endif //_UnitVTObject_
