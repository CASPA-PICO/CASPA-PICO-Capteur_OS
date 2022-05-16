#ifndef CAPTEUR_OS_CAPTEURSD_H
#define CAPTEUR_OS_CAPTEURSD_H

/*
 * Connect the SD card to the following pins:
 *
 * SD Card | ESP32
 *    D2       -
 *    D3       SS
 *    CMD      MOSI
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      SCK
 *    VSS      GND
 *    D0       MISO
 *    D1       -
 */
#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define DEBUG_SD

class CapteurSD {
public:
	CapteurSD();

	bool init();
	void end();
	bool dataAvailable();
	void startReadingFiles();
	File openNextFile();
private :
	File root;
};


#endif //CAPTEUR_OS_CAPTEURSD_H
