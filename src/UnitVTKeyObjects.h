//==============================================================================
//Definition objects TVTSoftkeyMask, TVTKey, TVTButton,
//TVTKeyGroupObject,TVTLabelReferenceListObject
//==============================================================================
//unit UnitVTKeyObjects.h;
//==============================================================================
#ifndef UnitVTObject_h
 #define UnitVTObject_h
 #include "UnitVTObject.h"
#endif


//==============================================================================
//==============================================================================
//type 4
class  TVTSoftKeyMask :public TVTObjectBgCol  {
  private:
  protected:
    //Events
    uint8_t VTEventNr=4;
    uint8_t VTEventList[4]={VTOnShow,VTOnHide,VTOnChangeSoftKeyMask,
                            VTOnChangeAttribute};
  public:
    QString   VTObjName="VTSoftKeyMask";
    //uint8_t VTObjType=4;
    QString  VTItems=""; //TVTObjectItemList;
    QString  VTMacros="";  //TVTMacroList;
    //procedure
    QString  getVTObjName(){return VTObjName;}; 
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
    //
    QString getItems()     {return VTItems;};
    QString getMacros()    {return VTMacros;};
};


//------------------------------------------------------------------------------
//type 5
class TVTKey : public TVTObjectBgCol{
  private:
  protected:
    //Events
    uint8_t VTEventNr=7;
    uint8_t VTEventList[7]={VTOnSoftKeyPress,VTOnSoftKeyRelease,
                            VTOnChangeAttribute,VTOnChangeChildLocation,VTOnChangeChildPosition,
                            VTOnInputFieldSelection,VTOnInputFieldDeselection};
  public:
    QString   VTObjName="VTKey";
    //uint8_t  VTObjType=5;
    //uint16_t VTInputStatus=0;
    uint8_t  VTKeyCode=0;
    QString  VTObjects ="";//TVTObjectList;
    QString  VTMacros="";  //TVTMacroList;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream  (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
    //
    QString getObjects()   {return VTObjects;};
    QString getMacros()    {return VTMacros;};
};

//------------------------------------------------------------------------------
//type 6
class TVTButton : public TVTObject {
  private:
  protected:
    //Events
    uint8_t VTEventNr=11;
    uint8_t VTEventList[11]={VTOnSoftKeyPress,VTOnSoftKeyRelease,VTOnChangeSize,
                            VTOnChangeAttribute,VTOnChangeBackgroundColour,
                            VTOnChangeChildLocation,VTOnChangeChildPosition,
                            VTOnEnable,VTOnDisable,
                            VTOnInputFieldSelection,VTOnInputFieldDeselection};
  public:
    QString   VTObjName="VTButton";
    //uint8_t VTObjType=6;
    int16_t VTInputStatus=0;
    int16_t VTWidth=0;
    int16_t VTHeight=0;
    //
    uint8_t VTBackgroundColour=0;
    uint8_t VTBorderColour=0;
    uint8_t VTKeyCode=0;
    uint8_t VTOptions=0;
    QString  VTObjects ="";//TVTObjectList;
    QString  VTMacros="";  //TVTMacroList;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
    //
    QString getObjects()   {return VTObjects;};
    QString getMacros()    {return VTMacros;};
};



//------------------------------------------------------------------------------
//Version 4
//------------------------------------------------------------------------------
//type 35
class  TVTKeyGroupObject :public TVTObject {
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnChangeAttribute};
  public:
    QString  VTObjName="TVTKeyGroupObject";
    //uint8_t VTObjType=35;
    uint8_t VTOptions=0;    //TVTKeyGroupOption;
    //
    uint16_t VTName        =0xFFFF;
    uint16_t VTKeyGroupIcon=0xFFFF;
    //
    QString VTItems=""; //TVTObjectItemList;
    QString VTMacros=""; //TVTMacroList;
    //procedure
    bool  PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool  writeToStream  (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool  readFromStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
    //
    QString getItems()     {return VTItems;};
    QString getMacros()    {return VTMacros;};
};


//------------------------------------------------------------------------------
//type 40
class  TVTLabelReferenceListObject :public TVTObject {
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnRefresh};
  public:
    QString  VTObjName="VTLabelReferenceListObject";
    //uint8_t VTObjType=40;
    //
    QString VTLabels=""; //TVTObjectLabelList;
    //procedure
    bool  PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool  writeToStream  (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool  readFromStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
    //
    QString getLabels()     {return VTLabels;};
};


//==============================================================================
//==============================================================================
