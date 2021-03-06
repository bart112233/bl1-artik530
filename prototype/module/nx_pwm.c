/*
 *      Copyright (C) 2012 Nexell Co., All Rights Reserved
 *      Nexell Co. Proprietary & Confidential
 *
 *      NEXELL INFORMS THAT THIS CODE AND INFORMATION IS PROVIDED "AS IS" BASE
 *      AND WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING
 *      BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
 *	FITNESS
 *      FOR A PARTICULAR PURPOSE.
 *
 *      Module          : PWM (Pulse Width Modulation)
 *      File            : nx_pwm.c
 *      Description     :
 *      Author          : Jonghyuk Park(charles@nexell.co.kr)
 *      History         : 2012.08.30 first implementation
 *			  2014.10.15 deoks modify to functionality
 *			  2015.05.20 dahye modify to functionality
 */
#include "nx_pwm.h"

static struct NX_PWM_RegisterSet *__g_pRegister[5];


//------------------------------------------------------------------------------
// Module Interface
//------------------------------------------------------------------------------
/**
 *	@brief	Initialize of prototype enviroment & local variables.
 *	@return CTRUE	indicates that Initialize is successed.
 *			CFALSE	indicates that Initialize is failed.
 */
CBOOL	NX_PWM_Initialize( void )
{
	static CBOOL bInit = CFALSE;

	if( CFALSE == bInit )
	{
		__g_pRegister[0] = (struct NX_PWM_RegisterSet *)CNULL;

		bInit = CTRUE;
	}

	return bInit;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get number of modules in the chip.
 *	@return		Module's number.
 */
U32		NX_PWM_GetNumberOfModule( void )
{
	return NUMBER_OF_PWM_MODULE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get number of submodules in the timer.
 *	@return		SubModule's number.
 */
U32		NX_PWM_GetNumberOfChannel( void )
{
	return NUMBER_OF_PWM_CHANNEL;
}

//------------------------------------------------------------------------------
// Basic Interface
//------------------------------------------------------------------------------
/**
 *	@brief		Get module's physical address.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		Module's physical address
 */
U32		NX_PWM_GetPhysicalAddress( U32 ModuleIndex )
{
	static const U32 PhysicalAddr[] = { PHY_BASEADDR_LIST( PWM ) };

	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );

	return (U32)PhysicalAddr[ModuleIndex];
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get a size, in byte, of register set.
 *	@return		Size of module's register set.
 */
U32		NX_PWM_GetSizeOfRegisterSet( void )
{
	return sizeof( struct NX_PWM_RegisterSet );
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set a base address of register set.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@param[in]	BaseAddress		Module's base address
 *	@return		None.
 */
void	NX_PWM_SetBaseAddress( U32 ModuleIndex, void* BaseAddress )
{
	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );
	NX_ASSERT( CNULL != BaseAddress );

	__g_pRegister[ModuleIndex] = (struct NX_PWM_RegisterSet *)BaseAddress;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get a base address of register set
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		Module's base address.
 */
void*	NX_PWM_GetBaseAddress( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );

	return (void*)__g_pRegister[ModuleIndex];
}

//------------------------------------------------------------------------------
/**
 *	@brief		Initialize selected modules with default value.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		CTRUE			indicates that Initialize is successed.
 *				CFALSE			indicates that Initialize is failed.
 */
CBOOL	NX_PWM_OpenModule( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );

	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Deinitialize selected module to the proper stage.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		CTRUE			indicates that Deinitialize is successed. 
 *				CFALSE			indicates that Deinitialize is failed.
 */
CBOOL	NX_PWM_CloseModule( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );

	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether the selected modules is busy or not.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		CTRUE			indicates that Module is Busy.
 *				CFALSE			indicates that Module is NOT Busy.
 */
CBOOL	NX_PWM_CheckBusy( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );

	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicaes whether the selected modules is ready to enter power-down stage
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		CTRUE			indicates that Ready to enter power-down stage. 
 *				CFALSE			indicates that This module can't enter to power-down stage.
 */
CBOOL	NX_PWM_CanPowerDown( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );

	return CTRUE;
}

//------------------------------------------------------------------------------
//	clock Interface
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/**
 *	@brief		Get module's clock index.
 *	@return		Module's clock index.
 *				It is equal to CLOCKINDEX_OF_PWM?_MODULE in <nx_chip.h>.
 */
U32 NX_PWM_GetClockNumber ( U32 ModuleIndex, U32 Channel )
{
	const U32 ClockNumber[] =
	{
//		CLOCKINDEX_LIST( PWM ),
		CLOCKINDEX_OF_PWM_MODULE,
		CLOCKINDEX_OF_Inst_PWM01_MODULE,
		CLOCKINDEX_OF_Inst_PWM02_MODULE,
		CLOCKINDEX_OF_Inst_PWM03_MODULE,
		CLOCKINDEX_OF_PWM_MODULE
	};
	
    NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );
    NX_ASSERT( NUMBER_OF_PWM_CHANNEL > Channel );

	return	ClockNumber[Channel];
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get module's reset index.
 *	@return		Module's reset index.
 *				It is equal to RESETINDEX_OF_PWM?_MODULE_i_nRST in <nx_chip.h>.
 */
U32 NX_PWM_GetResetNumber ( U32 ModuleIndex )
{
	const U32 ResetNumber[] =
	{
		RESETINDEX_LIST( PWM, PRESETn )
	};
	NX_CASSERT( NUMBER_OF_PWM_MODULE == (sizeof(ResetNumber)/sizeof(ResetNumber[0])) );
    NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );

	return	ResetNumber[ModuleIndex];
}

//------------------------------------------------------------------------------
// Interrupt Interface
//------------------------------------------------------------------------------
/**
 *	@brief		Get a interrupt number for interrupt controller.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		Interrupt number
 */
U32		NX_PWM_GetInterruptNumber( U32 ModuleIndex, U32 Channel )
{
	const U32	PWMInterruptNumber[NUMBER_OF_PWM_MODULE][4] =
				{
					{
						INTNUM_WITH_CHANNEL_LIST(PWM,INT0),
						INTNUM_WITH_CHANNEL_LIST(PWM,INT1),
						INTNUM_WITH_CHANNEL_LIST(PWM,INT2),
						INTNUM_WITH_CHANNEL_LIST(PWM,INT3),
					}
				};

	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );
	NX_ASSERT( NUMBER_OF_PWM_CHANNEL > Channel );

	return	PWMInterruptNumber[ModuleIndex][Channel];
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set a specified interrupt to be enable or disable.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@param[in]	IntNum			Interrupt Number.
 *	@param[in]	Enable	CTRUE	indicates that Interrupt Enable.
 *						CFALSE	indicates that Interrupt Disable.
 *	@return		None.
 */
void	NX_PWM_SetInterruptEnable( U32 ModuleIndex, U32 IntNum, CBOOL Enable )
{
	register struct NX_PWM_RegisterSet*	pRegister;
	register U32	ReadValue;
	const U32		PEND_POS	=	0;
	const U32		PEND_MASK	=	1UL << (PEND_POS + IntNum);
	
	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );
	NX_ASSERT( NUMBER_OF_PWM_CHANNEL > IntNum );
	NX_ASSERT( (0==Enable) || (1==Enable) );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

	ReadValue	=	ReadIO32(&pRegister->TINT_CSTAT);
	ReadValue	&=	(U32)(~PEND_MASK);
	ReadValue	|=	(U32)Enable << (PEND_POS + IntNum) ;

	WriteIO32(&pRegister->TINT_CSTAT, ReadValue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether a specified interrupt is enabled or disabled.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@param[in]	IntNum			Interrupt Number.
 *	@return		CTRUE			indicates that Interrupt is enabled. 
 *				CFALSE			indicates that Interrupt is disabled.
 */
CBOOL	NX_PWM_GetInterruptEnable( U32 ModuleIndex, U32 IntNum )
{
	register struct NX_PWM_RegisterSet*	pRegister;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );
	NX_ASSERT( NUMBER_OF_PWM_CHANNEL > IntNum );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

	return	(CBOOL)( (ReadIO32(&pRegister->TINT_CSTAT) >> IntNum) & 0x01 );
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether a specified interrupt is pended or not
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@param[in]	IntNum			Interrupt Number.
 *	@return		CTRUE			indicates that Pending is seted.
 *				CFALSE			indicates that Pending is Not Seted.
 */
CBOOL	NX_PWM_GetInterruptPending( U32 ModuleIndex, U32 IntNum )
{
	register struct NX_PWM_RegisterSet*	pRegister;
	const U32	PEND_POS	=	5;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );
	NX_ASSERT( NUMBER_OF_PWM_CHANNEL > IntNum );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

	return	(CBOOL)( (ReadIO32(&pRegister->TINT_CSTAT) >> (IntNum+PEND_POS)) & 0x01 );
}

//------------------------------------------------------------------------------
/**
 *	@brief		Clear a pending state of specified interrupt.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ 5 ).
 *	@param[in]	IntNum			Interrupt number.
 *	@return		None.
 */
void	NX_PWM_ClearInterruptPending( U32 ModuleIndex, U32 IntNum )
{
	register struct NX_PWM_RegisterSet*	pRegister;
	const U32	PEND_POS	=	5;
	const U32	PEND_MASK	=	1UL << (PEND_POS + IntNum);
	register U32 ReadValue;


	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );
	NX_ASSERT( NUMBER_OF_PWM_CHANNEL > IntNum );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

	ReadValue	 =	ReadIO32(&pRegister->TINT_CSTAT);
	ReadValue 	&=  ~PEND_MASK;
	ReadValue 	|=	PEND_MASK;

	WriteIO32(&pRegister->TINT_CSTAT, ReadValue );
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set all interrupts to be enables or disables.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@param[in]	Enable	CTRUE	indicates that Set to all interrupt enable.
 *						CFALSE	indicates that Set to all interrupt disable.
 *	@return		None.
 */
void	NX_PWM_SetInterruptEnableAll( U32 ModuleIndex, CBOOL Enable )
{
	register struct NX_PWM_RegisterSet*	pRegister;
	register U32	SetValue;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );
	NX_ASSERT( (CFALSE==Enable) || (CTRUE==Enable) );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );


	if( Enable )
		SetValue	=	0x1F;
	else
		SetValue	=	0;

	WriteIO32(&pRegister->TINT_CSTAT, SetValue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether some of interrupts are enable or not.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		CTRUE			indicates that At least one( or more ) interrupt is enabled.
 *				CFALSE			indicates that All interrupt is disabled.
 */
CBOOL	NX_PWM_GetInterruptEnableAll( U32 ModuleIndex )
{
	register struct NX_PWM_RegisterSet*	pRegister;
	const U32	ENABLE_POS	=	0;
	const U32	INT_MASK	=	0x1f;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

	if( ReadIO32(&pRegister->TINT_CSTAT) & (INT_MASK << ENABLE_POS) )
	{
		return CTRUE;
	}

	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether some of interrupts are pended or not.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		CTRUE	indicates that At least one( or more ) pending is seted.
 *				CFALSE	indicates that All pending is NOT seted.
 */
CBOOL	NX_PWM_GetInterruptPendingAll( U32 ModuleIndex )
{
	register struct NX_PWM_RegisterSet*	pRegister;
	const U32	PEND_POS	=	5;
	const U32	PEND_MASK	=	0x1f;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

	if( ReadIO32(&pRegister->TINT_CSTAT) & (PEND_MASK << PEND_POS) )
	{
		return CTRUE;
	}

	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Clear pending state of all interrupts.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		None.
 */
void	NX_PWM_ClearInterruptPendingAll( U32 ModuleIndex )
{
	register struct NX_PWM_RegisterSet*	pRegister;
	const U32	PEND_POS	=	5;
	const U32	PEND_MASK	=	0x1f;

	register U32 PendEnb;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

	PendEnb	=	ReadIO32(&pRegister->TINT_CSTAT) & PEND_MASK;
	PendEnb |=	PEND_MASK<<PEND_POS;

	WriteIO32(&pRegister->TINT_CSTAT, PendEnb );
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get a interrupt number which has the most prority of pended interrupts
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		Pending Number( If all pending is not set then return -1 ).
 */
U32		NX_PWM_GetInterruptPendingNumber( U32 ModuleIndex )	// -1 if None
{
	register struct NX_PWM_RegisterSet	*pRegister;
	const U32	PEND_POS	=	5;
	const U32	PEND_MASK	=	0x1f << PEND_POS;
	register U32 PendingIndex, Pend;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > ModuleIndex );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

	Pend	=	(ReadIO32(&pRegister->TINT_CSTAT) & PEND_MASK)>>PEND_POS;

	for( PendingIndex = 0; PendingIndex<NX_PWM_INT; PendingIndex++)
		if(Pend & (1UL<<PendingIndex))
			break;

	if(PendingIndex > NX_PWM_INT)
		return -1;
	else
		return PendingIndex;
}

//--------------------------------------------------------------------------
//	Configuration operations
//--------------------------------------------------------------------------
//------------------------------------------------------------------------------
/**
 *	@brief		Set prescaler ( register value 1 is bypass )
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@param[in]	value		divide value (1 ~ 0xFF).
 *	@return		none.
 */
void	NX_PWM_SetPrescaler(U32 Channel, U32 value)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 RegValue;
	const U32 PRSC_MASK = 0xFF;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	NX_ASSERT( (0x100 > value) && (0 < value) );

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	RegValue = ReadIO32(&pRegister->TCFG0);

	if(Channel & 0x6)
	{
		RegValue &= ~(1UL<<8);
		RegValue |= ((value-1) & PRSC_MASK)<<8;		// timer channel 2, 3, 4
	}
	else
	{
		RegValue &= ~(1UL<<0);
		RegValue |= ((value-1) & PRSC_MASK)<<0;		// timer channel 0, 1
	}
	WriteIO32(&pRegister->TCFG0, RegValue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get prescaler ( register value 1 is bypass )
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@return		divide value (1 ~ 0xFF).
 */
U32		NX_PWM_GetPrescaler(U32 Channel)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 RegValue;
	const U32 PRSC_MASK = 0xFF;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	RegValue = ReadIO32(&pRegister->TCFG0);
	
	if(Channel & 0x6)
		return ((RegValue>>8) & PRSC_MASK)+1;		// timer channel 2, 3, 4
	else
		return ((RegValue>>0) & PRSC_MASK)+1;		// timer channel 0, 1
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set Dead Zone width
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@param[in]	Length		value (0 ~ 0xFE).
 *	@return		none.
 */
void	NX_PWM_SetDeadZoneLength( U32 Channel, U32 Length )
{
    const U32   DEADZ_POS   =   16;    
	const U32	DEADZ_MASK	=	0xff;
    
	register struct NX_PWM_RegisterSet* pRegister;
	register U32                        RegValue;
	
	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	RegValue = ReadIO32(&pRegister->TCFG0);
	RegValue &= ~(DEADZ_MASK<<DEADZ_POS);
	RegValue |= (Length & DEADZ_MASK)<<DEADZ_POS;
	WriteIO32(&pRegister->TCFG0, RegValue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get Dead Zone width
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@return		width value (0 ~ 0xFE).
 */
U32		NX_PWM_GetDeadZoneLength(U32 Channel)
{
    const U32   DEADZ_POS   =   16;    
	const U32	DEADZ_MASK	=	0xff;
    
	register struct NX_PWM_RegisterSet	*pRegister;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	return (U32)((ReadIO32(&pRegister->TCFG0)>>DEADZ_POS) & DEADZ_MASK);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set Dead Zone run
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@param[in]	Enable		CTRUE: enable, CFALSE: disable.
 *	@return		none.
 */
CBOOL	NX_PWM_SetDeadZoneEnable(U32 Channel, CBOOL Enable)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 RegValue;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	NX_ASSERT( (CFALSE==Enable) || (CTRUE == Enable) );

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	if(Channel != 0)
		return CFALSE;

	RegValue = ReadIO32(&pRegister->TCON);
	if(Enable)
		RegValue |= (1UL<<4);
	else
		RegValue &= ~(1UL<<4);

	WriteIO32(&pRegister->TCON, RegValue);

	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get Dead Zone run status
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@return		CTRUE 		Dead zone is working
 				CFALSE 		Not working.
 */
CBOOL	NX_PWM_GetDeadZoneEnable(U32 Channel)
{
	register struct NX_PWM_RegisterSet	*pRegister;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	if(Channel != 0)
		return CFALSE;

	if(ReadIO32(&pRegister->TCON) & (1UL<<4))
		return CTRUE;

	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set divider path
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@param[in]	divider		divider select.
 							(0: DIV1, 1: DIV2, 2: DIV4, 3: DIV8, 4: DIV16)
 *	@return		CTRUE: this channel can select which selecting.
 *				CFALSE: channel cannot select selecting path divider channel.
 */
CBOOL	NX_PWM_SetDividerPath(U32 Channel, NX_PWM_DIVIDSELECT divider)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel, RegValue, updatevalue;
	const U32	DIV_MASK	=	0xF;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;
	NX_ASSERT( NX_PWM_DIVIDSELECT_TCLK >= divider );

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	if(ModuleChannel == 4 && NX_PWM_DIVIDSELECT_TCLK == divider)
		return CFALSE;

	updatevalue = divider<<(4*ModuleChannel);

	RegValue = ReadIO32(&pRegister->TCFG1);
	RegValue &= ~(DIV_MASK<<(4*ModuleChannel));
	RegValue |= updatevalue;
	WriteIO32(&pRegister->TCFG1, RegValue);

	return CTRUE;
}
//------------------------------------------------------------------------------
/**
 *	@brief		Get divider path
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@return		current Divider path number
 */
NX_PWM_DIVIDSELECT NX_PWM_GetDividerPath(U32 Channel)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel, RegValue;
	const U32	DIV_MASK	=	0xF;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;

	RegValue = ReadIO32(&pRegister->TCFG1);
	RegValue >>= (4*ModuleChannel);
	RegValue &= DIV_MASK;

	return (NX_PWM_DIVIDSELECT)RegValue;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set Output Invert
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@param[in]	Enable		CTRUE: enable, CFALSE: disable.
 *	@return		CTRUE		this channel can invert output signal.
 *				CFALSE	 	this channel has no output port, so cannot invert signal.
 */
CBOOL	NX_PWM_SetOutInvert(U32 Channel, CBOOL Enable)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel, RegValue, updatevalue;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	NX_ASSERT( (CFALSE==Enable) || (CTRUE == Enable) );

	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;
	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	if(ModuleChannel == 4)
		return CFALSE;

	if(ModuleChannel == 0)
		updatevalue = 1UL<<(4*(ModuleChannel+0)+2);
	else
		updatevalue = 1UL<<(4*(ModuleChannel+1)+2);

	RegValue = ReadIO32(&pRegister->TCON);
	if(Enable)
		RegValue |= updatevalue;
	else
		RegValue &= ~updatevalue;

	WriteIO32(&pRegister->TCON, RegValue);

	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get Output Invert status
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@return		CTRUE	this channel is inverted output signal.
 *				CFALSE	channel has no output port or not inverted.
 */
CBOOL	NX_PWM_GetOutInvert(U32 Channel)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel, comparevalue;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );

	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;
	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	if(ModuleChannel == 4)
		return CFALSE;

	if(ModuleChannel == 0)
		comparevalue = 1UL<<(4*(ModuleChannel+0)+2);
	else
		comparevalue = 1UL<<(4*(ModuleChannel+1)+2);

	if(comparevalue & ReadIO32(&pRegister->TCON))
		return CTRUE;

	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set LoadMode is AutoReload or OneShot
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@param[in]	ShotMode	LoadMode (0:OneShot, 1:AutoReload)
 *	@return		None.
 */
void	NX_PWM_SetShotMode(U32 Channel, NX_PWM_LOADMODE ShotMode)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel, RegValue;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	
	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;
	NX_ASSERT( (NX_PWM_LOADMODE_ONESHOT == ShotMode) || (NX_PWM_LOADMODE_AUTORELOAD == ShotMode));

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	RegValue = ReadIO32(&pRegister->TCON);

	if(ModuleChannel == 0)
	{
		RegValue &= ~(1UL<<3);
		RegValue |= ShotMode<<3;
	}
	else if(ModuleChannel & 0x3 )
	{
		RegValue &= ~(1UL<<(4*(ModuleChannel+1)+3));
		RegValue |= ShotMode<<(4*(ModuleChannel+1)+3);
	}
	else
	{	
		RegValue &= ~(1UL<<22);
		RegValue |= ShotMode<<22;
	}

	WriteIO32(&pRegister->TCON, RegValue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set LoadMode is AutoReload or OneShot
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@return 	ShotMode	LoadMode (0:OneShot, 1:AutoReload)
 */
NX_PWM_LOADMODE	NX_PWM_GetShotMode(U32 Channel)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel, RegValue;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	RegValue = ReadIO32(&pRegister->TCON);

	if(ModuleChannel == 0)
	{
		RegValue >>= 3;
	}
	
	if(ModuleChannel == 4)
	{
		RegValue >>= 22;
	}else
	{
		RegValue >>= (4*(ModuleChannel+1)+3);
	}
	RegValue &= 0x1;

	return (NX_PWM_LOADMODE)RegValue;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set TCNTx, TCMPx Manual Update
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@param[in]	Enable	CTRUE	Indicates that Manual Update is enabled.
 						CFALSE	Indicates that Manual Update is disabled.
 *	@return		None.						
 */
void	NX_PWM_UpdateCounter( U32 Channel )
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel;
	register U32 RegValue			= 0;
	register U32 UpdateDoneValue	= 0;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	RegValue = ReadIO32(&pRegister->TCON);
	if(ModuleChannel == 0)
	{
		RegValue |= 1UL<<1;
        UpdateDoneValue &= ~(1UL<<1);
	}
	else
	{
		RegValue |= 1<<(4*(ModuleChannel+1)+1);
        UpdateDoneValue &= ~(1<<(4*(ModuleChannel+1)+1));
	}

	WriteIO32(&pRegister->TCON, RegValue);
    WriteIO32(&pRegister->TCON, UpdateDoneValue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set PWM Start(Run)
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@return		None.
 */
void	NX_PWM_Run(U32 Channel)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel, RegValue;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	RegValue = ReadIO32(&pRegister->TCON);

	if(ModuleChannel == 0)
	{
		RegValue |= 1UL<<0;
	}
	else
	{
		RegValue |= 1<<(4*(ModuleChannel+1));
	}

	WriteIO32(&pRegister->TCON, RegValue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set PWM Stop
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@return		None.
 */
void	NX_PWM_Stop(U32 Channel)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel, RegValue;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	RegValue = ReadIO32(&pRegister->TCON);

	if(ModuleChannel == 0)
	{
		RegValue &= ~(1UL<<0);
	}
	else
	{
		RegValue &= ~(1<<(4*(ModuleChannel+1)));
	}

	WriteIO32(&pRegister->TCON, RegValue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get PWM Running state.
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@return		None.
 */
CBOOL	NX_PWM_IsRun(U32 Channel)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel, RegValue;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	RegValue = ReadIO32(&pRegister->TCON);

	if(ModuleChannel == 0)
	{
		RegValue >>= 0;
	}
	else
	{
		RegValue >>= (4*(ModuleChannel+1));
	}
	RegValue &= 0x1;

	return (CBOOL)RegValue;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set PWM Period (Count).
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@param[in]	Period		PWM Period ( range : 0 ~ 0xFFFFFFFF )
 *	@return		None.
 */
void	NX_PWM_SetPeriod(U32 Channel, U32 Period)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	if(ModuleChannel == 0)
	{
		WriteIO32(&pRegister->TCNTB0, Period);
	}
	else if(ModuleChannel == 1)
	{
		WriteIO32(&pRegister->TCNTB1, Period);
	}
	else if(ModuleChannel == 2)
	{
		WriteIO32(&pRegister->TCNTB2, Period);
	}
	else if(ModuleChannel == 3)
	{
		WriteIO32(&pRegister->TCNTB3, Period);
	}	
	else if(ModuleChannel == 4)
	{
		WriteIO32(&pRegister->TCNTB4, Period);
	}

}

//------------------------------------------------------------------------------
/**
 *	@brief		Set PWM Period (Count).
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@return		Period		PWM Period ( range : 0 ~ 0xFFFFFFFF )
 */
U32		NX_PWM_GetPeriod(U32 Channel)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];
	NX_ASSERT( CNULL != pRegister );

	if(ModuleChannel == 0)
	{
		return ReadIO32(&pRegister->TCNTB0);
	}
	else if(ModuleChannel == 1)
	{
		return ReadIO32(&pRegister->TCNTB1);;
	}
	else if(ModuleChannel == 2)
	{
		return ReadIO32(&pRegister->TCNTB2);
	}
	else if(ModuleChannel == 3)
	{
		return ReadIO32(&pRegister->TCNTB3);
	}	
	else if(ModuleChannel == 4)
	{
		return ReadIO32(&pRegister->TCNTB4);
	}

	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set PWM Duty (Compare).
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@param[in]	Duty		PWM Duty ( range : 0 ~ 0xFFFFFFFF )
 *	@return		None.
 */
CBOOL	NX_PWM_SetDuty(U32 Channel, U32 Duty)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );


	if(ModuleChannel == 0)
	{
		WriteIO32(&pRegister->TCMPB0, Duty);;
	}
	else if(ModuleChannel == 1)
	{
		WriteIO32(&pRegister->TCMPB1, Duty);
	}
	else if(ModuleChannel == 2)
	{
		WriteIO32(&pRegister->TCMPB2, Duty);
	}
	else if(ModuleChannel == 3)
	{
		WriteIO32(&pRegister->TCMPB3, Duty);
	}	
	else if(ModuleChannel == 4)
	{
		return CFALSE;
	}

	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get PWM Duty (Compare).
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@return		Duty		PWM Duty. ( range : 0 ~ 0xFFFFFFFF )
 */
U32		NX_PWM_GetDuty(U32 Channel)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	if(ModuleChannel == 0)
	{
		return ReadIO32(&pRegister->TCMPB0);
	}
	else if(ModuleChannel == 1)
	{
		return ReadIO32(&pRegister->TCMPB1);;
	}
	else if(ModuleChannel == 2)
	{
		return ReadIO32(&pRegister->TCMPB2);
	}
	else if(ModuleChannel == 3)
	{
		return ReadIO32(&pRegister->TCMPB3);
	}	
	else if(ModuleChannel == 4)
	{
		return CFALSE;
	}

	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get PWM Current Count.
 *	@param[in]	Channel		An index of timer channel ( 0 ~ x ).
 *	@return		Count		PWM Count. ( range : 0 ~ x )
 */
U32		NX_PWM_GetCurrentCount(U32 Channel)
{
	register struct NX_PWM_RegisterSet	*pRegister;
	register U32 ModuleChannel;

	NX_ASSERT( NUMBER_OF_PWM_MODULE > Channel/NUMBER_OF_PWM_CHANNEL );
	ModuleChannel = Channel % NUMBER_OF_PWM_CHANNEL;

	pRegister	=	__g_pRegister[Channel/NUMBER_OF_PWM_CHANNEL];

	NX_ASSERT( CNULL != pRegister );

	if(ModuleChannel == 0)
	{
		return ReadIO32(&pRegister->TCNTO0);
	}
	else if(ModuleChannel == 1)
	{
		return ReadIO32(&pRegister->TCNTO1);;
	}
	else if(ModuleChannel == 2)
	{
		return ReadIO32(&pRegister->TCNTO2);
	}
	else if(ModuleChannel == 3)
	{
		return ReadIO32(&pRegister->TCNTO3);
	}	
	else if(ModuleChannel == 4)
	{
		return ReadIO32(&pRegister->TCNTO4);
	}

	return CTRUE;
}
//@}
