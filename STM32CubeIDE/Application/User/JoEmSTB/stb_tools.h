/*
 * stb_tools.h
 *
 *  Created on: Oct 23, 2025
 */

#ifndef APPLICATION_USER_JOEMSTB_STB_TOOLS_H_
#define APPLICATION_USER_JOEMSTB_STB_TOOLS_H_


#define LED_ON_TIME_RX 500	// BLUE
#define LED_ON_TIME_TX 500	// GREEN
#define LED_ON_TIME_SIG 500	// RED Signal Std.
#define LED_ON_TIME_SIGF 200	// RED Signal Kurz
#define LED_ON_TIME_SIGERR 2000 // ERROR
#define LED_ON_TIME_NET 1	// RED flash

extern uint32_t stb_now_runtime_sec;	// RunTimeCounter
extern bool stb_join_flag;

void joEmTriggerBlueLed(void);
void joEmTriggerGreenLed(void);
void joEmTriggerRedLedWd(uint32_t ms);
void joEmWatchdogService(void);

// Einmalig aufrufen, initialisiert Sequencers
void joEmSetup(void);


#endif /* APPLICATION_USER_JOEMSTB_STB_TOOLS_H_ */
