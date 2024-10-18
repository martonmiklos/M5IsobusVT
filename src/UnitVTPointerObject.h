//==============================================================================
//Definition objects
//TVTObjectPointer,
//==============================================================================
//unit UnitVTPointerObject.h;
//==============================================================================
#ifndef UnitVTObject_h
 #define UnitVTObject_h
 #include "UnitVTObject.h"
#endif


//==============================================================================
//==============================================================================
//type 27
class TVTObjectPointer : public TVTObject{
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnChangeValue};
  public:
    QString  VTObjName="VTObjectPointer";
    //uint8_t VTObjType=27;
    uint16_t VTValue=0xFFFF;
    //
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream  (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};


//==============================================================================
//type 232
class TVTObjectDummy : public TVTObject{
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnMacro};
  public:
    QString  VTObjName="VTObjectDummy";
    //uint8_t  VTObjType=232;
    uint16_t VTParentObjID=0xFFFF;
    uint8_t  VTParentObjType=0xFF;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream  (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};



//==============================================================================
//==============================================================================
