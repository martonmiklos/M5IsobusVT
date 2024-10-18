//==============================================================================
//Definition objects TECU and Diagnostic Messages
//TVTAcknowledgeMessage, TVTWorkingSetMaster, TVTWorkingSetMember
//TVT_TECUFacilities, TVT_TECURemoteControl, TVT_TECURepetitionRate,
//TVT_DiagConformance,
//Functions
//SetBasedSpeedMessage, SetEngineSpeedMessage
//SetHitchStatusMessage, SetPTOOutShaftMessage,
//SetAuxiliaryValveMessage
//==============================================================================
//unit UnitVTCommandTECU.h
//==============================================================================
#ifndef UnitVTObjConsts_h
 #define UnitVTObjConsts_h
 #include "UnitVTObjConsts.h"
#endif

//==============================================================================
#ifndef UnitVTObject_h
 #define UnitVTObject_h
 #include "UnitVTObject.h"
#endif

//==============================================================================
//CLASSES
//==============================================================================
//type  PGN E8FF  $00, $01
  class TVTAcknowledgeMessage {
  private:
    //
  protected:
    //
   uint32_t VTPGN=0xFFFFFFFF;
  public:
   uint8_t VT0PCommFunction=0x00;
   uint8_t VTError=0x01;
   //
   bool setMsgToAttr (CANMsg *pMsg,TVT_Net *pVT_Net);
  };


//=========================================================================
QString getSpeedMessage (CANMsg *pMsg,TVT_Net *pVT_Net);
QString getEngineSpeedMessage(CANMsg *pMsg,TVT_Net *pVT_Net);
QString getHitchStatusMessage(CANMsg *pMsg,TVT_Net *pVT_Net);
QString getPTOOutShaftMessage(CANMsg *pMsg,TVT_Net *pVT_Net);
//
bool setTECUMonitor(TVT_Net *pVT_Net);
bool setTECUDataValue(int8_t k, TVT_Net *pVT_Net);
bool getTECUMonitor(CANMsg *pMsg,TVT_Net *pVT_Net);


//==============================================================================
//==============================================================================
