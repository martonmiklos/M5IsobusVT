//==============================================================================
//Definition and Create Pooldata objects
//==============================================================================
//unit UnitVTObjCreatePool.h;
//==============================================================================
#if defined(ESP32)
//void * StackPtrAtStart;
//void * StackPtrEnd;
//UBaseType_t watermarkStart;
#endif

//------------------------------------------------------------------------------
#ifndef UnitVTObjConsts_h
#define UnitVTObjConsts_h
#include "UnitVTObjConsts.h"
TVT_Net VT_Net;
TVT_Net *pVT_Net = &VT_Net;
#endif

//------------------------------------------------------------------------------
#ifndef UnitVTObject_h
#define UnitVTObject_h
#include "UnitVTObject.h"
#endif

//==============================================================================
#ifndef UnitVTMacroCommandObject_h
#define UnitVTMacroCommandObject_h
#include "UnitVTMacroCommandObject.h"
#endif

//==============================================================================
#ifndef UnitVTAuxAssignment_h
#define UnitVTAuxAssignment_h
#include "UnitVTAuxAssignment.h"
#endif

//==============================================================================
//CAN-Messages
//==============================================================================
#ifndef UnitVTCommandTechData_h
#define UnitVTCommandTechData_h
#include "UnitVTCommandTechData.h"
#endif

//==============================================================================
//TECU CAN-Messages
//==============================================================================
#ifndef UnitVTCommandTECU_h
#define UnitVTCommandTECU_h
#include "UnitVTCommandTECU.h"
#endif

//==============================================================================
//VTScreen Keyboard
//==============================================================================
#include <Free_Fonts.h>
//==============================================================================
//shift,blank,LF,CR,TAB,LR,ESC,ESC
String keyStr[8] = {"shift", "mod", "blank", "LF", "CR", "TAB", "left", "right"};
//String keyStr[8]={"SHT","MOD","BLK","LF","CR","TAB","LFT","RGT"};
//
wchar_t keymap[MAX_SHIFT_MODE][ROWS][COLS] = {
    {
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
        {'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'},
        {'q', 'r', 's', 't', 'u', 'v', 'w', 'x'},
        {'y', 'z', '=', '.', '{', '|', '}', '~'}, //,0x007F,0x0080},
        {'\001',
         '\002',
         0x0020,
         0x000A,
         0x000D,
         0x0009,
         '\003',
         '\004'}, //001=shift, 002=mode,0x0020=blank,0x000A=LF,0x000D=CR,0x0009=TAB,003=left,004=right
                  //shift,mode,blank,LF,CR,TAB,left,right
    },
    {
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
        {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
        {'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
        {'Y', 'Z', '[', '\\', ']', '^', '_', '`'},
        {'\001',
         '\002',
         0x0020,
         0x000A,
         0x000D,
         0x0009,
         '\003',
         '\004'}, //001=shift, 002=mode,0x0020=blank,0x000A=LF,0x000D=CR,0x0009=TAB,003=left,004=right
                  //shift,mode,blank,LF,CR,TAB,left,right
    },
    {
        {'1', '2', '3', '4', '5', '6', '7', '8'},
        {'9', '0', '-', '+', '.', ',', '=', 'E'},
        {'!', '"', '#', '$', '%', '&', '\'', '('},
        {')', '*', '/', ':', ';', '<', '>', '@'},
        {'\001',
         '\002',
         0x0020,
         0x000A,
         0x000D,
         0x0009,
         '\003',
         '\004'}, //001=shift, 002=mode,0x0020=blank,0x000A=LF,0x000D=CR,0x0009=TAB,003=left,004=right
                  //shift,mode,blank,LF,CR,TAB,left,right
    },
    {
        {'!', '"', '#', '$', '%', '&', '\'', '^'},
        {'(', ')', '*', '+', ',', '-', '.', '/'},
        {':', ';', '<', '=', '>', '?', '@', '['},
        {'\\', ']', '^', '_', '{', '|', '}', '~'},
        {'\001',
         '\002',
         0x0020,
         0x000A,
         0x000D,
         0x0009,
         '\003',
         '\004'}, //001=shift, 002=mode,0x0020=blank,0x000A=LF,0x000D=CR,0x0009=TAB,003=left,004=right
                  //shift,mode,blank,LF,CR,TAB,left,right
    },
};

//==============================================================================
//global variable
//==============================================================================
int16_t key_pos = 0, key_start = 0, key_max = 10, key_size = 20;
String input_text = "";
key_mode_t key_mode = KEY_MODE_LETTER;
bool shift_mode = false;
bool setGesture = false;

Button *touch_button_list[COLS * ROWS];
//uniCode viewer
Button *touch_button_uniCode[3];

setup_t user; // The library defines the type "setup_t" as a struct
              // Calling tft.getSetup(user) populates it with the settings


//==============================================================================
void getUserSetup()
{
    pVT_Net->tft.getSetup(user);
    //
    if (!pVT_Net->serialOut)
        return;
    qWarning() << "\n[code]\n";

    qWarning() << "TFT_eSPI ver = ";
    qWarning() << user.version;
    printProcessorName();
    qWarning() << "Transactions = ";
    qWarning() << (user.trans == 1) ? "Yes" : "No";
    qWarning() << "Interface    = ";
    qWarning() << (user.serial == 1) ? "SPI" : "Parallel";
    if (user.tft_driver != 0xE9D) // For ePaper displays the size is defined in the sketch
    {
        qWarning() << "Display driver = ";
        qWarning() << user.tft_driver, HEX; // Hexadecimal code
        qWarning() << "Display width  = ";
        qWarning() << user.tft_width; // Rotation 0 width and height
        qWarning() << "Display height = ";
        qWarning() << user.tft_height;
        qWarning() << ;
    } else if (user.tft_driver == 0xE9D)
        qWarning() << "Display driver = ePaper\n";

    if (user.r0_x_offset != 0) {
        qWarning() << "R0 x offset = ";
        qWarning() << user.r0_x_offset;
    } // Offsets, not all used yet
    if (user.r0_y_offset != 0) {
        qWarning() << "R0 y offset = ";
        qWarning() << user.r0_y_offset;
    }
    if (user.r1_x_offset != 0) {
        qWarning() << "R1 x offset = ";
        qWarning() << user.r1_x_offset;
    }
    if (user.r1_y_offset != 0) {
        qWarning() << "R1 y offset = ";
        qWarning() << user.r1_y_offset;
    }
    if (user.r2_x_offset != 0) {
        qWarning() << "R2 x offset = ";
        qWarning() << user.r2_x_offset;
    }
    if (user.r2_y_offset != 0) {
        qWarning() << "R2 y offset = ";
        qWarning() << user.r2_y_offset;
    }
    if (user.r3_x_offset != 0) {
        qWarning() << "R3 x offset = ";
        qWarning() << user.r3_x_offset;
    }
    if (user.r3_y_offset != 0) {
        qWarning() << "R3 y offset = ";
        qWarning() << user.r3_y_offset;
    }

    if (user.pin_tft_mosi != -1) {
        qWarning() << "MOSI    = ";
        qWarning() << "GPIO ";
        qWarning() << getPinName(user.pin_tft_mosi);
    }
    if (user.pin_tft_miso != -1) {
        qWarning() << "MISO    = ";
        qWarning() << "GPIO ";
        qWarning() << getPinName(user.pin_tft_miso);
    }
    if (user.pin_tft_clk != -1) {
        qWarning() << "SCK     = ";
        qWarning() << "GPIO ";
        qWarning() << getPinName(user.pin_tft_clk);
    }


    if (user.esp == 0x32F) {
        Serial.println(
            "\n>>>>> Note: STM32 pin references above D15 may not reflect board markings <<<<<");
        pinNameRef = "D";
    }
    if (user.pin_tft_cs != -1) {
        qWarning() << "TFT_CS   = " + pinNameRef;
        qWarning() << getPinName(user.pin_tft_cs);
    }
    if (user.pin_tft_dc != -1) {
        qWarning() << "TFT_DC   = " + pinNameRef;
        qWarning() << getPinName(user.pin_tft_dc);
    }
    if (user.pin_tft_rst != -1) {
        qWarning() << "TFT_RST  = " + pinNameRef;
        qWarning() << getPinName(user.pin_tft_rst);
    }

    if (user.pin_tch_cs != -1) {
        qWarning() << "TOUCH_CS = " + pinNameRef;
        qWarning() << getPinName(user.pin_tch_cs);
    }

    if (user.pin_tft_wr != -1) {
        qWarning() << "TFT_WR   = " + pinNameRef;
        qWarning() << getPinName(user.pin_tft_wr);
    }
    if (user.pin_tft_rd != -1) {
        qWarning() << "TFT_RD   = " + pinNameRef;
        qWarning() << getPinName(user.pin_tft_rd);
    }

    if (user.pin_tft_d0 != -1) {
        qWarning() << "\nTFT_D0 = " + pinNameRef;
        qWarning() << getPinName(user.pin_tft_d0);
    }
    if (user.pin_tft_d1 != -1) {
        qWarning() << "TFT_D1   = " + pinNameRef;
        qWarning() << getPinName(user.pin_tft_d1);
    }
    if (user.pin_tft_d2 != -1) {
        qWarning() << "TFT_D2   = " + pinNameRef;
        qWarning() << getPinName(user.pin_tft_d2);
    }
    if (user.pin_tft_d3 != -1) {
        qWarning() << "TFT_D3   = " + pinNameRef;
        qWarning() << getPinName(user.pin_tft_d3);
    }
    if (user.pin_tft_d4 != -1) {
        qWarning() << "TFT_D4   = " + pinNameRef;
        qWarning() << getPinName(user.pin_tft_d4);
    }
    if (user.pin_tft_d5 != -1) {
        qWarning() << "TFT_D5   = " + pinNameRef;
        qWarning() << getPinName(user.pin_tft_d5);
    }
    if (user.pin_tft_d6 != -1) {
        qWarning() << "TFT_D6   = " + pinNameRef;
        qWarning() << getPinName(user.pin_tft_d6);
    }
    if (user.pin_tft_d7 != -1) {
        qWarning() << "TFT_D7   = " + pinNameRef;
        qWarning() << getPinName(user.pin_tft_d7);
    }

    qWarning() << ;

    uint16_t fonts = Set_fontsLoaded(pVT_Net);
    if (fonts & (1 << 1))
        qWarning() << "Font GLCD   loaded\n";
    if (fonts & (1 << 2))
        qWarning() << "Font 2      loaded\n";
    if (fonts & (1 << 4))
        qWarning() << "Font 4      loaded\n";
    if (fonts & (1 << 6))
        qWarning() << "Font 6      loaded\n";
    if (fonts & (1 << 7))
        qWarning() << "Font 7      loaded\n";
    if (fonts & (1 << 9))
        qWarning() << "Font 8N     loaded\n";
    else if (fonts & (1 << 8))
        qWarning() << "Font 8      loaded\n";
    if (fonts & (1 << 15))
        qWarning() << "Smooth font enabled\n";
    qWarning() << "\n";

    if (user.serial == 1) {
        qWarning() << "Display SPI frequency = ";
        qWarning() << user.tft_spi_freq / 10.0;
    }
    if (user.pin_tch_cs != -1) {
        qWarning() << "Touch SPI frequency   = ";
        qWarning() << user.tch_spi_freq / 10.0;
    }

    qWarning() << "[/code]";
    qWarning() << delm1;
}; //getUserSetup

//------------------------------------------------------------------------------
// List files ESP32 SPIFFS memory or SD
//------------------------------------------------------------------------------
void listDir(fs::FS &fs, const char *dirname, uint8_t levels, QString str = "")
{
    uint16_t lCount = 0;
    String fileStr = "", dirStr = QString(dirname), fileSize = "";
    if ((pVT_Net->valid_sp) || (pVT_Net->valid_sd)) {
        if (dirStr.indexOf('/') == 0) {
            //TODO
        } else {
            dirStr = '/' + dirStr;
        }
        //
        setSerialPrint(pVT_Net, str + "Listing " + str + " directory:" + dirStr);
        //
        fs::File root = fs.open(dirStr.constData());
        //
        if (!root) {
            setSerialPrint(pVT_Net, "Failed to open directory");
            return;
        }
        if (!root.isDirectory()) {
            setSerialPrint(pVT_Net, "Not a directory");
            return;
        }
        //pVT_Net->fs_SP=root;

        fs::File file = root.openNextFile();
        while (file) {
            if (file.isDirectory()) {
                setSerialPrint(pVT_Net, delm0);
                setSerialPrint(pVT_Net, "DIR : ", true);
                fileStr = QString(file.name());
                setSerialPrint(pVT_Net, fileStr);
                if (levels) {
                    listDir(fs, file.name(), levels - 1);
                }
            } else {
                lCount++;
                fileStr = QString(file.name());
                setSerialPrint(pVT_Net, "  " + fileStr, true);
                int spaces = 32 - fileStr.length(); // Tabulate nicely
                if (spaces < 1)
                    spaces = 1;
                while (spaces--)
                    setSerialPrint(pVT_Net, " ", true);
                fileSize = QString(file.size());
                spaces = 8 - fileSize.length(); // Tabulate nicely
                if (spaces < 1)
                    spaces = 1;
                while (spaces--)
                    setSerialPrint(pVT_Net, " ", true);
                setSerialPrint(pVT_Net, fileSize + " bytes [" + QString(lCount) + "]", true);
                //
                time_t t = file.getLastWrite();
                pVT_Net->tmstruct = *localtime(&t);
                printDateTimeStructure("LastWrite", pVT_Net);
            }
            file = root.openNextFile();
        } //while
    }
}; //listDir

//--------------------------------------------------------
String getSdFat_Info()
{
    QString str = "";
    uint64_t cardSize0 = 0, cardSize = 0;
    if (pVT_Net->valid_sd) {
        uint8_t cardType = SD.cardType();
        if (cardType == CARD_NONE) {
            str = "No SD card attached";
            setSerialPrint(pVT_Net, str);
            return str;
        }
        str = "SdFat_Info SD Card Type: ";
        //
        if (cardType == CARD_MMC) {
            str += "MMC";
        } else if (cardType == CARD_SD) {
            str += "SDSC";
        } else if (cardType == CARD_SDHC) {
            str += "SDHC";
        } else {
            str += "UNKNOWN";
        }
        setSerialPrint(pVT_Net, str);
        str = "";
        uint64_t cardSize = 0;
        cardSize0 = SD.cardSize() / (1024 * 1024);
        printf("SD Card Size: %lluMB\n", cardSize0, str);
        //
        cardSize0 = SD.totalBytes();
        printf("SD total bytes: %lluMB\n", cardSize0 / (1024 * 1024), str);
        cardSize = SD.usedBytes();
        printf("SD used bytes: %lluMB\n", cardSize / (1024 * 1024), str);
        cardSize = cardSize0 - cardSize;
        printf("SD free bytes: %lluMB\n", cardSize / (1024 * 1024), str);
        //
        setSerialPrint(pVT_Net, str);
        setSerialPrint(pVT_Net, delm1);
    }
    return str;
    //
}; //getSdFat_Info

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Create Pooldata Objects
//------------------------------------------------------------------------------
uint16_t getPoolObjectCreate(TVT_Net *pVT_Net,
                             uint8_t objType,
                             uint16_t objID,
                             LoopbackStream *pStream)
{
    bool valid = (pStream->available());
    int16_t objIdx = -1;
    TVT_ViewRect VT_ViewRect;
    if (valid) {
        //UnitVTObject.cpp
        if (HasInArray(objType, _objTypeSet)) {
            //read from stream
            pVT_Net->VTObjID = objID;
            pVT_Net->VTObjType = objType;
            valid = runClassObj(pVT_Net, &VT_ViewRect, pStream);
        } //HasInArray
    } //valid
    //
    return pVT_Net->objNr;
}; //getPoolObjectCreate

//------------------------------------------------------------------------------
bool VTPoolDataStore(TVT_Net *pVT_Net)
{
    uint16_t listSize = getVTObjectListSize(pVT_Net);
    bool valid = (listSize > 0);
    uint8_t objType = 0xFF, runType = 0;
    uint16_t objID = 0xFFFF, objNr = 0, pSize = pVT_Net->VT_PoolSize; // 16384;
    QString str = "";
    if ((valid) && (pSize > 0)) {
        pVT_Net->stream_ETP[pVT_Net->listNr].clear();
    } //valid
    return valid;
}; //VTPoolDataStore

//------------------------------------------------------------------------------
//const uint16_t TFT_Width=320;
//const uint16_t TFT_Height=240;
void VTPoolDataRefresh(TVT_Net *pVT_Net, bool poolInfo = true, bool pClear = false)
{
    uint16_t x = 0, y = 0, w = pVT_Net->TFT_Width, h = pVT_Net->TFT_Height;
    QString str = "", fntName = "";
    getHeapStatus(pVT_Net, 1);
    pVT_Net->level = 0;
    pVT_Net->x = x;
    pVT_Net->y = y;
    pVT_Net->pVisible = true;
    pVT_Net->w = w;
    pVT_Net->h = h;
    getStackStatus(pVT_Net);
    for (int i = 0; i < 15; i++) {
        //for (int j=0;j<4;j++) pVT_Net->fontSet[i][j]=0;
    }
    //
    if (pVT_Net->fontSet[pVT_Net->fntNr][pVT_Net->fntSr] == 1) {
        fntName = "arial" + QString(pVT_Net->fontSet[pVT_Net->fntNr][6]) + "-"
                  + QString(pVT_Net->fntSr);
        //Load new font
        if (!Set_loadFont(pVT_Net, fntName)) {
            pVT_Net->fntNr = 0;
            pVT_Net->fntSr = 0;
            fntName = "arial" + QString(pVT_Net->fontSet[pVT_Net->fntNr][6]) + "-"
                      + QString(pVT_Net->fntSr);
            Set_loadFont(pVT_Net, fntName);
        }
    }
    //
    if (pVT_Net->ImgMode) {
        if (pVT_Net->ImgMode == 1) {
            pVT_Net->ImgMode = 2;
            pVT_Net->ImgTFT.setColorDepth(8);
            // Create the sprite and clear background
            pVT_Net->ImgTFT.createSprite(pVT_Net->TFT_Width, pVT_Net->TFT_Height);
        }
    }
    //
    pVT_Net->VTPoolRefresh = true;
    pVT_Net->VTPoolClear = pClear;
    //
    getHeapStatus(pVT_Net, 2);
    getStackStatus(pVT_Net);
}; //VTPoolDataRefresh

//------------------------------------------------------------------------------
void getPoolObjectReset(TVT_Net *pVT_Net, bool pClear = false)
{
    uint16_t lCount = getVTObjectListSize(pVT_Net);
    setVTObjectListClear(pVT_Net);
    setSerialPrint(pVT_Net, "VTObjectList=" + QString(lCount));
    VTPoolDataRefresh(pVT_Net, pClear);
    logMemory();
    //getHeapStatus(pVT_Net,3);
}; //getPoolObjectReset

//------------------------------------------------------------------------------
bool getPoolObjectClear(TVT_Net *pVT_Net)
{
    uint16_t lCount = getVTObjectListSize(pVT_Net);
    bool valid = false;
    if (lCount > 0) {
        getPoolObjectReset(pVT_Net);
        valid = true;
    }
    //
    return valid;
}; //getPoolObjectClear

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool Set_loadFontToPSRAM(fs::FS &fs, const char *path, LoopbackStream *pStream)
{
    uint32_t len = 0;
    uint8_t *buff;
    bool valid = QFile::exists(":/" + path);
    //
    if (pStream != NULL)
        pStream->clear();
    //
    if (valid) {
        fs::QFile(path FILE_READ);
        if ((file) && (pStream != NULL)) {
            setSerialPrint(pVT_Net, QString(path), true);
            setSerialPrint(pVT_Net, " FileSize=", true);
            setSerialPrint(pVT_Net, QString(file.size()), true);
            if (pVT_Net->PSRam) {
                pStream->setNewBufferSize(file.size(), pVT_Net->PSRam);
                buff = pStream->getBuffer();
                len = file.available();
                len = file.readBytes((char *) buff, len);
                pStream->setSize(len);
                pStream->setPos(0);
            }
            //
            setSerialPrint(pVT_Net, " BufferSize=", true);
            setSerialPrint(pVT_Net, QString(pStream->getBufferSize()), true);
            setSerialPrint(pVT_Net, " Bufferlen=", true);
            setSerialPrint(pVT_Net, QString(pStream->available()));
            file.close();
        }
        //setSerialPrint(pVT_Net,String(pStream->available()));
    }
    return valid; //  (len>0);
}; //Set_loadFontToPSRAM

//------------------------------------------------------------------------------
void showFontSet()
{
    QString str = "", ss = "", fntName = "", dName = "", aStr = "", fntStr = "", tStr = ".";
    bool valid = true;
    int i = 0, j = 0;
    //uint16_t x=pVT_Net->TFT_HEIGHT, h=pVT_Net->TFT_KEYHEIGHT,w=pVT_Net->TFT_KEYWIDTH;
    uint16_t x = pVT_Net->TFT_Height, w = pVT_Net->TFT_KeyWidth, h = pVT_Net->TFT_KeyHeight;
    uint8_t kNr = pVT_Net->TFT_KeyNr;
    setSerialPrint(pVT_Net, "FontSet:");
    //max fonts
    //for (i=0;i<15;i++) {
    for (i = 0; i < 5; i++) {
        ss = "arial" + QString(i);
        str = "";
        aStr = "/" + ss + "  \t";
        fntStr = "";
        str += "  \t(";
        //
        if (i < kNr) {
            Set_fillRect(pVT_Net, x, i * h, w, h, cl_silver);
            Set_drawRect(pVT_Net, x, i * h, w, h, cl_blue);
            fntStr = QString(i);
            Set_drawString(pVT_Net, fntStr, x + 10, i * h + 10);
        }
        //
        for (j = 0; j < 4; j++) {
            fntName = ss + "-" + QString(j);
            fntStr = "";
            dName = "/" + fntName + +".vlw";
            pVT_Net->fontSet[i][j] = QFile::exists(":/" + dName);
            //
            if (pVT_Net->fontSet[i][j] == 1) {
                dName = "/" + fntName + +".vlw";
                valid = false;
                tStr = ".";
                //Set font to PSRAM from SPIFFS
                if ((!valid) && (pVT_Net->valid_sp)) {
                    valid = (Set_loadFontToPSRAM(SPIFFS,
                                                 dName.constData(),
                                                 &pVT_Net->stream_Font[i][j]));
                    tStr = ".";
                }
                //Set font to PSRAM from SD
                if ((!valid) && (pVT_Net->valid_sd)) {
                    //setSerialPrint(pVT_Net,dName);
                    valid = (Set_loadFontToPSRAM(SD, dName.constData(), &pVT_Net->stream_Font[i][j]));
                    tStr = ":";
                }
                //
                //
                if (valid) {
                    if (i < kNr) {
                        fntStr += "." + QString(j);
                        Set_drawString(pVT_Net, fntStr, x + 20 + 12 * j, i * h + 10);
                    }
                    //TEST
                    //setSerialPrint(pVT_Net,String(i) + "_" + QString(j) + " ",true);
                    //setSerialPrint(pVT_Net,String(pVT_Net->stream_Font[i][j].available()));
                } else
                    str += "!";
            } else
                str += "!";
            //
            str += "/" + fntName + +".vlw";
            if (j < 3)
                str += ", ";
        } //for j
        //
        str += ")";
        //
        for (j = 0; j < 7; j++) {
            aStr += QString(pVT_Net->fontSet[i][j]) + ",";
        }
        str = aStr + str;
        //
        setSerialPrint(pVT_Net, str);
        setSerialPrint(pVT_Net, delm0);
    } //for i
    //
    logMemory();
    setSerialPrint(pVT_Net, delm1);
}; //showFontSet

//==============================================================================
//==============================================================================
