//==============================================================================
//Definition objects TVTOutputShapeObject,
//TVTLine, TVTRectangle,TVTEllipse, TVTPolygon
//==============================================================================
//unit UnitVTOutputShapeObjects.h
//==============================================================================
#ifndef UnitVTObject_h
 #define UnitVTObject_h
 #include "UnitVTObject.h"
#endif


//==============================================================================
//==============================================================================
//type global
class TVTOutputShapeObject : public TVTObject{
  private:
  protected:
    QString  VTObjName="VTOutputShapeObject";
    //Events ID
    uint8_t VTEventNr=2;
    uint8_t VTEventList[2]={VTOnChangeAttribute,VTOnChangeSize};
  public:
    uint16_t VTLineAttributes=0xFFFF;
    uint16_t VTWidth=0;
    uint16_t VTHeight=0;
    QString VTMacros="";
    //
    uint8_t  lineWidth=1;
    uint8_t  lineColor=cl_black;
    uint16_t lineArt=0xFFFF;
    //
    uint8_t  fillType=0;
    uint8_t  fillColor=cl_white;
    uint16_t fillAttr=0xFFFF;  
    //
    uint16_t aw=0;
    uint16_t ah=0;
    //
    //procedure
    virtual bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net){};
    virtual bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream){};
    virtual bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream){};
    virtual void setAID(){};
    virtual void getAID(){};
    //
    bool getLineAndFill(uint16_t lineID, uint16_t fillID, TVT_Net *pVT_Net);
    bool PaintObjToFillBitmap(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net,TVTPoints points[],uint16_t pNr);
};


//------------------------------------------------------------------------------
//type 13
class TVTLine : public TVTOutputShapeObject{
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=3;
    uint8_t VTEventList[3]={VTOnChangeAttribute,VTOnChangeSize,VTOnChangeEndPoint};
  public:
    QString  VTObjName="VTLine";
    //uint8_t VTObjType=13;
    bool VTLineDirection=false;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};


//------------------------------------------------------------------------------
//type 14
class TVTRectangle : public TVTOutputShapeObject{
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=2;
    uint8_t VTEventList[2]={VTOnChangeAttribute,VTOnChangeSize};
  public:
    QString  VTObjName="VTRectangle";
    //uint8_t  VTObjType=14;
    uint8_t  VTLineSuppression=0;
    uint16_t VTFillAttributes=0xFFFF;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};

//------------------------------------------------------------------------------
//type 15
class TVTEllipse : public TVTOutputShapeObject{
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=2;
    uint8_t VTEventList[2]={VTOnChangeAttribute,VTOnChangeSize};
  public:
    QString  VTObjName="VTEllipse";
    //uint8_t  VTObjType=15;
    uint8_t  VTEllipseType=0;
    uint8_t  VTStartAngle=0;
    uint8_t  VTEndAngle=0;
    uint16_t VTFillAttributes=0xFFFF;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};


//------------------------------------------------------------------------------
//type 16
class TVTPolygon : public TVTOutputShapeObject{
  private:
  protected:
    //Events ID
    uint8_t VTEventNr=2;
    uint8_t VTEventList[2]={VTOnChangeAttribute,VTOnChangeSize};
  public:
    QString  VTObjName="VTPolygon";
    //uint8_t VTObjType=16;
    uint8_t  VTPolygonType=0;
    uint16_t VTFillAttributes=0xFFFF;
    uint8_t  VTPoints=0;
    //
    bool VTZPointsSized=false;
    bool VTZPointsOptimized=false;
    //procedure
    bool PaintObjTo(TVT_ViewRect *pViewRect,TVT_Net *pVT_Net);
    void SetLinePolygon (TVT_Net *pVT_Net,TVTPoints points[]);    
    //
    bool writeToStream (TVT_Net *pVT_Net,LoopbackStream *pStream);
    bool readFromStream(TVT_Net *pVT_Net,LoopbackStream *pStream);
    void setAID();
    void getAID();
};


//==============================================================================
//==============================================================================
