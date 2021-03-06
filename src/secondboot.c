/*
 * Copyright (C) 2016  Nexell Co., Ltd.
 * Author: Sangjong, Han <hans@nexell.co.kr>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#define __SET_GLOBAL_VARIABLES

#include "sysheader.h"
#include "memtester.h"

extern void DMC_Delay(int milisecond);
extern void ResetCon(U32 devicenum, CBOOL en);
extern void device_reset(void);

extern void subcpu_bringup(void);

#if (CONFIG_SUSPEND_RESUME == 1)
extern void enterSelfRefresh(void);
extern void exitSelfRefresh(void);
#endif

#if (CONFIG_BUS_RECONFIG == 1)
extern void setBusConfig(void);
#endif

extern CBOOL iUSBBOOT(struct NX_SecondBootInfo * pTBI);
extern CBOOL iSDXCBOOT(struct NX_SecondBootInfo * pTBI);
extern void initClock(void);
#ifdef MEM_TYPE_DDR3
extern void init_DDR3(U32);
#endif
#ifdef MEM_TYPE_LPDDR23
extern void init_LPDDR3(U32);
#endif

#if defined( INITPMIC_YES )
extern void initPMIC(void);
#endif
extern void buildinfo(void);
extern void printClkInfo(void);

extern void setEMA(void);
extern void s5p4418_resume(void);
extern void run_secure_svc(U32 jumpaddr);
extern void run_bl2(U32 jumpaddr);

extern int CRC_Check(void* buf, unsigned int size, unsigned int ref_crc);
extern void bl2_usbboot(struct NX_SecondBootInfo *tbi);

void delay_ms(int ms)
{
	int i, k;

	for (i = 0; i < (ms * 1000); i++)
		for (k = 0; k < 1000; k++);
}

void enableL2Cache(unsigned int enb)
{
	unsigned int reg;

	// L2 Cache
	reg = ReadIO32(&pReg_Tieoff->TIEOFFREG[0]);
	if (enb)
		reg |= (3UL << 12);
	else
		reg &= ~(3UL << 12);

	WriteIO32(&pReg_Tieoff->TIEOFFREG[0], reg);
}

void device_set_env(void)
{
	/* (Device Port Number) for U-BOOT  */
	unsigned int dev_portnum = pSBI->DBI.SDMMCBI.PortNumber;
	WriteIO32(&pReg_ClkPwr->SCRATCH[1], dev_portnum );
}

void BootMain(void)
{
	struct NX_SecondBootInfo TBI;
	struct NX_SecondBootInfo *pTBI = &TBI; // third boot info
	int ret = CFALSE;
#if (CONFIG_SUSPEND_RESUME == 1)
	U32 signature, wakeup_status, reset_status = 0;
#endif
	U32 is_resume = 0;
	U32 debug_ch = 0;

#if defined(AVN) || defined(NAVI) || defined(RAPTOR)
	debug_ch = 3;
#endif

#if 0 // Low Level Debug Message
	/*  Low Level Debug Message */
	DebugInit(debug_ch);
#endif

#if (CONFIG_SUSPEND_RESUME == 1)
	WriteIO32(&pReg_Alive->ALIVEPWRGATEREG, 1);
	signature = ReadIO32(&pReg_Alive->ALIVESCRATCHREADREG);
	wakeup_status = (ReadIO32(&pReg_Alive->WAKEUPSTATUS) & 0xFF);
	if (SUSPEND_SIGNATURE == signature) {
		reset_status = ReadIO32(&pReg_ClkPwr->RESETSTATUS);
		// normal-wakeup or watchdog-reset
		if ((wakeup_status != 0) || ((reset_status >> 2) & 0x1))
			is_resume = 1;
	}

#endif  //#if (CONFIG_SUSPEND_RESUME == 1)

#if defined(INITPMIC_YES)
	/* Set the PMIC */
	initPMIC();
#endif
	DMC_Delay(0xFFFFF);

	/* S5PXX18 Clock initialize */
	initClock();

	/* Console initialize */
	DebugInit(debug_ch);

	NOTICE("signature: 0x%X, is_resume: %d \r\n", signature, is_resume);
	NOTICE("wakeup_status: 0x%08X, reset_status: 0x%08X \r\n",
			wakeup_status, reset_status);

	/* Build information */
	buildinfo();

	/* Set the EMA */
	setEMA();

	/*  */
	enableL2Cache(CTRUE);

#if 1 // Clock Information Display.
	/* Clock Information */
	printClkInfo();
#endif
	device_reset();

#if defined(SECURE_MODE)
	/* Secondary cpu bring up */
	subcpu_bringup();
#endif

#if (CONFIG_SUSPEND_RESUME == 1)
#ifdef MEM_TYPE_DDR3
	init_DDR3(is_resume);
#endif
#ifdef MEM_TYPE_LPDDR23
	init_LPDDR3(is_resume);
#endif
	/* Exit to Self Refresh */
	if (is_resume)
		exitSelfRefresh();

	NOTICE("DDR3/LPDDR3 Init Done!\r\n");

#if (CONFIG_BUS_RECONFIG == 1)
	setBusConfig();
#endif

	if (is_resume) {
		NOTICE(" DDR3 SelfRefresh exit Done!\r\n0x%08X\r\n",
				ReadIO32(&pReg_Alive->WAKEUPSTATUS));
		s5p4418_resume();
	}
	WriteIO32(&pReg_Alive->ALIVEPWRGATEREG, 0);
#else // #if (CONFIG_SUSPEND_RESUME == 1)

	/* (DDR3/LPDDR3) SDRAM initialize */
#ifdef MEM_TYPE_DDR3
	init_DDR3(is_resume);
#endif
#ifdef MEM_TYPE_LPDDR23
	init_LPDDR3(is_resume);
#endif
	NOTICE("DDR3/LPDDR3 Init Done!\r\n");

#if (CONFIG_BUS_RECONFIG == 1)
	setBusConfig();
#endif
#endif // #if (CONFIG_SUSPEND_RESUME == 1)

	/*
	 * SD/MMC,SPI - port number stored for u-boot.
	 */
	device_set_env();


	if (pSBI->SIGNATURE != HEADER_ID) {
		ERROR("2nd Boot Header is invalid, Please check it out!\r\n");
	}

	/* Check the (SDRAM)Memory */
#if defined(STANDARD_MEMTEST)
	memtester_main((U32)0x91000000UL, (U32)0xb1000000UL, 0x10);
#elif defined(SIMPLE_MEMTEST)
	simple_memtest((U32*)0x91000000UL, (U32*)0xb1000000UL);
#endif

#if defined(LOAD_FROM_USB)
	NOTICE("Loading from usb...\r\n" );
	ret = iUSBBOOT(pTBI);			// for USB boot
#endif

	switch (pSBI->DBI.SPIBI.LoadDevice) {
#if defined(SUPPORT_USB_BOOT)
	case BOOT_FROM_USB:
		SYSMSG("Loading from usb...\r\n");
		ret = iUSBBOOT(pTBI);	// for USB boot
		bl2_usbboot(pTBI);
		break;
#endif

#if defined(SUPPORT_SDMMC_BOOT)
	case BOOT_FROM_SDMMC:
		SYSMSG("Loading from sdmmc...\r\n");
		ret = iSDXCBOOT(pTBI);	// for SD boot
		break;
#endif
	}

#ifdef CRC_CHECK_ON
	/* Check the data loaded to the SDRAM CRC. */
	ret = CRC_Check((void*)pTBI->LOADADDR, (unsigned int)pTBI->LOADSIZE
			,(unsigned int)pTBI->DBI.SDMMCBI.CRC32);
#endif
	if (ret) {
#if defined(SECURE_MODE)
		void (*pLaunch)(U32, U32) = (void (*)(U32, U32))pTBI->LAUNCHADDR;
		SYSMSG("Image Loading Done!\r\n");
		SYSMSG("Launch to 0x%08X\r\n", (U32)pLaunch);
		while (!DebugIsUartTxDone())
			;
		pLaunch(0, 4330);
#else
		SYSMSG("Image Loading Done!\r\n");
		SYSMSG("Launch to 0x%08X\r\n", pTBI->LAUNCHADDR);
		while (!DebugIsUartTxDone())
			;
//		run_secure_svc(pTBI->LAUNCHADDR);
		pSBI->BL2_START = pTBI->LAUNCHADDR;
		run_bl2(pTBI->LAUNCHADDR);
#endif
	}

	SYSMSG("Image Loading Failure Try to USB boot\r\n");
	while (!DebugIsUartTxDone());
}
