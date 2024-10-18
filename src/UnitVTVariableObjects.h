//==============================================================================
//Definition objects TVTNumberVariable,TVTStringVariable,
//TVTColourMap,
//TVTColourPalette, TVTGraphicData, TVTScaledGraphic, TVTWorkingSetControl
//==============================================================================
//unit UnitVTVariableObjects.h
//==============================================================================
#ifndef UnitVTObject_h
 #define UnitVTObject_h
 #include "UnitVTObject.h"
#endif



//==============================================================================
//type 21
class  TVTNumberVariable : public TVTObject{
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnChangeValue};
  public:
    QString  VTObjName="VTNumberVariable";
    //uint8_t VTObjType=21;
    uint32_t VTValue=0;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};


//------------------------------------------------------------------------------
//type 22
class TVTStringVariable :public TVTObject{
  private:
  protected:
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnChangeValue};

  public:
    QString  VTObjName="VTStringVariable";
    //uint8_t VTObjType=22;
    uint16_t VTLength=4;
    QString   VTValue="TEST";
    bool  VTZValidLength=true;
    bool  VTZValidCheck=true;
    bool  VTZUniCode=false;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    //
    void setAID();
    void getAID();
};


//------------------------------------------------------------------------------
//type 39
class TVTColourMap :public TVTObject{
  private:
  protected:
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnRefresh};
  public:
    QString  VTObjName="VTColourMap";
    //uint8_t VTObjType=39;
    uint16_t VTIndexNumber=2; //TVTColourMapTyp;
    //helper
    uint8_t VTZIndexItem=0;
    bool VTZIndexChange=false;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    void    setVTColourMap(TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    //
    void setAID();
    void getAID();
};
  
//------------------------------------------------------------------------------
//type 45
class TVTColourPalette :public TVTObject{
  private:
  protected:
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnChangeAttribute};
  public:
    QString  VTObjName="VTColourPalette";
    //uint8_t VTObjType=45;
    uint16_t VTOptions=0;
    uint16_t VTColourItems=0; 
    //helper
    uint8_t VTZIndexItem=0;
    bool VTZIndexChange=false;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    void    setVTColourPalette(TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    //
    void setAID();
    void getAID();
};


//------------------------------------------------------------------------------
//type 46
class TVTGraphicData :public TVTObject{
  private:
  protected:
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnRefresh};
  public:
    QString  VTObjName="VTGraphicData";
    //uint8_t VTObjType=46;
    uint8_t  VTFormat=0;
    QString   VTPicData=""; //TMemoryStream;
    //uint32_t VTRawCount=0;
    //helper
    QString   VTZPictureFileName="";
    uint8_t  Scale=1;
    uint16_t ScaleWidth=0;
    uint16_t ScaleHeight=0;
    uint8_t  ScaleType=0;
    uint8_t  ScaleOptions=0;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    //
    void setAID();
    void getAID();
};

//------------------------------------------------------------------------------
//type 48
class TVTScaledGraphic :public TVTObject{
  private:
  protected:
    uint8_t VTEventNr=2;
    uint8_t VTEventList[2]={VTOnChangeAttribute,VTOnChangeValue};
  public:
    QString  VTObjName="VTScaledGraphic";
    //uint8_t VTObjType=48;
    uint16_t VTWidth=0;
    uint16_t VTHeight=0;
    //
    uint8_t  VTScaleType=0;
    //
    uint8_t  VTScale_Mode=0;//TVTScaleMode;
    uint8_t  VTScale_Hor=0; //TVTScaleHorizontal;
    uint8_t  VTScale_Ver=0; //TVTScaleVertical;
    //
    uint8_t  VTScaleOptions=0;//TVTScaleOption;
    uint16_t VTValue=0xFFFF;
    //
    QString VTMacros="";
    //helper
    bool VTZClipping=false;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    //
    void setAID();
    void getAID();
};


//------------------------------------------------------------------------------
//type 47
class TVTWorkingSetControl :public TVTObject{
  private:
  protected:
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnRefresh};
  public:
    QString   VTObjName="VTWorkingSetControl";
    //uint8_t  VTObjType=47;
    uint8_t  VTByteNumber=0;
    uint16_t VTColourMap=0xFFFF;
    uint16_t VTColourPalette=0xFFFF;
    QString   VTLanguages="";
    //
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    //
    void setAID();
    void getAID();
};

//==============================================================================
//==============================================================================
