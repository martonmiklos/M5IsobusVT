QT       += core gui widgets serialbus

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/UnitVTActivationMsg.cpp \
    ../src/UnitVTAttributeObjects.cpp \
    ../src/UnitVTAuxAssignment.cpp \
    ../src/UnitVTAuxiliaryObjects.cpp \
    ../src/UnitVTCommandTECU.cpp \
    ../src/UnitVTCommandTechData.cpp \
    ../src/UnitVTExternalObject.cpp \
    ../src/UnitVTGraphicContextObject.cpp \
    ../src/UnitVTInputFieldObjects.cpp \
    ../src/UnitVTKeyObjects.cpp \
    ../src/UnitVTMacroCommandObject.cpp \
    ../src/UnitVTMacroObject.cpp \
    ../src/UnitVTObjConsts.cpp \
    ../src/UnitVTObject.cpp \
    ../src/UnitVTOutputFieldObjects.cpp \
    ../src/UnitVTOutputGraphicObjects.cpp \
    ../src/UnitVTOutputShapeObjects.cpp \
    ../src/UnitVTPictureGraphicObject.cpp \
    ../src/UnitVTPointerObject.cpp \
    ../src/UnitVTTopLevelObjects.cpp \
    ../src/UnitVTVariableObjects.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../src/UnitVTActivationMsg.h \
    ../src/UnitVTAttributeObjects.h \
    ../src/UnitVTAuxAssignment.h \
    ../src/UnitVTAuxiliaryObjects.h \
    ../src/UnitVTCommandTECU.h \
    ../src/UnitVTCommandTechData.h \
    ../src/UnitVTExternalObject.h \
    ../src/UnitVTGraphicContextObject.h \
    ../src/UnitVTInputFieldObjects.h \
    ../src/UnitVTKeyObjects.h \
    ../src/UnitVTMacroCommandObject.h \
    ../src/UnitVTMacroObject.h \
    ../src/UnitVTObjConsts.h \
    ../src/UnitVTObjCreatePool.h \
    ../src/UnitVTObject.h \
    ../src/UnitVTOutputFieldObjects.h \
    ../src/UnitVTOutputGraphicObjects.h \
    ../src/UnitVTOutputShapeObjects.h \
    ../src/UnitVTPictureGraphicObject.h \
    ../src/UnitVTPointerObject.h \
    ../src/UnitVTTopLevelObjects.h \
    ../src/UnitVTVariableObjects.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
