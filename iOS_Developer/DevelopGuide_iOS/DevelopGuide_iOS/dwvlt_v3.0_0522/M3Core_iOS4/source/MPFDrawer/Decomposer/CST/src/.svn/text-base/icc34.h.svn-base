/* Header file guard bands */
#ifndef ICC_H
#define ICC_H

/***************************************************************** 
 Copyright (c) 1994-1996 SunSoft, Inc.

                    Rights Reserved

Permission is hereby granted, free of charge, to any person 
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without restrict- 
ion, including without limitation the rights to use, copy, modify, 
merge, publish distribute, sublicense, and/or sell copies of the 
Software, and to permit persons to whom the Software is furnished 
to do so, subject to the following conditions: 
 
The above copyright notice and this permission notice shall be 
included in all copies or substantial portions of the Software. 
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-
INFRINGEMENT.  IN NO EVENT SHALL SUNSOFT, INC. OR ITS PARENT 
COMPANY BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
OTHER DEALINGS IN THE SOFTWARE. 
 
Except as contained in this notice, the name of SunSoft, Inc. 
shall not be used in advertising or otherwise to promote the 
sale, use or other dealings in this Software without written 
authorization from SunSoft Inc. 

enum を#define に変更してある by Toshio Yamazaki
******************************************************************/

/*
 * This version of the header file corresponds to the profile
 * specification version 3.4.
 *
 * All header file entries are pre-fixed with "ic" to help 
 * avoid name space collisions. Signatures are pre-fixed with
 * icSig.
 *
 * The structures defined in this header file were created to
 * represent a description of an ICC profile on disk. Rather
 * than use pointers a technique is used where a single byte array 
 * was placed at the end of each structure. This allows us in "C"
 * to extend the structure by allocating more data than is needed
 * to account for variable length structures.
 *
 * This also ensures that data following is allocated
 * contiguously and makes it easier to write and read data from
 * the file. 
 *
 * For example to allocate space for a 256 count length UCR
 * and BG array, and fill the allocated data.  Note strlen + 1
 * to remember NULL terminator.
 *
        icUcrBgCurve    *ucrCurve, *bgCurve;
        int             ucr_nbytes, bg_nbytes, string_bytes;
        icUcrBg         *ucrBgWrite;
        char            ucr_string[100], *ucr_char;

        strcpy(ucr_string, "Example ucrBG curves");
        ucr_nbytes = sizeof(icUInt32Number) + 
                 (UCR_CURVE_SIZE * sizeof(icUInt16Number));
        bg_nbytes = sizeof(icUInt32Number) + 
                 (BG_CURVE_SIZE * sizeof(icUInt16Number));
        string_bytes = strlen(ucr_string) + 1;

        ucrBgWrite = (icUcrBg *)malloc(
                                (ucr_nbytes + bg_nbytes + string_bytes));
 
        ucrCurve = (icUcrBgCurve *)ucrBgWrite->data;
        ucrCurve->count = UCR_CURVE_SIZE;
        for (i=0; i<ucrCurve->count; i++)
                ucrCurve->curve[i] = (icUInt16Number)i;
 
        bgCurve = (icUcrBgCurve *)((char *)ucrCurve + ucr_nbytes);
        bgCurve->count = BG_CURVE_SIZE;
        for (i=0; i<bgCurve->count; i++)
                bgCurve->curve[i] = 255 - (icUInt16Number)i;

        ucr_char = (char *)((char *)bgCurve + bg_nbytes);
        memcpy(ucr_char, ucr_string, string_bytes);
 *
 */

/*
 * Many of the structures contain variable length arrays. This
 * is represented by the use of the convention.
 *
 *      type    data[icAny];
 */

/*------------------------------------------------------------------------*/
/*
 * Defines used in the specification
 */
#define icMagicNumber                   0x61637370L     /* 'acsp' */
#define icVersionNumber                 0x02100000L     /* 2.1.0, BCD */

/* Screening Encodings */
#define icPrtrDefaultScreensFalse       0x00000000L     /* Bit pos 0 */
#define icPrtrDefaultScreensTrue        0x00000001L     /* Bit pos 0 */
#define icLinesPerInch                  0x00000002L     /* Bit pos 1 */
#define icLinesPerCm                    0x00000000L     /* Bit pos 1 */

/* 
 * Device attributes, currently defined values correspond
 * to the low 4 bytes of the 8 byte attribute quantity, see
 * the header for their location.
 */
#define icReflective                    0x00000000L     /* Bit pos 0 */
#define icTransparency                  0x00000001L     /* Bit pos 0 */
#define icGlossy                        0x00000000L     /* Bit pos 1 */
#define icMatte                         0x00000002L     /* Bit pos 1 */

/*
 * Profile header flags, the low 16 bits are reserved for consortium
 * use.
 */
#define icEmbeddedProfileFalse          0x00000000L     /* Bit pos 0 */
#define icEmbeddedProfileTrue           0x00000001L     /* Bit pos 0 */
#define icUseAnywhere                   0x00000000L     /* Bit pos 1 */
#define icUseWithEmbeddedDataOnly       0x00000002L     /* Bit pos 1 */

/* Ascii or Binary data */
#define icAsciiData                     0x00000000L 
#define icBinaryData                    0x00000001L

/* 
 * Define used to indicate that this is a variable length array
 */
#define icAny                           1


/*------------------------------------------------------------------------*/
/*
 * Use this area to translate platform definitions of long
 * etc into icXXX form. The rest of the header uses the icXXX
 * typedefs. Signatures are 4 byte quantities.
 */
#ifdef __sgi
#include "sgidefs.h"

typedef __int32_t       icSignature;

/*
 * Number definitions
 */

/* Unsigned integer numbers */
typedef unsigned char   icUInt8Number;
typedef unsigned short  icUInt16Number;
typedef __uint32_t      icUInt32Number;
typedef __uint32_t      icUInt64Number[2];

/* Signed numbers */
typedef char            icInt8Number;
typedef short           icInt16Number;
typedef __int32_t       icInt32Number;
typedef __int32_t       icInt64Number[2];

/* Fixed numbers */
typedef __int32_t       icS15Fixed16Number;
typedef __uint32_t      icU16Fixed16Number;

#else   /* default definitions */

typedef long            icSignature;

/*
 * Number definitions
 */

/* Unsigned integer numbers */
typedef unsigned char   icUInt8Number;
typedef unsigned short  icUInt16Number;
typedef unsigned long   icUInt32Number;
typedef unsigned long   icUInt64Number[2];

/* Signed numbers */
typedef char            icInt8Number;
typedef short           icInt16Number;
typedef long            icInt32Number;
typedef long            icInt64Number[2];

/* Fixed numbers */
typedef long            icS15Fixed16Number;
typedef unsigned long   icU16Fixed16Number;
#endif  /* default defs */

/*------------------------------------------------------------------------*/
/* public tags and sizes */
/* typedef enum { */
#define icSigAToB0Tag			0x41324230L	/* 'A2B0' */ 
#define icSigAToB1Tag			0x41324231L	/* 'A2B1' */
#define icSigAToB2Tag			0x41324232L	/* 'A2B2' */ 
#define icSigBlueColorantTag		0x6258595AL	/* 'bXYZ' */
#define icSigBlueTRCTag			0x62545243L	/* 'bTRC' */
#define icSigBToA0Tag			0x42324130L	/* 'B2A0' */
#define icSigBToA1Tag			0x42324131L	/* 'B2A1' */
#define icSigBToA2Tag			0x42324132L	/* 'B2A2' */
#define icSigCalibrationDateTimeTag	0x63616C74L	/* 'calt' */
#define icSigCharTargetTag		0x74617267L	/* 'targ' */ 
#define icSigCopyrightTag		0x63707274L	/* 'cprt' */
#define icSigCrdInfoTag			0x63726469L	/* 'crdi' */
#define icSigDeviceMfgDescTag		0x646D6E64L	/* 'dmnd' */
#define icSigDeviceModelDescTag		0x646D6464L	/* 'dmdd' */
#define icSigGamutTag			0x67616D74L	/* 'gamt ' */
#define icSigGrayTRCTag			0x6b545243L	/* 'kTRC' */
#define icSigGreenColorantTag		0x6758595AL	/* 'gXYZ' */
#define icSigGreenTRCTag		0x67545243L	/* 'gTRC' */
#define icSigLuminanceTag		0x6C756d69L	/* 'lumi' */
#define icSigMeasurementTag		0x6D656173L	/* 'meas' */
#define icSigMediaBlackPointTag		0x626B7074L	/* 'bkpt' */
#define icSigMediaWhitePointTag		0x77747074L	/* 'wtpt' */
#define icSigNamedColorTag		0x6E636f6CL	/* 'ncol' OBSOLETE, use ncl2 */
#define icSigNamedColor2Tag		0x6E636C32L	/* 'ncl2' */
#define icSigPreview0Tag		0x70726530L	/* 'pre0' */
#define icSigPreview1Tag		0x70726531L	/* 'pre1' */
#define icSigPreview2Tag		0x70726532L	/* 'pre2' */
#define icSigProfileDescriptionTag	0x64657363L	/* 'desc' */
#define icSigProfileSequenceDescTag	0x70736571L	/* 'pseq' */
#define icSigPs2CRD0Tag			0x70736430L	/* 'psd0' */
#define icSigPs2CRD1Tag			0x70736431L	/* 'psd1' */
#define icSigPs2CRD2Tag			0x70736432L	/* 'psd2' */
#define icSigPs2CRD3Tag			0x70736433L	/* 'psd3' */
#define icSigPs2CSATag			0x70733273L	/* 'ps2s' */
#define icSigPs2RenderingIntentTag	0x70733269L	/* 'ps2i' */
#define icSigRedColorantTag		0x7258595AL	/* 'rXYZ' */
#define icSigRedTRCTag			0x72545243L	/* 'rTRC' */
#define icSigScreeningDescTag		0x73637264L	/* 'scrd' */
#define icSigScreeningTag		0x7363726EL	/* 'scrn' */
#define icSigTechnologyTag		0x74656368L	/* 'tech' */
#define icSigUcrBgTag			0x62666420L	/* 'bfd ' */
#define icSigViewingCondDescTag		0x76756564L	/* 'vued' */
#define icSigViewingConditionsTag	0x76696577L	/* 'view' */
#define icMaxEnumTag			0xFFFFFFFFL 
/* } icTagSignature; */
typedef long icTagSignature;

/* technology signature descriptions */
/* typedef enum { */
#define icSigDigitalCamera		0x6463616DL	/* 'dcam' */
#define icSigFilmScanner		0x6673636EL	/* 'fscn' */
#define icSigReflectiveScanner		0x7273636EL	/* 'rscn' */
#define icSigInkJetPrinter		0x696A6574L	/* 'ijet' */ 
#define icSigThermalWaxPrinter		0x74776178L	/* 'twax' */
#define icSigElectrophotographicPrinter	0x6570686FL	/* 'epho' */
#define icSigElectrostaticPrinter	0x65737461L	/* 'esta' */
#define icSigDyeSublimationPrinter	0x64737562L	/* 'dsub' */
#define icSigPhotographicPaperPrinter	0x7270686FL	/* 'rpho' */
#define icSigFilmWriter			0x6670726EL	/* 'fprn' */
#define icSigVideoMonitor		0x7669646DL	/* 'vidm' */
#define icSigVideoCamera		0x76696463L	/* 'vidc' */
#define icSigProjectionTelevision	0x706A7476L	/* 'pjtv' */
#define icSigCRTDisplay			0x43525420L	/* 'CRT ' */
#define icSigPMDisplay			0x504D4420L	/* 'PMD ' */
#define icSigAMDisplay			0x414D4420L	/* 'AMD ' */
#define icSigPhotoCD			0x4B504344L	/* 'KPCD' */
#define icSigPhotoImageSetter		0x696D6773L	/* 'imgs' */
#define icSigGravure			0x67726176L	/* 'grav' */
#define icSigOffsetLithography		0x6F666673L	/* 'offs' */
#define icSigSilkscreen			0x73696C6BL	/* 'silk' */
#define icSigFlexography		0x666C6578L	/* 'flex' */
#define icMaxEnumTechnology		0xFFFFFFFFL   
/* } icTechnologySignature; */
typedef long icTechnologySignature;

/* type signatures */
/* typedef enum { */
#define icSigCurveType			0x63757276L	/* 'curv' */
#define icSigDataType			0x64617461L	/* 'data' */
#define icSigDateTimeType		0x6474696DL	/* 'dtim' */
#define icSigLut16Type			0x6d667432L	/* 'mft2' */
#define icSigLut8Type			0x6d667431L	/* 'mft1' */
#define icSigMeasurementType		0x6D656173L	/* 'meas' */
#define icSigNamedColorType		0x6E636f6CL	/* 'ncol' OBSOLETE, use ncl2 */
#define icSigProfileSequenceDescType	0x70736571L	/* 'pseq' */
#define icSigS15Fixed16ArrayType	0x73663332L	/* 'sf32' */
#define icSigScreeningType		0x7363726EL	/* 'scrn' */
#define icSigSignatureType		0x73696720L	/* 'sig ' */
#define icSigTextType			0x74657874L	/* 'text' */
#define icSigTextDescriptionType	0x64657363L	/* 'desc' */
#define icSigU16Fixed16ArrayType	0x75663332L	/* 'uf32' */
#define icSigUcrBgType			0x62666420L	/* 'bfd ' */
#define icSigUInt16ArrayType		0x75693136L	/* 'ui16' */
#define icSigUInt32ArrayType		0x75693332L	/* 'ui32' */
#define icSigUInt64ArrayType		0x75693634L	/* 'ui64' */
#define icSigUInt8ArrayType		0x75693038L	/* 'ui08' */
#define icSigViewingConditionsType	0x76696577L	/* 'view' */
#define icSigXYZType			0x58595A20L	/* 'XYZ ' */
#define icSigXYZArrayType		0x58595A20L	/* 'XYZ ' */
#define icSigNamedColor2Type		0x6E636C32L	/* 'ncl2' */
#define icSigCrdInfoType		0x63726469L	/* 'crdi' */
#define icMaxEnumType			0xFFFFFFFFL   
/* } icTagTypeSignature; */
typedef long icTagTypeSignature;

/* 
 * Color Space Signatures
 * Note that only icSigXYZData and icSigLabData are valid
 * Profile Connection Spaces (PCSs)
 */ 
/* typedef enum { */
#define icSigXYZData		0x58595A20L	/* 'XYZ ' */
#define icSigLabData		0x4C616220L	/* 'Lab ' */
#define icSigLuvData		0x4C757620L	/* 'Luv ' */
#define icSigYCbCrData		0x59436272L	/* 'YCbr' */
#define icSigYxyData		0x59787920L	/* 'Yxy ' */
#define icSigRgbData		0x52474220L	/* 'RGB ' */
#define icSigGrayData		0x47524159L	/* 'GRAY' */
#define icSigHsvData		0x48535620L	/* 'HSV ' */
#define icSigHlsData		0x484C5320L	/* 'HLS ' */
#define icSigCmykData		0x434D594BL	/* 'CMYK' */
#define icSigCmyData		0x434D5920L	/* 'CMY ' */
#define icSig2colorData		0x32434C52L	/* '2CLR' */
#define icSig3colorData		0x33434C52L	/* '3CLR' */
#define icSig4colorData		0x34434C52L	/* '4CLR' */
#define icSig5colorData		0x35434C52L	/* '5CLR' */
#define icSig6colorData		0x36434C52L	/* '6CLR' */
#define icSig7colorData		0x37434C52L	/* '7CLR' */
#define icSig8colorData		0x38434C52L	/* '8CLR' */
#define icSig9colorData		0x39434C52L	/* '9CLR' */
#define icSig10colorData	0x41434C52L	/* 'ACLR' */
#define icSig11colorData	0x42434C52L	/* 'BCLR' */
#define icSig12colorData	0x43434C52L	/* 'CCLR' */
#define icSig13colorData	0x44434C52L	/* 'DCLR' */
#define icSig14colorData	0x45434C52L	/* 'ECLR' */
#define icSig15colorData	0x46434C52L	/* 'FCLR' */
#define icMaxEnumData		0xFFFFFFFFL   
/* } icColorSpaceSignature; */
typedef long icColorSpaceSignature;

/* profileClass enumerations */
/*typedef enum {*/
#define icSigInputClass		0x73636E72L	/* 'scnr' */
#define icSigDisplayClass	0x6D6E7472L	/* 'mntr' */
#define icSigOutputClass	0x70727472L	/* 'prtr' */
#define icSigLinkClass		0x6C696E6BL	/* 'link' */
#define icSigAbstractClass	0x61627374L	/* 'abst' */
#define icSigColorSpaceClass	0x73706163L	/* 'spac' */
#define icSigNamedColorClass	0x6e6d636cL	/* 'nmcl' */
#define icMaxEnumClass		0xFFFFFFFFL  
/*} icProfileClassSignature; */
typedef long icProfileClassSignature;

/* Platform Signatures */
/*typedef enum { */
#define icSigMacintosh		0x4150504CL	/* 'APPL' */
#define icSigMicrosoft		0x4D534654L	/* 'MSFT' */
#define icSigSolaris		0x53554E57L	/* 'SUNW' */
#define icSigSGI		0x53474920L	/* 'SGI ' */
#define icSigTaligent		0x54474E54L	/* 'TGNT' */
#define icMaxEnumPlatform	0xFFFFFFFFL  
/*} icPlatformSignature;*/
typedef long icPlatformSignature;

/*------------------------------------------------------------------------*/
/*
 * Other enums
 */

/* Measurement Flare, used in the measurmentType tag */
/* typedef enum { */
#define icFlare0		0x00000000L	/* 0% flare */
#define icFlare100		0x00000001L	/* 100% flare */
#define icMaxFlare		0xFFFFFFFFL   
/* } icMeasurementFlare; */
typedef long icMeasurementFlare;

/* Measurement Geometry, used in the measurmentType tag */
/* typedef enum { */
#define icGeometryUnknown	0x00000000L	/* Unknown */
#define icGeometry045or450	0x00000001L	/* 0/45, 45/0 */
#define icGeometry0dord0	0x00000002L	/* 0/d or d/0 */
#define icMaxGeometry		0xFFFFFFFFL   
/* } icMeasurementGeometry; */
typedef long icMeasurementGeometry;

/* Rendering Intents, used in the profile header */
/* typedef enum { */
#define icPerceptual		0
#define icRelativeColorimetric	1
#define icSaturation		2
#define icAbsoluteColorimetric	3
#define icMaxEnumIntent		0xFFFFFFFFL   
/* } icRenderingIntent; */
typedef long icRenderingIntent;

/* Different Spot Shapes currently defined, used for screeningType */
/* typedef enum { */
#define icSpotShapeUnknown		0
#define icSpotShapePrinterDefault	1
#define icSpotShapeRound		2
#define icSpotShapeDiamond		3
#define icSpotShapeEllipse		4
#define icSpotShapeLine			5
#define icSpotShapeSquare		6
#define icSpotShapeCross		7
#define icMaxEnumSpot			0xFFFFFFFFL   
/* } icSpotShape; */
typedef long icSpotShape;

/* Standard Observer, used in the measurmentType tag */
/* typedef enum { */
#define icStdObsUnknown		0x00000000L	/* Unknown */
#define icStdObs1931TwoDegrees	0x00000001L	/* 2 deg */
#define icStdObs1964TenDegrees	0x00000002L	/* 10 deg */
#define icMaxStdObs		0xFFFFFFFFL   
/* } icStandardObserver; */
typedef long icStandardObserver;

/* Pre-defined illuminants, used in measurement and viewing conditions type */
/* typedef enum { */
#define icIlluminantUnknown	0x00000000L
#define icIlluminantD50		0x00000001L
#define icIlluminantD65		0x00000002L
#define icIlluminantD93		0x00000003L
#define icIlluminantF2		0x00000004L
#define icIlluminantD55		0x00000005L
#define icIlluminantA		0x00000006L
#define icIlluminantEquiPowerE	0x00000007L  
#define icIlluminantF8		0x00000008L  
#define icMaxEnumIluminant	0xFFFFFFFFL   
/* } icIlluminant; */
typedef long icIlluminant;


/*------------------------------------------------------------------------*/
/*
 * Arrays of numbers 
 */

/* Int8 Array */
typedef struct {
    icInt8Number        data[icAny];    /* Variable array of values */
} icInt8Array;

/* UInt8 Array */
typedef struct {
    icUInt8Number       data[icAny];    /* Variable array of values */
} icUInt8Array;

/* uInt16 Array */
typedef struct {
    icUInt16Number      data[icAny];    /* Variable array of values */
} icUInt16Array;

/* Int16 Array */
typedef struct {
    icInt16Number       data[icAny];    /* Variable array of values */
} icInt16Array;

/* uInt32 Array */
typedef struct {
    icUInt32Number      data[icAny];    /* Variable array of values */
} icUInt32Array;

/* Int32 Array */
typedef struct {
    icInt32Number       data[icAny];    /* Variable array of values */
} icInt32Array;

/* UInt64 Array */
typedef struct {
    icUInt64Number      data[icAny];    /* Variable array of values */
} icUInt64Array;

/* Int64 Array */
typedef struct {
    icInt64Number       data[icAny];    /* Variable array of values */
} icInt64Array;
    
/* u16Fixed16 Array */
typedef struct {
    icU16Fixed16Number  data[icAny];    /* Variable array of values */
} icU16Fixed16Array;

/* s15Fixed16 Array */
typedef struct {
    icS15Fixed16Number  data[icAny];    /* Variable array of values */
} icS15Fixed16Array;

/* The base date time number */
typedef struct {
    icUInt16Number      year;
    icUInt16Number      month;
    icUInt16Number      day;
    icUInt16Number      hours;
    icUInt16Number      minutes;
    icUInt16Number      seconds;
} icDateTimeNumber;

/* XYZ Number  */
typedef struct {
    icS15Fixed16Number  X;
    icS15Fixed16Number  Y;
    icS15Fixed16Number  Z;
} icXYZNumber;

/* XYZ Array */
typedef struct {
    icXYZNumber         data[icAny];    /* Variable array of XYZ numbers */
} icXYZArray;

/* Curve */
typedef struct {
    icUInt32Number      count;          /* Number of entries */
    icUInt16Number      data[icAny];    /* The actual table data, real
                                         * number is determined by count
                                         * Interpretation depends on how
                                         * data is used with a given tag
                                         */
} icCurve;

/* Data */
typedef struct {
    icUInt32Number      dataFlag;       /* 0 = ascii, 1 = binary */
    icInt8Number        data[icAny];    /* Data, size from tag */
} icData;

/* lut16 */
typedef struct {
    icUInt8Number       inputChan;      /* Number of input channels */
    icUInt8Number       outputChan;     /* Number of output channels */
    icUInt8Number       clutPoints;     /* Number of grid points */
    icInt8Number        pad;            /* Padding for byte alignment */
    icS15Fixed16Number  e00;            /* e00 in the 3 * 3 */
    icS15Fixed16Number  e01;            /* e01 in the 3 * 3 */    
    icS15Fixed16Number  e02;            /* e02 in the 3 * 3 */
    icS15Fixed16Number  e10;            /* e10 in the 3 * 3 */
    icS15Fixed16Number  e11;            /* e11 in the 3 * 3 */    
    icS15Fixed16Number  e12;            /* e12 in the 3 * 3 */ 
    icS15Fixed16Number  e20;            /* e20 in the 3 * 3 */
    icS15Fixed16Number  e21;            /* e21 in the 3 * 3 */    
    icS15Fixed16Number  e22;            /* e22 in the 3 * 3 */
    icUInt16Number      inputEnt;       /* Num of in-table entries */
    icUInt16Number      outputEnt;      /* Num of out-table entries */
    icUInt16Number      data[icAny];    /* Data follows see spec */
/*
 *  Data that follows is of this form
 *
 *  icUInt16Number      inputTable[inputChan][icAny];   * The in-table
 *  icUInt16Number      clutTable[icAny];               * The clut 
 *  icUInt16Number      outputTable[outputChan][icAny]; * The out-table
 */
} icLut16;

/* lut8, input & output tables are always 256 bytes in length */
typedef struct {
    icUInt8Number       inputChan;      /* Num of input channels */
    icUInt8Number       outputChan;     /* Num of output channels */
    icUInt8Number       clutPoints;     /* Num of grid points */
    icInt8Number        pad;
    icS15Fixed16Number  e00;            /* e00 in the 3 * 3 */
    icS15Fixed16Number  e01;            /* e01 in the 3 * 3 */    
    icS15Fixed16Number  e02;            /* e02 in the 3 * 3 */
    icS15Fixed16Number  e10;            /* e10 in the 3 * 3 */
    icS15Fixed16Number  e11;            /* e11 in the 3 * 3 */    
    icS15Fixed16Number  e12;            /* e12 in the 3 * 3 */ 
    icS15Fixed16Number  e20;            /* e20 in the 3 * 3 */
    icS15Fixed16Number  e21;            /* e21 in the 3 * 3 */    
    icS15Fixed16Number  e22;            /* e22 in the 3 * 3 */
    icUInt8Number       data[icAny];    /* Data follows see spec */
/*
 *  Data that follows is of this form
 *
 *  icUInt8Number       inputTable[inputChan][256];     * The in-table
 *  icUInt8Number       clutTable[icAny];               * The clut 
 *  icUInt8Number       outputTable[outputChan][256];   * The out-table
 */
} icLut8;

/* Measurement Data */
typedef struct {
    icStandardObserver          stdObserver;    /* Standard observer */
    icXYZNumber                 backing;        /* XYZ for backing */
    icMeasurementGeometry       geometry;       /* Meas. geometry */
    icMeasurementFlare          flare;          /* Measurement flare */
    icIlluminant                illuminant;     /* Illuminant */
} icMeasurement;

/* Named color */

/*
 * icNamedColor2 takes the place of icNamedColor 
 */
typedef struct {
    icUInt32Number      vendorFlag;     /* Bottom 16 bits for IC use */
    icUInt32Number      count;          /* Count of named colors */
    icUInt32Number      nDeviceCoords;  /* Num of device coordinates */
    icInt8Number        prefix[32];     /* Prefix for each color name */
    icInt8Number        suffix[32];     /* Suffix for each color name */
    icInt8Number        data[icAny];    /* Named color data follows */
/*
 *  Data that follows is of this form
 *
 * icInt8Number         root1[32];              * Root name for 1st color
 * icUInt16Number       pcsCoords1[icAny];      * PCS coords of 1st color
 * icUInt16Number       deviceCoords1[icAny];   * Dev coords of 1st color
 * icInt8Number         root2[32];              * Root name for 2nd color
 * icUInt16Number       pcsCoords2[icAny];      * PCS coords of 2nd color
 * icUInt16Number       deviceCoords2[icAny];   * Dev coords of 2nd color
 *                      :
 *                      :
 * Repeat for name and PCS and device color coordinates up to (count-1)
 * 
 * NOTES:  
 * PCS and device space can be determined from the header.
 *
 * PCS coordinates are icUInt16 numbers and are described in Annex A of 
 * the ICC spec. Only 16 bit L*a*b* and XYZ are allowed. The number of 
 * coordinates is consistent with the headers PCS.
 *
 * Device coordinates are icUInt16 numbers where 0x0000 represents
 * the minimum value and 0xFFFF represents the maximum value. 
 * If the nDeviceCoords value is 0 this field is not given.
 */
} icNamedColor2;

/* Profile sequence structure */
typedef struct {
    icSignature                 deviceMfg;      /* Dev Manufacturer */
    icSignature                 deviceModel;    /* Dev Model */
    icUInt64Number              attributes;     /* Dev attributes */
    icTechnologySignature       technology;     /* Technology sig */
    icInt8Number                data[icAny];    /* Desc text follows */
/*
 *  Data that follows is of this form, this is an icInt8Number
 *  to avoid problems with a compiler generating  bad code as 
 *  these arrays are variable in length.
 *
 * icTextDescription            deviceMfgDesc;  * Manufacturer text
 * icTextDescription            modelDesc;      * Model text
 */
} icDescStruct;

/* Profile sequence description */
typedef struct {
    icUInt32Number      count;          /* Number of descriptions */
    icUInt8Number       data[icAny];    /* Array of desc structs */
} icProfileSequenceDesc;

/* textDescription */
typedef struct {
    icUInt32Number      count;          /* Description length */
    icInt8Number        data[icAny];    /* Descriptions follow */
/*
 *  Data that follows is of this form
 *
 * icInt8Number         desc[count]     * NULL terminated ascii string
 * icUInt32Number       ucLangCode;     * UniCode language code
 * icUInt32Number       ucCount;        * UniCode description length
 * icInt16Number        ucDesc[ucCount];* The UniCode description
 * icUInt16Number       scCode;         * ScriptCode code
 * icUInt8Number        scCount;        * ScriptCode count
 * icInt8Number         scDesc[67];     * ScriptCode Description
 */
} icTextDescription;

/* Screening Data */
typedef struct {
    icS15Fixed16Number  frequency;      /* Frequency */
    icS15Fixed16Number  angle;          /* Screen angle */
    icSpotShape         spotShape;      /* Spot Shape encodings below */
} icScreeningData;

typedef struct {
    icUInt32Number      screeningFlag;  /* Screening flag */
    icUInt32Number      channels;       /* Number of channels */
    icScreeningData     data[icAny];    /* Array of screening data */
} icScreening;

/* Text Data */
typedef struct {
    icInt8Number        data[icAny];    /* Variable array of chars */
} icText;

/* Structure describing either a UCR or BG curve */
typedef struct {
    icUInt32Number      count;          /* Curve length */
    icUInt16Number      curve[icAny];   /* The array of curve values */
} icUcrBgCurve;

/* Under color removal, black generation */
typedef struct {
    icInt8Number        data[icAny];            /* The Ucr BG data */
/*
 *  Data that follows is of this form, this is a icInt8Number
 *  to avoid problems with a compiler generating  bad code as 
 *  these arrays are variable in length.
 *
 * icUcrBgCurve         ucr;            * Ucr curve
 * icUcrBgCurve         bg;             * Bg curve
 * icInt8Number         string;         * UcrBg description
 */
} icUcrBg;

/* viewingConditionsType */
typedef struct {
    icXYZNumber         illuminant;     /* In candelas per sq. meter */
    icXYZNumber         surround;       /* In candelas per sq. meter */
    icIlluminant        stdIluminant;   /* See icIlluminant defines */
} icViewingCondition;

/* CrdInfo type */
typedef struct {
    icUInt32Number      count;          /* Char count includes NULL */
    icInt8Number        desc[icAny];    /* Null terminated string */
} icCrdInfo;

/*------------------------------------------------------------------------*/
/*
 * Tag Type definitions
 */

/*
 * Many of the structures contain variable length arrays. This
 * is represented by the use of the convention.
 *
 *      type    data[icAny];
 */

/* The base part of each tag */
typedef struct {
    icTagTypeSignature  sig;            /* Signature */
    icInt8Number        reserved[4];    /* Reserved, set to 0 */
} icTagBase;

/* curveType */
typedef struct {
    icTagBase           base;           /* Signature, "curv" */
    icCurve             curve;          /* The curve data */
} icCurveType;

/* dataType */
typedef struct {
    icTagBase           base;           /* Signature, "data" */
    icData              data;           /* The data structure */
} icDataType;

/* dateTimeType */
typedef struct {
    icTagBase           base;           /* Signature, "dtim" */
    icDateTimeNumber    date;           /* The date */
} icDateTimeType;

/* lut16Type */
typedef struct {
    icTagBase           base;           /* Signature, "mft2" */
    icLut16             lut;            /* Lut16 data */
} icLut16Type;

/* lut8Type, input & output tables are always 256 bytes in length */
typedef struct {
    icTagBase           base;           /* Signature, "mft1" */
    icLut8              lut;            /* Lut8 data */
} icLut8Type;

/* Measurement Type */
typedef struct {
    icTagBase           base;           /* Signature, "meas" */
    icMeasurement       measurement;    /* Measurement data */
} icMeasurementType;

/* Named color type */
/* icNamedColor2Type, replaces icNamedColorType */
typedef struct {
    icTagBase           base;           /* Signature, "ncl2" */
    icNamedColor2       ncolor;         /* Named color data */
} icNamedColor2Type;

/* Profile sequence description type */
typedef struct {
    icTagBase                   base;   /* Signature, "pseq" */
    icProfileSequenceDesc       desc;   /* The seq description */
} icProfileSequenceDescType;

/* textDescriptionType */
typedef struct {
    icTagBase                   base;   /* Signature, "desc" */
    icTextDescription           desc;   /* The description */
} icTextDescriptionType;

/* s15Fixed16Type */
typedef struct {
    icTagBase           base;           /* Signature, "sf32" */
    icS15Fixed16Array   data;           /* Array of values */
} icS15Fixed16ArrayType;

typedef struct {
    icTagBase           base;           /* Signature, "scrn" */
    icScreening         screen;         /* Screening structure */
} icScreeningType;

/* sigType */
typedef struct {
    icTagBase           base;           /* Signature, "sig" */
    icSignature         signature;      /* The signature data */
} icSignatureType;

/* textType */
typedef struct {
    icTagBase           base;           /* Signature, "text" */
    icText              data;           /* Variable array of chars */
} icTextType;

/* u16Fixed16Type */
typedef struct {
    icTagBase           base;           /* Signature, "uf32" */
    icU16Fixed16Array   data;           /* Variable array of values */
} icU16Fixed16ArrayType;

/* Under color removal, black generation type */
typedef struct {
    icTagBase           base;           /* Signature, "bfd " */
    icUcrBg             data;           /* ucrBg structure */
} icUcrBgType;

/* uInt16Type */
typedef struct {
    icTagBase           base;           /* Signature, "ui16" */
    icUInt16Array       data;           /* Variable array of values */
} icUInt16ArrayType;

/* uInt32Type */
typedef struct {
    icTagBase           base;           /* Signature, "ui32" */
    icUInt32Array       data;           /* Variable array of values */
} icUInt32ArrayType;

/* uInt64Type */
typedef struct {
    icTagBase           base;           /* Signature, "ui64" */
    icUInt64Array       data;           /* Variable array of values */
} icUInt64ArrayType;
    
/* uInt8Type */
typedef struct {
    icTagBase           base;           /* Signature, "ui08" */
    icUInt8Array        data;           /* Variable array of values */
} icUInt8ArrayType;

/* viewingConditionsType */
typedef struct {
    icTagBase           base;           /* Signature, "view" */
    icViewingCondition  view;           /* Viewing conditions */
} icViewingConditionType;

/* XYZ Type */
typedef struct {
    icTagBase           base;           /* Signature, "XYZ" */
    icXYZArray          data;           /* Variable array of XYZ nums */
} icXYZType;

/* CRDInfoType where [0] is the CRD product name count and string and
 * [1] -[5] are the rendering intents 0-4 counts and strings
 */
typedef struct {
    icTagBase           base;           /* Signature, "crdi" */
    icCrdInfo           info;           /* 5 sets of counts & strings */
}icCrdInfoType;
     /*   icCrdInfo       productName;     PS product count/string */
     /*   icCrdInfo       CRDName0;        CRD name for intent 0 */ 
     /*   icCrdInfo       CRDName1;        CRD name for intent 1 */ 
     /*   icCrdInfo       CRDName2;        CRD name for intent 2 */ 
     /*   icCrdInfo       CRDName3;        CRD name for intent 3 */
    
/*------------------------------------------------------------------------*/

/*
 * Lists of tags, tags, profile header and profile structure
 */

/* A tag */
typedef struct {
    icTagSignature      sig;            /* The tag signature */
    icUInt32Number      offset;         /* Start of tag relative to 
                                         * start of header, Spec 
                                         * Clause 5 */
    icUInt32Number      size;           /* Size in bytes */
} icTag;

/* A Structure that may be used independently for a list of tags */
typedef struct {
    icUInt32Number      count;          /* Num tags in the profile */
    icTag               tags[icAny];    /* Variable array of tags */
} icTagList;

/* The Profile header */
typedef struct {
    icUInt32Number              size;           /* Prof size in bytes */
    icSignature                 cmmId;          /* CMM for profile */
    icUInt32Number              version;        /* Format version */
    icProfileClassSignature     deviceClass;    /* Type of profile */
    icColorSpaceSignature       colorSpace;     /* Clr space of data */
    icColorSpaceSignature       pcs;            /* PCS, XYZ or Lab */
    icDateTimeNumber            date;           /* Creation Date */
    icSignature                 magic;          /* icMagicNumber */
    icPlatformSignature         platform;       /* Primary Platform */
    icUInt32Number              flags;          /* Various bits */
    icSignature                 manufacturer;   /* Dev manufacturer */
    icUInt32Number              model;          /* Dev model number */
    icUInt64Number              attributes;     /* Device attributes */
    icUInt32Number              renderingIntent;/* Rendering intent */
    icXYZNumber                 illuminant;     /* Profile illuminant */
    icSignature                 creator;        /* Profile creator */
    icInt8Number                reserved[44];   /* Reserved */
} icHeader;

/* 
 * A profile, 
 * we can't use icTagList here because its not at the end of the structure
 */
typedef struct {
    icHeader            header;         /* The header */
    icUInt32Number      count;          /* Num tags in the profile */
    icInt8Number        data[icAny];    /* The tagTable and tagData */
/*
 * Data that follows is of the form
 *
 * icTag        tagTable[icAny];        * The tag table 
 * icInt8Number tagData[icAny];         * The tag data 
 */
} icProfile;           

/*------------------------------------------------------------------------*/
/* Obsolete entries */

/* icNamedColor was replaced with icNamedColor2 */
typedef struct {
    icUInt32Number      vendorFlag;     /* Bottom 16 bits for IC use */
    icUInt32Number      count;          /* Count of named colors */
    icInt8Number        data[icAny];    /* Named color data follows */
/*
 *  Data that follows is of this form
 *
 * icInt8Number         prefix[icAny];  * Prefix 
 * icInt8Number         suffix[icAny];  * Suffix 
 * icInt8Number         root1[icAny];   * Root name 
 * icInt8Number         coords1[icAny]; * Color coordinates 
 * icInt8Number         root2[icAny];   * Root name 
 * icInt8Number         coords2[icAny]; * Color coordinates 
 *                      :
 *                      :
 * Repeat for root name and color coordinates up to (count-1)
 */
} icNamedColor;

/* icNamedColorType was replaced by icNamedColor2Type */
typedef struct {
    icTagBase           base;           /* Signature, "ncol" */
    icNamedColor        ncolor;         /* Named color data */
} icNamedColorType;

#endif /* ICC_H */
