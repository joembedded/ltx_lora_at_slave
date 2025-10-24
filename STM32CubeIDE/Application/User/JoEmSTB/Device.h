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

#define DEVICE_TYP 8000	// 8000: Nucleo-Testboard

#if DEVICE_TYP == 8000
	#define DEVICE_NAME  "EVK-Nucleo-WL55JC1"
	#define DEVICE_FIRMWARE	1
#endif

#endif /* APPLICATION_USER_JOEMSTB_DEVICE_H_ */
