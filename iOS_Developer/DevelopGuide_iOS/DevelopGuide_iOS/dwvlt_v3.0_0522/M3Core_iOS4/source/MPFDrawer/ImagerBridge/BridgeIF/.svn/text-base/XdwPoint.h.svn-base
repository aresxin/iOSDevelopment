/**
 * @file  XdwPoint.h
 * @brief 座標関連クラス用ヘッダファイル
 *
 * 座標値に関する型の宣言やグローバルな関数を提供する．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-04-03
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-04-03	Toshio Yamazaki<br>
 */
#ifndef XDWPOINT_H_INCLUDED
#define XDWPOINT_H_INCLUDED

#include <math.h>

#if !defined(HB_USE_FIXEDPOINT)
typedef float XDW_REAL32;
typedef double XDW_REAL64;
#else
#include "COM_HB_Fixed.h"
typedef HB_Fixed32 XDW_REAL32;
typedef HB_Fixed64 XDW_REAL64;
#endif

/*!座標値クラス

  実数型の座標値を提供する．
 */
class XdwPoint {
public:
    XDW_REAL64	xF;	/*!< x座標値	*/
    XDW_REAL64	yF;	/*!< x座標値	*/

    /*! デフォルトコンストラクタ
     * デフォルトコンストラクタは適当
     */
    XdwPoint() {};
    /*! コンストラクタ
     * 任意の座標値で初期化するコンストラクタ
     * @param x X座標値
     * @param y Y座標値
     */
    XdwPoint( XDW_REAL64 x, XDW_REAL64 y) : xF(x), yF(y) {};

    /***************************************************/
    /*! @name 多重定義operator
     * operatorの多重定義
     */
    /***************************************************/
    /*@{*/

    /*!operator==
     * ==比較演算子
     * @param p 比較対象座標
     * @retval 比較結果
     */
    inline int operator==( const XdwPoint &p ) const {
	return ((xF==p.xF) && (yF==p.yF));
    };
    /*!operator!=
     * !=比較演算子
     * @param p 比較対象座標
     * @retval 比較結果
     */
    inline int operator!=( const XdwPoint &p ) const {
	return ((xF!=p.xF) || (yF!=p.yF));
    };
    /*!operator+
     * +単項演算子
     * @retval 単項加算結果
     */
    inline XdwPoint operator+( void ) const {
	return *this;
    };
    /*!operator-
     * -単項演算子
     * @retval 単項減算結果
     */
    inline XdwPoint operator-( void ) const {
      return XdwPoint(-xF,-yF);
    };
    /*!operator+=
     * +=二項演算子
     * @param p 加算座標値
     * @retval 加算結果へのリファレンス
     */
    inline XdwPoint& operator+=( const XdwPoint& p ) {
	xF += p.xF; yF += p.yF;
	return *this;
    };
    /*!operator-=
     * -=二項演算子
     * @param p 減算座標値
     * @retval 減算結果へのリファレンス
     */
    inline XdwPoint& operator-=( const XdwPoint& p ) {
	xF -= p.xF; yF -= p.yF;
	return *this;
    };
    /*!operator*=
     * *=二項演算子
     * @param s スカラー値
     * @retval 乗算結果へのリファレンス
     */
    inline XdwPoint& operator*=( XDW_REAL64 s ) {
	xF *= s; yF *= s;
	return *this;
    };
    /*!operator/=
     * /=二項演算子
     * @param s スカラー値
     * @retval 除算結果へのリファレンス
     */
    inline XdwPoint& operator/=( XDW_REAL64 s ) {
	xF /= s; yF /= s;
	return *this;
    };
    /*!operator+
     * +二項演算子
     * @param p 加算座標値
     * @retval 加算結果
     */
    inline XdwPoint operator+( const XdwPoint p ) const {
	return XdwPoint( xF+p.xF, yF+p.yF );
    };
    /*!operator-
     * -二項演算子
     * @param p 減算座標値
     * @retval 減算結果
     */
    inline XdwPoint operator-( const XdwPoint p ) const {
	return XdwPoint( xF-p.xF, yF-p.yF );
    };

    /*!operator*
     * *二項演算子
     * @param s スカラー値
     * @retval 乗算結果
     */
    inline XdwPoint operator*( XDW_REAL64 s ) const {
	return XdwPoint( xF*s, yF*s );
    };
    /*!operator/
     * /二項演算子
     * @param s スカラー値
     * @retval 除算結果
     */
    inline XdwPoint operator/( XDW_REAL64 s ) const {
	return XdwPoint( xF/s, yF/s );
    };
    /*!operator*
     * *二項演算子
     * @param s スカラー値
     * @param p 乗算座標値
     * @retval 乗算結果
     */
    friend inline XdwPoint operator*(XDW_REAL64 s, const XdwPoint& p ) {
	return XdwPoint( p.xF*s, p.yF*s );
    };
    /*!operator/
     * /二項演算子
     * @param s スカラー値
     * @param p 除算座標値
     * @retval 除算結果
     */
    friend inline XdwPoint operator/(XDW_REAL64 s, const XdwPoint& p ) {
	return XdwPoint( p.xF/s, p.yF/s );
    };
    /*@}*/

    /***************************************************/
    /*! @name 必要な関数
     * まぁ，割と使う雑多な関数．
     */
    /***************************************************/
    /*@{*/
    /*!Swapping
     * X座標値とY座標値を交換する．
     * 座標変換に使う.
     */
    inline void Swap( XdwPoint *p ) {
	XdwPoint	tmp;
	tmp = *this;
	*this = *p;
	*p = tmp;
    };
    /*!ベクトル長の計算
     * 座標値をベクトルとみてベクトル長を求める．
     * @retval ベクトル長
     */
    inline double Length(void) const {
	return sqrt(xF*xF+yF*yF);
    };
    /*!単位ベクトル化
     * 単位ベクトルにする．
     */
    inline void unit(void) {
	double	l;
	if ( (xF != 0.0) || (yF != 0.0 ) ){
	    l = sqrt(xF*xF+yF*yF);
	    xF /= l; yF /= l;
	};
    };
    /*!内積
     * 二次元ベクトルの内積を求める
     * @param p 内積対象のベクトル
     * @retval 内積値
     */
    inline double inner_product(XdwPoint &p) const {
	return xF*p.xF+yF*p.yF;
    };
    /*@}*/
};

/* I/F用のtemplateのtypedef */
#include <vector>
#include "System/SystemIF/XdwStl.h"

typedef XdwStlVector(XdwPoint)	XdwPointVector;	/*!< 引数用PointのVector */

#endif /* XDWPOINT_H_INCLUDED */
