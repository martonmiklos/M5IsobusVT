//==============================================================================
//Definition objects TVTWorkingSet, TVTMask, TVTAlarmMask,
// TVTContainer, TVTWindowMaskObject
// TVTAnimationObject
//==============================================================================
//unit UnitVTTopLevelObjects.h;
//==============================================================================
#ifndef UnitVTObject_h
 #define UnitVTObject_h
 #include "UnitVTObject.h"
#endif



//==============================================================================
//==============================================================================
//type 0
class TVTWorkingSet :public TVTObjectBgCol{
  private:
     
  protected:
    //Events ID
    uint8_t VTEventNr=5;
    uint8_t VTEventList[5]={VTOnActivate,VTOnDeactivate,VTOnChangeActiveMask,
                            VTOnChangeChildLocation,VTOnChangeChildPosition};
  public:
    QString   VTObjName="VTWorkingSet";
    //uint8_t  VTObjType=0;
    //
    bool  VTSelectable=1;
    uint16_t VTActiveMask=0xFFFF;
    uint16_t VTColourMap=0xFFFF ;
    uint16_t VTColourPalette=0xFFFF;
    //
    QString VTObjects="";//TVTObjectPointerList;
    QString VTMacros=""; //TVTMacroList;
    QString VTLanguages="";
    //
    //procedure
    bool  PaintObjTo(TVT_ViewRect *pViewRect, TVT_Net *pVT_Net);
    bool  writeToStream  (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool  readFromStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    //
    void setAID();
    void getAID();
    //
    QString getObjects()   {return VTObjects;};
    QString getMacros()    {return VTMacros;};
    QString getLanguages() {return VTLanguages;};
    //
    uint16_t getVTActiveMask(){return VTActiveMask;};
};




//------------------------------------------------------------------------------
//type global
class TVTMask :public TVTObjectBgCol {
  
  private:
  protected:
    QString  VTObjName="VTMask";
    //Events  ID
    uint8_t VTEventNr=6;
    uint8_t VTEventList[6]={VTOnShow,VTOnHide,VTOnChangeSoftKeyMask,
                            VTOnChangeAttribute,VTOnChangeChildLocation,VTOnChangeChildPosition};
  public:
    uint16_t VTSoftKeyMask=0xFFFF;
    QString VTObjects="";//TVTObjectPointerList;
    QString VTMacros=""; //TVTMacroList;
    //procedure
    virtual bool  PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net){};
    virtual bool  readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream){};
    virtual bool  writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream){};
    //
    bool getSoftKeyMask(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool PaintObjToMask(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    virtual void setAID(){};
    virtual void getAID(){};
    //
    QString getObjects()   {return VTObjects;};
    QString getMacros()    {return VTMacros;};
    uint16_t getVTSoftKeyMask(){return VTSoftKeyMask;};
    
};


//------------------------------------------------------------------------------
//type 1
class TVTDataMask : public TVTMask {
  private:
  protected:
  public:
   QString VTObjName="VTDataMask";
   //uint8_t VTObjType=1;
    //procedure
    bool  PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool  writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool  readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};  



//------------------------------------------------------------------------------
//type 2
class  TVTAlarmMask : public TVTMask {
  private:
  protected:
    //Events ID
    uint8_t VTOnChangePriority=17;  //TVTOnChangePriority;  //17
  public:
    QString VTObjName="VTAlarmMask";
    //uint8_t VTObjType=2;
    uint8_t VTPriority=1;
    uint8_t VTAcousticSignal=1;
    //procedure    
    bool  PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool  writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool  readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};

//------------------------------------------------------------------------------
//type 3
class  TVTContainer :public TVTObject {
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=5;
    uint8_t VTEventList[5]={VTOnShow,VTOnHide,VTOnChangeSize,
                            VTOnChangeChildLocation,VTOnChangeChildPosition};
  public:
    QString  VTObjName="VTContainer";
    //uint8_t  VTObjType=3;
    uint16_t VTHeight=0;
    uint16_t VTWidth=0;;
    bool  VTHidden;
    QString VTObjects="";//TVTObjectPointerList;
    QString VTMacros=""; //TVTMacroList;
    //procedure
    bool  PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool  writeToStream  (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool  readFromStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
    //
    QString getObjects()   {return VTObjects;};
    QString getMacros()    {return VTMacros;};
};



//------------------------------------------------------------------------------
//ISOVersion >04
//------------------------------------------------------------------------------
//type 34
class  TVTWindowMaskObject :public TVTObjectBgCol {
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=5;
    uint8_t VTEventList[5]={VTOnShow,VTOnHide,VTOnChangeAttribute,
                            VTOnChangeChildLocation,VTOnChangeChildPosition};
  public:
    QString  VTObjName="VTWindowMaskObject";
    //uint8_t VTObjType=34;
    uint8_t VTHeight=0;
    uint8_t VTWidth=0;;
    uint8_t VTWindowType=0; //TVTWindowType;
    uint8_t VTOptions=0;    //TVTKeyGroupOption;
    //
    uint16_t VTName       =0xFFFF;
    uint16_t VTWindowTitle=0xFFFF;
    uint16_t VTWindowIcon =0xFFFF;
    //
    QString VTObjRefs="";//TVTObjectReferenceList;
    QString VTObjects="";//TVTObjectPointerList;
    QString VTMacros=""; //TVTMacroList;
    //procedure
    bool  PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool  writeToStream  (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool  readFromStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
    //
    QString getObjects()   {return VTObjects;};
    QString getMacros()    {return VTMacros;};
};


//------------------------------------------------------------------------------
//ISOVersion >04
//------------------------------------------------------------------------------
//type 44
class  TVTAnimationObject :public TVTObject {
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=5;
    uint8_t VTEventList[5]={VTOnEnable,VTOnDisable,VTOnChangeAttribute,
                            VTOnChangeValue,VTOnChangeSize};
  public:
    QString  VTObjName="VTAnimationObject";
    //uint8_t  VTObjType=44;
    uint16_t VTHeight=0;
    uint16_t VTWidth=0;;
    uint16_t VTRefreshInterval;
    uint8_t  VTValue;
    //
    bool  VTEnabled;
    uint8_t  VTFirstChildIndex;
    uint8_t  VTLastChildIndex;
    uint8_t  VTDefaultChildIndex;
    //
    uint8_t  VTAnimationOptions;
    //helper
    uint8_t  VTAnimationSequence;        //TVTAnimationSequence;         //=(a0_SingleShotMode,a1_LoopMode);
    uint8_t  VTAnimationDisabledBehavior;//TVTAnimationDisabledBehavior; // =(b0_PauseMode,b1_ResetMode,b2_DefaultObjectMode,b3_BlankMode);
    //
    //helper
    bool  VTZ_VisibleMode;
    uint16_t VTZ_AnimateTime;
    uint8_t  VTZChangeIndex ;
    //list
    QString VTObjects="";//TVTObjectPointerList;
    QString VTMacros=""; //TVTMacroList;
    //procedure
    bool  PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool  writeToStream  (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool  readFromStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
    //
    QString getObjects()   {return VTObjects;};
    QString getMacros()    {return VTMacros;};
};

//==============================================================================
//==============================================================================
