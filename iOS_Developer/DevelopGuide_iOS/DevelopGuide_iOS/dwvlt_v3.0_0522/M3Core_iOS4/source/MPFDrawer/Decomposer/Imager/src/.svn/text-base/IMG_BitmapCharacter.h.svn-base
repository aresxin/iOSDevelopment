#ifndef INC_IMG_BitmapCharacter_h
#define INC_IMG_BitmapCharacter_h

/* IMG_BitmapCharacter.h */

#include "IMG_BitmapShape.h"
#include "IMG_ClassPointer.h"

/* 宣言 */
/* フォントデータインデックス */
#define IMG_FONT_INDEX_OFFSET_X		4	/* オフセットＸ */
#define	IMG_FONT_INDEX_OFFSET_Y		8	/* オフセットＹ */
#define	IMG_FONT_INDEX_HEIGHT		12	/* 高さ */
#define	IMG_FONT_INDEX_WIDTH		14	/* 幅 */
#define	IMG_FONT_INDEX_WIDTH_BYTES	16
/*#define	IMG_FONT_INDEX_DEPTH		17*/
#define IMG_FONT_INDEX_DATA			18

/* 構造体宣言 */
typedef struct IMG_Font {
	/*IMG_UINT32	fontFormat;*/
	/*IMG_UINT8	weight;*/
	/*IMG_BOOL	italic;*/
	/*IMG_BOOL	gray;*/
	IMG_Point	offset;			/* フォント右下から実際のデータの右下までのオフセット */
	IMG_UINT16	width;			/* 文字幅 */
	IMG_UINT16	widthBytes;		/* 文字のバイト幅(やはり必要になった)*/
	IMG_UINT16	height;			/* 文字高さ */
	/*IMG_UINT8	depth;*/
	IMG_UINT32	dataSize;		/* データサイズ */
	char		*dataAddress;	/* データアドレス */
} IMG_Font,*IMG_FontPointer;

typedef struct IMG_BitmapCharacter {
	int				(*destroy)(IMG_BitmapShape *object);
	int				(*draw)(IMG_BitmapShapePointer object,
							IMG_DisplayList *displayList,
							IMG_TagFilterPtr	tagFilter,
							IMG_Matrix *matrix);
	IMG_UINT8		bitmapType;		/* character,image,imagemaskのどれなのか */
	/* ここまでは共通 */
	IMG_Context		context;		/* Image共通context */
	IMG_Point		paintingPoint;	/* 表示座標 */
	IMG_Font		font;			/* フォント情報 */
} IMG_BitmapCharacter,*IMG_BitmapCharacterPointer;

/* プロトタイプ宣言 */
IMG_BitmapShapePointer
	IMG_BitmapCharacterCreate(IMG_Context *context,IMG_Point *point,char *fontData);

#endif /* INC_IMG_BitmapCharacter_h */
