#ifndef _HBPS_H
#define _HBPS_H

#ifndef DOCUWORKS_VIEWER
#define DOCUWORKS_VIEWER
#endif

#include "DataObject/Base/Include/XdwDataObjectBaseGenerator.h"
#include "DataObject/Base/Header/XdwDataObjectBaseMemory.h"
#include "DataObject/Base/Header/XdwDataObjectBaseSharedMemory.h"
#include "DocuWorksDecoder/Include/XdwDocuWorksBinaryInterface.h"
#include "DocuWorksDecoder/Access/Header/XdwDocuWorksAccessLittleEndianBinary.h"
#include "ImagerBridge/HBPSBridge/XdwBridgeHBPS.h"

#if defined _PF_IOS_ || defined _PF_OSX_
#include "ImagerBridge/QuartzBridge/XdwBridgeQuartz.h"
#endif

// add 2011/03/03 by NEU for Android begin
#if (defined _PF_ANDROID_ && defined USE_SKIABRIDGE)
#include "ImagerBridge/SkiaBridge/XdwBridgeSkiaImpl.h"
#endif
// add 2011/03/03 by NEU for Android end

#include "GraphicFormatParser/Header/XdwGraphicFormatParser.h"
#include "GraphicFormatParser/Raster/Header/XdwGraphicFormatRasterParser.h"
#include "GraphicFormatParser/EMF/Header/XdwGraphicFormatEMFParser.h"
#include "GraphicFormatParser/WMF/Header/XdwGraphicFormatWMFParser.h"
#include "ContentManager/Header/MetaFileContentManager.h"
#include "ContentManager/Header/NthDataGenerator.h"
#include "ImagerBridge/DebugBridge/XdwNulLog.h"

#if defined _PF_WIN32_ || defined _PF_WINCE_
#include "System/WinCE/XdwFileIOWinCE.h"
#include "Viewer/OffScreen/WinCE/Header/XdwOffScreenDIB.h"
#elif defined _PF_IOS_ || defined _PF_OSX_
#include "System/Linux/XdwFileIOLinux.h"
#include "Viewer/OffScreen/iOS/Header/XdwOffScreenDIB.h"
// add 2011/03/03 by NEU for Android begin
#elif (defined _PF_ANDROID_ && defined USE_SKIABRIDGE)
#include "System/Linux/XdwFileIOLinux.h"
#include "Viewer/OffScreen/Android/Header/XdwOffScreenDIB.h"
// add 2011/03/03 by NEU for Android end
#else
#include "System/Linux/XdwFileIOLinux.h"
#include "Viewer/OffScreen/Linux/Header/XdwOffScreenDIB.h"
#endif

// 省メモリ対策 新規追加 M.Chikyu
#include "DataObject/Base/Header/XdwDataObjectBaseTmpFile.h"

#endif

