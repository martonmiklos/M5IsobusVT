//==============================================================================
//Definition objects TVTAuxiliary, TVTAuxiliaryFuncInp,
//TVTAuxiliaryFunction, TVTAuxiliaryInput,
//TVTAuxFunction2,TVTAuxInput2,
//TVTAuxObject, TVTAuxDesignPointer
//==============================================================================
//unit UnitVTAuxiliaryObjects.h
//==============================================================================

#ifndef UnitVTObject_h
 #define UnitVTObject_h
 #include "UnitVTObject.h"
#endif


//==============================================================================
//------------------------------------------------------------------------------
//type global
class TVTAuxiliaryFuncInp : public TVTObjectBgCol{
  private:
  protected:
    QString   VTObjName="VTAuxiliaryFuncInp";
    //uint8_t  VTObjType=29,30,31,32;
    //Events
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnSoftKeyPress};
  public:
    uint8_t  VTFuncTyp=0;  //TVTFunctionTyp; //UnitVTObjDef.pas
    uint8_t  VTInputID=0;
    bool  VTEnabled=true;
    uint16_t VTInputValue1=0;
    uint16_t VTInputValue2=0;
    //
    QString VTAuxAssignment="";
    QString VTAuxAssignName="";
    QString VTObjects="";
    //
    uint16_t ModelIdentCode=0;
    uint16_t VTAuxAssignObjID=0xFFFF;
    uint16_t AuxPrefAssignObjID=0xFFFF;
    uint16_t AuxECU_Nr=0;
    bool  AuxAssignFunction=false;
    bool  AuxInpStatus=false;
    uint32_t AuxTimeStamp=0;
    //
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream  (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
    //
    QString getObjects()   {return VTObjects;};
};


//------------------------------------------------------------------------------
//type 29
class TVTAuxiliaryFunction : public TVTAuxiliaryFuncInp{
  private:
  protected:
    //Events
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnSoftKeyPress};
  public:
    QString   VTObjName="VTAuxiliaryFuncion";
    //uint8_t  VTObjType=29;
  //procedure
};


//------------------------------------------------------------------------------
//type 30
class TVTAuxiliaryInput : public TVTAuxiliaryFuncInp{
  private:
  protected:
    //Events
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnSoftKeyPress};
  public:
    QString   VTObjName="VTAuxiliaryInput";
    //uint8_t  VTObjType=30;
    //procedure
};


//------------------------------------------------------------------------------
//type 31
class TVTAuxiliaryFunction2 : public TVTAuxiliaryFuncInp{
  private:
  protected:
    //Events
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnSoftKeyPress};
  public:
    QString   VTObjName="VTAuxiliaryFunction2";
    //uint8_t VTObjType=31;
    bool VTCriticalControl=false; //Bit 5
    bool VTLockAssign=false;      //Bit 6
    bool VTSingleAssign=false;    //Bit 7
    //
    //procedure
    void getAID2();
};


//------------------------------------------------------------------------------
//type 32
class TVTAuxiliaryInput2 : public TVTAuxiliaryFuncInp{
  private:
  protected:
    //Events
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnSoftKeyPress};
  public:
    QString   VTObjName="VTAuxiliaryInput2";
    //uint8_t VTObjType=32;
    bool VTCriticalControl=false; //Bit 5
    bool VTSingleAssign=false;    //Bit 7
    //
    //procedure
    void getAID2();
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//type global
class TVTAuxObject : public TVTObject{
  private:
  protected:
    //Events
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnSoftKeyPress};
  public:
    QString   VTObjName="TVTAuxObject";
    uint8_t  VTPointerTyp=0; //         :TVTAuxPointerTyp;
    uint16_t VTValue=0xFFFF;
    //
    uint16_t VTZExternalObjectRef=0xFFFF;
    //
    bool VTEnabled=true;
    //fVTAuxItemList        :TVTObjectItemList;
    //fReferProp            :TVTObjectReferenceList;
    //
    //fVTFont               :TVTFont;
    //
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream  (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};


//------------------------------------------------------------------------------
//type 33
class TVTAuxDesignPointer : public TVTAuxObject{
  private:
  protected:
    //Events
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnSoftKeyPress};
  public:
    QString   VTObjName="TVTAuxObject";
    //uint8_t  VTObjType=33;
};


//==============================================================================
//==============================================================================
