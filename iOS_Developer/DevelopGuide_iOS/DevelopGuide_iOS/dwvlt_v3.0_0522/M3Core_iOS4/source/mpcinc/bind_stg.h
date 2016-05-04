// File: BIND_STG.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

/*
*  BIND_STG.H
*
*	CORE_STGと、CORE_LDRをプロシジャコールするためのプロトタイプ宣言
*/

// CORE_STGとローダを結合する DLL interface
typedef MPCSession*   ( __stdcall *DLLCREATEMPCSESSION)(void* hInstance, HRESULT* phres, long version);

DLLBINDFUNC_(MPCSession*, MPCSPI_DLLCreateMPCSession)(void* hInstance, HRESULT* phres, long version);

#ifdef _WIN64
// for 64bit 
#define MPSYM_DLLCREATEMPCSESSION "MPCSPI_DLLCreateMPCSession"
#else
// for 32bit
#define MPSYM_DLLCREATEMPCSESSION "_MPCSPI_DLLCreateMPCSession@12"
#endif

#define MPC_VERSION	(0x00030610)	// Version 3,  6/10 interface

mpinterface MP_Canvas;
mpinterface	MP_PtrArray;
mpinterface	MP_Children;
mpinterface MP_PD;
mpinterface IStgObject;

MPC_EXTERN_GUID(IID_SPISessionForDLL, 0x1314);


mpinterface SPISessionForDLL
{
STDMETHOD_(void*, GetCORE_STGInstanceHandle)(HRESULT* phres) PURE;

STDMETHOD_(MP_PtrArray*, MPCreateMPPtrArray)(MPCSession* session, HRESULT* phres) PURE;
STDMETHOD_(MP_Children*, MPCreateMPChildren)(MPCSession* session, MPCObject* mpcobj, IStgObject* stgobj, MP_Integer part_objtype, IStgObject* midkeeper, HRESULT* phres) PURE;
STDMETHOD_(MP_Children*, MPCreateMPCDocRootChildren)(MPCSession* session, MPCObject* mpcobj, IStgObject* stgobj, MP_Integer part_objtype, IStgObject* midkeeper, HRESULT* phres) PURE;
};

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//05.8.02 - Y.Ito - 64bit対応にともないMPSYM_DLLCREATEMPCSESSIONを分けた
