#ifndef CHR_WIDTH_H
#define CHR_WIDTH_H

#include "w2mpf_def.h"

class CharacterWidth
{
public:
	CharacterWidth();
	~CharacterWidth();
	void SetFontInfo(const WCHAR* facename, int pitchAndFamily, int charset);
	float GetPointWidth(WCHAR ch, float fontsize) const;
private:
	int m_fonttype;
	enum {
		FONTTYPE_DEFAULT = 0,
		FONTTYPE_TIMES = 1,
		FONTTYPE_ARIAL = 2,
		FONTTYPE_COURIER = 3,
	};
};

#endif
