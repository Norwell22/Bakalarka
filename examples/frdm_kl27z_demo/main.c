/*
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2019 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*
* ==== Context library application examples for FRDM-KL27z ====
* This file, originally SDK example provided by NXP under name power_mode_switch
* was moddified do showcase functionality of my library. 
*
* Original header is left on the beggining of this file and every code is clearly marked as either
* mine or part of original example.
*
*/

/*
* Driver functions, that are part of SDK
*
* Part of original example
*/
#include "fsl_common.h"
#include "fsl_smc.h"
#include "fsl_rcm.h"
#include "fsl_port.h"
#include "power_mode_switch.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "peripherals.h"
#include "board.h"
#include "fsl_lpuart.h"
#include "fsl_pmc.h"
#include "fsl_tpm.h"
#include "fsl_gpio.h"

/*
* Context manager library
*/
#include "context_manager.h"




/*
* Macro definitions
* 
* Mostly part of original example
*/
#define APP_DEBUG_UART_BAUDRATE 115200 
#define APP_DEBUG_UART_DEFAULT_CLKSRC_NAME kCLOCK_McgPeriphClk /* MCGPCLK. */
#define APP_DEBUG_UART_DEFAULT_CLKSRC      0x01
#define APP_DEBUG_UART_VLPR_CLKSRC_NAME kCLOCK_McgInternalRefClk /* MCGIRCLK. */
#define APP_DEBUG_UART_VLPR_CLKSRC      0x03
#define APP_LLWU            DEMO_LLWU_PERIPHERAL
#define APP_LLWU_IRQHANDLER DEMO_LLWU_IRQHANDLER
#define APP_LPTMR            DEMO_LPTMR_PERIPHERAL
#define APP_LPTMR_IRQHANDLER DEMO_LPTMR_IRQHANDLER
#define LLWU_LPTMR_IDX       0U 
#define LLWU_WAKEUP_PIN_IDX  6U 
#define LLWU_WAKEUP_PIN_TYPE kLLWU_ExternalPinFallingEdge
#define APP_WAKEUP_BUTTON_GPIO        BOARD_SW3_GPIO
#define APP_WAKEUP_BUTTON_PORT        BOARD_SW3_PORT
#define APP_WAKEUP_BUTTON_GPIO_PIN    BOARD_SW3_GPIO_PIN
#define APP_WAKEUP_BUTTON_IRQ         BOARD_SW3_IRQ
#define APP_WAKEUP_BUTTON_IRQ_HANDLER BOARD_SW3_IRQ_HANDLER
#define APP_WAKEUP_BUTTON_NAME        BOARD_SW3_NAME
#define APP_WAKEUP_BUTTON_IRQ_TYPE    kPORT_InterruptFallingEdge
#define DEBUG_CONSOLE_RX_PORT   PORTA
#define DEBUG_CONSOLE_RX_GPIO   GPIOA
#define DEBUG_CONSOLE_RX_PIN    1U
#define DEBUG_CONSOLE_RX_PINMUX kPORT_MuxAlt2
#define DEBUG_CONSOLE_TX_PORT   PORTA
#define DEBUG_CONSOLE_TX_GPIO   GPIOA
#define DEBUG_CONSOLE_TX_PIN    2U
#define DEBUG_CONSOLE_TX_PINMUX kPORT_MuxAlt2
#define CORE_CLK_FREQ           CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define BOARD_TPM TPM2
#define BOARD_TPM_IRQ_NUM TPM2_IRQn
#define BOARD_TPM_HANDLER TPM2_IRQHandler
#define TPM_SOURCE_CLOCK (CLOCK_GetFreq(kCLOCK_McgIrc48MClk) / 4)

#define EEPROM_ADDR 0x50

/*
* Function prototypes
*
* Part of original code
*/
void APP_PowerPreSwitchHook(smc_power_state_t originPowerState, app_power_mode_t targetMode);
void APP_PowerPostSwitchHook(smc_power_state_t originPowerState, app_power_mode_t targetMode);
extern void APP_SetClockRunFromVlpr(void);
extern void APP_SetClockVlpr(void);
extern void APP_PowerPreSwitchHook(smc_power_state_t originPowerState, app_power_mode_t targetMode);
extern void APP_PowerPostSwitchHook(smc_power_state_t originPowerState, app_power_mode_t targetMode);


/*
* Global variables used in this application
*
* Mainly added code
*/

// variable is set in TPM2 interrupt routine
volatile bool tpmIsrFlag           = false;
// counter increments on every TPM2 interrupt. after hiting certain value, action happens 
volatile uint32_t action_count = 0U;
// counter increments on every TPM2 interrupt. after hiting certain value, MCU goes to sleep
volatile uint32_t sleep_count = 0U;
// counter increments on every TPM2 interrupt. after hiting certain value, LEDs toggle
volatile uint32_t case2_led_ms = 0U;
// counter increments on every TPM2 interrupt. after hiting certain value, MCU goes to sleep
volatile uint32_t case2_vlls_ms = 0U;

// original code
static uint8_t s_wakeupTimeout;            
static app_wakeup_source_t s_wakeupSource; 

// original code: variable is set in case of on-board SW3 button interrupt routine
volatile bool hit = false;

// variables set in case of external buttons interrupt routines
volatile bool button1_hit = false;
volatile bool button2_hit = false;
volatile bool button3_hit = false;

// value read by potentiometer
volatile uint16_t adc_value = 0;
// variable set in case of potentiometer interrupt routine
volatile bool adc_conversion_done = false;

// place in RAM for Layer 3 metadata
uint32_t metadata[8];

// array that stores number of button presses
uint32_t buttons[4] = {0,0,0,0};
// array that stores measured potentiometer values
uint32_t potent[5] = {0,0,0,0,0};
uint32_t cur_val = 0;


/*
* Memory areas used by the library
*
* Added code
*/

// external programmable memory used in use case 3
const Cl_memory_area_t eeprom = {31, (uint32_t *)0, (uint32_t *)127, CL_EEPROM};

// area that stores data from buttons
const Cl_memory_area_t buttons_ma = {32, buttons, buttons + 4, CL_CPU};

// area that stores data from potentiometer
const Cl_memory_area_t potent_ma = {33, potent, potent + 5, CL_CPU};

const Cl_peripheral_area_t cur_val_ma = {34, 1,CL_CPU, &cur_val};

// metadata memory area
const Cl_memory_area_t cl_metadata_ma = {255,metadata,metadata + 7,CL_CPU};

// register of the timer
const Cl_peripheral_area_t tpm2_regs = {200, 3,CL_CPU,
    {
       // &(TPM2->MOD),
		&(TPM2->CNT),
		&(action_count), // necesarry added metadata
    	&(TPM2->SC),}
};

// gpio registers
const Cl_peripheral_area_t gpio_regs = {201,3,CL_MCUXPRESSO_GPIO, // special function is used on layer 1
		{
				// instead of addresses, simple pin numbers are enough
				(cl_addr_t)3,
				(cl_addr_t)5,
				(cl_addr_t)6
		}
};

// on-board retention memory
const Cl_memory_area_t frdm_register_file = {1,(cl_addr_t)0x40041000,(cl_addr_t)0x4004101c,CL_CPU};


const cl_int_t cl_area_backup_table_size = 3;
struct cl_area_backup cl_area_backup_table[] = {
    {&cl_metadata_ma, &eeprom, CL_VLLS0,false},
	{&buttons_ma, &eeprom, CL_VLLS0,false},
	{&potent_ma, &eeprom, CL_VLLS0,false}
};

const cl_int_t cl_peripheral_backup_table_size = 1;
const struct cl_peripheral_backup cl_peripheral_backup_table[] = {
		{&cur_val_ma,&eeprom,CL_VLLS0,false}
};



/*
* Original functions
*
* Functions that were already part of the example, although they might have been changed.
* They serve mainly to set up low power mode and wakeup source. 
*/

static void APP_InitDefaultDebugConsole(void)
{
    uint32_t uartClkSrcFreq;
    CLOCK_SetLpuart0Clock(APP_DEBUG_UART_DEFAULT_CLKSRC);
    uartClkSrcFreq = CLOCK_GetFreq(APP_DEBUG_UART_DEFAULT_CLKSRC_NAME);
    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, APP_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);
}

static void APP_InitVlprDebugConsole(void)
{
    uint32_t uartClkSrcFreq;
    CLOCK_SetLpuart0Clock(APP_DEBUG_UART_VLPR_CLKSRC);
    uartClkSrcFreq = CLOCK_GetFreq(APP_DEBUG_UART_VLPR_CLKSRC_NAME);
    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, APP_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);
}

void APP_PowerPreSwitchHook(smc_power_state_t originPowerState, app_power_mode_t targetMode)
{
    while (!(kLPUART_TransmissionCompleteFlag & LPUART_GetStatusFlags((LPUART_Type *)BOARD_DEBUG_UART_BASEADDR)))
    {
    }
    DbgConsole_Deinit();

    if ((kAPP_PowerModeRun != targetMode) && (kAPP_PowerModeVlpr != targetMode))
    {
        PORT_SetPinMux(DEBUG_CONSOLE_RX_PORT, DEBUG_CONSOLE_RX_PIN, kPORT_PinDisabledOrAnalog);
    }
}

void APP_PowerPostSwitchHook(smc_power_state_t originPowerState, app_power_mode_t targetMode)
{
    smc_power_state_t powerState = SMC_GetPowerModeState(SMC);
    if ((kSMC_PowerStateVlpr == originPowerState) && (kSMC_PowerStateRun == powerState))
    {
        APP_SetClockRunFromVlpr();
    }

    if ((kAPP_PowerModeRun != targetMode) && (kAPP_PowerModeVlpr != targetMode))
    {
        PORT_SetPinMux(DEBUG_CONSOLE_RX_PORT, DEBUG_CONSOLE_RX_PIN, DEBUG_CONSOLE_RX_PINMUX);
    }
    if (kSMC_PowerStateVlpr == powerState)
    {
        APP_InitVlprDebugConsole();
    }
    else
    {
        APP_InitDefaultDebugConsole();
    }
}

void APP_LLWU_IRQHANDLER(void)
{
    if (LLWU_GetInternalWakeupModuleFlag(APP_LLWU, LLWU_LPTMR_IDX))
    {
        LLWU_EnableInternalModuleInterruptWakup(APP_LLWU, LLWU_LPTMR_IDX, false);
    }
    if (LLWU_GetExternalWakeupPinFlag(APP_LLWU, LLWU_WAKEUP_PIN_IDX))
    {
        LLWU_ClearExternalWakeupPinFlag(APP_LLWU, LLWU_WAKEUP_PIN_IDX);
    }
}

void APP_LPTMR_IRQHANDLER(void)
{
    if (kLPTMR_TimerInterruptEnable & LPTMR_GetEnabledInterrupts(APP_LPTMR))
    {
        LPTMR_DisableInterrupts(APP_LPTMR, kLPTMR_TimerInterruptEnable);
        LPTMR_ClearStatusFlags(APP_LPTMR, kLPTMR_TimerCompareFlag);
        LPTMR_StopTimer(APP_LPTMR);
    }
}


void APP_WAKEUP_BUTTON_IRQ_HANDLER2(void)
{
	if ((1U << APP_WAKEUP_BUTTON_GPIO_PIN) & PORT_GetPinsInterruptFlags(APP_WAKEUP_BUTTON_PORT))
	{
		hit = true;
		PORT_ClearPinsInterruptFlags(APP_WAKEUP_BUTTON_PORT, (1U << APP_WAKEUP_BUTTON_GPIO_PIN));
	}
	SDK_ISR_EXIT_BARRIER;
}

/*
* Function gets called when ADC completes conversion. Mainly just clears registers and notifies main cycle 
* using global variable adc_conversion_done.
*
* Function added by me.
*/
void ADC0_IRQHandler(void) {
    /* Reading the Result (R[0]) clears the interrupt flag automatically */
    adc_value = ADC16_GetChannelConversionValue(ADC0, 0U);
    adc_conversion_done = true;
    SDK_ISR_EXIT_BARRIER;
}

/*
* Handles interrupt requests from GPIO pins connected to buttons. 
* Mainly just notifies main app via global variables
* 
* Function added by me.
*/
void APP_WAKEUP_BUTTON_IRQ_HANDLER(void)
{
    uint32_t flags = GPIO_PortGetInterruptFlags(GPIOC);

    // check for on-board switch 
    if ((1U << APP_WAKEUP_BUTTON_GPIO_PIN) & flags)
    {
    	hit  = true;
        PORT_ClearPinsInterruptFlags(APP_WAKEUP_BUTTON_PORT, (1U << APP_WAKEUP_BUTTON_GPIO_PIN));
    }

    // check for first button
    if (flags & (1U << 4U))
    {
           button3_hit = true;
           GPIO_PortClearInterruptFlags(GPIOC, 1U << 4U);
    }

   // check for second button
   if (flags & (1U << 5U))
   {
       button1_hit = true;
       GPIO_PortClearInterruptFlags(GPIOC, 1U << 5U);
   }

   // check for third button
    if (flags & (1U << 6U))
    {
       button2_hit = true;
       GPIO_PortClearInterruptFlags(GPIOC, 1U << 6U);
    }

    SDK_ISR_EXIT_BARRIER;
}


static app_wakeup_source_t APP_GetWakeupSource(void)
{
    return kAPP_WakeupSourcePin;
}


void APP_GetWakeupConfig(app_power_mode_t targetMode)
{
    if (targetMode == kAPP_PowerModeVlls0)
    {
        PRINTF("Not support LPTMR wakeup because LPO is disabled in VLLS0 mode.\r\n");
        s_wakeupSource = kAPP_WakeupSourcePin;
    }
    else
    {
        s_wakeupSource = APP_GetWakeupSource();
    }
    PRINTF("Press %s to wake up.\r\n", APP_WAKEUP_BUTTON_NAME);
}

void APP_SetWakeupConfig(app_power_mode_t targetMode)
{
    PORT_SetPinInterruptConfig(APP_WAKEUP_BUTTON_PORT, APP_WAKEUP_BUTTON_GPIO_PIN, APP_WAKEUP_BUTTON_IRQ_TYPE);
    if ((kAPP_PowerModeWait != targetMode) && (kAPP_PowerModeVlpw != targetMode) &&
        (kAPP_PowerModeVlps != targetMode) && (kAPP_PowerModeStop != targetMode))
    {
        if (kAPP_WakeupSourceLptmr == s_wakeupSource)
        {
            LLWU_EnableInternalModuleInterruptWakup(APP_LLWU, LLWU_LPTMR_IDX, true);
        }
        else
        {
            LLWU_SetExternalWakeupPinMode(APP_LLWU, LLWU_WAKEUP_PIN_IDX, LLWU_WAKEUP_PIN_TYPE);
        }
        NVIC_EnableIRQ(LLWU_IRQn);
    }
}

void APP_ShowPowerMode(smc_power_state_t powerMode)
{
    switch (powerMode)
    {
        case kSMC_PowerStateRun:
            PRINTF("    Power mode: RUN\r\n");
            break;
        case kSMC_PowerStateVlpr:
            PRINTF("    Power mode: VLPR\r\n");
            break;
        default:
            PRINTF("    Power mode wrong\r\n");
            break;
    }
}

void APP_PowerModeSwitch(smc_power_state_t curPowerState, app_power_mode_t targetPowerMode)
{
    smc_power_mode_vlls_config_t vlls_config;
    vlls_config.enablePorDetectInVlls0 = true;
    vlls_config.enableLpoClock         = true; 
    smc_power_mode_lls_config_t lls_config;
    lls_config.enableLpoClock = true;
    switch (targetPowerMode)
    {
        case kAPP_PowerModeVlpr:
            APP_SetClockVlpr();
            SMC_SetPowerModeVlpr(SMC);
            while (kSMC_PowerStateVlpr != SMC_GetPowerModeState(SMC))
            {
            }
            break;

        case kAPP_PowerModeRun:
            SMC_SetPowerModeRun(SMC);
            while (kSMC_PowerStateRun != SMC_GetPowerModeState(SMC))
            {
            }
            if (kSMC_PowerStateVlpr == curPowerState)
            {
                APP_SetClockRunFromVlpr();
            }
            break;
        case kAPP_PowerModeWait:
            SMC_PreEnterWaitModes();
            SMC_SetPowerModeWait(SMC);
            SMC_PostExitWaitModes();
            break;
        case kAPP_PowerModeStop:
            SMC_PreEnterStopModes();
            SMC_SetPowerModeStop(SMC, kSMC_PartialStop);
            SMC_PostExitStopModes();
            break;
        case kAPP_PowerModeVlpw:
            SMC_PreEnterWaitModes();
            SMC_SetPowerModeVlpw(SMC);
            SMC_PostExitWaitModes();
            break;
        case kAPP_PowerModeVlps:
            SMC_PreEnterStopModes();
            SMC_SetPowerModeVlps(SMC);
            SMC_PostExitStopModes();
            break;
        case kAPP_PowerModeLls:
            SMC_PreEnterStopModes();
            SMC_SetPowerModeLls(SMC, &lls_config);
            SMC_PostExitStopModes();
            break;
        case kAPP_PowerModeVlls0:
            vlls_config.subMode = kSMC_StopSub0;
            SMC_PreEnterStopModes();
            SMC_SetPowerModeVlls(SMC, &vlls_config);
            SMC_PostExitStopModes();
            break;
        case kAPP_PowerModeVlls1:
            vlls_config.subMode = kSMC_StopSub1;
            SMC_PreEnterStopModes();
            SMC_SetPowerModeVlls(SMC, &vlls_config);
            SMC_PostExitStopModes();
            break;
        case kAPP_PowerModeVlls3:
            vlls_config.subMode = kSMC_StopSub3;
            SMC_PreEnterStopModes();
            SMC_SetPowerModeVlls(SMC, &vlls_config);
            SMC_PostExitStopModes();
            break;
        default:
            PRINTF("Wrong value");
            break;
    }
}

/*
* Added functions
*
* Via main(), three different applications can be run using these functions.
*
* Functions here were implemented by me.
*/

/*
* Helper function that changes power mode of the device.
*
* Highly edited version of original function.
*/
void changeMode(app_power_mode_t targetPowerMode)
{
	smc_power_state_t curPowerState = SMC_GetPowerModeState(SMC);
    bool needSetWakeup; 
	if ((targetPowerMode > kAPP_PowerModeMin) && (targetPowerMode < kAPP_PowerModeMax))
       {
           if ((kAPP_PowerModeRun == targetPowerMode) || (kAPP_PowerModeVlpr == targetPowerMode)){
               needSetWakeup = false;
           }
           else{
               needSetWakeup = true;
           }
           if (needSetWakeup){
               APP_GetWakeupConfig(targetPowerMode);
           }
           APP_PowerPreSwitchHook(curPowerState, targetPowerMode);
           if (needSetWakeup){
               APP_SetWakeupConfig(targetPowerMode);
           }
           APP_PowerModeSwitch(curPowerState, targetPowerMode);
           APP_PowerPostSwitchHook(curPowerState, targetPowerMode);
           PRINTF("INFO\tPower mode cycle successfully ended\n");
       }
}


/*
* Function that complements ConfigTools and serves its part in initializing application.
* Mainly serves for initializing GPIO and interrupts.
*/
void app_init(void) {
		CLOCK_EnableClock(kCLOCK_PortE);
	    PORTC->PCR[1] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	    gpio_pin_config_t sw_config = {kGPIO_DigitalInput, 0};
	    GPIO_PinInit(GPIOC, 1U, &sw_config);

	    PORT_SetPinInterruptConfig(PORTC, 1U, kPORT_InterruptFallingEdge);
	    NVIC_ClearPendingIRQ(PORTB_PORTC_PORTD_PORTE_IRQn);
	    EnableIRQ(PORTB_PORTC_PORTD_PORTE_IRQn);

	    PORT_SetPinMux(PORTC, 4U, kPORT_MuxAsGpio);
	    GPIO_PinInit(GPIOC, 4U, &sw_config);
	    PORT_SetPinInterruptConfig(PORTC, 4U, kPORT_InterruptFallingEdge);

	    PORT_SetPinMux(PORTC, 5U, kPORT_MuxAsGpio);
	    GPIO_PinInit(GPIOC, 5U, &sw_config);
	    PORT_SetPinInterruptConfig(PORTC, 5U, kPORT_InterruptFallingEdge);

	    PORT_SetPinMux(PORTC, 6U, kPORT_MuxAsGpio);
	    GPIO_PinInit(GPIOC, 6U, &sw_config);
	    PORT_SetPinInterruptConfig(PORTC, 6U, kPORT_InterruptFallingEdge);
	    PRINTF("\r\n End of app_init\r\n");
}


/*
* Function for initializing timer. Was taken from different SDK example. 
*/
void tpm2_init()
{
	tpm_config_t tpmInfo;
	/* Board pin, clock, debug console init */
	BOARD_BootClockRUN();
	/* Select the clock source for the TPM counter as MCGPLLCLK */
	CLOCK_SetTpmClock(1U);
	/* Print a note to terminal */
	TPM_GetDefaultConfig(&tpmInfo);
	/* TPM clock divide  */
	tpmInfo.prescale = kTPM_Prescale_Divide_128;
	/* Initialize TPM module */
	TPM_Init(BOARD_TPM, &tpmInfo);
	// Set timer period
	TPM_SetTimerPeriod(BOARD_TPM, USEC_TO_COUNT(1000U, TPM_SOURCE_CLOCK));
	TPM_EnableInterrupts(BOARD_TPM, kTPM_TimeOverflowInterruptEnable);
	EnableIRQ(BOARD_TPM_IRQ_NUM);
	TPM_StartTimer(BOARD_TPM, kTPM_SystemClock);

}

/*
* First application implemented by this library. Function runs timer and waits.
* Periodically, timer triggers some action. Also, periodically, timer triggers transfer
* to Very low leakage stop 0 mode. After wakeup, timer should count from already reached number,
* not from zero. Context saving and restoring for this timer is necessary.
*/
void use_case1()
{
    PRINTF("\r\n Started execution of use case 1\r\n");
	tpm2_init();
	if (kRCM_SourceWakeup & RCM_GetPreviousResetSources(RCM)){ /* Wakeup from VLLS. */
      PRINTF("\r\n Wakeup from VLLS mode\r\n");
	  cl_init();
	  cl_load_peripheral(&tpm2_regs,frdm_register_file,NULL); // load TPM2 data
	}
	else{
	    PRINTF("\rWakeup from power on reset");
	    cl_clear_mem_area(frdm_register_file,NULL); // initialize backup area
	}

    while (true){
        if (tpmIsrFlag){ // interrupt from timer
            action_count++; // count to next action
            sleep_count++; // count to next sleep
            tpmIsrFlag = false;
            if (action_count >= 1000U){
                PRINTF("\r\n Timer triggers action here\r\n");
                action_count = 0U;
            }
            if (sleep_count >= 1500U){
                PRINTF("\r\n Timer triggers controler transfer into VLLS0");
                sleep_count = 0U;
                cl_save_peripheral(&tpm2_regs,frdm_register_file,NULL); // save TPM2 data
                changeMode(kAPP_PowerModeVlls0);
            }
        }
     __WFI();
    }
}

/*
* Second application implemented by this library. Application also runs on the timer, when timer triggers RGB led color change. Similarly to use
* case 1, timer also triggers sleep. This time, no RAM data are stored but the application instead directly saves and then restores GPIO registers
* using special function.
*/

void use_case2()
{
	PRINTF("\r\n Use case 2 started\r\n");
	char port_letter = 'C';
	tpm2_init();

    // initialize GPIO to 0s
    GPIO_PinWrite(GPIOC,6,0);
    GPIO_PinWrite(GPIOC,3,0);
    GPIO_PinWrite(GPIOC,5,0);


	uint32_t led_channels[] = {3,5,6};
	uint32_t led_index = 0;
	if (kRCM_SourceWakeup & RCM_GetPreviousResetSources(RCM)){ // wakeup from VLLS0
		   PRINTF("\r\nMCU wakeup from VLLS modes...\r\n");
		  cl_init();
		   cl_load_peripheral(&gpio_regs,frdm_register_file,(void *) &port_letter); // load saved values of output pins
	}
	else{ // wakeup from POR
	    PRINTF("\rMCU wakeup from power on reset\n");
	    cl_clear_mem_area(frdm_register_file,NULL); // initialize register file
	}
	while (true){
        if (tpmIsrFlag){ // TPM2 interrupt
            case2_led_ms++;
            case2_vlls_ms++;
            tpmIsrFlag = false;
            if (case2_led_ms >= 500U){ // toggle led
                PRINTF("\r\n Toggling LED module\r\n");
                GPIO_PortToggle(GPIOC,1 << (led_channels[led_index]));
                led_index = (led_index + 1) % 3;
                case2_led_ms = 0U;
            }
            if (case2_vlls_ms >= 1700U){ // put controller to sleep
                sleep_count = 0U;
                cl_save_peripheral(&gpio_regs,frdm_register_file,(void *) &port_letter);
                changeMode(kAPP_PowerModeVlls0);
            }
        }

    __WFI();
    }
}


/*
* Initialize I2C module for EEPROM
*/
void i2c_init(void)
{
    SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
    I2C0->F = I2C_F_ICR(0x14) | I2C_F_MULT(0);
    I2C0->C1 = I2C_C1_IICEN_MASK;
}

/*
* Initialize ADC module for reading data from potentiometer.
*/
void init_potentiometer(void) {
    CLOCK_EnableClock(kCLOCK_Adc0);
    adc16_config_t adc_config;
    ADC16_GetDefaultConfig(&adc_config);
    adc_config.resolution = kADC16_ResolutionSE12Bit;
    ADC16_Init(ADC0, &adc_config);
    CLOCK_EnableClock(kCLOCK_Adc0);
    EnableIRQ(ADC0_IRQn);
}

/*
* Read value from potentiometer, interrupt when finished.
*/
void read_pot_value(void) {
    adc16_channel_config_t channel_config;
    channel_config.channelNumber = 1U; 
    channel_config.enableInterruptOnConversionCompleted = true;
    channel_config.enableDifferentialConversion = false;
    ADC16_SetChannelConfig(ADC0, 0U, &channel_config);
}

/*
* Helper function for reading data given by user using buttons and potentiometer
*/
void print_3(void)
{
	PRINTF("\r\n Buttons: %d %d %d %d\r\n",buttons[0],buttons[1],buttons[2],buttons[3]);
	PRINTF("\r\n Potentiometer: %d %d %d %d %d \r\n",potent[0],potent[1],potent[2],potent[3],potent[4]);
	PRINTF("\r\n Current value: %d \r\n",cur_val);
}

void cur_val_inc(void)
{
	cur_val = (cur_val + 1) % 9;
}

/*
* Last application implemented in this file. Simulates complicated system with lot of user input that needs to be stored
* between application runs. Makes use of external EEPROM memory for context storage.
*/
void use_case3() {
	init_potentiometer();

	if (kRCM_SourceWakeup & RCM_GetPreviousResetSources(RCM)){ /* Wakeup from VLLS. */
		  PRINTF("\r\nMCU wakeup from VLLS modes...\r\n");
		  cl_init();
		  cl_load_mem_area(cl_metadata_ma,eeprom,NULL); // load L3 metadata
		  cl_load_mem_area(buttons_ma,eeprom,NULL); // load button data
		  cl_load_mem_area(potent_ma,eeprom,NULL); // load potentiometer data
	}
	else{
        PRINTF("\r\n NON-VLLS RESET: Initialize areas\r\n");
        cl_init();
		cl_clear_mem_area(frdm_register_file,NULL);
		cl_clear_mem_area(eeprom,NULL);
	}

	uint16_t last_printed_value = 0;

	while(true){
		if (hit){
			PRINTF("\r\n SW3 pressed: enter VLLS0\r\n");
			print_3();
            // save context
			cl_save_mem_area(buttons_ma,eeprom,NULL);
			cl_save_mem_area(potent_ma,eeprom,NULL);
			cl_save_mem_area(cl_metadata_ma,eeprom,NULL);
			changeMode(kAPP_PowerModeVlls0);
			hit = false;
		}
		if (button1_hit){
			if (cur_val < 5){
			    PRINTF("\r\n Button 1 pressed: increment in array\r\n");
				buttons[cur_val]++;
			}
			button1_hit = false;
		}
		if (button2_hit){
			if (cur_val < 5){
			    PRINTF("\r\n Button 2 pressed: decrement in array\r\n");
				buttons[cur_val]--;
			}
			button2_hit = false;
		}
		if (button3_hit){
			PRINTF("\r\n Button 3 pressed: increment cur_val\r\n");
			print_3();
			cur_val_inc();
			button3_hit = false;
		}
		read_pot_value(); // Trigger adc reading
		if (adc_conversion_done) {
			adc_conversion_done = false;
			if (abs((int)adc_value - (int)last_printed_value) > 100 && cur_val > 4) {
			      PRINTF("Potentiometer Value: %d\r\n", adc_value);
			      potent[cur_val - 4] = adc_value;
			      last_printed_value = adc_value;
			}
		}
		for(volatile int i=0; i<50000; i++);
	}
}

/*
* Initialize application and run one of three use cases.
* First part of initialization is taken from the original code.
*/
int main(void)
{
    BOARD_InitPins();
    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);
    if (kRCM_SourceWakeup & RCM_GetPreviousResetSources(RCM)){
        PMC_ClearPeriphIOIsolationFlag(PMC);
        NVIC_ClearPendingIRQ(LLWU_IRQn);
    }

    BOARD_InitBootClocks();
    APP_InitDefaultDebugConsole();
    BOARD_InitBootPeripherals();
    PRINTF("\rINFO\tApp successfully started\n");
    NVIC_EnableIRQ(APP_WAKEUP_BUTTON_IRQ);
    app_init();
    cl_init();
    // use_case1();
    // use_case2();
    // use_case3();
}

void BOARD_TPM_HANDLER(void)
{
    /* Clear interrupt flag.*/
    TPM_ClearStatusFlags(BOARD_TPM, kTPM_TimeOverflowFlag);
    tpmIsrFlag = true;
    __DSB();
}

