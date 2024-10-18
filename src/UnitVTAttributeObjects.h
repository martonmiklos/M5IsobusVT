//==============================================================================
//Definition objects TVTAttributeObject,
//TVTFontAttribute, TVTLineAttribute, TVTFillAttribute, TVTInputAttribute,
//TVTExtendedInputAttribute
//==============================================================================
//unit UnitVTAttributeObjects.h
//==============================================================================

#ifndef UnitVTObject_h
 #define UnitVTObject_h
 #include "UnitVTObject.h"
#endif


//==============================================================================
//type global
class TVTAttributeObject : public TVTObject {
  private:
  protected:
  public:
    QString VTMacros="";
    //procedure
    virtual bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net){};
    virtual bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream){};
    virtual bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream){};
    virtual void setAID(){};
    virtual void getAID(){};
};

//------------------------------------------------------------------------------
//type 23
class TVTFontAttribute : public TVTAttributeObject{
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=2;
    uint8_t VTEventList[2]={VTOnChangeFontAttributes,VTOnChangeAttribute};
  public:
    QString  VTObjName="VTFontAttribute";
    //uint8_t VTObjType=23;
    uint8_t VTFontColour=0;
    uint8_t VTFontSize=0;
    uint8_t VTFontType=0;
    uint8_t VTFontStyle=0;
    bool VTZFontHSFlash=false;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};


//------------------------------------------------------------------------------
//type 24
class TVTLineAttribute : public TVTAttributeObject{
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=2;
    uint8_t VTEventList[2]={VTOnChangeLineAttributes,VTOnChangeAttribute};
  public:
    QString  VTObjName="VTLineAttribute";
    //uint8_t  VTObjType=24;
    uint8_t  VTLineColour=0;
    uint8_t  VTLineWidth=1;
    uint16_t VTLineArt=0xFFFF;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};


//------------------------------------------------------------------------------
//type 25
class TVTFillAttribute : public TVTAttributeObject{
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=2;
    uint8_t VTEventList[2]={VTOnChangeFillAttributes,VTOnChangeAttribute};
  public:
    QString  VTObjName="VTFillAttribute";
    //uint8_t   VTObjType=25;
    uint8_t   VTFillType=0;
    uint8_t   VTFillColour=0;
    uint16_t  VTFillPattern=0xFFFF;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};


//------------------------------------------------------------------------------
//type 26
class TVTInputAttribute : public TVTAttributeObject{
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnChangeValue};
  public:
    QString  VTObjName="VTInputAttribute";
    //uint8_t VTObjType=26;
    bool VTValidationType=false;
    uint8_t VTLength        =4;
    QString  VTValidationString="TEST";
    bool VTZValidLength=false;
    bool VTZValidCheck =false;
    bool VTZUniCode    =false;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};


//------------------------------------------------------------------------------
//type 38
class TVTExtendedInputAttribute : public TVTAttributeObject{
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnChangeValue};
  public:
    QString  VTObjName="VTExtendedInputAttribute";
    //uint8_t VTObjType=38;
    bool VTValidationType=false;
    QString  VTCodePlanes="";
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};

//==============================================================================
//==============================================================================
