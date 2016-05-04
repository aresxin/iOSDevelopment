#ifndef IMPL_INTERNAL_DOCUMENT_H
#define IMPL_INTERNAL_DOCUMENT_H

#include <mpc_api.h>

class ImplInternalDocument : public MPCInternalDocument
{
public:
	ImplInternalDocument(MPCObject* obj);
	~ImplInternalDocument();
	STDMETHOD(GetDocumentName)(MP_MBString& documentName, MP_TAType& tatype, int codepage);
	STDMETHOD(GetDocumentNameW)(MP_String& documentName, MP_TAType& tatype, int codepage);
	STDMETHOD(SetDocumentName)(const char* documentName, MP_TAType tatype, int codepage);
	STDMETHOD(SetDocumentNameW)(const MP_Text* documentName, MP_TAType tatype, int codepage);

private:
	MPCTextAttributeHelper* GetMPCTextAttributeHelper();

private:
	MPCObject* m_object;
};

MPCInternalDocument* CreateMPCInternalDocument(MPCObject*);
void DestroyMPCInternalDocument(MPCInternalDocument*);

#endif
