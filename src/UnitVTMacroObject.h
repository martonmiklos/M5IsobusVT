//==============================================================================
//Definition objects TVTMacroObject
//==============================================================================
//unit UnitVTMacroObject.h;
//==============================================================================
#ifndef UnitVTObject_h
 #define UnitVTObject_h
 #include "UnitVTObject.h"
#endif


//==============================================================================
//==============================================================================
//type 28
class TVTMacroObject : public TVTObject{
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=1;
    uint8_t VTEventList[1]={VTOnMacro};
  public:
    QString  VTObjName="VTMacroObject";
    //uint8_t  VTObjType=28;
    bool  VTExecuteMacro=false;
    uint16_t VTCommands=0;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};



//==============================================================================
//==============================================================================
