/*
 * stb_tools.c
 *
 * Toolbox-Routinen fuer STM
 *
 *  Created on: Oct 23, 2025
 */

//Allg
#include "platform.h"
#include "sys_app.h"
#include "utilities_def.h"

#include "iwdg.h"
#include "stm32_seq.h"
#include "stm32_timer.h"

// Fuer hier
#include "device.h"
#include "stb_tools.h"

#define JOEM_PERIODIC_SEC	1	//

static UTIL_TIMER_Object_t joem_periodic_timer;
#ifdef LED_GREEN_Pin
static UTIL_TIMER_Object_t TxLedTimer;
#endif
#ifdef LED_BLUE_Pin
static UTIL_TIMER_Object_t RxLedTimer;
#endif
#ifdef LED_RED_Pin
static UTIL_TIMER_Object_t JoinedLedTimer;
#endif
uint32_t stb_now_runtime_sec = 0; // "stb_": STM-TolBox: Absolute Laufzeit in sec, Global

bool stb_join_flag = false; //
#ifdef LED_RED_Pin
static bool stb_red_running = false; //
#endif

// Timers
#ifdef LED_GREEN_Pin
static void OnTxTimerLedEvent(void *context) {
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET); /* LED_GREEN */
}
#endif

#ifdef LED_BLUE_Pin
static void OnRxTimerLedEvent(void *context) {
	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET); /* LED_BLUE */
}
#endif
#ifdef LED_RED_Pin
static void OnJoinTimerLedEvent(void *context) {
#ifdef PLED_RED // Sonderfall RAK
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET); /* nLED_RED */
#else
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET); /* LED_RED */
#endif
	stb_red_running = false; //
}
#endif
// Task, der aufgerufen werden kann und schafft
static void joEmPeriodicTask(void) {
	// Joined: Alle 4 Sekunden 1* Blitzen
	// Unjoined: Jede Sekunde Blitzen
	if ((!(stb_now_runtime_sec & 3)) || (stb_join_flag == false)) {
		joEmTriggerRedLedWd(LED_ON_TIME_NET);
	}

}
// Der IRQ, der nicht lange brauchen darf. Er triggert nur den Task an und zaehlt RUNTIME
static void joEmPeriodicTimerCb(void *arg) {
	stb_now_runtime_sec += JOEM_PERIODIC_SEC;
	UTIL_SEQ_SetTask((1 << CFG_SEQ_Task_JoEmPeriodic), CFG_SEQ_Prio_0);
}

//--------- Externs-------------

// LED Flashs
void joEmTriggerBlueLed(void) {
#ifdef LED_BLUE_Pin
	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET); /* LED_BLUE */
	UTIL_TIMER_Start(&RxLedTimer);
#else
	// Wenn nur 1 LED da ist, diese einfach nur kurz
	joEmTriggerRedLedWd(LED_ON_TIME_RX);
#endif
}
void joEmTriggerGreenLed(void) {
#ifdef LED_GREEN_Pin
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET); /* LED_GREEN */
	UTIL_TIMER_Start(&TxLedTimer);
#else
	// Wenn nur 1 LED da ist, diese einfach nur kurz
	joEmTriggerRedLedWd(LED_ON_TIME_TX);
#endif
}
void joEmTriggerRedLedWd(uint32_t redPeriodMs) {	// With Watchdog
#if !defined(DEBUG)
	HAL_IWDG_Refresh(&hiwdg);
#endif
#ifdef LED_RED_Pin
	if (stb_red_running)
		return;
	stb_red_running = true;
#ifdef PLED_RED
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET); /* nLED_RED */
#else
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET); /* LED_RED */
#endif
	UTIL_TIMER_SetPeriod(&JoinedLedTimer, redPeriodMs);
	UTIL_TIMER_Start(&JoinedLedTimer);
#endif
}
// WD Timeout: 32 sec
void joEmWatchdogService(void) { // Only Watchdog
#if !defined(DEBUG)
	HAL_IWDG_Refresh(&hiwdg);
#endif
}

void joEmSetup(void) {
#ifdef LED_GREEN_Pin
	UTIL_TIMER_Create(&TxLedTimer, LED_ON_TIME_RX, UTIL_TIMER_ONESHOT,
			OnTxTimerLedEvent, NULL);
#endif
#ifdef LED_BLUE_Pin
	UTIL_TIMER_Create(&RxLedTimer, LED_ON_TIME_RX, UTIL_TIMER_ONESHOT,
			OnRxTimerLedEvent, NULL);
#endif
#ifdef LED_RED_Pin
	UTIL_TIMER_Create(&JoinedLedTimer, LED_ON_TIME_NET, UTIL_TIMER_ONESHOT,
			OnJoinTimerLedEvent, NULL);
#endif
	// Sequencer-Task registrieren: CFG_SEQ_Task_JoEmPeriodic in utilities_def.h
	UTIL_SEQ_RegTask((1 << CFG_SEQ_Task_JoEmPeriodic), UTIL_SEQ_RFU,
			joEmPeriodicTask);
	// Timer erzeugen & starten (periodisch)
	UTIL_TIMER_Create(&joem_periodic_timer, (JOEM_PERIODIC_SEC * 1000),
			UTIL_TIMER_PERIODIC, joEmPeriodicTimerCb, NULL);
	UTIL_TIMER_Start(&joem_periodic_timer);

	APP_PRINTF(
			"\r\n--- "DEVICE_NAME" V%u.%u Type:%u ("__DATE__ " " __TIME__") "COPYRIGHT" ---\r\n",
			DEVICE_FIRMWARE/10, DEVICE_FIRMWARE%10, DEVICE_TYP);
#ifdef DEBUG
	APP_PRINTF("*** DEBUG DEB.ENA.:%d ***\r\n", (uint8_t)DEBUGGER_ENABLED);
#else
	#if DEBUGGER_ENABLED
	APP_PRINTF("*** !!!RELEASE!!! with DEBUGGER ENABLED ***\r\n");
	#endif
#endif
	// Und PeriodicTimer initial starten
	joEmPeriodicTimerCb(NULL);

}

