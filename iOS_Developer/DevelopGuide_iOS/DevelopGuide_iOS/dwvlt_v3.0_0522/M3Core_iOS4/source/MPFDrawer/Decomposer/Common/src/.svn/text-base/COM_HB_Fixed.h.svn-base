/*
 * Copyright (C) 2003 by Fuji Xerox Co.,LTD. All rights reserved.
 *
 * HB_Fixed.h -- 固定小数点クラスの定義
 *
 * Created : 2003.09.18		Masao.Morita(DPSC/SDM/PFCoreG)
 * Modify  : 2004.02.18		Masao.Morita(DPSC/SDM/PFCoreG)
 *
 */

#if !defined(COM_HB_FIXED_H_INCLUDED)
#define COM_HB_FIXED_H_INCLUDED


//----------------------------------------------------------------
// 固定小数点のdebug設定
//----------------------------------------------------------------
//#define HB_FIXED_DEBUG
#if defined(HB_FIXED_DEBUG)
#include <stdio.h>
#include <stdlib.h>
#endif

//----------------------------------------------------------------
// 固定小数点の共通設定
//----------------------------------------------------------------
// 小数部のビット数
#define HB_DBITS	16

// 丸め量 かけ算
#define HB_FIXED_ROUND_MUL_VAL		( 1 << (FixedDecBits - 1) )
// 丸め量 割算
#define HB_FIXED_ROUND_DIV_ADDBIT	( 1 )
#define HB_FIXED_ROUND_DIV_VAL		( 1 )

// 丸め量 倍精度->単精度
#define HB_FIXED_ROUND_DOUBLE_ADDBIT	( 0 )
#define HB_FIXED_ROUND_DOUBLE_VAL	( 0 )

// 丸め量 浮動小数->固定小数
#define HB_FIXED_ROUND_CONVERT_ADDBIT	( 1 )
#define HB_FIXED_ROUND_CONVERT_VAL	( 1 )

class HB_Fixed32;
class HB_Fixed64;

//----------------------------------------------------------------
// 動作環境に応じた設定
//----------------------------------------------------------------
// 64ビット整数型
#if defined(__GNUC__)
typedef long long		HB_LONGLONG;
typedef	unsigned long long	HB_ULONGLONG;
#elif defined(_MSC_VER)
typedef __int64			HB_LONGLONG;
typedef unsigned __int64	HB_ULONGLONG;
#else
// 知らない処理系だ!!
typedef error_int64		HB_LONGLONG;
typedef error_uint64		HB_ULONGLONG;
#endif


//----------------------------------------------------------------
// HB_Fixed32 : float代用　固定小数点クラスの定義
// この設定は，30ビット整数部＋16ビット小数部
//----------------------------------------------------------------
class HB_Fixed32 {
  friend class HB_Fixed64;

public:
  // 値を保持する変数の型
  typedef HB_LONGLONG	FixedRepT;
  enum {
    FixedBits	 = sizeof(FixedRepT) * 8,		// 全ビット数
    FixedDecBits = HB_DBITS,				// 小数部のビット数
    FixedIntBits = (int)FixedBits - FixedDecBits	// 整数部のビット数
  };
  // 演算時の型
  typedef HB_LONGLONG	SignedComputeT;
  typedef int		HB_INT32;

private:
  FixedRepT	fixval;

public:
  FixedRepT	fixedrep() const { return fixval; }


  //----------------------------------------------------------------
  // クラス内ユーティリティ
  //----------------------------------------------------------------
private:
#if defined(HB_FIXED_DEBUG)
  // Overflowのチェック
  inline static void
  OverflowCheck( SignedComputeT value )
  {
    // 消されてしまうビット(FixedDecBits分左シフトするので)を調べる
    SignedComputeT	mask = 0;
    mask = (~mask) << FixedIntBits;
    
    if ( ((value > 0) ? value : -value) & mask ) {
      ComputeError( value, mask );
    }
  }

  // Underflowのチェック
  inline static void
  UnderflowCheck( SignedComputeT a, SignedComputeT b, SignedComputeT result )
  {
    if ( a != 0 && b != 0 && result == 0 ) {
      ComputeError( result, ~(0) );
    }
  }

  static void
  ComputeError( SignedComputeT value, SignedComputeT mask )
  {
    printf("%llx,%llx,%llx\n",value,mask,((value>0) ? value : -value) & mask);
//    abort();    
  }
#endif

public:
  // XXX -> 内部表現
  inline static FixedRepT
  toFixedRep( const HB_Fixed32 &f )
  {
    return ( f.fixval );
  }

  inline static FixedRepT
  toFixedRep( int i )
  {
    SignedComputeT	tmp;

    tmp = ((SignedComputeT)i);

#if defined(HB_FIXED_DEBUG)
    OverflowCheck( tmp );
#endif

    tmp = tmp << FixedDecBits;

    return ( (FixedRepT)tmp );
  }

  inline static FixedRepT
  toFixedRep( float f )
  {
#if defined(HB_FIXED_DEBUG)
    //	Zaurusは、double->long longもとっても遅い。
    //	エラーチェックしたい時だけにする
    //  丸め処理してないので、精度は悪い
    SignedComputeT	tmp;
    tmp = (SignedComputeT)((double)f);
    OverflowCheck( tmp );
    tmp = (SignedComputeT)( ((double)f) * ((double)((FixedRepT)1 << FixedDecBits)) );
#else
    SignedComputeT	tmp;
    HB_INT32		integer;
    HB_INT32		decimal;
    HB_INT32		mask = 0;
    mask = ~((~mask) << (FixedDecBits + HB_FIXED_ROUND_CONVERT_ADDBIT));	// 小数部分のマスク

    integer = (HB_INT32)f;
    decimal = (HB_INT32)(((double)f) *
			 ((double)((HB_INT32)1 << (FixedDecBits + HB_FIXED_ROUND_CONVERT_ADDBIT))));
    decimal = decimal & mask;
    decimal += HB_FIXED_ROUND_CONVERT_VAL;
    decimal = decimal >> HB_FIXED_ROUND_CONVERT_ADDBIT;
    mask = mask >> HB_FIXED_ROUND_CONVERT_ADDBIT;
    if ( f < 0 ) {
      if ( decimal != 0 ) {
	decimal = (decimal | (~mask));	// 負号拡張
      }
    }
    tmp = integer;
    tmp = tmp << FixedDecBits;
    tmp = tmp + decimal;
#endif

    return ( (FixedRepT)tmp );
  }

  inline static FixedRepT
  toFixedRep( double d )
  {
#if defined(HB_FIXED_DEBUG)
    //	Zaurusは、double->long longもとっても遅い。
    //	エラーチェックしたい時だけにする
    //  丸め処理してないので、精度は悪い
    SignedComputeT	tmp;
    tmp = (SignedComputeT)d;
    OverflowCheck( tmp );
    tmp = (SignedComputeT)( d * ((double)((FixedRepT)1 << FixedDecBits)) );
#else
    SignedComputeT	tmp;
    HB_INT32		integer;
    HB_INT32		decimal;
    HB_INT32		mask = 0;
    mask = ~((~mask) << (FixedDecBits + HB_FIXED_ROUND_CONVERT_ADDBIT));	// 小数部分のマスク

    integer = (HB_INT32)d;
    decimal = (HB_INT32)(((double)d) *
			 ((double)((HB_INT32)1 << (FixedDecBits + HB_FIXED_ROUND_CONVERT_ADDBIT))));
    decimal = decimal & mask;
    decimal += HB_FIXED_ROUND_CONVERT_VAL;
    decimal = decimal >> HB_FIXED_ROUND_CONVERT_ADDBIT;
    mask = mask >> HB_FIXED_ROUND_CONVERT_ADDBIT;
    if ( d < 0 ) {
      if ( decimal != 0 ) {
	decimal = (decimal | (~mask));	// 負号拡張
      }
    }
    tmp = integer;
    tmp = tmp << FixedDecBits;
    tmp = tmp + decimal;
#endif
    return ( (FixedRepT)tmp );
  }

private:
  // 内部表現 -> XXX
  inline static int
  fixedrep2int( FixedRepT fix )
  {
    int	integer;

    integer = (fix >> FixedDecBits);
    if ( integer < 0 ) {
      SignedComputeT	mask = 0;
      mask = ~((~mask) << FixedDecBits);	// 小数部分のマスク
      if ( (fix & mask) != 0 ) {
	integer++;
      }
    }
    return ( integer );
  }

  inline static float
  fixedrep2float( FixedRepT fix )
  {
    return ( (float)(((double)fix) / ((double)((FixedRepT)1 << FixedDecBits))) );
  }

  inline static double
  fixedrep2double( FixedRepT fix )
  {
    return ( (double)(((double)fix) / ((double)((FixedRepT)1 << FixedDecBits))) );
  }

private:
  // 演算
  inline static FixedRepT
  multiply( FixedRepT a, FixedRepT b )
  {
    // gcc2.95の最適化のバグらしい(arm版だけかも)
    // 最適化を抑制するためにvolatileを使用
    // 変数を使いすぎなのかな
    volatile SignedComputeT	tmp, tmp2, tmp3;
    volatile SignedComputeT	aInt, bInt;	// 符号付整数部
    volatile SignedComputeT	aDec, bDec;	// 符号付小数部
    SignedComputeT	mask = 0;
    mask = ~((~mask) << FixedDecBits);	// 小数部分のマスク

    // 整数部、小数部の取り出し
    aInt = a >> FixedDecBits;
    bInt = b >> FixedDecBits;
    aDec = (a & mask);
    bDec = (b & mask);
    if ( aInt < 0 ) {
      if ( aDec != 0 ) {
	aDec = (aDec | (~mask));	// 負号拡張
	if ( aInt != 0 ) {
	  aInt += 1;
	}
      }
    }
    if ( bInt < 0 ) {
      if ( bDec != 0 ) {
	bDec = (bDec | (~mask));	// 負号拡張
	if ( bInt != 0 ) {
	  bInt += 1;
	}
      }
    }

    // 整数部の演算
    tmp = (aInt * bInt);
#if defined(HB_FIXED_DEBUG)
    OverflowCheck( tmp );
#endif
    tmp = tmp << FixedDecBits;

    // 小数部の演算
    // 桁あわせ不用
    tmp2  = ((aInt * bDec));
    tmp2 += ((bInt * aDec));

    // 桁あわせ、丸めが必要
    tmp3 = (aDec * bDec);

    // 丸め処理
    // 削除される小数部の先頭から繰上がらせる
    tmp3 += HB_FIXED_ROUND_MUL_VAL;

    // 桁あわせ
    tmp3 = tmp3 >> FixedDecBits;

    // 結果の合成
    tmp = tmp + tmp2 + tmp3;

#if defined(HB_FIXED_DEBUG)
    UnderflowCheck( a, b, tmp );
#endif

    return ( (FixedRepT)tmp );
  };
  
  inline static FixedRepT
  divide( FixedRepT a, FixedRepT b )
  {
    SignedComputeT	tmp;
    
    if ( b == 0 ) {
      // 0除算
      // 無限大の代わりに最大値をセット
      tmp = MaxValue().fixedrep();
      if ( a < 0 ) {
	tmp *= -1;
      }
    }
    else {
#if defined(HB_FIXED_DEBUG)
      OverflowCheck( a );
#endif
      tmp = ((SignedComputeT)a) << (FixedDecBits + HB_FIXED_ROUND_DIV_ADDBIT);
      tmp = tmp / ((SignedComputeT)b);

      // 丸め処理
      // 削除される小数部の先頭から繰上がらせる
      tmp += HB_FIXED_ROUND_DIV_VAL;

      // 桁あわせ
      tmp = tmp >> HB_FIXED_ROUND_DIV_ADDBIT;
    }

#if defined(HB_FIXED_DEBUG)
    OverflowCheck( tmp );
    UnderflowCheck( a, b, tmp );
#endif
    
    return ( (FixedRepT)tmp );
  }

  //
  // 苦肉の策
  // 汚いコンストラクタ
  inline
  HB_Fixed32( FixedRepT dirty, int ) : fixval( dirty )
  {
  }

  
  //----------------------------------------------------------------
  // 公開外部インタフェース
  //----------------------------------------------------------------
public:
  // コピーコンストラクタはデフォルトで十分
  // コンストラクタ
  inline
  HB_Fixed32( int i = 0 ) : fixval( toFixedRep( (int)i ) )
  {
  }

  inline
  HB_Fixed32( unsigned int i ) : fixval( toFixedRep( (int)i ) )
  {
  }

  inline
  HB_Fixed32( long l ) : fixval( toFixedRep( (int)l ) )
  {
  }

  inline
  HB_Fixed32( unsigned long l ) : fixval( toFixedRep( (int)l ) )
  {
  }

  inline
  HB_Fixed32( short s ) : fixval( toFixedRep( (int)s ) )
  {
  }

  inline
  HB_Fixed32( unsigned short s ) : fixval( toFixedRep( (int)s ) )
  {
  }

  inline
  HB_Fixed32( char c ) : fixval( toFixedRep( (int)c ) )
  {
  }
  
  inline
  HB_Fixed32( unsigned char c ) : fixval( toFixedRep( (int)c ) )
  {
  }

  inline
  HB_Fixed32( float d ) : fixval( toFixedRep( (float)d ) )
  {
  }

  inline
  HB_Fixed32( double d ) : fixval( toFixedRep( (double)d ) )
  {
  }

  HB_Fixed32( HB_Fixed64 fix64 );


  // キャスト
  inline
  operator int() const
  {
    return ( fixedrep2int( fixedrep() ) );
  }

  inline
  operator unsigned int() const
  {
    return ( (unsigned int)fixedrep2int( fixedrep() ) );
  }

  inline
  operator long() const
  {
    return ( (long)fixedrep2int( fixedrep() ) );
  }

  inline
  operator unsigned long() const
  {
    return ( (unsigned long)fixedrep2int( fixedrep() ) );
  }

  inline
  operator short() const
  {
    return ( (short)fixedrep2int( fixedrep() ) );
  }

  inline
  operator unsigned short() const
  {
    return ( (unsigned short)fixedrep2int( fixedrep() ) );
  }

  inline
  operator char() const
  {
    return ( (char)fixedrep2int( fixedrep() ) );
  }

  inline
  operator unsigned char() const
  {
    return ( (unsigned char)fixedrep2int( fixedrep() ) );
  }
  
  inline
  operator float() const
  {
    return ( fixedrep2float( fixedrep() ) );
  }

  inline
  operator double() const
  {
    return ( fixedrep2double( fixedrep() ) );
  }

  operator HB_Fixed64();


  // 単項演算子 マイナス
  inline HB_Fixed32 
  operator -() const
  {
    return ( HB_Fixed32( -fixval, 0 ) );
  }


  // 代入はデフォルトで十分

    
  // 加算代入
  inline HB_Fixed32 &
  operator +=( const HB_Fixed32 &fix )
  {
    fixval += fix.fixval;
    return ( *this );
  }

  // 減算代入
  inline HB_Fixed32 &
  operator -=( const HB_Fixed32 &fix )
  {
    fixval -= fix.fixedrep();
    return ( *this );
  }

  // 乗算代入
  inline HB_Fixed32 &
  operator *=( const HB_Fixed32 &fix )
  {
    fixval = HB_Fixed32::multiply( fixval, fix.fixedrep() );
    return ( *this );
  }

  // 除算代入
  inline HB_Fixed32 &
  operator /=( const HB_Fixed32 &fix )
  {
    fixval = HB_Fixed32::divide( fixval, fix.fixedrep() );
    return ( *this );
  }

  // 定数
  inline static HB_Fixed32 MaxValue()
  {
    FixedRepT	v = 1;
    v = ~(v << (FixedBits - 1));

    return ( HB_Fixed32(v, 0) );
  }
 
};


//----------------------------------------------------------------
// HB_Fixed64 : double代用　固定小数点クラスの定義
// この設定は，30bit整数部＋17bit小数部
//----------------------------------------------------------------
class HB_Fixed64 {
  friend class HB_Fixed32;

public:
  // 値を保持する変数の型
  typedef HB_LONGLONG	FixedRepT;
  enum {
    FixedBits	 = sizeof(FixedRepT) * 8,			// 全ビット数
    FixedDecBits = HB_DBITS + HB_FIXED_ROUND_DOUBLE_ADDBIT,	// 小数部のビット数
    FixedIntBits = (int)FixedBits - FixedDecBits		// 整数部のビット数
  };
  // 演算時の型
  typedef HB_LONGLONG	SignedComputeT;
  typedef int		HB_INT32;

private:
  FixedRepT	fixval;

public:
  FixedRepT	fixedrep() const { return fixval; }


  //----------------------------------------------------------------
  // クラス内ユーティリティ
  //----------------------------------------------------------------
private:
#if defined(HB_FIXED_DEBUG)
  // Overflowのチェック
  inline static void
  OverflowCheck( SignedComputeT value )
  {
    // 消されてしまうビット(FixedDecBits分左シフトするので)を調べる
    SignedComputeT	mask = 0;
    mask = (~mask) << FixedIntBits;
    
    if ( ((value > 0) ? value : -value) & mask ) {
      ComputeError( value, mask );
    }
  }

  // Underflowのチェック
  inline static void
  UnderflowCheck( SignedComputeT a, SignedComputeT b, SignedComputeT result )
  {
    if ( a != 0 && b != 0 && result == 0 ) {
      ComputeError( result, ~(0) );
    }
  }

  static void
  ComputeError( SignedComputeT value, SignedComputeT mask )
  {
    printf("%llx,%llx,%llx\n",value,mask,((value>0) ? value : -value) & mask);
//    abort();    
  }
#endif

public:
  // XXX -> 内部表現
  inline static FixedRepT
  toFixedRep( const HB_Fixed64 &f )
  {
    return ( f.fixval );
  }

  inline static FixedRepT
  toFixedRep( int i )
  {
    SignedComputeT	tmp;

    tmp = ((SignedComputeT)i);

#if defined(HB_FIXED_DEBUG)
    OverflowCheck( tmp );
#endif

    tmp = tmp << FixedDecBits;

    return ( (FixedRepT)tmp );
  }

  inline static FixedRepT
  toFixedRep( float f )
  {
#if defined(HB_FIXED_DEBUG)
    //	Zaurusは、double->long longもとっても遅い。
    //	エラーチェックしたい時だけにする
    //  丸め処理してないので、精度は悪い
    SignedComputeT	tmp;
    tmp = (SignedComputeT)((double)f);
    OverflowCheck( tmp );
    tmp = (SignedComputeT)( ((double)f) * ((double)((FixedRepT)1 << FixedDecBits)) );
#else
    SignedComputeT	tmp;
    HB_INT32		integer;
    HB_INT32		decimal;
    HB_INT32		mask = 0;
    mask = ~((~mask) << (FixedDecBits + HB_FIXED_ROUND_CONVERT_ADDBIT));	// 小数部分のマスク

    integer = (HB_INT32)f;
    decimal = (HB_INT32)(((double)f) *
			 ((double)((HB_INT32)1 << (FixedDecBits + HB_FIXED_ROUND_CONVERT_ADDBIT))));
    decimal = decimal & mask;
    decimal += HB_FIXED_ROUND_CONVERT_VAL;
    decimal = decimal >> HB_FIXED_ROUND_CONVERT_ADDBIT;
    mask = mask >> HB_FIXED_ROUND_CONVERT_ADDBIT;
    if ( f < 0 ) {
      if ( decimal != 0 ) {
	decimal = (decimal | (~mask));	// 負号拡張
      }
    }
    tmp = integer;
    tmp = tmp << FixedDecBits;
    tmp = tmp + decimal;
#endif

    return ( (FixedRepT)tmp );
  }

  inline static FixedRepT
  toFixedRep( double d )
  {
#if defined(HB_FIXED_DEBUG)
    //	Zaurusは、double->long longもとっても遅い。
    //	エラーチェックしたい時だけにする
    //  丸め処理してないので、精度は悪い
    SignedComputeT	tmp;
    tmp = (SignedComputeT)d;
    OverflowCheck( tmp );
    tmp = (SignedComputeT)( d * ((double)((FixedRepT)1 << FixedDecBits)) );
#else
    SignedComputeT	tmp;
    HB_INT32		integer;
    HB_INT32		decimal;
    HB_INT32		mask = 0;
    mask = ~((~mask) << (FixedDecBits + HB_FIXED_ROUND_CONVERT_ADDBIT));	// 小数部分のマスク

    integer = (HB_INT32)d;
    decimal = (HB_INT32)(((double)d) *
			 ((double)((HB_INT32)1 << (FixedDecBits + HB_FIXED_ROUND_CONVERT_ADDBIT))));
    decimal = decimal & mask;
    decimal += HB_FIXED_ROUND_CONVERT_VAL;
    decimal = decimal >> HB_FIXED_ROUND_CONVERT_ADDBIT;
    mask = mask >> HB_FIXED_ROUND_CONVERT_ADDBIT;
    if ( d < 0 ) {
      if ( decimal != 0 ) {
	decimal = (decimal | (~mask));	// 負号拡張
      }
    }
    tmp = integer;
    tmp = tmp << FixedDecBits;
    tmp = tmp + decimal;
#endif
    return ( (FixedRepT)tmp );
  }

private:
  // 内部表現 -> XXX
  inline static int
  fixedrep2int( FixedRepT fix )
  {
    int	integer;

    integer = (fix >> FixedDecBits);
    if ( integer < 0 ) {
      SignedComputeT	mask = 0;
      mask = ~((~mask) << FixedDecBits);	// 小数部分のマスク
      if ( (fix & mask) != 0 ) {
	integer++;
      }
    }
    return ( integer );
  }

  inline static float
  fixedrep2float( FixedRepT fix )
  {
    return ( (float)(((double)fix) / ((double)((FixedRepT)1 << FixedDecBits))) );
  }

  inline static double
  fixedrep2double( FixedRepT fix )
  {
    return ( (double)(((double)fix) / ((double)((FixedRepT)1 << FixedDecBits))) );
  }

private:
  // 演算
  inline static FixedRepT
  multiply( FixedRepT a, FixedRepT b )
  {
    // gcc2.95の最適化のバグらしい(arm版だけかも)
    // 最適化を抑制するためにvolatileを使用
    // 変数を使いすぎなのかな
    volatile SignedComputeT	tmp, tmp2, tmp3;
    volatile SignedComputeT	aInt, bInt;	// 符号付整数部
    volatile SignedComputeT	aDec, bDec;	// 符号付小数部
    SignedComputeT	mask = 0;
    mask = ~((~mask) << FixedDecBits);	// 小数部分のマスク

    // 整数部、小数部の取り出し
    aInt = a >> FixedDecBits;
    bInt = b >> FixedDecBits;
    aDec = (a & mask);
    bDec = (b & mask);
    if ( aInt < 0 ) {
      if ( aDec != 0 ) {
	aDec = (aDec | (~mask));	// 負号拡張
	if ( aInt != 0 ) {
	  aInt += 1;
	}
      }
    }
    if ( bInt < 0 ) {
      if ( bDec != 0 ) {
	bDec = (bDec | (~mask));	// 負号拡張
	if ( bInt != 0 ) {
	  bInt += 1;
	}
      }
    }

    // 整数部の演算
    tmp = (aInt * bInt);
#if defined(HB_FIXED_DEBUG)
    OverflowCheck( tmp );
#endif
    tmp = tmp << FixedDecBits;

    // 小数部の演算
    // 桁あわせ不用
    tmp2  = ((aInt * bDec));
    tmp2 += ((bInt * aDec));

    // 桁あわせ、丸めが必要
    tmp3 = (aDec * bDec);

    // 丸め処理
    // 削除される小数部の先頭から繰上がらせる
    tmp3 += HB_FIXED_ROUND_MUL_VAL;

    // 桁あわせ
    tmp3 = tmp3 >> FixedDecBits;

    // 結果の合成
    tmp = tmp + tmp2 + tmp3;

#if defined(HB_FIXED_DEBUG)
    UnderflowCheck( a, b, tmp );
#endif

    return ( (FixedRepT)tmp );
  };
  
  inline static FixedRepT
  divide( FixedRepT a, FixedRepT b )
  {
    SignedComputeT	tmp;
    
    if ( b == 0 ) {
      // 0除算
      // 無限大の代わりに最大値をセット
      tmp = MaxValue().fixedrep();
      if ( a < 0 ) {
	tmp *= -1;
      }
    }
    else {
#if defined(HB_FIXED_DEBUG)
      OverflowCheck( a );
#endif
      tmp = ((SignedComputeT)a) << (FixedDecBits + HB_FIXED_ROUND_DIV_ADDBIT);
      tmp = tmp / ((SignedComputeT)b);

      // 丸め処理
      // 削除される小数部の先頭から繰上がらせる
      tmp += HB_FIXED_ROUND_DIV_VAL;

      // 桁あわせ
      tmp = tmp >> HB_FIXED_ROUND_DIV_ADDBIT;
    }

#if defined(HB_FIXED_DEBUG)
    OverflowCheck( tmp );
    UnderflowCheck( a, b, tmp );
#endif
    
    return ( (FixedRepT)tmp );
  }

  //
  // 苦肉の策
  // 汚いコンストラクタ
  inline
  HB_Fixed64( FixedRepT dirty, int ) : fixval( dirty )
  {
  }

  
  //----------------------------------------------------------------
  // 公開外部インタフェース
  //----------------------------------------------------------------
public:
  // コピーコンストラクタはデフォルトで十分
  // コンストラクタ
  inline
  HB_Fixed64( int i = 0 ) : fixval( toFixedRep( (int)i ) )
  {
  }

  inline
  HB_Fixed64( unsigned int i ) : fixval( toFixedRep( (int)i ) )
  {
  }

  inline
  HB_Fixed64( long l ) : fixval( toFixedRep( (int)l ) )
  {
  }

  inline
  HB_Fixed64( unsigned long l ) : fixval( toFixedRep( (int)l ) )
  {
  }

  inline
  HB_Fixed64( short s ) : fixval( toFixedRep( (int)s ) )
  {
  }

  inline
  HB_Fixed64( unsigned short s ) : fixval( toFixedRep( (int)s ) )
  {
  }

  inline
  HB_Fixed64( char c ) : fixval( toFixedRep( (int)c ) )
  {
  }
  
  inline
  HB_Fixed64( unsigned char c ) : fixval( toFixedRep( (int)c ) )
  {
  }

  inline
  HB_Fixed64( float d ) : fixval( toFixedRep( (float)d ) )
  {
  }

  inline
  HB_Fixed64( double d ) : fixval( toFixedRep( (double)d ) )
  {
  }

  HB_Fixed64( HB_Fixed32 fix32 );


  // キャスト
  inline
  operator int() const
  {
    return ( fixedrep2int( fixedrep() ) );
  }

  inline
  operator unsigned int() const
  {
    return ( (unsigned int)fixedrep2int( fixedrep() ) );
  }

  inline
  operator long() const
  {
    return ( (long)fixedrep2int( fixedrep() ) );
  }

  inline
  operator unsigned long() const
  {
    return ( (unsigned long)fixedrep2int( fixedrep() ) );
  }

  inline
  operator short() const
  {
    return ( (short)fixedrep2int( fixedrep() ) );
  }

  inline
  operator unsigned short() const
  {
    return ( (unsigned short)fixedrep2int( fixedrep() ) );
  }

  inline
  operator char() const
  {
    return ( (char)fixedrep2int( fixedrep() ) );
  }

  inline
  operator unsigned char() const
  {
    return ( (unsigned char)fixedrep2int( fixedrep() ) );
  }
  
  inline
  operator float() const
  {
    return ( fixedrep2float( fixedrep() ) );
  }

  inline
  operator double() const
  {
    return ( fixedrep2double( fixedrep() ) );
  }

  operator HB_Fixed32();


  // 単項演算子 マイナス
  inline HB_Fixed64 
  operator -() const
  {
    return ( HB_Fixed64( -fixval, 0 ) );
  }


  // 代入はデフォルトで十分

    
  // 加算代入
  inline HB_Fixed64 &
  operator +=( const HB_Fixed64 &fix )
  {
    fixval += fix.fixval;
    return ( *this );
  }

  // 減算代入
  inline HB_Fixed64 &
  operator -=( const HB_Fixed64 &fix )
  {
    fixval -= fix.fixedrep();
    return ( *this );
  }

  // 乗算代入
  inline HB_Fixed64 &
  operator *=( const HB_Fixed64 &fix )
  {
    fixval = HB_Fixed64::multiply( fixval, fix.fixedrep() );
    return ( *this );
  }

  // 除算代入
  inline HB_Fixed64 &
  operator /=( const HB_Fixed64 &fix )
  {
    fixval = HB_Fixed64::divide( fixval, fix.fixedrep() );
    return ( *this );
  }

  // 定数
  inline static HB_Fixed64 MaxValue()
  {
    FixedRepT	v = 1;
    v = ~(v << (FixedBits - 1));

    return ( HB_Fixed64(v, 0) );
  }
 
};





//
// 二項演算子の定義
//
#define HB_FIXED_BINARYOP1(OP, NAME, TYPE)			\
inline HB_Fixed##NAME						\
operator OP ( const HB_Fixed##NAME arg1, TYPE arg2 ) {		\
  HB_Fixed##NAME ret = arg1;					\
  return ( ret OP##= arg2 );					\
};

#define HB_FIXED_BINARYOP2(OP, NAME, TYPE)			\
inline HB_Fixed##NAME						\
operator OP ( const HB_Fixed##NAME arg1, TYPE arg2 ) {		\
  HB_Fixed##NAME ret = arg1;					\
  return ( ret OP##= (HB_Fixed##NAME)arg2 );					\
};								\
inline HB_Fixed##NAME						\
operator OP ( TYPE arg1, const HB_Fixed##NAME arg2 ) {		\
  HB_Fixed##NAME ret = arg1;					\
  return ( ret OP##= arg2 );					\
};								\

// 二項演算子 足し算
HB_FIXED_BINARYOP1(+, 32, const HB_Fixed32 );
HB_FIXED_BINARYOP2(+, 32, int );
HB_FIXED_BINARYOP2(+, 32, float );
HB_FIXED_BINARYOP2(+, 32, double );
HB_FIXED_BINARYOP1(+, 64, const HB_Fixed64 );
HB_FIXED_BINARYOP2(+, 64, int );
HB_FIXED_BINARYOP2(+, 64, unsigned long );
HB_FIXED_BINARYOP2(+, 64, float );
HB_FIXED_BINARYOP2(+, 64, double );
  
// 二項演算子 引き算
HB_FIXED_BINARYOP1(-, 32, const HB_Fixed32 );
HB_FIXED_BINARYOP2(-, 32, int );
HB_FIXED_BINARYOP2(-, 32, float );
HB_FIXED_BINARYOP2(-, 32, double );
HB_FIXED_BINARYOP1(-, 64, const HB_Fixed64 );
HB_FIXED_BINARYOP2(-, 64, int );
HB_FIXED_BINARYOP2(-, 64, float );
HB_FIXED_BINARYOP2(-, 64, double );

// 二項演算子 掛け算
HB_FIXED_BINARYOP1(*, 32, const HB_Fixed32 );
HB_FIXED_BINARYOP2(*, 32, int );
HB_FIXED_BINARYOP2(*, 32, float );
HB_FIXED_BINARYOP2(*, 32, double );
HB_FIXED_BINARYOP1(*, 64, const HB_Fixed64 );
HB_FIXED_BINARYOP2(*, 64, int );
HB_FIXED_BINARYOP2(*, 64, float );
HB_FIXED_BINARYOP2(*, 64, double );
    
// 二項演算子 割り算
HB_FIXED_BINARYOP1(/, 32, const HB_Fixed32 );
HB_FIXED_BINARYOP2(/, 32, int );
HB_FIXED_BINARYOP2(/, 32, float );
HB_FIXED_BINARYOP2(/, 32, double );
HB_FIXED_BINARYOP1(/, 64, const HB_Fixed64 );
HB_FIXED_BINARYOP2(/, 64, int );
HB_FIXED_BINARYOP2(/, 64, float );
HB_FIXED_BINARYOP2(/, 64, double );


//
// 比較演算子の定義
//
#define	HB_FIXED_COMPAREOP1(OP, NAME)					\
inline bool								\
operator OP ( const HB_Fixed##NAME arg1, const HB_Fixed##NAME arg2 ) {	\
  return ( arg1.fixedrep() OP arg2.fixedrep() );			\
}

#define	HB_FIXED_COMPAREOP2(OP, NAME, TYPE)				\
inline bool								\
operator OP ( const HB_Fixed##NAME arg1, TYPE arg2 ) {			\
  return ( arg1.fixedrep() OP HB_Fixed##NAME::toFixedRep(arg2) );	\
}									\
inline bool								\
operator OP ( TYPE arg1, const HB_Fixed##NAME arg2 ) {			\
  return ( HB_Fixed##NAME::toFixedRep(arg1) OP arg2.fixedrep() );	\
}

// 比較演算子 ==
HB_FIXED_COMPAREOP1(==, 32);
HB_FIXED_COMPAREOP2(==, 32, int);
HB_FIXED_COMPAREOP2(==, 32, float);
HB_FIXED_COMPAREOP2(==, 32, double);
HB_FIXED_COMPAREOP1(==, 64);
HB_FIXED_COMPAREOP2(==, 64, int);
HB_FIXED_COMPAREOP2(==, 64, float);
HB_FIXED_COMPAREOP2(==, 64, double);

// 比較演算子 !=
HB_FIXED_COMPAREOP1(!=, 32);
HB_FIXED_COMPAREOP2(!=, 32, int);
HB_FIXED_COMPAREOP2(!=, 32, float);
HB_FIXED_COMPAREOP2(!=, 32, double);
HB_FIXED_COMPAREOP1(!=, 64);
HB_FIXED_COMPAREOP2(!=, 64, int);
HB_FIXED_COMPAREOP2(!=, 64, float);
HB_FIXED_COMPAREOP2(!=, 64, double);

// 比較演算子 <
HB_FIXED_COMPAREOP1(<, 32);
HB_FIXED_COMPAREOP2(<, 32, int);
HB_FIXED_COMPAREOP2(<, 32, float);
HB_FIXED_COMPAREOP2(<, 32, double);
HB_FIXED_COMPAREOP1(<, 64);
HB_FIXED_COMPAREOP2(<, 64, int);
HB_FIXED_COMPAREOP2(<, 64, float);
HB_FIXED_COMPAREOP2(<, 64, double);

// 比較演算子 >
HB_FIXED_COMPAREOP1(>, 32);
HB_FIXED_COMPAREOP2(>, 32, int);
HB_FIXED_COMPAREOP2(>, 32, float);
HB_FIXED_COMPAREOP2(>, 32, double);
HB_FIXED_COMPAREOP1(>, 64);
HB_FIXED_COMPAREOP2(>, 64, int);
HB_FIXED_COMPAREOP2(>, 64, float);
HB_FIXED_COMPAREOP2(>, 64, double);

// 比較演算子 <=
HB_FIXED_COMPAREOP1(<=, 32);
HB_FIXED_COMPAREOP2(<=, 32, int);
HB_FIXED_COMPAREOP2(<=, 32, float);
HB_FIXED_COMPAREOP2(<=, 32, double);
HB_FIXED_COMPAREOP1(<=, 64);
HB_FIXED_COMPAREOP2(<=, 64, int);
HB_FIXED_COMPAREOP2(<=, 64, float);
HB_FIXED_COMPAREOP2(<=, 64, double);

// 比較演算子 >=
HB_FIXED_COMPAREOP1(>=, 32);
HB_FIXED_COMPAREOP2(>=, 32, int);
HB_FIXED_COMPAREOP2(>=, 32, float);
HB_FIXED_COMPAREOP2(>=, 32, double);
HB_FIXED_COMPAREOP1(>=, 64);
HB_FIXED_COMPAREOP2(>=, 64, int);
HB_FIXED_COMPAREOP2(>=, 64, float);
HB_FIXED_COMPAREOP2(>=, 64, double);


//
// その他サービス関数
//
#define HB_FIXED_FABS( NAME )					\
static HB_Fixed##NAME						\
fabs( const HB_Fixed##NAME &fix )				\
{								\
  HB_Fixed##NAME ret = fix;					\
  return ( (fix.fixedrep() < 0) ? -ret : ret );			\
}

#define HB_FIXED_FLOOR( NAME )					\
inline HB_Fixed##NAME						\
floor( const HB_Fixed##NAME &fix )				\
{								\
  HB_Fixed##NAME ret = (int)fix;				\
  HB_Fixed##NAME::FixedRepT mask = 0;				\
  mask = ~((~mask) << HB_Fixed##NAME::FixedDecBits);		\
  if ( fix.fixedrep() >= 0 || (fix.fixedrep() & mask) == 0 ) {	\
    return ( ret );						\
  }								\
  else {							\
    ret -= 1;							\
    return ( ret );						\
  }								\
}

// fabs
HB_FIXED_FABS(32);
HB_FIXED_FABS(64);
// floor
HB_FIXED_FLOOR(32);
HB_FIXED_FLOOR(64);


// 相互変換
// Fixed32 -> Fixed64
inline
HB_Fixed32::operator HB_Fixed64()
{
  HB_Fixed64::FixedRepT	fixed64;

  fixed64 = fixedrep();

  // 桁あわせ
  fixed64 = fixed64 << HB_FIXED_ROUND_DOUBLE_ADDBIT;

  return ( HB_Fixed64(fixed64,0) );
}

// Fixed64 -> Fixed32
inline
HB_Fixed32::HB_Fixed32( HB_Fixed64 fix64 )
{
  SignedComputeT	fixed64;

  fixed64 = fix64.fixedrep();

  // 丸め処理
  // 削除される小数部の先頭から繰上がらせる
  fixed64 += HB_FIXED_ROUND_DOUBLE_VAL;

  // 桁あわせ
  fixed64 = fixed64 >> HB_FIXED_ROUND_DOUBLE_ADDBIT;

#if defined(HB_FIXED_DEBUG)
  OverflowCheck( fixed64 );
  UnderflowCheck( fix64.fixedrep(), 0, fixed64 );
#endif

  fixval = (HB_Fixed32::FixedRepT)fixed64;
}

// Fixed64 -> Fixed32
inline
HB_Fixed64::operator HB_Fixed32()
{
  SignedComputeT	fixed64;

  fixed64 = fixedrep();

#if defined(HB_FIXED_DEBUG)
  SignedComputeT	mask = 0;
  mask = (~mask) << (HB_Fixed32::FixedBits + HB_FIXED_ROUND_DOUBLE_ADDBIT);
  if ( fixed64 & mask ) {
    // Overflow
    HB_Fixed32::ComputeError( fixed64, mask );
  }
#endif

  // 丸め処理
  // 削除される小数部の先頭から繰上がらせる
  fixed64 += HB_FIXED_ROUND_DOUBLE_VAL;

  // 桁あわせ
  fixed64 = fixed64 >> HB_FIXED_ROUND_DOUBLE_ADDBIT;

#if defined(HB_FIXED_DEBUG)
  HB_Fixed32::UnderflowCheck( fixedrep(), 0, fixed64 );
#endif

  return ( HB_Fixed32((HB_Fixed32::FixedRepT)fixed64,0) );
}

// Fixed32 -> Fixed64
inline
HB_Fixed64::HB_Fixed64( HB_Fixed32 fix32 )
{
  HB_Fixed64::FixedRepT	fixed64;

  fixed64 = fix32.fixedrep();

  // 桁あわせ
  fixed64 = fixed64 << HB_FIXED_ROUND_DOUBLE_ADDBIT;

  fixval = fixed64;
}

  
//
// 定数
//

#define HB_FIXED32_CONST_MAX	HB_Fixed32::MaxValue()
#define HB_FIXED64_CONST_MAX	HB_Fixed64::MaxValue()

#define HB_FIXED32_CONST_0_5	HB_Fixed32::Const_0_5()
#define HB_FIXED32_CONST_0_0	HB_Fixed32::Const_0_0()


#endif
