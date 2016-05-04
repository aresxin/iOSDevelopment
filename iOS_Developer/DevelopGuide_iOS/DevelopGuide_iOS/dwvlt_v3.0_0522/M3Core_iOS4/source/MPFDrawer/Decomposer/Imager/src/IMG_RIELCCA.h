/*                 */
/*	IMG_RIELCCA.h  */
/*                 */

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0 
#endif

/*      */
/* LCCA */
/*      */
typedef struct {
	int rblock_[9];      /* 3ｘ3縮小レンジブロック記憶用 */
	int ravrge_;         /* 縮小レンジブロックの平均値   … 真の値の９倍値 */
	int rstdiv_;         /* 縮小レンジブロックの標準偏差 … 真の値の９倍値 */
	int dblock_[3][9];   /* 3ｘ3ドメインブロック(注目ブロック)記憶用 24bit用 */
	int davrge_[3];      /* 3ｘ3ドメインブロック(注目ブロック)の平均値 24bit用 */
	int dstdiv_[3];      /* 3ｘ3ドメインブロック(注目ブロック)の標準偏差 24bit用 */
	int edge_threshold_; /* エッジ判定閾値 */
	int outotsu_;        /* 注目ブロックの凹凸数 */	
	int dblock_8_[9];    /* 3ｘ3ドメインブロック(注目ブロック)記憶用 8bit用 */
	int davrge_8_;       /* 3ｘ3ドメインブロック(注目ブロック)の平均値 8bit用 */
	int dstdiv_8_;       /* 3ｘ3ドメインブロック(注目ブロック)の標準偏差 8bit用 */
	
	int ibytes_;         /* 横幅のバイト数 */
	int* iptr_;          /* 入力画像の格納先 */
	int* ibuf_[5];       /* 入力画像のバッファポインタ */
	float kr_;           /* 輝度変換パラメータ( kr*z + kh の kr 値) */
	float* optr_;        /* 出力画像の格納先 */
	float* obuf_[3];     /* 出力画像のバッファポインタ */
	float eblock_[9];    /* 書き出し用3ｘ3ブロック記憶用 */
	float edge_param_;   /* エッジ(コントラスト)強調パラメータ */
} LCCA;

