//==============================================================================
//Definition objects TVTFieldObject,
//TVTOutputStringField, TVTOutputNumberField, TVTOutputListField
//==============================================================================
//unit UnitVTOutputFieldObjects.h
//==============================================================================
#ifndef UnitVTObject_h
 #define UnitVTObject_h
 #include "UnitVTObject.h"
#endif

//==============================================================================
//==============================================================================
//type
class   TVTFieldObject: public TVTObject{
  private:
  protected:
    //Events  ID
    uint8_t VTEventNr=4;
    uint8_t VTEventList[4]={VTOnChangeValue,VTOnChangeAttribute,
                            VTOnChangeSize,VTOnChangeBackgroundColour};
  public:
    uint16_t VTWidth=50;
    uint16_t VTFontAttributes=0xFFFF;
    uint16_t VTVariableReference=0xFFFF;
    bool  VTZFontSynchron=false;
    QString   VTZValue="";
    //
    uint8_t VTJustification=0x00;
    uint8_t VTJust_Horz=0x00;
    uint8_t VTJust_Vert=0x00;
    uint8_t VTBackgroundColour=0x01;
    //list
    QString VTMacros="";
    //
    //procedure
    virtual bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net){};
    virtual bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream){};
    virtual bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream){};
    virtual void setAID(){};
    virtual void getAID(){};
};  


//------------------------------------------------------------------------------
//type
class   TVTOutputFieldObject: public TVTFieldObject{
  private:
  protected:

  public:
    uint16_t VTHeight=50;
    //procedure
    virtual bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net){};
    virtual bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream){};
    virtual bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream){};
    virtual void setAID(){};
    virtual void getAID(){};
};  


//------------------------------------------------------------------------------
//type 11
class   TVTOutputStringField: public TVTOutputFieldObject{
  private:
  protected:
  public:
    QString   VTObjName="VTOutputStringField";
    //uint8_t  VTObjType=11;
    uint8_t  VTOptions=0x00;
    uint16_t VTLength=4;
    QString   VTValue="TEXT";
    bool  VTZValidLength=true;
    bool  VTZValidCheck=true;
    bool  VTZUniCode=false;
    //
    //procedure
    virtual bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    virtual bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    virtual bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};  



//------------------------------------------------------------------------------
//type 12
class   TVTOutputNumberField: public TVTOutputFieldObject{
  private:
  protected:
  public:
    QString   VTObjName="VTOutputNumberField";
    //uint8_t  VTObjType=12;
    uint8_t  VTOptions=0x00;
    uint32_t VTValue=0;
    int32_t  VTOffset=0;
    int32_t  VTScale=1;
    bool  VTZScaleCalc=true;
    //   
    uint8_t  VTNumOfDecimals=0;
    bool  VTFormat=false;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};  





//------------------------------------------------------------------------------
//type 37
class   TVTOutputListField: public TVTOutputFieldObject{
  private:
  protected:
  public:
    QString   VTObjName="VTOutputListField";
    //uint8_t  VTObjType=37;
    uint8_t ActiveItem=0;
    uint8_t VTZChangeIndex=0;
    //
    uint8_t VTValue=0;
    uint8_t VTBackgroundColour=0;
    bool VTZSkipMode=false;
    //list
    QString VTItems="";
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};  

//==============================================================================
//==============================================================================
