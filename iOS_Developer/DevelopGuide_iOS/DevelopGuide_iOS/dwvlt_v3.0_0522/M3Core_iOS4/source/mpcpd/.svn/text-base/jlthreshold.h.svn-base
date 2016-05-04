//
// jlthreshold.h -- threshold data of ACCES for DocuWorks
// ACCES : Automatic Compression Choice on Estimated Statistics
//
// Copyright (C) 2000 by Fuji Xerox Co., Ltd.
// All rights reserved.
//
// Written: Jul.18,2000 by YOKOSE Taro, STD/CP&S/DPC, Fuji Xerox Co., Ltd.
//
// Description
//
//
//
#ifndef _JLTHRESHOLD_H_
#define _JLTHRESHOLD_H_

//////////////////// Definition
///
typedef struct tagJLTH {	// struct for thresholds
    short	sf;
    double	th;
} JLTH;
static const char NUMOF_JLTH(15);	// number of SF samples

//////////////////// Threshold of choice between JPEG and Lossless
///
/// for 8bit
///
static const JLTH jlth08[NUMOF_JLTH] = {
    {6, 0.6471079},
    {8, 0.728609},
    {12, 0.8127273},
    {16, 0.8571175},
    {22, 0.8884795},
    {34, 0.9206008},
    {44, 0.9356346},
    {70, 0.9562535},
    {90, 0.9674516},
    {135, 0.9787961},
    {161, 0.9828333},
    {278, 0.9919677},
    {500, 0.997514},
    {714, 0.9996854},
    {1000, 1.001237}};

///
/// for 24bit
///
static const JLTH jlth24[NUMOF_JLTH] = {
    {6, 0.9068668},
    {8, 0.918956},
    {12, 0.9351728},
    {16, 0.9454466},
    {22, 0.9531971},
    {34, 0.9622627},
    {44, 0.9670542},
    {70, 0.9739765},
    {90, 0.9776655},
    {135, 0.9823474},
    {161, 0.9841514},
    {278, 0.9887314},
    {500, 0.9919745},
    {714, 0.993353},
    {1000, 0.994391}};
#endif
