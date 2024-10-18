//==============================================================================
//Definition objects TVTGraphicsContext
//==============================================================================
//unit UnitVTGraphicContextObject.h
//==============================================================================

#ifndef UnitVTObject_h
 #define UnitVTObject_h
 #include "UnitVTObject.h"
#endif


#ifndef UnitVTPictureGraphicObject_h
  #define UnitVTPictureGraphicObject_h
  #include "UnitVTPictureGraphicObject.h"
#endif 


//==============================================================================
//type 36
class TVTGraphicsContext : public TVTGraphicObject{
  private:
  protected:
    //Events ID
    //uint8_t VTEventNr=1;
    //uint8_t VTEventList[1]={VTOnChangeAttribute};  //9
  public:
    QString  VTObjName="VTGraphicsContext";
    //uint8_t  VTObjType=36;
    uint16_t VTWidth=0 ;  //Canvas width
    uint16_t VTHeight=0;  //Canvas height
    //
    bool VTViewportActive=false;
    uint16_t VTViewportWidth=0;
    uint16_t VTViewportHeight=0;
    QString   ViewportSizeStr="";

    int16_t VTViewportX;
    int16_t VTViewportY;
    QString  fViewportPosStr="";
    
    float VTViewportZoom=1.000;       //ShortInt -32.0 .. 32.0
    bool VTViewportZoomMode=false; //Pan and Zoom
    bool VTViewportVisible=true;
    //
    int16_t VTGraphicsCursorX=0;
    int16_t VTGraphicsCursorY=0;
    QString  GraphicsCursorPosStr="";
    bool VTGraphicsCursorVisible=false;
    bool GraphicsCursorMove=false;
    //
    uint8_t VTForegroundColour=0;
    uint8_t VTBackgroundColour=1;
    //
    uint8_t  VTOptions; //TVTContextOption;
    uint16_t VTLineAttributes=0xFFFF;
    uint16_t VTFillAttributes=0xFFFF;
    uint16_t VTFontAttributes=0xFFFF;
    //
    QString VTDrawText=""; //TVTWideString;
    //
    //helper
    bool VTZUniCode=false;
    //
    uint16_t DrawVTObject=0xFFFF;
    uint16_t CopyCanvasToPicture=0xFFFF;
    uint16_t CopyViewPortToPicture=0xFFFF;
    //
    QString DrawShape="";
    QString CommandStr="";
    QString SizeStr="";
    //
    bool Undo=false;
    uint16_t DrawWidth=0;
    uint16_t DrawHeight=0;
    bool DrawTextSize=false;
    //
    int16_t DrawOldX=0;
    int16_t DrawOldY=0;
    bool DrawVisible=false;
    bool DrawPoint=false;
    QString  DrawPointText="";
    //
    bool ViewPortPosXY=false;
    
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    //
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readPictureFromStream(TVT_Net *pVT_Net,uint32_t bCount,LoopbackStream *pStream);
    //
    void setAID();
    void getAID();
};


//==============================================================================
//==============================================================================
