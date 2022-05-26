#ifndef CAPTEUR_OS_CAPTEURDATATRANSFERT_H
#define CAPTEUR_OS_CAPTEURDATATRANSFERT_H

#include "CapteurSD.h"
#include "PLTP.h"

//Pin de détection de la charge du capteur (lance le transfert en Bluetooth)
#define PIN_CHARGE_DETECT 25

//Affichage des informations de débogage dans la console
#define DEBUG_DATA_TRANSFERT

class CapteurDataTransfert {
public:
	CapteurDataTransfert();
	void transfertData();
private :
	CapteurSD capteurSd;
	PLTP pltp = PLTP(false);
};


#endif //CAPTEUR_OS_CAPTEURDATATRANSFERT_H
