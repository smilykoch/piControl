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

#include "IoProtocol.h"

typedef enum _EPiBridgeMasterStatus {
	// states for IO Protocol
	enPiBridgeMasterStatus_Init,	// 0
	enPiBridgeMasterStatus_MasterIsPresentSignalling1,	// 1
	enPiBridgeMasterStatus_MasterIsPresentSignalling2,	// 2
	enPiBridgeMasterStatus_InitialSlaveDetectionRight,	// 3
	enPiBridgeMasterStatus_ConfigRightStart,	// 4
	enPiBridgeMasterStatus_ConfigDialogueRight,	// 5
	enPiBridgeMasterStatus_SlaveDetectionRight,	// 6
	enPiBridgeMasterStatus_InitialSlaveDetectionLeft,	// 7
	enPiBridgeMasterStatus_ConfigLeftStart,	// 8
	enPiBridgeMasterStatus_ConfigDialogueLeft,	// 9
	enPiBridgeMasterStatus_SlaveDetectionLeft,	// 10
	enPiBridgeMasterStatus_EndOfConfig,	// 11
	enPiBridgeMasterStatus_Continue,	// 12
	enPiBridgeMasterStatus_InitRetry,	// 13

	// states for MGate Protocol
	enPiBridgeMasterStatus_FWUMode,	// 14
	enPiBridgeMasterStatus_ProgramSerialNum,	// 15
	enPiBridgeMasterStatus_FWUFlashErase,	// 16
	enPiBridgeMasterStatus_FWUFlashWrite,	// 17
	enPiBridgeMasterStatus_FWUReset,	// 18

} EPiBridgeMasterStatus;

typedef struct _SRevPiCoreImage {
	// input data, 6 Byte: set by driver
	INT8U i8uStatus;
	INT8U i8uIOCycle;
	INT16U i16uRS485ErrorCnt;
	INT8U i8uCPUTemperature;
	INT8U i8uCPUFrequency;

	// output data, 5 Byte: set by application
	INT8U i8uLED;
	//INT8U i8uMode;		// for debugging
	//INT8U i16uRS485ErrorLimit1;	// for debugging
	INT16U i16uRS485ErrorLimit1;
	INT16U i16uRS485ErrorLimit2;

} __attribute__ ((__packed__)) SRevPiCoreImage;

struct revpi_compact_image {
	u8;			/* rx */
	u8 i8uIOCycle;
	u16;
	u8 i8uCPUTemperature;
	u8 i8uCPUFrequency;

	INT8U i8uLED;		/* tx */
	u16;
	u16;
};

struct revpi_compact_image_dio_rx {
	SDioModuleStatus dio_status;
	u16 din;
};

struct revpi_compact_image_dio_tx {
	u16 dout;
};

struct revpi_compact_image_aio_rx {
	u8 aio_status;
#define AIO_RX_ERR 0x80
#define AIO_TX_ERR 0x40
	u16 ain[8];
};

struct revpi_compact_image_aio_tx {
	u16 aout[2];
};

void PiBridgeMaster_Reset(void);
int PiBridgeMaster_Adjust(void);
void PiBridgeMaster_setDefaults(void);
int PiBridgeMaster_Run(void);
void PiBridgeMaster_Stop(void);
void PiBridgeMaster_Continue(void);
int PiBridgeMaster_gotoMGateComMode(void);
INT32S PiBridgeMaster_FWUModeEnter(INT32U address, INT8U i8uScanned);
INT32S PiBridgeMaster_FWUsetSerNum(INT32U serNum);
INT32S PiBridgeMaster_FWUflashErase(void);
INT32S PiBridgeMaster_FWUflashWrite(INT32U flash_add, char *data, INT32U length);
INT32S PiBridgeMaster_FWUReset(void);
