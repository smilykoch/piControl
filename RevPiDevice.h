/*=======================================================================================
 *
 *	       KK    KK   UU    UU   NN    NN   BBBBBB    UU    UU    SSSSSS
 *	       KK   KK    UU    UU   NNN   NN   BB   BB   UU    UU   SS
 *	       KK  KK     UU    UU   NNNN  NN   BB   BB   UU    UU   SS
 *	+----- KKKKK      UU    UU   NN NN NN   BBBBB     UU    UU    SSSSS
 *	|      KK  KK     UU    UU   NN  NNNN   BB   BB   UU    UU        SS
 *	|      KK   KK    UU    UU   NN   NNN   BB   BB   UU    UU        SS
 *	|      KK    KKK   UUUUUU    NN    NN   BBBBBB     UUUUUU    SSSSSS     GmbH
 *	|
 *	|            [#]  I N D U S T R I A L   C O M M U N I C A T I O N
 *	|             |
 *	+-------------+
 *
 *---------------------------------------------------------------------------------------
 *
 * (C) KUNBUS GmbH, Heerweg 15C, 73770 Denkendorf, Germany
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License V2 as published by
 * the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *  For licencing details see COPYING
 *
 *=======================================================================================
 */

#pragma once

#include <ModGateComMain.h>
#include <piIOComm.h>

#define REV_PI_DEV_UNDEF            255
#define REV_PI_DEV_FIRST_RIGHT      32
#define REV_PI_DEV_CNT_MAX          64

typedef struct _SDevice
{
    INT8U i8uAddress;
    INT8U i8uActive;
    INT8U i8uScan;			// found on scan
    INT16U i16uInputOffset;
    INT16U i16uOutputOffset;
    INT16U i16uConfigLength;
    INT16U i16uConfigOffset;
    INT16U i16uErrorCnt;
    MODGATECOM_IDResp sId;
} SDevice;


typedef struct _SDeviceConfig
{
    INT8U i8uAddressRight;
    INT8U i8uAddressLeft;
    INT8U i8uDeviceCount;
    INT16U i16uErrorCnt;

    INT8U  i8uStatus;               // status bitfield of RevPi
    SRevPiCoreImage *pCoreData;     // Pointer to process image, may point to NULL
    SDevice dev[REV_PI_DEV_CNT_MAX];
} SDeviceConfig;

extern SDeviceConfig RevPiScan;
extern const MODGATECOM_IDResp RevPi_ID_g;

TBOOL RevPiDevice_writeNextConfiguration(INT8U i8uAddress_p, MODGATECOM_IDResp *pModgateId_p);

void RevPiDevice_init(void);
void RevPiDevice_finish(void);

int RevPiDevice_run(void);
TBOOL RevPiDevice_writeNextConfigurationRight(void);
TBOOL RevPiDevice_writeNextConfigurationLeft(void);
void RevPiDevice_startDataexchange(void);
void RevPiDevice_stopDataexchange(void);
void RevPiDevice_checkFirmwareUpdate(void);

