/**
 * @file  XdwShape.h
 * @brief 図形関連クラス用ヘッダファイル
 *
 * 図形(1次元,2次元図形)関する型の宣言やグローバルな関数を提供する．<br>
 * 豆知識：点は0次元
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-04-08
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-04-08	Toshio Yamazaki<br>
 */
#ifndef XDWSHAPE_H_INCLUDED
#define XDWSHAPE_H_INCLUDED

#include "XdwPoint.h"

/*!巻き方向
  円弧系の図形において，その図形の巻き方向を指定する．
*/
enum XdwArcWiseMode {
    XDW_CIRCLEWM_COUNTERCLOCKWISE = 1,	/*!< 半時計周り		*/
    XDW_CIRCLEWM_CLOCKWISE = 2		/*!< 時計周り		*/
};
/*!弧形状
  開始角，終了角が指定される円/楕円においては，
  間隙図形の形状に幾つかのバリエーションが存在する．
  そこで，その間隙図形形状を指定する．
*/
enum XdwArcType {
    XDW_CIRCLEAT_FULL,	/*!< 真円/真楕円	*/
    XDW_CIRCLEAT_ARC,	/*!< 弧形状,開図形	*/
    XDW_CIRCLEAT_CHORD,	/*!< 弓形状		*/
    XDW_CIRCLEAT_PIE	/*!< パイ形状		*/
};

/*!矩形クラス
  矩形を提供する．
*/
class XdwRectangle {
public:
    XdwPoint	LeftTopF;	/*!< 矩形左上の座標	*/
    XdwPoint	RightBottomF;	/*!< 矩形右下の座標	*/
};

/*!円弧クラス

  円弧図形を提供する．
 */
class XdwArc {
public:
    XdwPoint		CenterPointF;	/*!< 中心点		*/
    double		XRadiusF;	/*!< x軸方向半径	*/
    double		YRadiusF;	/*!< y軸方向半径	*/
    double		StartAngleF;	/*!< 開始角度		*/
    double		EndAngleF;	/*!< 終了角度		*/
    XdwArcType		TypeF;		/*!< 弧形状		*/
};

/*!楕円クラス

  楕円図形を提供する．
 */
class XdwEllipse {
public:
    /*! 楕円の外接矩形 */
    XdwRectangle RectF;
    /*! 始点の放射直線の端点 */
    XdwPoint StartF;
    /*! 終点の放射直線の端点 */
    XdwPoint EndF;
    /*! 弧形状 */
    XdwArcType TypeF;
};

/*!円クラス

  円は，楕円の長軸半径と短軸半径が等しい場合とみて，
  楕円を継承している．
*/
class XdwCircle : public XdwEllipse {
};

/*!角丸矩形クラス
  角が丸い矩形を提供する．
*/
class XdwRoundRect {
public:
    XdwRectangle	RectF;		/*!< 角丸矩形の外接矩形	*/
    double		XRadiusF;	/*!< 角丸のX方向半径	*/
    double		YRadiusF;	/*!< 角丸のY方向半径	*/
};

/* I/F用のtemplateのtypedef */
#include <vector>
#include "System/SystemIF/XdwStl.h"

typedef XdwStlVector(XdwEllipse)	XdwEllipseVector;	/*!< 引数用EllipseのVector	*/
typedef XdwStlVector(XdwCircle)		XdwCircleVector;	/*!< 引数用CircleのVector	*/
typedef XdwStlVector(XdwRectangle)	XdwRectangleVector;	/*!< 引数用RectangleのVector	*/
typedef XdwStlVector(XdwRoundRect)	XdwRoundRectVector;	/*!< 引数用RoundRectのVector	*/

#endif /* XDWSHAPE_H_INCLUDED */
