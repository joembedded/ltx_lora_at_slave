/*
 * Device.h
 *
 *  Created on: Oct 23, 2025
 *      Author: jwick
 */

#ifndef APPLICATION_USER_JOEMSTB_DEVICE_H_
#define APPLICATION_USER_JOEMSTB_DEVICE_H_

// Struktur: 8000 ist LoRaWAN
// Ab 8100 Geraet, darunter Test-Equipment
#define COPYRIGHT "(C)JoEmbedded.de"

//#define DEVICE_TYP 8000	// 8000: Nucleo-Testboard - Hierauf wird Basis-SW entwickelt und .IOC-Daten
#define DEVICE_TYP 8001	// 8001: RAK3172LP-SIP-Testboard


#if DEVICE_TYP == 8000
	#define DEVICE_NAME  "EVK-Nucleo-WL55JC1"

	//Workaround fuer Praeprozessor Port A=100, B:200, C:300 plus NR.
	//Name LED_xxx schon vergeben... Dxx: Led gg. GND
	//#define DLED_RED		211 // PB11
	//#define DLED_GREEN	209 // PB9
	//#define DLED_BLUE		215 // PB15

	#define DEVICE_FIRMWARE	1

#endif
#if DEVICE_TYP == 8001
	#define DEVICE_NAME  "RAK3172LP-SIP-WLE5"
	// Das RAK3172LP_SIP ist baugleich mit ST50HE
	#define RAK3172LP_SIP

	// Wie oben, Pxx: LED gg. plus - am RAK-Modul nur 1 LED und gg. VCC
	#define PLED_RED		104 // PA4


	#define DEVICE_FIRMWARE	1
#endif

#endif /* APPLICATION_USER_JOEMSTB_DEVICE_H_ */
