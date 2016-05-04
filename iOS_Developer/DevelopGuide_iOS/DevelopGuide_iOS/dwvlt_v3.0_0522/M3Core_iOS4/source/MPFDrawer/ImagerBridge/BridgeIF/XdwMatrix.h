/**
 * @file  XdwMatrix.h
 * @brief Matrixおよび座標変換関連クラス用ヘッダファイル
 *
 * Matrixと座標変換に関する型の宣言やグローバルな関数を提供する．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-04-03
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-04-03	Toshio Yamazaki<br>
 */
#include "System/SystemIF/XdwError.h"

#ifndef XDWMATRIX_H_INCLUDED
#define XDWMATRIX_H_INCLUDED

#if !defined(HB_USE_FIXEDPOINT)
typedef float XDW_MATREAL32;
typedef double XDW_MATREAL64;
#else
#include "COM_HB_Fixed.h"
typedef HB_Fixed32 XDW_MATREAL32;
typedef HB_Fixed64 XDW_MATREAL64;
#endif

/**
 *! 乗算時の方法
 */
enum XdwMatrixMultipleMode{
    /*! 初期化時のCTMとの乗算 */
    XDW_MATRIX_MULTIPLE_IDENTITY = 1,
    /*! 指定したMatrix * 現在のCTM */
    XDW_MATRIX_MULTIPLE_LEFT,
    /*! 現在のCTM * 指定したMatrix */
    XDW_MATRIX_MULTIPLE_RIGHT
};

/*!Matrixクラス

  Matrixクラスだよ．
 */
class XdwMatrix {
public:
    double aF;	/*!< Matrix a 要素			*/
    double bF;	/*!< Matrix b 要素			*/
    double cF;	/*!< Matrix c 要素，不要		*/
    double dF;	/*!< Matrix d 要素			*/
    double eF;	/*!< Matrix e 要素			*/
    double fF;	/*!< Matrix f 要素，不要		*/
    double gF;	/*!< Matrix g 要素，x方向平行移動成分	*/
    double hF;	/*!< Matrix h 要素，y方向平行移動成分	*/
    double iF;	/*!< Matrix i 要素，普通1		*/

    /*! コンストラクタ
     * 単位行列で初期化するコンストラクタ
     */
    XdwMatrix()
	: aF(1.0), bF(0.0), cF(0.0),
	  dF(0.0), eF(1.0), fF(0.0),
	  gF(0.0), hF(0.0), iF(1.0) {};
    /*! コンストラクタ
     * 任意の行列で初期化するコンストラクタ
     * @param a 行列a要素
     * @param b 行列b要素
     * @param c 行列c要素
     * @param d 行列d要素
     * @param e 行列e要素
     * @param f 行列f要素
     * @param g 行列g要素
     * @param h 行列h要素
     * @param i 行列i要素
     */
    XdwMatrix(double a, double b, double c,
	      double d, double e, double f,
	      double g, double h, double i )
	: aF(a), bF(b), cF(c),
	  dF(d), eF(e), fF(f),
	  gF(g), hF(h), iF(i) {};
    /*!デストラクタ
     * 何もしないデストラクタ
     */
    ~XdwMatrix() {};

    /*
     * define of operator
     */
    /*!operator==
     * ==比較演算子
     * @param mat 比較対象マトリクス
     * @retval 比較結果
     */
    inline int operator==( const XdwMatrix &mat ) {
	return ((aF==mat.aF) && (bF==mat.bF) && (cF==mat.cF)
		&& (dF==mat.dF) && (eF==mat.eF) && (fF==mat.fF)
		&& (gF==mat.gF) && (hF==mat.hF) && (iF==mat.iF));
    };
    /*!operator!=
     * !=比較演算子
     * @param mat 比較対象マトリクス
     * @retval 比較結果
     */
    inline int operator!=( const XdwMatrix &mat ) {
	return ((aF!=mat.aF) || (bF!=mat.bF) || (cF!=mat.cF)
		|| (dF!=mat.dF) || (eF!=mat.eF) || (fF!=mat.fF)
		|| (gF!=mat.gF) || (hF!=mat.hF) || (iF!=mat.iF));
    };

    /*!operator+
     * +単項演算子
     * @retval 単項加算結果
     */
    inline XdwMatrix operator+( void ){ return *this; };
    /*!operator-
     * -単項演算子
     * @retval 単項減算結果
     */
    inline XdwMatrix operator-( void ){
	return XdwMatrix( -aF, -bF, -cF,
			  -dF, -eF, -fF,
			  -gF, -hF, -iF );
    };

    /*!operator+=
     * +=二項演算子
     * @param mat 加算マトリクス
     * @retval 加算結果へのリファレンス
     */
    inline XdwMatrix& operator+=(const XdwMatrix& mat) {
	aF += mat.aF; bF += mat.bF; cF += mat.cF;
	dF += mat.dF; eF += mat.eF; fF += mat.fF;
	gF += mat.gF; hF += mat.hF; iF += mat.iF;

	return *this;
    };
    /*!operator-=
     * -=二項演算子
     * @param mat 減算マトリクス
     * @retval 減算結果へのリファレンス
     */
    inline XdwMatrix& operator-=(const XdwMatrix& mat) {
	aF -= mat.aF; bF -= mat.bF; cF -= mat.cF;
	dF -= mat.dF; eF -= mat.eF; fF -= mat.fF;
	gF -= mat.gF; hF -= mat.hF; iF -= mat.iF;

	return *this;
    };
    /*!operator*=
     * *=二項演算子
     * @param mat 乗算マトリクス
     * @retval 乗算結果へのリファレンス
     */
    inline XdwMatrix operator*=( const XdwMatrix& mat ) {

	double	tmp_a, tmp_b, tmp_c;
	double	tmp_d, tmp_e, tmp_f;
	double	tmp_g, tmp_h, tmp_i;

	tmp_a = aF*mat.aF+bF*mat.dF+cF*mat.gF;
	tmp_b = aF*mat.bF+bF*mat.eF+cF*mat.hF;
	tmp_c = aF*mat.cF+bF*mat.fF+cF*mat.iF;

	tmp_d = dF*mat.aF+eF*mat.dF+fF*mat.gF;
	tmp_e = dF*mat.bF+eF*mat.eF+fF*mat.hF;
	tmp_f = dF*mat.cF+eF*mat.fF+fF*mat.iF;

	tmp_g = gF*mat.aF+hF*mat.dF+iF*mat.gF;
	tmp_h = gF*mat.bF+hF*mat.eF+iF*mat.hF;
	tmp_i = gF*mat.cF+hF*mat.fF+iF*mat.iF;

	aF = tmp_a; bF = tmp_b; cF = tmp_c;
	dF = tmp_d; eF = tmp_e; fF = tmp_f;
	gF = tmp_g; hF = tmp_h; iF = tmp_i;

	return *this;
    };
    /*!operator*=
     * *=二項演算子
     * @param s スカラー値
     * @retval 乗算結果へのリファレンス
     */
    inline XdwMatrix& operator*=( double s ) {
	aF *= s; bF *= s; cF *= s;
	dF *= s; eF *= s; fF *= s;
	gF *= s; hF *= s; iF *= s;

	return *this;
    };
    /*!operator/=
     * /=二項演算子
     * @param s スカラー値
     * @retval 除算結果へのリファレンス
     */
    inline XdwMatrix& operator/=( double s ) {
	if ( s != 0.0 ) {
	    aF /= s; bF /= s; cF /= s;
	    dF /= s; eF /= s; fF /= s;
	    gF /= s; hF /= s; iF /= s;
	} else {
	    aF = bF = cF = 0.0;
	    dF = eF = fF = 0.0;
	    gF = hF = iF = 0.0;
	};

	return *this;
    };

    /*!operator+
     * +二項演算子
     * @param mat 加算マトリクス
     * @retval 加算結果
     */
    inline XdwMatrix operator+( const XdwMatrix& mat ) {
	return XdwMatrix(aF+mat.aF, bF+mat.bF, cF+mat.cF,
			 dF+mat.dF, eF+mat.eF, fF+mat.fF,
			 gF+mat.gF, hF+mat.hF, iF+mat.iF );
    };
    /*!operator-
     * -二項演算子
     * @param mat 減算マトリクス
     * @retval 減算結果
     */
    inline XdwMatrix operator-( const XdwMatrix& mat ) {
	return XdwMatrix(aF-mat.aF, bF-mat.bF, cF-mat.cF,
			 dF-mat.dF, eF-mat.eF, fF-mat.fF,
			 gF-mat.gF, hF-mat.hF, iF-mat.iF );
    };
    /*!operator*
     * *二項演算子
     * @param mat 乗算マトリクス
     * @retval 乗算結果
     */
    inline XdwMatrix operator*( const XdwMatrix& mat ) {
	return XdwMatrix(aF*mat.aF+bF*mat.dF+cF*mat.gF, aF*mat.bF+bF*mat.eF+cF*mat.hF, aF*mat.cF+bF*mat.fF+cF*mat.iF,
			 dF*mat.aF+eF*mat.dF+fF*mat.gF, dF*mat.bF+eF*mat.eF+fF*mat.hF, dF*mat.cF+eF*mat.fF+fF*mat.iF,
			 gF*mat.aF+hF*mat.dF+iF*mat.gF, gF*mat.bF+hF*mat.eF+iF*mat.hF, gF*mat.cF+hF*mat.fF+iF*mat.iF );
    };
    /*!operator*
     * *二項演算子
     * @param s スカラー値
     * @retval 乗算結果
     */
    inline XdwMatrix operator*( double s ) {
	return XdwMatrix(aF*s, bF*s, cF*s,
			 dF*s, eF*s, fF*s,
			 gF*s, hF*s, iF*s );
    };
    /*!operator/
     * /二項演算子
     * @param s スカラー値
     * @retval 除算結果
     */
    inline XdwMatrix operator/( double s ) {
	if ( s != 0.0 ) {
	    return XdwMatrix(aF/s, bF/s, cF/s,
			     dF/s, eF/s, fF/s,
			     gF/s, hF/s, iF/s );
	} else {
	    return XdwMatrix(0.0, 0.0, 0.0,
			     0.0, 0.0, 0.0,
			     0.0, 0.0, 0.0 );
	};
    };

    /*!operator*
     * *二項演算子
     * @param s スカラー値
     * @param mat 乗算マトリクス
     * @retval 乗算結果
     */
    friend inline XdwMatrix operator*( double s, const XdwMatrix& mat ) {
	return XdwMatrix(mat.aF*s, mat.bF*s, mat.cF*s,
			 mat.dF*s, mat.eF*s, mat.fF*s,
			 mat.gF*s, mat.hF*s, mat.iF*s );
    };
    /*!operator/
     * /二項演算子
     * @param s スカラー値
     * @param mat 除算マトリクス
     * @retval 除算結果
     */
    friend inline XdwMatrix operator/( double s, const XdwMatrix& mat ) {
	if ( s != 0.0 ) {
	    return XdwMatrix(mat.aF/s, mat.bF/s, mat.cF/s,
			     mat.dF/s, mat.eF/s, mat.fF/s,
			     mat.gF/s, mat.hF/s, mat.iF/s );
	} else {
	    return XdwMatrix(0.0, 0.0, 0.0,
			     0.0, 0.0, 0.0,
			     0.0, 0.0, 0.0 );
	};
    };

    /*
     * define of operation
     */
    /*!デノミの演算
     * デノミを計算する
     * @retval デノミ値
     */
    inline double CalcDenomi( void ) {
	return (aF*eF*iF + dF*hF*cF + bF*fF*gF
		- cF*eF*gF - bF*dF*iF - aF*fF*hF);
    }

    XdwErrorCode GetInvertMatrix( XdwMatrix *ans );
    XdwErrorCode ChangeToInvertMatrix( void );
    XdwErrorCode GetAngle90Status( double *, bool * );
    /*!座標変換
     * 引数の座標値をマトリクスで座標変換する
     * @param src_x ソースX座標値
     * @param src_y ソースY座標値
     * @param ans_x 座標変換結果X座標値
     * @param ans_y 座標変換結果Y座標値
     */
    inline void TransPoint(double *src_x, double *src_y,
			   double *ans_x, double *ans_y ) {
	double	tmp_x, tmp_y;	/* because, for src_* == ans_* */

	tmp_x = (*src_x)*aF+(*src_y)*dF+gF;
	tmp_y = (*src_x)*bF+(*src_y)*eF+hF;
	*ans_x = tmp_x;
	*ans_y = tmp_y;
    };
#if defined(HB_USE_FIXEDPOINT)
    inline void TransPoint(XDW_MATREAL64 *src_x, XDW_MATREAL64 *src_y,
			   XDW_MATREAL64 *ans_x, XDW_MATREAL64 *ans_y ) {
	XDW_MATREAL64	tmp_x, tmp_y;	/* because, for src_* == ans_* */

	tmp_x = (*src_x)*aF+(*src_y)*dF+gF;
	tmp_y = (*src_x)*bF+(*src_y)*eF+hF;
	*ans_x = tmp_x;
	*ans_y = tmp_y;
    };
#endif
    /*!平行移動なし座標変換
     * 引数の座標値をマトリクスで座標変換する．
     * ただし，平行移動成分を無視する．
     * @param src_x ソースX座標値
     * @param src_y ソースY座標値
     * @param ans_x 座標変換結果X座標値
     * @param ans_y 座標変換結果Y座標値
     */
    /* _nopt == dont parallel transfor */
    inline void TransPointNoPT(double *src_x, double *src_y,
			       double *ans_x, double *ans_y ) {
	double	tmp_x, tmp_y;	/* because, for src_* == ans_* */

	tmp_x = (*src_x)*aF+(*src_y)*dF;
	tmp_y = (*src_x)*bF+(*src_y)*eF;
	*ans_x = tmp_x;
	*ans_y = tmp_y;
    };
#if defined(HB_USE_FIXEDPOINT)
    inline void TransPointNoPT(XDW_MATREAL64 *src_x, XDW_MATREAL64 *src_y,
			       XDW_MATREAL64 *ans_x, XDW_MATREAL64 *ans_y ) {
	XDW_MATREAL64	tmp_x, tmp_y;	/* because, for src_* == ans_* */

	tmp_x = (*src_x)*aF+(*src_y)*dF;
	tmp_y = (*src_x)*bF+(*src_y)*eF;
	*ans_x = tmp_x;
	*ans_y = tmp_y;
    };
#endif
};

#endif /* XDWMATRIX_H_INCLUDED */
