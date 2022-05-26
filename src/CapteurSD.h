#ifndef CAPTEUR_OS_CAPTEURSD_H
#define CAPTEUR_OS_CAPTEURSD_H

#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

//Affichage des informations de débogage dans la console
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
